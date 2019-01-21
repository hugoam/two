#pragma once

#include <stl/tuple.h>
#include <ecs/Forward.h>
#include <ecs/Registry.h>
#include <jobs/JobLoop.h>

#define FOR_VARIADIC 1

#if FOR_VARIADIC
//#include <functional>
#endif

namespace mud
{
#if FOR_VARIADIC
	template <class... Ts, size_t... Is, class T_Function>
	Job* for_components_impl(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action, index_sequence<Is...>)
	{
		EntFlags prototype = any_flags(1ULL << TypedBuffer<Ts>::index()...);

		Job* job = job_system.job(parent);

		vector<ParallelBuffers*> matches = ecs.Match(prototype);
		for(ParallelBuffers* stream : matches)
		{
			tuple<ComponentBuffer<Ts>&...> buffers = { stream->Buffer<Ts>()... };

			auto process = [action, stream, buffers](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t index = start; index < start + count; ++index)
				{
					uint32_t handle = stream->m_handles[index];
					action(handle, at<Is>(buffers).m_data[index]...);
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
		return for_components_impl<Ts...>(job_system, parent, ecs, action, make_index_sequence<sizeof...(Ts)>());
	}
#else

	template <class T0, class T_Function>
	Job* for_components(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action)
	{
		EntFlags prototype = (1ULL << TypedBuffer<T0>::index());

		Job* job = job_system.job(parent);

		vector<ParallelBuffers*> matches = ecs.Match(prototype);
		for(ParallelBuffers* stream : matches)
		{
			ComponentBuffer<T0>& buffer0 = stream->Buffer<T0>();

			auto process = [action, stream, &buffer0](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t index = start; index < start + count; ++index)
				{
					uint32_t handle = stream->m_handles[index];
					action(handle, buffer0.m_data[index]);
				}
			};

			Job* stream_job = split_jobs<64>(job_system, job, 0, uint32_t(stream->m_handles.size()), process);
			job_system.run(stream_job);
		}

		return job;
	}

	template <class T0, class T1, class T_Function>
	Job* for_components(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action)
	{
		EntFlags prototype = (1ULL << TypedBuffer<T0>::index()) | (1ULL << TypedBuffer<T1>::index());

		Job* job = job_system.job(parent);

		vector<ParallelBuffers*> matches = ecs.Match(prototype);
		for(ParallelBuffers* stream : matches)
		{
			ComponentBuffer<T0>& buffer0 = stream->Buffer<T0>();
			ComponentBuffer<T1>& buffer1 = stream->Buffer<T1>();

			auto process = [action, stream, &buffer0, &buffer1](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t index = start; index < start + count; ++index)
				{
					uint32_t handle = stream->m_handles[index];
					action(handle, buffer0.m_data[index], buffer1.m_data[index]);
				}
			};

			Job* stream_job = split_jobs<64>(job_system, job, 0, uint32_t(stream->m_handles.size()), process);
			job_system.run(stream_job);
		}

		return job;
	}

	template <class T0, class T1, class T2, class T_Function>
	Job* for_components(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action)
	{
		EntFlags prototype = (1ULL << TypedBuffer<T0>::index()) | (1ULL << TypedBuffer<T1>::index()) | (1ULL << TypedBuffer<T2>::index());

		Job* job = job_system.job(parent);

		vector<ParallelBuffers*> matches = ecs.Match(prototype);
		for(ParallelBuffers* stream : matches)
		{
			ComponentBuffer<T0>& buffer0 = stream->Buffer<T0>();
			ComponentBuffer<T1>& buffer1 = stream->Buffer<T1>();
			ComponentBuffer<T2>& buffer2 = stream->Buffer<T2>();

			auto process = [action, stream, &buffer0, &buffer1, &buffer2](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t index = start; index < start + count; ++index)
				{
					uint32_t handle = stream->m_handles[index];
					action(handle, buffer0.m_data[index], buffer1.m_data[index], buffer2.m_data[index]);
				}
			};

			Job* stream_job = split_jobs<64>(job_system, job, 0, uint32_t(stream->m_handles.size()), process);
			job_system.run(stream_job);
		}

		return job;
	}
#endif
}
