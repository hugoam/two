#include <stl/vector.hpp>
#include <stl/span.h>
#include <stl/math.h>
#include <stl/algorithm.h>
#include <infra/AlignedAlloc.h>
#include <infra/Arena.h>
#include <infra/Thread.h>
#include <jobs/JobSystem.h>
#include <jobs/JobQueue.h>
#include <jobs/Job.h>

#include <cassert>
#include <cmath>
#include <random>

#include <atomic>
#include <thread>

#include <condition_variable>
#include <mutex>

#ifndef MUD_PLATFORM_EMSCRIPTEN
#include <immintrin.h>
#endif

#include <Tracy.hpp>

#define __i386__

#if defined __i386__ || defined __x86_64__
#   define HAS_HYPER_THREADING 0      // on x86 we assume we have hyper-threading.
#else
#   define HAS_HYPER_THREADING 0
#endif

#if defined __EMSCRIPTEN__
#   define HAS_THREADING 0
#else
#   define HAS_THREADING 1
#endif

#ifdef __ARM_ACLE
#   include <arm_acle.h>
#   define WAIT_FOR_EVENT()       __wfe()
#elif defined __EMSCRIPTEN__
#   define WAIT_FOR_EVENT()
#else
#   if defined __i386__ || defined __x86_64__
#       define WAIT_FOR_EVENT()       _mm_pause();
#   else
#       define WAIT_FOR_EVENT()
#   endif
#endif

namespace mud
{
	thread_local JobSystem::ThreadState* s_thread_state(nullptr);

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

	struct alignas(CACHELINE_SIZE) JobSystem::ThreadState  // this causes 40-bytes padding // make sure storage is cache-line aligned
	{
		WorkQueue<MAX_JOB_COUNT> work_queue;

		// these are not accessed by the worker threads
		alignas(CACHELINE_SIZE) JobSystem* js;    // this causes 56-bytes padding
		std::thread thread;
		uint32_t index;
		uint32_t mask;
	};

	static_assert((sizeof(Job) % CACHELINE_SIZE == 0) || (CACHELINE_SIZE % sizeof(Job) == 0),
				  "A Job must be N cache-lines long or N Jobs must fit in a cache line exactly.");

	struct JobSystem::Impl
	{
	public:
		Impl()
			: m_job_pool("JobSystem Job pool", MAX_JOB_COUNT * sizeof(Job))
			, m_jobs(static_cast<Job*>(m_job_pool.current()))
		{
			UNUSED(padding);
		}

		void init(JobSystem& js, uint16_t num_threads, uint16_t adoptable_threads)
		{
			m_thread_states = aligned_vector<ThreadState>(num_threads + adoptable_threads);

			printf("INFO: job system running on %i worker threads\n", int(num_threads));

			for(size_t i = 0, n = m_thread_states.size(); i < n; i++)
			{
				ThreadState& state = m_thread_states[i];
				state.work_queue.m_jobs = m_jobs;
				state.index = uint32_t(i);
				state.mask = uint32_t(1UL << i);
				state.js = &js;
				if(i < size_t(num_threads))
				{
					state.thread = std::thread(&JobSystem::loop, &js, &state);
				}
			}
		}

		static_assert(sizeof(ThreadState) % CACHELINE_SIZE == 0, "ThreadState doesn't align to a cache line");

	public:
		// these have thread contention, keep them together
		std::mutex m_lock;
		std::condition_variable m_condition;
		std::atomic<uint32_t> m_active_jobs = { 0 };
		Arena<Job, AtomicFreeList> m_job_pool;

#ifndef USE_STL
		template <class T>
		using aligned_vector = vector<T, TinystlAlignedAllocator<T>>;
#else
		template <class T>
		using aligned_vector = vector<T, STLAlignedAllocator<T>>;
#endif

		// these are essentially const, make sure they're on a different cache-lines than the read-write atomics.
		// We can't use "alignas(CACHELINE_SIZE)" because the standard allocator can't make this guarantee.
		char padding[CACHELINE_SIZE];

		alignas(16) // at least we align to half (or quarter) cache-line
			aligned_vector<ThreadState> m_thread_states;      // actual data is stored offline
		std::atomic<bool> m_exit_requested = { 0 };           // this one is almost never written
		std::atomic<uint16_t> m_adopted_threads = { 0 };      // this one is almost never written
		Job* const m_jobs;									  // base for conversion to indices
	};

	JobSystem::JobSystem(uint16_t num_threads, uint16_t adoptable_threads)
		: m_impl(construct<Impl>())
	{
		if(num_threads == 0)
		{
			uint32_t hardware_threads = std::thread::hardware_concurrency();
			if(HAS_HYPER_THREADING)
				num_threads = uint16_t(hardware_threads / 2 - 1);
			else
				num_threads = uint16_t(hardware_threads - 1);
		}
		num_threads = min(uint16_t(HAS_THREADING ? 32 : 0), num_threads);

		m_thread_count = num_threads;
		m_parallel_split_count = (uint8_t)ceil(log2f(float(num_threads + adoptable_threads)));

		m_impl->init(*this, num_threads, adoptable_threads);
	}

	JobSystem::~JobSystem()
	{
		this->shutdown();

		for(ThreadState& state : m_impl->m_thread_states)
		{
			if(state.thread.joinable())
				state.thread.join();
		}
	}

	JobSystem* JobSystem::instance()
	{
		ThreadState* const state = s_thread_state;
		return state ? state->js : nullptr;
	}

	void JobSystem::shutdown()
	{
		m_impl->m_exit_requested.store(true, std::memory_order_relaxed);
		m_impl->m_condition.notify_all();
	}

	uint32_t JobSystem::thread()
	{
		return s_thread_state->index;
	}

	inline bool JobSystem::exiting() const
	{
		return m_impl->m_exit_requested.load(std::memory_order_relaxed);
	}

	inline bool JobSystem::completed(Job const* job)
	{
		return job->running_jobs.load(std::memory_order_relaxed) <= 0;
		//return job->running_jobs.load(std::memory_order_acquire) <= 0;
	}

	inline JobSystem::ThreadState& JobSystem::state()
	{
		assert(s_thread_state);
		return *s_thread_state;
	}

	static inline uint32_t random_index(uint16_t range)
	{
		thread_local std::default_random_engine generator(std::random_device{}());
		return generator() % range;
	}

	inline JobSystem::ThreadState& JobSystem::random_thread_state()
	{
		uint16_t adopted = m_impl->m_adopted_threads.load(std::memory_order_relaxed);
		uint32_t index = random_index(m_thread_count + adopted);
		assert(index < m_impl->m_thread_states.size());
		return m_impl->m_thread_states[index];
	}

	bool JobSystem::execute(ThreadState& state)
	{
		Job* job = state.work_queue.pop();
		if(job == nullptr)
		{
			ThreadState& steal_target = random_thread_state();
			if(&steal_target != &state)
				job = steal_target.work_queue.steal();
		}

		if(job)
		{
			uint32_t active_jobs = m_impl->m_active_jobs.fetch_sub(1, std::memory_order_acq_rel);
			assert(active_jobs);
			UNUSED(active_jobs);

			if(job->function) //[[likely]]
			{
				ZoneScopedN("job");
				job->function(job->storage, *this, job);
			}

			finish(job);
		}
		return job != nullptr;
	}

	void JobSystem::loop(ThreadState* thread_state)
	{
		set_thread_name("JobSystem::loop");
		set_thread_priority(ThreadPriority::Display);
		set_thread_affinity(1 << (thread_state->index + 1));

		s_thread_state = thread_state;

		do {
			if(!execute(*thread_state))
			{
				std::unique_lock<std::mutex> lock(m_impl->m_lock);
				while(!exiting() && !(m_impl->m_active_jobs.load(std::memory_order_relaxed)))
					m_impl->m_condition.wait(lock);
			}
		} while(!exiting());
	}
	
	Job* JobSystem::create(Job* parent, JobFunc func)
	{
		parent = (parent == nullptr) ? m_master_job : parent;
		Job* const job = m_impl->m_job_pool.make();
		if(job) //[[likely]]
		{
			//printf("%i jobs\n", int(job - m_jobs));
			size_t index = 0x7FFF;
			if(parent)
			{
				assert(parent->running_jobs.load(std::memory_order_relaxed) > 0);

				parent->running_jobs.fetch_add(1, std::memory_order_relaxed);
				index = parent - m_impl->m_jobs;
				assert(index < MAX_JOB_COUNT);
			}
			job->function = func;
			job->parent = uint16_t(index);
			job->running_jobs.store(1, std::memory_order_relaxed);
		}
		else
		{
			//printf("no jobs\n");
		}
		return job;
	}

	void JobSystem::finish(Job* job)
	{
		auto& job_pool = m_impl->m_job_pool;
		Job* const storage = m_impl->m_jobs;
		do {
			int32_t running_jobs = job->running_jobs.fetch_sub(1, std::memory_order_release) - 1;
			assert(running_jobs >= 0);
			if(running_jobs > 0)
			{
				break;
			}
			else
			{
				Job* const parent = job->parent == 0x7FFF ? nullptr : &storage[job->parent];
				job_pool.destroy(job);
				job = parent;
			}
		} while(job);
	}

	void JobSystem::run(Job* job, uint32_t flags)
	{
		ThreadState& state = this->state();

		uint32_t active_jobs = m_impl->m_active_jobs.fetch_add(1, std::memory_order_relaxed);
		state.work_queue.push(job);

		if(!(flags & DONT_SIGNAL))
		{
			if(active_jobs)
			{
				{ std::lock_guard<std::mutex> lock(m_impl->m_lock); }
				m_impl->m_condition.notify_one();
			}
		}
	}

	void JobSystem::wait(Job const* job)
	{
		assert(job);
		ThreadState& state = this->state();
		do {
			if(!execute(state))
				WAIT_FOR_EVENT();
		} while(!completed(job) && !exiting());

		std::atomic_thread_fence(std::memory_order_acquire);
	}

	void JobSystem::adopt()
	{
		ThreadState* const state = s_thread_state;
		if(state)
			return;

		uint16_t adopted = m_impl->m_adopted_threads.fetch_add(1, std::memory_order_relaxed);
		size_t index = m_thread_count + adopted;

		set_thread_priority(ThreadPriority::Display);

		s_thread_state = &m_impl->m_thread_states[index];
	}

	void JobSystem::emancipate()
	{
		ThreadState* const state = s_thread_state;
		UNUSED(state);
		s_thread_state = nullptr;
	}
}
