#include "Edge.h"

SubDiv::Edge::Edge(SDVertex* x, SDVertex* y)
{
	a = x; b = y;
}

void SubDiv::Edge::AddTriangle(Triangle* f)
{
	faces.push_back(f);
}

bool SubDiv::Edge::Has(SDVertex* v)
{
	return v == a || v == b;
}

SubDiv::SDVertex* SubDiv::Edge::GetOtherVertex(SDVertex* v)
{
	if (a != v) return a;
	return b;
}
