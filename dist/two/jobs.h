#pragma once

#include <two/infra.h>
#include <two/type.h>


#include <stl/vector.h>
#include <stl/memory.h>



#ifndef TWO_JOBS_EXPORT
#define TWO_JOBS_EXPORT TWO_IMPORT
#endif

namespace two
{
	class JobSystem;
}

#include <cassert>
#include <stl/stddef.h>
#include <stdint.h>

// Size is chosen so that we can store at least std::function<> and a job size is a multiple of a cacheline.
#define JOB_PADDING (6+8)

namespace two
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
	using JobStorage = void*[JOB_PADDING];

	export_ class refl_ nocopy_ TWO_JOBS_EXPORT JobSystem
	{
		static constexpr size_t MAX_JOB_COUNT = 4096;
		static_assert(MAX_JOB_COUNT <= 0x7FFE, "MAX_JOB_COUNT must be <= 0x7FFE");

	public:
		explicit JobSystem(uint16_t num_threads = 0, uint16_t adoptable_threads = 1);

		~JobSystem();

		void adopt();
		void emancipate();

		static JobSystem* instance();

		uint32_t thread();

		enum runFlags { DONT_SIGNAL = 0x1 };

		Job* create(Job* parent, JobFunc func);
		void run(Job* job, uint32_t flags = 0);
		void wait(Job const* job);

		void complete(Job* job)
		{
			run(job);
			wait(job);
		}

		void finish(Job* job);

		Job* job(Job* parent = nullptr) { return this->create(parent, nullptr); }

		template <class T>
		Job* job(Job* parent, T functor);

		struct ThreadState;

	private:
		static ThreadState& state();

		ThreadState& random_thread_state();
		bool completed(Job const* job);

		void shutdown();
		bool exiting() const;

		void loop(ThreadState* state);
		bool execute(ThreadState& state);

		struct Impl;
		unique<Impl> m_impl;

	public:
		uint16_t m_thread_count = 0;            // total # of threads in the pool
		uint8_t m_parallel_split_count = 0;     // # of split allowable in parallel_for
	private:
		Job* m_master_job = nullptr;
	};
}
//#include <jobs/Job.h>
//#include <jobs/JobLoop.h>

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif



namespace two
{
    // Exported types
    
    
    export_ template <> TWO_JOBS_EXPORT Type& type<two::JobSystem>();
}

#include <stl/move.h>
#include <stl/new.h>

#include <atomic>

namespace two
{
	struct alignas(CACHELINE_SIZE)Job
	{
		Job() {}
		Job(const Job&) = delete;
		Job(Job&&) = delete;

		JobFunc function;
		uint16_t parent;
		std::atomic<uint16_t> running_jobs = { 0 };
		JobStorage storage; // on 64-bits systems, there is an extra 32-bits lost here
	};

	template <class T>
	Job* JobSystem::job(Job* parent, T functor)
	{
		static_assert(sizeof(functor) <= sizeof(JobStorage), "functor too large");
		auto call = [](void* user, JobSystem& js, Job* job)
		{
			T& func = *static_cast<T*>(user);
			func(js, job);
			func.~T();
		};
		Job* job = this->create(parent, call);
		if(job)
			new(stl::placeholder(), job->storage) T(move(functor));
		return job;
	}
}

#include <stl/span.h>

namespace two
{
	namespace details
	{
		template <class Splitter, class Functor>
		struct ParallelJob
		{
			using Jobs = ParallelJob;

			ParallelJob(uint32_t start, uint32_t count, uint8_t splits, Functor functor, const Splitter& splitter)
				: m_start(start), m_count(count)
				, m_functor(move(functor))
				, m_splits(splits)
				, m_splitter(splitter)
			{}

			void operator()(JobSystem& js, Job* parent)
			{
				this->run(js, parent);
			}

			void run(JobSystem& js, Job* parent)
			{
				if(m_splits == js.m_parallel_split_count)
				{
					parallel(js, parent, m_start, m_count, m_splits);
					return;
				}

				if(m_splitter.split(m_splits, m_count))
				{
					const uint32_t lc = m_count / 2;
					Jobs ld(m_start, lc, m_splits + uint8_t(1), m_functor, m_splitter);
					Job* left = js.job(parent, ld);

					js.run(left);

					const uint32_t rc = m_count - lc;
					Jobs rd(m_start + lc, rc, m_splits + uint8_t(1), m_functor, m_splitter);
					Job* right = js.job(parent, rd);

					js.run(right, JobSystem::DONT_SIGNAL);
				}
				else
				{
					m_functor(js, parent, m_start, m_count);
				}
			}

			void parallel(JobSystem& js, Job* parent, uint32_t start, uint32_t count, uint8_t splits)
			{
				//auto round_to = [](uint32_t number, uint32_t divisor) { return number - number % divisor + divisor * !!(number % divisor); };
				if(m_splitter.split(splits, count))
				{
					//const uint32_t left = round_to(count / 2, 64);
					const uint32_t left = count / 2;
					parallel(js, parent, start, left, splits);
					parallel(js, parent, start + left, count - left, splits + 1);
				}
				else
				{
					Job* job = js.job(parent, [f = m_functor, start, count](JobSystem& js, Job* job) {
						f(js, job, start, count);
					});
					if(job)
						js.run(job);
					else
						m_functor(js, parent, start, count);
				}
			}

			uint32_t m_start;             // 4
			uint32_t m_count;             // 4
			Functor m_functor;            // ?
			uint8_t m_splits;             // 1
			Splitter m_splitter;          // 1
		};

	}

	template <class S, class F>
	Job* split_jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor, const S& splitter)
	{
		using Jobs = details::ParallelJob<S, F>;
		Jobs jobs(start, count, 0, move(functor), splitter);
		return js.job(parent, jobs);
	}

	template <class T, class S, class F>
	Job* split_jobs(JobSystem& js, Job* parent, T* data, uint32_t count, F functor, const S& splitter)
	{
		auto user = [data, f = move(functor)](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			UNUSED(js); UNUSED(job);
			f(data + start, count);
		};
		using Jobs = details::ParallelJob<S, decltype(user)>;
		Jobs jobs(0, count, 0, move(user), splitter);
		return js.job(parent, jobs);
	}

	template <class T, class S, class F>
	Job* split_jobs(JobSystem& js, Job* parent, span<T> slice, F functor, const S& splitter)
	{
		return split_jobs(js, parent, slice.data(), slice.size(), functor, splitter);
	}

	template <uint32_t Count, uint32_t MaxSplits = 12>
	class CountSplitter
	{
	public:
		bool split(uint32_t splits, uint32_t count) const { return (splits < MaxSplits && count >= Count * 2); }
	};

	template <uint32_t Count, class F>
	Job* split_jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor)
	{
		return split_jobs(js, parent, start, count, functor, CountSplitter<Count>());
	}

	template <uint32_t Count, class T, class F>
	Job* split_jobs(JobSystem& js, Job* parent, span<T> slice, F functor)
	{
		return split_jobs(js, parent, slice.data(), slice.size(), functor, CountSplitter<Count>());
	}

	template <uint32_t Count, class F>
	Job* parallel_jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor)
	{
		auto user = [f = move(functor)](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			for(uint32_t i = start; i < start + count; ++i)
				f(js, job, i);
		};
		using Jobs = details::ParallelJob<CountSplitter<Count>, decltype(user)>;
		Jobs jobs(start, count, 0, move(user), CountSplitter<Count>());
		return js.job<Jobs>(parent, jobs);
	}

	template <uint32_t Count, class T_Source, class T_Dest>
	void parallel_copy(JobSystem& js, Job* parent, T_Source& source, T_Dest& dest, uint32_t count)
	{
		auto copy = [&source, &dest](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			UNUSED(js); UNUSED(job);
			for(uint32_t i = start; i < start + count; ++i)
				dest[i] = source[i];
		};

		Job* job = split_jobs<Count>(js, parent, 0, count, copy);
		js.complete(job);
	}

	template <uint32_t Count, class T_Value, class T_Dest>
	void parallel_set(JobSystem& js, Job* parent, T_Value value, T_Dest& dest, uint32_t count)
	{
		auto copy = [value, &dest](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			UNUSED(js); UNUSED(job);
			for(uint32_t i = start; i < start + count; ++i)
				dest[i] = value;
		};

		Job* job = split_jobs<Count>(js, parent, 0, count, copy);
		js.complete(job);
	}
}


#include <atomic>

#include <stl/stddef.h>
#include <cassert>

namespace two
{
	template <class T, size_t Count>
	class StealQueue
	{
		static_assert(!(Count & (Count - 1)), "Count must be a power of two");
		static constexpr size_t Mask = Count - 1;
		std::atomic<int32_t> m_top = { 0 };      // written/read in pop()/steal()
		std::atomic<int32_t> m_bottom = { 0 };   // written only in pop(), read in push(), steal()
		T m_items[Count];

		T at(int32_t index) { return m_items[index & Mask]; }
		void set(int32_t index, T item) { m_items[index & Mask] = item; }

	public:
		using value_type = T;

		inline void push(T item);
		inline T pop();
		inline T steal();

		size_t size() const { return Count; }

		bool empty() const
		{
			uint32_t bottom = (uint32_t)m_bottom.load(std::memory_order_relaxed);
			uint32_t top = (uint32_t)m_top.load(std::memory_order_seq_cst);
			return top >= bottom;
		}

		int32_t count() const
		{
			int32_t bottom = m_bottom.load(std::memory_order_relaxed);
			int32_t top = m_top.load(std::memory_order_relaxed);
			return bottom - top;
		}
	};


	template <class T, size_t Count>
	void StealQueue<T, Count>::push(T item)
	{
		int32_t bottom = m_bottom.load(std::memory_order_relaxed);
		set(bottom, item);
		m_bottom.store(bottom + 1, std::memory_order_release);
	}

	template <class T, size_t Count>
	T StealQueue<T, Count>::pop()
	{
		int32_t bottom = m_bottom.fetch_sub(1, std::memory_order_relaxed) - 1;
		int32_t top = m_top.load(std::memory_order_seq_cst);

		if(top < bottom)
		{
			return at(bottom);
		}

		T item{};
		if(top == bottom)
		{
			item = at(bottom);

			if(m_top.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst, std::memory_order_relaxed))
			{
				top++;
			}
			else
			{
				item = T();
			}
		}

		m_bottom.store(top, std::memory_order_relaxed);
		return item;
	}

	template <class T, size_t Count>
	T StealQueue<T, Count>::steal()
	{
		do {
			int32_t top = m_top.load(std::memory_order_seq_cst);
			int32_t bottom = m_bottom.load(std::memory_order_acquire);

			if(top >= bottom)
			{
				return T();
			}

			T item(at(top));
			if(m_top.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst, std::memory_order_relaxed))
			{
				return item;
			}
		} while(true);
	}
}
