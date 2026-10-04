#!/bin/sh
# rasterizes the icons of the Visual Studio Image Library used by the ui into data/interface/uisprites/vs
# usage: scripts/tools/vs_icons.sh <image library>/images [size]
# the Visual Studio Image Library can be used in applications that look like Visual Studio, see its EULA
# svg2png is built with cl from a Visual Studio developer prompt:
#   cl /O2 /EHsc /std:c++17 /I <bimg>/3rdparty/nanosvg /I 3rdparty/stb scripts/tools/svg2png.cpp

set -e

images="$1"
size="${2:-16}"
root="$(cd "$(dirname "$0")/../.." && pwd)"
out="$root/data/interface/uisprites/vs"
svg2png="${SVG2PNG:-svg2png}"

# the names of the icons in the library
icons="
VisualStudio Backwards Forwards NewItem AddItem OpenFolder OpenFile Save SaveAll Undo Redo
Run RunOutline Bookmark Settings Search Refresh CollapseAll ShowAllFiles Home Sync Filter
Solution SolutionExplorerViews FolderClosed FolderOpened CPPFile CPPFileNode CPPHeaderFile CPPProjectNode
Class Method StatusOK Checkmark Branch Edit Pencil NotificationAlert Close Pin Output Document
Attach Debug ClearWindowContent WordWrap FindNext FindPrevious Comment Reference User Account
GitRepository Git Feedback Memory Event Performance ExpandDown ExpandRight GlyphDown GlyphRight Collapse Expand
"

mkdir -p "$out"
files=""
for icon in $icons; do files="$files $images/$icon.svg"; done

# dark: the neutral greys are inverted in lightness, for a dark background
"$svg2png" "$out" "$size" 1 $files

# the ui lowercases the image names it looks up: the icons are named in snake case
for f in "$out"/*.png; do
    name=$(basename "$f" .png)
    snake=$(echo "$name" | sed 's/\([A-Z]\)\([A-Z][a-z]\)/\1_\2/g; s/\([a-z0-9]\)\([A-Z]\)/\1_\2/g' | tr 'A-Z' 'a-z')
    # through a temporary name, for case insensitive file systems
    [ "$name" != "$snake" ] && mv "$f" "$out/$snake.png.tmp" && mv "$out/$snake.png.tmp" "$out/$snake.png"
done

echo "$(ls "$out" | wc -l) icons in $out"
