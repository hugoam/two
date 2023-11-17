//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.lang;

namespace two
{
	StreamBranch::StreamBranch() {}
	StreamBranch::StreamBranch(Stream* stream, const Var& value, StreamIndex index)
		: m_stream(stream)
		, m_index(index)
		, m_depth(index.size() - 1)
		, m_value(value)
	{}

	StreamBranch& StreamBranch::add_branch()
	{
		StreamIndex branch_index = m_index;
		branch_index.push_back(m_branches.size());
		m_branches.push_back({ m_stream, m_stream->m_default, branch_index });
		return m_branches.back();
	}

	void StreamBranch::resize(size_t size)
	{
		for(size_t i = m_branches.size(); i < size; ++i)
			this->add_branch();
	}

	void StreamBranch::clear()
	{
		m_branches.clear();
	}

	void StreamBranch::copy(const StreamBranch& source)
	{
		if(m_branches.size() == source.m_branches.size())
		{
			for(size_t i = 0; i < m_branches.size(); ++i)
				m_branches[i].copy(source.m_branches[i]);
		}
		else
		{
			*this = source;
		}
	}

	StreamBranch& StreamBranch::branch(const StreamIndex& index)
	{
		if(index.size() > m_depth + 1)
		{
			size_t at = index[m_depth + 1];
			while(at >= m_branches.size())
				this->add_branch();
			return m_branches[at].branch(index);
		}
		else
		{
			return *this;
		}
	}

	StreamBranch* StreamBranch::find_branch(const StreamIndex& index, size_t depth)
	{
		if(m_branches.empty())
			return this;
		else if(m_branches.size() <= index[depth])
			return nullptr;
		else
			return m_branches[index[depth]].find_branch(index, depth + 1);
	}

	void StreamBranch::write(const Var& value, bool multiplex)
	{
		if(multiplex && !(value == Var(Ref())) && is_sequence(type(value)))
		{
			Iterable& it = iter(value);
			this->resize(it.size(value));

			it.iteratei(value, [&](size_t i, Ref element) {
				m_branches[i].m_value = element;
			});
		}
		else
		{
			m_value = value;
		}
	}

	bool StreamBranch::read(Var& value, const Type* expected_type, bool ref)
	{
		if(!expected_type)
		{
			value = m_value.m_ref;
			return true;
		}
		bool result = convert(m_value, *expected_type, value, ref);
#if 0
		if(!result)
			warn("No conversion possible from %s to %s : dest set to None", type(source).m_name, output.m_name);
#endif
		return result;
	}

	Stream::Stream()
		: StreamBranch(this, Var(), { 0 })
	{}

	Stream::Stream(const Var& value, bool nullable, bool reference)
		: StreamBranch(this, value, { 0 })
		, m_default(value)
		, m_type(value == Var(Ref()) ? &type<Ref>() : &type(value))
		, m_nullable(nullable)
		, m_reference(reference)
	{}

	Stream::Stream(const Stream& stream)
		: Stream(stream.m_default, stream.m_nullable, stream.m_reference)
	{
		*this = stream;
	}

	Stream& Stream::operator=(const Stream& stream)
	{
		this->copy(stream);
		this->compute();
		return *this;
	}

	bool compare_tip(const Topology& topology, const Topology& other)
	{
		size_t depth = other.size();
		return equal(topology.end() - depth, topology.end(), other.begin(), other.end());
	}

	StreamBranch* Stream::match_branch(const StreamLocation& source)
	{
		if(source.m_topology.size() > 0 && m_topology.size() > 0)
			if(compare_tip(source.m_topology, m_topology))
			{
				size_t offset = source.m_topology.size() - m_topology.size();
				return this->find_branch(source.m_index, offset + 1);
			}

		return this->find_branch(source.m_index, m_depth + 1);
	}

	void Stream::compute()
	{
		m_size = 0;
		m_topology.clear();

		if(m_branches.size() == 0)
			return;

		m_topology.resize(100, SIZE_MAX);

		this->visit(false, [&](StreamBranch& branch) {
			if(branch.m_branches.size() == 0)
				++m_size;
			
			if(m_topology[branch.m_depth] == SIZE_MAX)
				m_topology[branch.m_depth] = branch.m_branches.size();
			else if(m_topology[branch.m_depth] != branch.m_branches.size())
				m_topology[branch.m_depth] = 0;
		});

		remove_if(m_topology, [](size_t& val) { return val == 0 || val == SIZE_MAX; });
	}

	void Stream::flatten(Stream& source)
	{
		if(source.m_branches.empty())
			return;

		m_branches.clear();

		m_value = meta(*m_type).m_empty_var;
		Sequence& seq = sequence(m_value);
		Var element = meta(*iter(*m_type).m_element_type).m_empty_var;

		source.visit(true, [&](StreamBranch& branch)
		{
			branch.read(element, iter(*m_type).m_element_type, m_reference);
			seq.add(m_value, element);
		});
	}

	void Stream::graft(Stream& source)
	{
		Iterable& iterable = iter(source.m_value);
		this->resize(iterable.size(source.m_value));

		size_t index = 0;
		iterable.iterate(source.m_value, [&](Ref element)
		{
			m_branches[index++].m_value = element;
		});
	}

	void Stream::read(Stream& source)
	{
		*this = source; // why is this needed :/
		
		m_num_invalid = 0;
		source.visit(true, [&](StreamBranch& source_branch)
		{
			StreamBranch& branch = this->branch(source_branch.m_index);
			bool success = source_branch.read(branch.m_value, m_type, m_reference);
			branch.m_valid = success && (m_nullable || !branch.m_value.null());
			if(!branch.m_valid)
				m_num_invalid++;
		});
	}

	void Stream::validate()
	{
		m_num_invalid = 0;
		this->visit(true, [&](StreamBranch& branch)
		{
			branch.m_valid = m_nullable || !branch.m_value.null();
			if(!branch.m_valid)
				m_num_invalid++;
		});
	}
}
