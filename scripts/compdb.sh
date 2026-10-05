#!/bin/sh
# two compilation database
# generates compile_commands.json for clangd from the ninja projects of the windows-clang toolchain:
#   genie --gcc=windows-clang ninja
# it must be regenerated when the structure of the build changes (files, projects, flags), the ninja build itself is not needed
# third party sources are left out: they're most of the build, and clangd scans and indexes every entry of the database

TWO_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$TWO_DIR/build/projects/ninja-windows-clang/debug64"
NINJA="${NINJA:-/c/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe}"

"$NINJA" -C "$BUILD_DIR" -t compdb cc cxx | awk '
	# the paths are relative to the ninja directory, four levels below the root of two
	function keep(file) {
		return file ~ /^"\.\.\/\.\.\/\.\.\/\.\.\/(src|example)\// || file ~ /^"\.\.\/\.\.\/\.\.\/std\//
	}
	BEGIN { printf "[\n" }
	/^  \{$/ { record = $0; next }
	/^  \},?$/ {
		if (keep(file)) {
			if (count++) printf ",\n"
			printf "%s\n  }", record
		}
		record = ""; next
	}
	record != "" {
		record = record "\n" $0
		if ($1 == "\"file\":") file = $2
		next
	}
	END { printf "\n]\n" }
' > "$BUILD_DIR/compile_commands.json"

echo "$(grep -c '"file"' "$BUILD_DIR/compile_commands.json") entries in $BUILD_DIR/compile_commands.json"
