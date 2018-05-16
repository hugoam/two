//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Var.h>
#include <obj/String/String.h>
#include <lang/Generated/Forward.h>

#include <vector>
#include <functional>

namespace mud
{
	typedef std::vector<size_t> StreamIndex;
	typedef std::vector<size_t> Topology;

	/*struct MUD_LANG_EXPORT StreamBranch : public StreamIndex
	{
		StreamBranch(StreamIndex index);

		Flow* flow;
		bool empty;
	};

	struct MUD_LANG_EXPORT Flow
	{
		std::vector<StreamBranch> branches;
		Topology topology;
	};*/

	struct StreamLocation
	{
		const StreamIndex& m_index;
		const Topology& m_topology;
	};

	class _refl_ MUD_LANG_EXPORT StreamBranch
	{
	public:
		StreamBranch(Stream* stream, Var value, StreamIndex index);

		Var& value(const StreamIndex& index) { return this->branch(index).m_value; }

		StreamBranch& add_branch();
		void resize(size_t size);

		void clear();

		void copy(const StreamBranch& branch);

		typedef std::function<void(StreamBranch&)> Visitor;
		void visit(bool leafs, const Visitor& visitor);
		
		StreamBranch& branch(const StreamIndex& index);

		StreamBranch* find_branch(const StreamIndex& branch, size_t depth);
		StreamBranch* find_branch(const StreamIndex& branch) { return this->find_branch(branch, m_depth); }

		void write(const Var& value, bool multiplex = true);
		bool read(Var& value, Type* expected_type, bool ref);

		void write(const StreamLocation& location, const Var& value, bool multiplex = true) { this->branch(location.m_index).write(value, multiplex); }
		//void write(const Var& value, bool multiplex = true) { this->branch({ 0 }).write(value, multiplex); }

		Stream* m_stream;
		StreamIndex m_index;
		size_t m_depth;
		Var m_value = {};
		bool m_valid = true;
		//bool m_empty = false;

		std::vector<StreamBranch> m_branches;
	};


	enum StreamModifier : unsigned int
	{
		SM_NONE,
		SM_FLATTEN,
		SM_GRAFT
	};

	class _refl_ MUD_LANG_EXPORT Stream : public StreamBranch
	{
	public:
		Stream();
		Stream(Var value, bool nullable, bool reference);
		Stream(const Stream& stream);
		Stream& operator=(const Stream& stream);

		StreamBranch* match_branch(const StreamLocation& source_location);

		void flatten(Stream& source);
		void graft(Stream& source);
		void read(Stream& source);
		void validate();

		size_t m_size = 1;
		Topology m_topology;
		size_t m_num_invalid = 0;

		Var m_default;
		Type* m_type = nullptr;
		bool m_nullable = false;
		bool m_reference = false;

		void compute();
	};
}
