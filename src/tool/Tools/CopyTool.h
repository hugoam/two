//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <refl/Injector.h>
#endif
#include <tool/Forward.h>
#include <tool/Action.h>
#include <tool/Tools/TranslateTool.h>

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT CopyAction : public TranslateAction
	{
	public:
		CopyAction(span<Transform*> targets);

		virtual void apply(Transform& transform) final;
		virtual void undo(Transform& transform) final;

	private:
		//vector<Transform*> m_copies;
		//Injector m_injector;
	};

	export_ class refl_ MUD_TOOL_EXPORT CopyTool final : public TransformTool
	{
	public:
		CopyTool(ToolContext& context);

		void begin(const vec3& position);
		void update(const vec3& position);
		void end();

		virtual object<TransformAction> create_action(span<Transform*> targets) final;

	private:
		object<CopyAction> m_action;
	};
}
