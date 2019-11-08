#include "SubdivisionModifier.h"
#include "Edge.h"
#include "Triangle.h"
#include "SubDivModel.h"
#include "Mesh.h"
#include <unordered_map>
#include <map>

ALightCreator::Mesh* SubDiv::SubdivisionModifier::Subdivide(ALightCreator::Mesh* source, int details, bool weld)
{
	auto model = MSubdivide(source, details);

	auto mesh = model->Build(weld);
	return mesh;
}

SubDiv::SDModel* SubDiv::SubdivisionModifier::MSubdivide(ALightCreator::Mesh* source, int details)
{
	auto model = new SDModel(source);
	for (int i = 0; i < details; i++)model =Divide(model);
	return model;
}

SubDiv::SDModel* SubDiv::SubdivisionModifier::Divide(SDModel* model)
{
	auto nmodel = new SDModel();
	for (int i = 0, n = model->triangles.size(); i < n; i++)
	{
		auto f = model->triangles[i];

		auto ne0 = GetEdgePoint(f->e0);
		auto ne1 = GetEdgePoint(f->e1);
		auto ne2 = GetEdgePoint(f->e2);

		auto nv0 = GetVertexPoint(f->v0);
		auto nv1 = GetVertexPoint(f->v1);
		auto nv2 = GetVertexPoint(f->v2);

		nmodel->AddTriangle(nv0, ne0, ne2);
		nmodel->AddTriangle(ne0, nv1, ne1);
		nmodel->AddTriangle(ne0, ne1, ne2);
		nmodel->AddTriangle(ne2, ne1, nv2);
	}
	return nmodel;
}
int Myfloor(float v)
{
	if (v > 0)return (int)v;
	else return (int)(v );
}
ALightCreator::Mesh* SubDiv::SubdivisionModifier::Weld(ALightCreator::Mesh* mesh, float threshold, float bucketStep)
{
	auto oldVertices = mesh->vertices;
	std::vector<ALightCreator::Vertex> newVertices;
	std::vector<unsigned> old2new;
	int newSize = 0;

	// Find AABB
	glm::vec3 min =glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	glm::vec3 max = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
	for (int i = 0; i < oldVertices.size(); i++)
	{
		if (oldVertices[i].Position.x < min.x) min.x = oldVertices[i].Position.x;
		if (oldVertices[i].Position.y < min.y) min.y = oldVertices[i].Position.y;
		if (oldVertices[i].Position.z < min.z) min.z = oldVertices[i].Position.z;
		if (oldVertices[i].Position.x > max.x) max.x = oldVertices[i].Position.x;
		if (oldVertices[i].Position.y > max.y) max.y = oldVertices[i].Position.y;
		if (oldVertices[i].Position.z > max.z) max.z = oldVertices[i].Position.z;
	}

	// Make cubic buckets, each with dimensions "bucketStep"
	int bucketSizeX = Myfloor((max.x - min.x) / bucketStep) + 1;
	int bucketSizeY = Myfloor((max.y - min.y) / bucketStep) + 1;
	int bucketSizeZ = Myfloor((max.z - min.z) / bucketStep) + 1;
	
	//std::vector<std::vector<std::vector<std::vector<int>>>> buckets;

	//std::vector<int>* buckets[3][3][3];
	// for (int i=0;i<bucketSizeX;i++)
	// {
	// 	std::vector< std::vector<std::vector<int>>> a;
	// 	buckets.push_back(a);
	// 	for (int j=0;j<bucketSizeY;j++)
	// 	{
	// 		std::vector<std::vector<int>> b;
	// 		buckets[i].push_back(b);
	// 		for (int k=0;k<bucketSizeZ;k++)
	// 		{
	// 			std::vector<int> c;
	// 			buckets[i][j].push_back(c);
	// 		}
	// 	}
	// }
	

	std::map<kk, std::vector<int>> buckets;
	
	for (int i = 0; i < oldVertices.size(); i++)
	{
		// Determine which bucket it belongs to
		int x = Myfloor((oldVertices[i].Position.x - min.x) / bucketStep);
		int y = Myfloor((oldVertices[i].Position.y - min.y) / bucketStep);
		int z = Myfloor((oldVertices[i].Position.z - min.z) / bucketStep);

		// Check to see if it's already been added

		
		if (buckets.find(std::make_tuple(x, y, z)) == buckets.end()) buckets[std::make_tuple(x, y, z)] =std::vector<int>(); // Make buckets lazily
		
		
		
		for (int j = 0; j < buckets[std::make_tuple(x, y, z)].size(); j++)
		{
			
			ALightCreator::Vertex to = newVertices[buckets[std::make_tuple(x, y, z)][j]] - oldVertices[i];
			if (pow(glm::length(to.Position),2) < threshold)
			{
				old2new.push_back(buckets[std::make_tuple(x, y, z)][j]);
				goto skip; 
			}
		}

		
		newVertices.push_back(oldVertices[i]); 
		buckets[std::make_tuple(x, y, z)].push_back(newSize);
		old2new.push_back(newSize);
		newSize++;

	skip:;
	}

	// Make new triangles




	
	std::vector<unsigned>newTris;
	newTris.reserve(mesh->indices.size());
	for (auto i = 0; i < mesh->indices.size(); i++)
		newTris.push_back(old2new[mesh->indices[i]]);
	

	std::vector<ALightCreator::Vertex> finalVertices;
	for (auto i = 0; i < newSize; i++)finalVertices.push_back(newVertices[i]);
	
	auto m = new ALightCreator::Mesh();
	m->vertices = finalVertices;
	m->indices = newTris;

	return m;
}


SubDiv::SDVertex* SubDiv::SubdivisionModifier::GetEdgePoint(Edge* e)
{
	if (e->ept != nullptr) return e->ept;

	if (e->faces.size() != 2) {
		// boundary case for edge
		auto m = *(*e->a->p + *e->b->p) * 0.5f;
		e->ept = new SDVertex(m, e->a->index);
	}
	else
	{
		const float alpha = 3.0f / 8.0f;
		const float beta = 1.0f / 8.0f;
		auto left = e->faces[0]->GetOtherVertex(e);
		auto right = e->faces[1]->GetOtherVertex(e);
		e->ept = new SDVertex(*(*(*e->a->p + *e->b->p) * alpha) + *(*(*left->p + *right->p) * beta), e->a->index);
	}

	return e->ept;
}

SubDiv::SDVertex* SubDiv::SubdivisionModifier::GetVertexPoint(SDVertex* v)
{
	if (v->updated != nullptr) return v->updated;

	auto adjancies = GetAdjancies(v);
	auto n = adjancies.size();
	if (n < 3)
	{
		// boundary case for vertex
		auto e0 = v->edges[0]->GetOtherVertex(v);
		auto e1 = v->edges[1]->GetOtherVertex(v);
		const float k0 = (3.0f / 4.0f);
		const float k1 = (1.0f / 8.0f);
		v->updated = new SDVertex(*(*v->p * k0) +  *(*(*e0->p + *e1->p)* k1), v->index);
	}
	else
	{
		const float pi2 = 3.1415926 * 2.0f;
		const float k0 = (5.0f / 8.0f);
		const float k1 = (3.0f / 8.0f);
		const float k2 = (1.0f / 4.0f);
		auto alpha = (n == 3) ? (3.0f / 16.0f) : ((1.0f / n) * (k0 - pow(k1 + k2 * cos(pi2 / n), 2.0f)));

		auto np =  (*v->p)* (1.0f - n * alpha);

		for (int i = 0; i < n; i++)
		{
			auto adj = adjancies[i];
			*np +=  *(*adj->p* alpha);
		}

		v->updated = new SDVertex(np, v->index);
	}

	return v->updated;
}

std::vector<SubDiv::SDVertex*> SubDiv::SubdivisionModifier::GetAdjancies(SDVertex* v)
{
	std::vector<SubDiv::SDVertex*> adjancies;
	for (int i = 0, n = v->edges.size(); i < n; i++)
	{
		adjancies.push_back(v->edges[i]->GetOtherVertex(v));
	}
	return adjancies;
}
