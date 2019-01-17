#pragma once

#include <jobs/Forward.h>
#include <jobs/JobSystem.h>

namespace mud
{
	template <typename Function, typename ... Args>
	Job* job(JobSystem& js, Job* parent, Function&& func, Args&&... args)
	{
		struct Data
		{
			std::function<void()> f;
			void gob(JobSystem&, Job*) { f(); }
		} user{ std::bind(std::forward<Function>(func), static_cast<Args&&>(args)...) };
		return js.job<Data, &Data::gob>(parent, move(user));
	}

	template <typename Function, typename T, typename ... Args, typename = typename std::enable_if<std::is_member_function_pointer<typename std::remove_reference<Function>::type>::value>::type>
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
