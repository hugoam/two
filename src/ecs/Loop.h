#pragma once

#include <stl/tuple.h>
#include <ecs/Forward.h>
#include <ecs/ECS.h>
#include <jobs/JobLoop.h>

namespace mud
{
	template <class... Ts, size_t... Is, class T_Function>
	Job* for_components_impl(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action, index_sequence<Is...>)
	{
		uint64_t prototype = any_flags(1ULL << TypedBuffer<Ts>::index()...);

		Job* job = job_system.job(parent);

		vector<ParallelBuffers*> matches = ecs.Match(prototype);
		for(ParallelBuffers* stream : matches)
		{
			tuple<ComponentBuffer<Ts>&...> buffers = { stream->Buffer<Ts>()... };

			auto process = [=](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t i = start; i < start + count; ++i)
				{
					action(at<Is>(buffers).m_data[i]...);
				}
			};

			Job* stream_job = split_jobs<64>(job_system, job, 0, uint32_t(stream->m_handles.size()), process);
			job_system.run(stream_job);
		}

		return job;
	}

	template <class... Ts, class T_Function>
	Job* for_components(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action)
	{
		return for_components_impl<Ts...>(job_system, parent, ecs, action, index_tuple<sizeof...(Ts)>());
	}
}
