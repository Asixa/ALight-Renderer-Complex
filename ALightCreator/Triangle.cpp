#include "Triangle.h"

SubDiv::SDVertex* SubDiv::Triangle::GetOtherVertex(Edge* e)
{
	if (!e->Has(v0)) return v0;
	else if (!e->Has(v1)) return v1;
	return v2;
}