//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <vg.cpp>

namespace vg
{
bool checkIntersectScissor(Context* ctx, float x, float y, float w, float h)
{
	State* state = getState(ctx);
	const float* stateTransform = state->m_TransformMtx;
	const float* scissorRect = state->m_ScissorRect;

	float pos[2], size[2];
	vgutil::transformPos2D(x, y, stateTransform, &pos[0]);
	vgutil::transformVec2D(w, h, stateTransform, &size[0]);

	if(scissorRect[2] == 0.f || scissorRect[3] == 0.f)
		return true;

	return !(scissorRect[0] > pos[0] + size[0]
		|| scissorRect[1] > pos[1] + size[1]
		|| scissorRect[0] + scissorRect[2] < pos[0]
		|| scissorRect[1] + scissorRect[3] < pos[1]);
}
}
