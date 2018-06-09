{
	"project": "${ module.namespace }${ module.name }.cpp",
	"target": "${ module.namespace }${ module.name }.cpp",
	"sources": [
% for s in module.sources :
		"${ module.subdir }/${ s }"${ "," if not loop.last else "" }
% endfor
	],
	"include_paths": [
        ""
	],
    "includes_map": {
		"${ module.name }/": "${ module.namespace }${ module.name }.h"${ "," if len(module.dependencies) > 0 else "" }
% for m in module.dependencies :
		"${ m.name }/": "${ m.namespace }${ m.name }.h"${ "," if not loop.last else "" }
% endfor
    },
	"clean_strings": [
		"//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net",
		"//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.",
		"//  This notice and the license may not be removed or altered from any source distribution.",
		"/* mud */"
	]
}

