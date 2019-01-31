//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <infra/Global.h>
#include <type/Any.h>
#include <type/Var.h>
#include <type/Dispatch.h>
#include <type/DispatchDecl.h>
#include <math/Interp.h>
#include <math/Types.h>
#endif

namespace mud
{
	class Lerp : public Dispatch<void, Ref, Ref, float>, public LazyGlobal<Lerp>
	{
	public:
		Lerp()
		{
			dispatch_branch<int>(*this, +[](int& value, Ref source, Ref dest, float ratio) { value = lerp(val<int>(source), val<int>(dest), ratio); });
			dispatch_branch<float>(*this, +[](float& value, Ref source, Ref dest, float ratio) { value = lerp(val<float>(source), val<float>(dest), ratio); });
			dispatch_branch<double>(*this, +[](double& value, Ref source, Ref dest, float ratio) { value = lerp(val<double>(source), val<double>(dest), ratio); });
			dispatch_branch<vec3>(*this, +[](vec3& value, Ref source, Ref dest, float ratio) { value = lerp(val<vec3>(source), val<vec3>(dest), ratio); });
			dispatch_branch<quat>(*this, +[](quat& value, Ref source, Ref dest, float ratio) { value = slerp(val<quat>(source), val<quat>(dest), ratio); });
		}
	};

	void interpolate(Ref result, Ref a, Ref b, float t) { Lerp::me().dispatch(result, a, b, t); }
	//Var interpolate(Ref a, Ref b, float t) { Var result = meta(a).m_empty_var; Lerp::me().dispatch(result.m_ref, a, b, t); return result; }
}
