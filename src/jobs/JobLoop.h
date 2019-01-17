#pragma once

#include <infra/Array.h>
#include <jobs/Job.h>

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
				, m_functor(move(functor))
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
					Job* left = js.job<Jobs, &Jobs::run>(parent, move(ld));

					js.run(left);

					const uint32_t rc = m_count - lc;
					Jobs rd(m_start + lc, rc, m_splits + uint8_t(1), m_functor, m_splitter);
					Job* right = js.job<Jobs, &Jobs::run>(parent, move(rd));

					js.run(right, JobSystem::DONT_SIGNAL);
				}
				else
				{
					m_functor(js, parent, m_start, m_count);
				}
			}

			void parallel(JobSystem& js, Job* parent, uint32_t start, uint32_t count, uint8_t splits)
			{
				//auto round_to = [](uint32_t number, uint32_t divisor) { return number - number % divisor + divisor * !!(number % divisor); };
				if(m_splitter.split(splits, count))
				{
					//const uint32_t left = round_to(count / 2, 64);
					const uint32_t left = count / 2;
					parallel(js, parent, start, left, splits);
					parallel(js, parent, start + left, count - left, splits + 1);
				}
				else
				{
					Job* job = js.job(parent, [f = m_functor, start, count](JobSystem& js, Job* job) {
						f(js, job, start, count);
					});
					if(job)
						js.run(job);
					else
						m_functor(js, parent, start, count);
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
	Job* split_jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor, const S& splitter)
	{
		using Jobs = details::ParallelJob<S, F>;
		Jobs jobData(start, count, 0, move(functor), splitter);
		return js.job<Jobs, &Jobs::run>(parent, move(jobData));
	}

	template <typename T, typename S, typename F>
	Job* split_jobs(JobSystem& js, Job* parent, T* data, uint32_t count, F functor, const S& splitter)
	{
		auto user = [data, f = move(functor)](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			UNUSED(js); UNUSED(job);
			f(data + start, count);
		};
		using Jobs = details::ParallelJob<S, decltype(user)>;
		Jobs jobData(0, count, 0, move(user), splitter);
		return js.job<Jobs, &Jobs::run>(parent, move(jobData));
	}

	template <typename T, typename S, typename F>
	Job* split_jobs(JobSystem& js, Job* parent, array<T> slice, F functor, const S& splitter)
	{
		return split_jobs(js, parent, slice.data(), slice.size(), functor, splitter);
	}

	template <uint32_t Count, uint32_t MaxSplits = 12>
	class CountSplitter
	{
	public:
		bool split(uint32_t splits, uint32_t count) const { return (splits < MaxSplits && count >= Count * 2); }
	};

	template <uint32_t Count, typename F>
	Job* split_jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor)
	{
		return split_jobs(js, parent, start, count, functor, CountSplitter<Count>());
	}

	template <uint32_t Count, typename T, typename F>
	Job* split_jobs(JobSystem& js, Job* parent, array<T> slice, F functor)
	{
		return split_jobs(js, parent, slice.data(), slice.size(), functor, CountSplitter<Count>());
	}

	template <uint32_t Count, typename F>
	Job* parallel_jobs(JobSystem& js, Job* parent, uint32_t start, uint32_t count, F functor)
	{
		auto user = [f = move(functor)](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			for(uint32_t i = start; i < start + count; ++i)
				f(js, job, i);
		};
		using Jobs = details::ParallelJob<CountSplitter<Count>, decltype(user)>;
		Jobs jobData(start, count, 0, move(user), CountSplitter<Count>());
		return js.job<Jobs, &Jobs::run>(parent, move(jobData));
	}

	template <uint32_t Count, class T_Source, class T_Dest>
	void parallel_copy(JobSystem& js, Job* parent, T_Source& source, T_Dest& dest, uint32_t count)
	{
		auto copy = [&source, &dest](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			UNUSED(js); UNUSED(job);
			for(uint32_t i = start; i < start + count; ++i)
				dest[i] = source[i];
		};

		Job* job = split_jobs<Count>(js, parent, 0, count, copy);
		js.complete(job);
	}

	template <uint32_t Count, class T_Value, class T_Dest>
	void parallel_set(JobSystem& js, Job* parent, T_Value value, T_Dest& dest, uint32_t count)
	{
		auto copy = [value, &dest](JobSystem& js, Job* job, uint32_t start, uint32_t count)
		{
			UNUSED(js); UNUSED(job);
			for(uint32_t i = start; i < start + count; ++i)
				dest[i] = value;
		};

		Job* job = split_jobs<Count>(js, parent, 0, count, copy);
		js.complete(job);
	}
}
