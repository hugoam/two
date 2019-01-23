#pragma once

#include <stl/tuple.h>
#include <ecs/Forward.h>
#include <ecs/ECS.h>
#include <jobs/JobLoop.h>

namespace mud
{
	template <class... Types, size_t... Is, class T_Function>
	Job* for_components_impl(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action, index_sequence<Is...>)
	{
		uint64_t prototype = ecs.prototype<Types...>();

		Job* job = job_system.job(parent);

		vector<EntityStream*> matches = ecs.match(prototype);
		for(EntityStream* stream : matches)
		{
			tuple<TBuffer<Types>&...> buffers = { stream->buffer<Types>()... };

			auto process = [=](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t i = start; i < start + count; ++i)
				{
					action(at<Is>(buffers).m_data[i]...);
				}
			};

			Job* stream_job = split_jobs<64>(job_system, job, 0, uint32_t(stream->size()), process);
			job_system.run(stream_job);
		}

		return job;
	}

	template <class... Types, class T_Function>
	Job* for_components(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action)
	{
		return for_components_impl<Types...>(job_system, parent, ecs, action, index_tuple<sizeof...(Types)>());
	}
}
