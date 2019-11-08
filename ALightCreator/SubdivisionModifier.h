#pragma once

#include "SubDivVertex.h"
#include "SubDivModel.h"
#include "tuple"
#include <unordered_map>
typedef std::tuple <int, int, int> kk;

namespace SubDiv {


	class SubdivisionModifier
	{
	public:
		static ALightCreator::Mesh* Subdivide(ALightCreator::Mesh* source, int details = 1, bool weld = false);
		static SubDiv::SDModel* MSubdivide(ALightCreator::Mesh* source, int details = 1);

		static SDModel* Divide(SDModel* model);
		static ALightCreator::Mesh* Weld(ALightCreator::Mesh* mesh, float threshold, float bucketStep);
		static SDVertex* GetEdgePoint(Edge* e);
		static SDVertex* GetVertexPoint(SDVertex* v);
		static std::vector<SDVertex*> GetAdjancies(SDVertex* v);
	};
}
