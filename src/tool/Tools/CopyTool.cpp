//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.tool;

namespace two
{
	CopyAction::CopyAction(span<Transform*> targets)
		: TranslateAction(targets)
		//, m_injector(type<Transform>())
	{}

	void CopyAction::apply(Transform& transform)
	{
		//	m_copies.push_back(&as<Transform>(m_creator.cloneObject(transform)));
		TranslateAction::apply(transform);
	}

	void CopyAction::undo(Transform& transform)
	{
		// m_copies[transform].destroy();
		TranslateAction::undo(transform);
	}

 	CopyTool::CopyTool(ToolContext& context)
		: TransformTool(context, "Copy", type<CopyTool>())
		, m_action()
	{}

	void CopyTool::begin(const vec3& position)
	{
		UNUSED(position);
		//m_action = oconstruct<CopyAction>(m_targets); // @kludge brute cast
	}

	void CopyTool::update(const vec3& position)
	{
		m_action->update(position, vec3());
		//m_action->apply();
	}

	void CopyTool::end()
	{
		this->commit(move(m_action));
	}

	object<TransformAction> CopyTool::create_action(span<Transform*> targets)
	{
		return oconstruct<CopyAction>(targets);
	}
}
