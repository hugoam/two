#pragma once

#include <infra/Array.h>
#include <infra/Job.h>

namespace mud
{
	namespace details
	{
		template <typename Splitter, typename Functor>
		struct ParallelJob
		{
			using Jobs = ParallelJob;

			ParallelJob(uint32_t start, uint32_t count, uint8_t splits, Functor functor, const Splitter& splitter)
				: m_start(start), m_count(count)
				, m_functor(std::move(functor))
				, m_splits(splits)
				, m_splitter(splitter)
			{}

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
					Job* left = js.job<Jobs, &Jobs::run>(parent, std::move(ld));

					js.run(left);

					const uint32_t rc = m_count - lc;
					Jobs rd(m_start + lc, rc, m_splits + uint8_t(1), m_functor, m_splitter);
					Job* right = js.job<Jobs, &Jobs::run>(parent, std::move(rd));

					js.run(right, JobSystem::DONT_SIGNAL);
				}
				else
				{
					m_functor(js, parent, m_start, m_count);
				}
			}

			void parallel(JobSystem& js, Job* parent, uint32_t start, uint32_t count, uint8_t splits)
			{
				if(m_splitter.split(splits, count))
				{
					const uint32_t left = count / 2;
					parallel(js, parent, start, left, splits);
					parallel(js, parent, start + left, count - left, splits + 1);
				}
				else
				{
					Job* job = js.job(parent, [f = m_functor, start, count](JobSystem& js, Job* job) {
						f(js, job, start, count);
					});
					js.run(job);
				}
			}

			uint32_t m_start;             // 4
			uint32_t m_count;             // 4
			Functor m_functor;            // ?
			uint8_t m_splits;             // 1
			Splitter m_splitter;          // 1
		};

	}

	template <typename S, typename F>
	Job* jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor, const S& splitter)
	{
		using Jobs = details::ParallelJob<S, F>;
		Jobs jobData(start, count, 0, std::move(functor), splitter);
		return js.job<Jobs, &Jobs::run>(parent, std::move(jobData));
	}

	template <typename T, typename S, typename F>
	Job* jobs(JobSystem& js, Job* parent, T* data, uint32_t count, F functor, const S& splitter)
	{
		auto user = [data, f = std::move(functor)](uint32_t s, uint32_t c)
		{
			f(data + s, c);
		};
		using Jobs = details::ParallelJob<S, decltype(user)>;
		Jobs jobData(0, count, 0, std::move(user), splitter);
		return js.job<Jobs, &Jobs::run>(parent, std::move(jobData));
	}

	template <typename T, typename S, typename F>
	Job* jobs(JobSystem& js, Job* parent, array<T> slice, F functor, const S& splitter)
	{
		return jobs(js, parent, slice.data(), slice.size(), functor, splitter);
	}

	template <size_t Count, size_t MaxSplits = 12>
	class CountSplitter
	{
	public:
		bool split(size_t splits, size_t count) const { return (splits < MaxSplits && count >= Count * 2); }
	};

	template <size_t Count, typename F>
	Job* jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor)
	{
		return jobs(js, parent, start, count, functor, CountSplitter<Count>());
	}

	template <size_t Count, typename T, typename F>
	Job* jobs(JobSystem& js, Job* parent, array<T> slice, F functor)
	{
		return jobs(js, parent, slice.data(), slice.size(), functor, CountSplitter<Count>());
	}
}
