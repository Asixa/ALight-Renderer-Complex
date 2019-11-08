#pragma once
#include <vector>
#include "SubDivVertex.h"

namespace ALightCreator {
	class Mesh;
}

namespace SubDiv {

	class SDModel
	{
	public:
		std::vector<SubDiv::SDVertex*>vertices;
		std::vector<Edge*>edges;
		std::vector<Triangle*>triangles;
	
		SDModel(){}
		SDModel(ALightCreator::Mesh* source);
		//Edge* GetEdge(std::vector<Edge*> edges, SDVertex* v0, SDVertex* v1);
		void AddTriangle(SDVertex* v0, SDVertex* v1, SDVertex* v2);
		Edge* GetEdge(SDVertex* v0, SDVertex* v1);
		SDModel* Divide(SDModel* model);

		ALightCreator::Mesh* Build(bool weld = false);
	};
}