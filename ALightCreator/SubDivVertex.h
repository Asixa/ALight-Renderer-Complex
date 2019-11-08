#pragma once
#include "Vertex.h"
#include <vector>


namespace SubDiv{
class Triangle;
class Edge;
class SDVertex
{
public:
	ALightCreator::Vertex* p;
	SDVertex* updated;
	std::vector<Edge*>edges;
	std::vector<Triangle*>triangles;
	int index;
	SDVertex(ALightCreator::Vertex* p, int index);


	void AddEdge(Edge* e);


	void AddTriangle(Triangle* f);
};
}
