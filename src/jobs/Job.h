#pragma once

#include <jobs/Forward.h>
#include <jobs/JobSystem.h>

#include <atomic>
#include <functional>

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
		void* padding[JOB_PADDING]; // on 64-bits systems, there is an extra 32-bits lost here
	};

	template <typename T, void(T::*method)(JobSystem&, Job*)>
	Job* job(JobSystem& js, Job* parent, T* data)
	{
		auto call = [](void* user, JobSystem& js, Job* job) { (*static_cast<T**>(user)->*method)(js, job); };
		Job* job = js.job(parent, &stub::call);
		if(job)
			job->padding[0] = data;
		return job;
	}

	template <typename T, void(T::*method)(JobSystem&, Job*)>
	Job* job(JobSystem& js, Job* parent, T data)
	{
		static_assert(sizeof(data) <= sizeof(Job::padding), "user data too large");
		auto stub = [](void* user, JobSystem& js, Job* job)
		{
			T* that = static_cast<T*>(user);
			(that->*method)(js, job);
			that->~T();
		};
		Job* job = js.job(parent, stub);
		if(job)
			new(job->padding) T(move(data));
		return job;
	}

	template <typename T>
	Job* job(JobSystem& js, Job* parent, T functor)
	{
		static_assert(sizeof(functor) <= sizeof(Job::padding), "functor too large");
		auto call = [](void* user, JobSystem& js, Job* job)
		{
			T& that = *static_cast<T*>(user);
			that(js, job);
			that.~T();
		};
		Job* job = js.job(parent, &stub::call);
		if(job)
			new(job->padding) T(move(functor));
		return job;
	}

	template <typename Function, typename... Args>
	Job* job(JobSystem& js, Job* parent, Function&& func, Args&&... args)
	{
		struct Data
		{
			std::function<void()> f;
			void gob(JobSystem&, Job*) { f(); }
		};
		Data user{ std::bind(std::forward<Function>(func), static_cast<Args&&>(args)...) };
		return job<Data, &Data::gob>(js, parent, move(user));
		return nullptr;
	}

	template <typename Function, typename T, typename... Args, typename = typename std::enable_if<std::is_member_function_pointer<typename std::remove_reference<Function>::type>::value>::type>
	Job* job(JobSystem& js, Job* parent, Function&& func, T&& o, Args&&... args)
	{
		struct Data
		{
			std::function<void()> f;
			void gob(JobSystem&, Job*) { f(); }
		} user { std::bind(std::forward<Function>(func), static_cast<T&&>(o), std::forward<Args>(args)...) };
		return js.job<Data, &Data::gob>(parent, move(user));
	}
}
