#pragma once
#include "Math.h"
#include "glm/vec4.hpp"
namespace ALight_Raster {
	class  Point //Simple point structure, store int.
	{
	public:
		int x, y;
		Point(const int x, const int y) :x(x), y(y) {}
		Point(glm::vec4 v) :x(v.x), y(v.y) {}
		static Point* Lerp(Point* a, Point* b, float t)
		{
			return new Point(Math::Lerp(a->x, b->x, t), Math::Lerp(a->y, b->y, t));
		}
	};
}
