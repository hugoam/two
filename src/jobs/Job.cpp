#include <infra/Config.h>
#include <jobs/Job.h>

#include <cassert>
#include <cmath>
#include <random>
#include <algorithm>

#include <immintrin.h>

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

	JobSystem::JobSystem(uint16_t num_threads, uint16_t adoptable_threads)
		: m_job_pool("JobSystem Job pool", MAX_JOB_COUNT * sizeof(Job))
		, m_jobs(static_cast<Job*>(m_job_pool.current()))
	{
		if(num_threads == 0)
		{
			uint32_t hardware_threads = std::thread::hardware_concurrency();
			if(HAS_HYPER_THREADING)
				num_threads = uint16_t(hardware_threads / 2 - 1);
			else
				num_threads = uint16_t(hardware_threads - 1);
		}
		num_threads = std::min(uint16_t(HAS_THREADING ? 32 : 0), num_threads);

		m_thread_states = aligned_vector<ThreadState>(num_threads + adoptable_threads);
		m_thread_count = uint16_t(num_threads);
		m_parallel_split_count = (uint8_t)std::ceil(std::log2f(float(num_threads + adoptable_threads)));

		printf("INFO: job system running on %i worker threads\n", int(m_thread_count));

		for(size_t i = 0, n = m_thread_states.size(); i < n; i++)
		{
			ThreadState& state = m_thread_states[i];
			state.work_queue.m_jobs = m_jobs;
			state.index = uint32_t(i);
			state.mask = uint32_t(1UL << i);
			state.js = this;
			if(i < size_t(m_thread_count))
			{
				state.thread = std::thread(&JobSystem::loop, this, &state);
			}
		}
	}

	JobSystem::~JobSystem()
	{
		this->shutdown();

		for(ThreadState& state : m_thread_states)
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
		m_exit_requested.store(true, std::memory_order_relaxed);
		m_condition.notify_all();
	}

	uint32_t JobSystem::thread()
	{
		return s_thread_state->index;
	}

	inline bool JobSystem::exiting() const
	{
		return m_exit_requested.load(std::memory_order_relaxed);
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
		uint16_t adopted = m_adopted_threads.load(std::memory_order_relaxed);
		uint32_t index = random_index(m_thread_count + adopted);
		assert(index < m_thread_states.size());
		return m_thread_states[index];
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
			uint32_t active_jobs = m_active_jobs.fetch_sub(1, std::memory_order_acq_rel);
			assert(active_jobs);
			UNUSED(active_jobs);

			if(job->function) //[[likely]]
			{
				ZoneScopedN("job");
				job->function(job->padding, *this, job);
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
				std::unique_lock<std::mutex> lock(m_lock);
				while(!exiting() && !(m_active_jobs.load(std::memory_order_relaxed)))
					m_condition.wait(lock);
			}
		} while(!exiting());
	}
	
	Job* JobSystem::create(Job* parent, JobFunc func)
	{
		parent = (parent == nullptr) ? m_master_job : parent;
		Job* const job = m_job_pool.make();
		if(job) //[[likely]]
		{
			//printf("%i jobs\n", int(job - m_jobs));
			size_t index = 0x7FFF;
			if(parent)
			{
				assert(parent->running_jobs.load(std::memory_order_relaxed) > 0);

				parent->running_jobs.fetch_add(1, std::memory_order_relaxed);
				index = parent - m_jobs;
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
		auto& job_pool = m_job_pool;
		Job* const storage = m_jobs;
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

		uint32_t active_jobs = m_active_jobs.fetch_add(1, std::memory_order_relaxed);
		state.work_queue.push(job);

		if(!(flags & DONT_SIGNAL))
		{
			if(active_jobs)
			{
				{ std::lock_guard<std::mutex> lock(m_lock); }
				m_condition.notify_one();
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

		uint16_t adopted = m_adopted_threads.fetch_add(1, std::memory_order_relaxed);
		size_t index = m_thread_count + adopted;

		set_thread_priority(ThreadPriority::Display);

		s_thread_state = &m_thread_states[index];
	}

	void JobSystem::emancipate()
	{
		ThreadState* const state = s_thread_state;
		UNUSED(state);
		s_thread_state = nullptr;
	}
}
