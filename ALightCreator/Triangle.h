#pragma once
#include "SubDivVertex.h"
#include "Edge.h"
namespace SubDiv {

	class  Triangle
	{
	public:
		SubDiv::SDVertex* v0, * v1, * v2;
		Edge* e0, * e1, * e2;
		Triangle(SDVertex* a0, SDVertex* a1, SDVertex* a2, Edge* _e0, Edge* _e1, Edge* _e2)
		{
			v0 = a0;
			v1 = a1;
			v2 = a2;
			e0 = _e0;
			e1 = _e1;
			e2 = _e2;
		}
		SubDiv::SDVertex* GetOtherVertex(Edge* e);

	};
}
