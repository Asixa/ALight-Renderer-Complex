#pragma once
#include "SubDivVertex.h"
#include <vector>

namespace SubDiv 
{
	class Edge
	{
	public:
		SDVertex* a, * b, * ept;
		std::vector<Triangle*>faces;
		
		Edge(SDVertex* x, SDVertex* y);
		void AddTriangle(Triangle* f);
		bool Has(SDVertex* v);
		SDVertex* GetOtherVertex(SDVertex* v);

	};
}
