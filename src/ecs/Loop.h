#pragma once

#include <ecs/Forward.h>
#include <ecs/Registry.h>
#include <jobs/JobLoop.h>

namespace mud
{
	template <class... Ts, size_t... Is, class T_Function>
	Job* for_components_impl(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action, std::index_sequence<Is...>)
	{
		EntFlags prototype = any_flags(1ULL << TypedBuffer<Ts>::index()...);

		Job* job = job_system.job(parent);

		vector<ParallelBuffers*> matches = ecs.Match(prototype);
		for(ParallelBuffers* stream : matches)
		{
			std::tuple<ComponentBuffer<Ts>&...> buffers = std::make_tuple(std::ref(stream->Buffer<Ts>())...);

			auto process = [action, stream, buffers](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t index = start; index < start + count; ++index)
				{
					uint32_t handle = stream->m_handles[index];
					action(handle, std::get<Is>(buffers).m_data[index]...);
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
		return for_components_impl<Ts...>(job_system, parent, ecs, action, std::make_index_sequence<sizeof...(Ts)>());
	}
}