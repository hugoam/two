#pragma once

#include <stl/vector.h>
#include <stl/memory.h>
#include <jobs/Forward.h>

#include <cassert>
#include <cstddef>
#include <cstdint>

// Size is chosen so that we can store at least std::function<> and a job size is a multiple of a cacheline.
#define JOB_PADDING (6+8)

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
	using JobStorage = void*[JOB_PADDING];

	export_ class refl_ nocopy_ MUD_JOBS_EXPORT JobSystem
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

		template <typename T>
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
