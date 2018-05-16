/** @file Rect.h
	@author Jukka Jyl�nki

	This work is released to Public Domain, do whatever you want with it.
*/
#ifndef TOY_RECT_H
#define TOY_RECT_H

#include <vector>

#include <cstring>

struct RectSize
{
	int width;
	int height;
};

struct BPRect
{
	int x;
	int y;
	int width;
	int height;
};

/// Performs a lexicographic compare on (rect short side, rect long side).
/// @return -1 if the smaller side of a is shorter than the smaller side of b, 1 if the other way around.
///   If they are equal, the larger side length is used as a tie-breaker.
///   If the rectangles are of same size, returns 0.
int CompareRectShortSide(const BPRect &a, const BPRect &b);

/// Performs a lexicographic compare on (x, y, width, height).
int NodeSortCmp(const BPRect &a, const BPRect &b);

/// Returns true if a is contained in b.
bool IsContainedIn(const BPRect &a, const BPRect &b);

class DisjointRectCollection
{
public:
	std::vector<BPRect> rects;

	bool Add(const BPRect &r)
	{
		// Degenerate rectangles are ignored.
		if (r.width == 0 || r.height == 0)
			return true;

		if (!Disjoint(r))
			return false;
		rects.push_back(r);
		return true;
	}

	void Clear()
	{
		rects.clear();
	}

	static bool Disjoint(const BPRect &a, const BPRect &b)
	{
		if (a.x + a.width <= b.x ||
			b.x + b.width <= a.x ||
			a.y + a.height <= b.y ||
			b.y + b.height <= a.y)
			return true;
		return false;
	}

	bool Disjoint(const BPRect &r) const
	{
		// Degenerate rectangles are ignored.
		if (r.width == 0 || r.height == 0)
			return true;

		for(size_t i = 0; i < rects.size(); ++i)
			if (!Disjoint(rects[i], r))
				return false;
		return true;
	}
};

#endif
