function amalgamate_headers(m)
    local clean_strings = {
        "//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net",
        "//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.",
        "//  This notice and the license may not be removed or altered from any source distribution.",
        "/* two */"
    }
    io.printf('{')
	io.printf('"project": "' .. m.idname .. '.h",')
    io.printf('"target": "' .. m.idname .. '.h",')
	io.printf('"sources": [')
    for _, h in m.headers do
        io.printf('	"' .. m.subpath .. h .. '"' .. "," if not loop.last else ""
    end
	
	io.printf('],')
	io.printf('"include_paths": [')
	io.printf('	""')
	io.printf('],')
	io.printf('"includes_map": {')
    for _, dep in m.deps do
		io.printf('"' .. m.name .. '/": "' .. m.idname .. '.h"' .. "," if not loop.last else ""
    end
	io.printf('},')
	io.printf('"ignore": [')
	io.printf('	"Generated"')
	io.printf('],')
	io.printf('"clean_strings": [')
	io.printf(']')
    io.printf('}')
end
