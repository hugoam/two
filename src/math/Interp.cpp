//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.math;
#else
#include <infra/Global.h>
#include <type/Any.h>
#include <type/Var.h>
#include <type/Dispatch.h>
#include <type/DispatchDecl.h>
#include <math/Interp.h>
#include <math/Types.h>
#endif

namespace two
{
	class Lerp : public Dispatch<void, Ref, Ref, float>, public LazyGlobal<Lerp>
	{
	public:
		Lerp()
		{
			dispatch_branch<int>(*this, +[](int& value, Ref source, Ref dest, float t) { value = lerp(val<int>(source), val<int>(dest), t); });
			dispatch_branch<float>(*this, +[](float& value, Ref source, Ref dest, float t) { value = lerp(val<float>(source), val<float>(dest), t); });
			dispatch_branch<double>(*this, +[](double& value, Ref source, Ref dest, float t) { value = lerp(val<double>(source), val<double>(dest), t); });
			dispatch_branch<vec3>(*this, +[](vec3& value, Ref source, Ref dest, float t) { value = lerp(val<vec3>(source), val<vec3>(dest), t); });
			dispatch_branch<quat>(*this, +[](quat& value, Ref source, Ref dest, float t) { value = slerp(val<quat>(source), val<quat>(dest), t); });
			
			dispatch_branch<vector<float>>(*this, +[](vector<float>& value, Ref source, Ref dest, float t)
			{
				vector<float>& sourcevec = val<vector<float>>(source);
				vector<float>& destvec = val<vector<float>>(dest);
				assert(sourcevec.size() == destvec.size());
				value.resize(sourcevec.size());
				for(size_t i = 0; i < sourcevec.size(); ++i)
					value[i] = lerp(sourcevec[i], destvec[i], t);
			});
		}
	};

	void interpolate(Ref result, Ref a, Ref b, float t) { Lerp::me().dispatch(result, a, b, t); }
	//Var interpolate(Ref a, Ref b, float t) { Var result = meta(a).m_empty_var; Lerp::me().dispatch(result.m_ref, a, b, t); return result; }
}
