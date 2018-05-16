//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Reflect/Injector.h>
#include <edit/Generated/Forward.h>
#include <edit/Action.h>
#include <edit/Tools/TranslateTool.h>

#include <vector>

namespace mud
{
	class _refl_ MUD_EDIT_EXPORT CopyAction : public TranslateAction
	{
	public:
		CopyAction(const std::vector<Transform*>& targets);

		virtual void apply(Transform& transform) final;
		virtual void undo(Transform& transform) final;

	private:
		std::vector<Transform*> m_copies;
		//Injector m_injector;
	};

	class _refl_ MUD_EDIT_EXPORT CopyTool : public TransformTool
	{
	public:
		CopyTool(ToolContext& context);

		void begin(const vec3& position);
		void update(const vec3& position);
		void end();

	private:
		object_ptr<CopyAction> m_action;
	};
}
