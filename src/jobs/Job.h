#pragma once

#include <stl/move.h>
#include <jobs/Forward.h>
#include <jobs/JobSystem.h>

#include <atomic>

namespace mud
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
			new(job->storage) T(move(functor));
		return job;
	}
}
