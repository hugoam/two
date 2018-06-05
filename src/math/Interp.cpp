//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
import mud.obj;
module mud.math;
#else
#include <obj/Any.h>
#include <obj/Util/DispatchDecl.h>
#include <math/Interp.h>
#include <math/Generated/Types.h>
#endif

namespace mud
{
	Lerp::Lerp()
	{
		dispatch_branch<int>(*this, [](int& value, Ref source, Ref dest, float ratio) { value = lerp(val<int>(source), val<int>(dest), ratio); });
		dispatch_branch<float>(*this, [](float& value, Ref source, Ref dest, float ratio) { value = lerp(val<float>(source), val<float>(dest), ratio); });
		dispatch_branch<double>(*this, [](double& value, Ref source, Ref dest, float ratio) { value = lerp(val<double>(source), val<double>(dest), ratio); });
		dispatch_branch<vec3>(*this, [](vec3& value, Ref source, Ref dest, float ratio) { value = mix(val<vec3>(source), val<vec3>(dest), ratio); });
		dispatch_branch<quat>(*this, [](quat& value, Ref source, Ref dest, float ratio) { value = slerp(val<quat>(source), val<quat>(dest), ratio); });
	}
}
