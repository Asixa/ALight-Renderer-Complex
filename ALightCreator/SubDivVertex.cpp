#include "SubDivVertex.h"

SubDiv::SDVertex::SDVertex(ALightCreator::Vertex* p, int index)
{
	this->p = p;
	this->index = index;

}
void SubDiv::SDVertex::AddEdge(Edge* e)
{
	edges.push_back(e);
}
void SubDiv::SDVertex::AddTriangle(Triangle* f)
{
	triangles.push_back(f);
}
