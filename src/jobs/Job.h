#pragma once

#include <infra/Array.h>
#include <infra/Pool.h>
#include <infra/Vector.h>
#include <infra/Thread.h>
#include <jobs/JobQueue.h>

#include <cassert>
#include <cstddef>

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include <condition_variable>
#include <mutex>

#ifdef WIN32
// Size is chosen so that we can store at least std::function<> and a job size is a multiple of a
// cacheline.
#    define JOB_PADDING (6+8)
#else
#    define JOB_PADDING (6)
#endif

namespace mud
{
#ifdef __ARM_32BIT_STATE
	// on ARM 32-bits, assume 32-bytes cache lines
	constexpr size_t CACHELINE_SIZE = 32;
#else
	// on ARM64 and x86 we assume 64-bytes cache lines
	constexpr size_t CACHELINE_SIZE = 64;
#endif

	struct Job;
	class JobSystem;

	using JobFunc = void(*)(void*, JobSystem&, Job*);

	struct alignas(CACHELINE_SIZE)Job
	{
		Job() {}
		Job(const Job&) = delete;
		Job(Job&&) = delete;

		JobFunc function;
		uint16_t parent;
		std::atomic<uint16_t> running_jobs = { 0 };
		void* padding[JOB_PADDING]; // on 64-bits systems, there is an extra 32-bits lost here
	};

	template <size_t Count>
	class WorkQueue
	{
	public:
		WorkQueue() {}
		WorkQueue(Job* jobs) : m_jobs(jobs) {}

		Job* m_jobs = nullptr;
		StealQueue<uint16_t, Count> m_queue;

		inline void push(Job* job)
		{
			size_t index = job - m_jobs;
			assert(index >= 0 && index < Count);
			m_queue.push(uint16_t(index + 1));
		}

		inline Job* pop()
		{
			size_t index = m_queue.pop();
			assert(index <= Count);
			return !index ? nullptr : (m_jobs - 1) + index;
		}

		inline Job* steal()
		{
			size_t index = m_queue.steal();
			assert(index <= Count);
			return !index ? nullptr : (m_jobs - 1) + index;
		}
	};

	class MUD_INFRA_EXPORT JobSystem
	{
		static constexpr size_t MAX_JOB_COUNT = 4096;
		static_assert(MAX_JOB_COUNT <= 0x7FFE, "MAX_JOB_COUNT must be <= 0x7FFE");

	public:
		static_assert((sizeof(Job) % CACHELINE_SIZE == 0) || (CACHELINE_SIZE % sizeof(Job) == 0),
					  "A Job must be N cache-lines long or N Jobs must fit in a cache line exactly.");

		explicit JobSystem(uint16_t num_threads = 0, uint16_t adoptable_threads = 1);

		~JobSystem();

		void adopt();
		void emancipate();

		static JobSystem* instance();

		uint32_t thread();

		Job* job(Job* parent = nullptr) { return create(parent, nullptr); }

		template <typename T, void(T::*method)(JobSystem&, Job*)>
		Job* job(Job* parent, T* data)
		{
			struct stub
			{
				static void call(void* user, JobSystem& js, Job* job) { (*static_cast<T**>(user)->*method)(js, job); }
			};
			Job* job = create(parent, &stub::call);
			if(job)
				job->padding[0] = data;
			return job;
		}

		template <typename T, void(T::*method)(JobSystem&, Job*)>
		Job* job(Job* parent, T data)
		{
			static_assert(sizeof(data) <= sizeof(Job::padding), "user data too large");
			struct stub
			{
				static void call(void* user, JobSystem& js, Job* job)
				{
					T* that = static_cast<T*>(user);
					(that->*method)(js, job);
					that->~T();
				}
			};
			Job* job = create(parent, &stub::call);
			if(job)
				new(job->padding) T(std::move(data));
			return job;
		}

		template <typename T>
		Job* job(Job* parent, T functor)
		{
			static_assert(sizeof(functor) <= sizeof(Job::padding), "functor too large");
			struct stub
			{
				static void call(void* user, JobSystem& js, Job* job)
				{
					T& that = *static_cast<T*>(user);
					that(js, job);
					that.~T();
				}
			};
			Job* job = create(parent, &stub::call);
			if(job)
				new(job->padding) T(std::move(functor));
			return job;
		}

		enum runFlags { DONT_SIGNAL = 0x1 };
		void run(Job* job, uint32_t flags = 0);
		void wait(Job const* job);

		void complete(Job* job)
		{
			run(job);
			wait(job);
		}

		void finish(Job* job);
		
	public:
		struct alignas(CACHELINE_SIZE) ThreadState  // this causes 40-bytes padding // make sure storage is cache-line aligned
		{   			   
			WorkQueue<MAX_JOB_COUNT> work_queue;

			// these are not accessed by the worker threads
			alignas(CACHELINE_SIZE) JobSystem* js;    // this causes 56-bytes padding
			std::thread thread;
			uint32_t index;
			uint32_t mask;
		};

	private:
		static_assert(sizeof(ThreadState) % CACHELINE_SIZE == 0, "ThreadState doesn't align to a cache line");

		static ThreadState& state();

		Job* create(Job* parent, JobFunc func);
		ThreadState& random_thread_state();
		bool completed(Job const* job);

		void shutdown();
		bool exiting() const;

		void loop(ThreadState* state);
		bool execute(ThreadState& state);

		// these have thread contention, keep them together
		std::mutex m_lock;
		std::condition_variable m_condition;
		std::atomic<uint32_t> m_active_jobs = { 0 };
		Arena<Job, AtomicFreeList> m_job_pool;

		template <typename T>
		using aligned_vector = std::vector<T, STLAlignedAllocator<T>>;

		// these are essentially const, make sure they're on a different cache-lines than the read-write atomics.
		// We can't use "alignas(CACHELINE_SIZE)" because the standard allocator can't make this guarantee.
		char padding[CACHELINE_SIZE];

		alignas(16) // at least we align to half (or quarter) cache-line
			aligned_vector<ThreadState> m_thread_states;          // actual data is stored offline
		std::atomic<bool> m_exit_requested = { 0 };           // this one is almost never written
		std::atomic<uint16_t> m_adopted_threads = { 0 };      // this one is almost never written
		Job* const m_jobs;									  // base for conversion to indices
	public:
		uint16_t m_thread_count = 0;                          // total # of threads in the pool
		uint8_t m_parallel_split_count = 0;                    // # of split allowable in parallel_for
	private:
		Job* m_master_job = nullptr;
	};

	template <typename Function, typename ... Args>
	Job* job(JobSystem& js, Job* parent, Function&& func, Args&&... args)
	{
		struct Data
		{
			std::function<void()> f;
			void gob(JobSystem&, Job*) { f(); }
		} user{ std::bind(std::forward<Function>(func), std::forward<Args>(args)...) };
		return js.job<Data, &Data::gob>(parent, std::move(user));
	}

	template <typename Function, typename T, typename ... Args, typename = typename std::enable_if<std::is_member_function_pointer<typename std::remove_reference<Function>::type>::value>::type>
	Job* job(JobSystem& js, Job* parent, Function&& func, T&& o, Args&&... args)
	{
		struct Data
		{
			std::function<void()> f;
			void gob(JobSystem&, Job*) { f(); }
		} user { std::bind(std::forward<Function>(func), std::forward<T>(o), std::forward<Args>(args)...) };
		return js.job<Data, &Data::gob>(parent, std::move(user));
	}
}
