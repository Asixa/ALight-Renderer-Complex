#include "SubDivModel.h"
#include "Edge.h"
#include "Triangle.h"
#include "Mesh.h"
SubDiv::SDModel::SDModel(ALightCreator::Mesh* source)
{

	for (int i = 0; i < source->vertices.size(); i++)
	{
		// printf("[%f,%f,%f]\n", points[i].Position.x, points[i].Position.y, points[i].Position.z);
		
		auto v = new SDVertex(&source->vertices[i], i);
		//printf("[%f,%f,%f]\n",v->p->Position.x, v->p->Position.y, v->p->Position.z);
		vertices.push_back(v);
	}


	for (int i = 0, n = source->indices.size(); i < n; i += 3)
	{
		int i0 = source->indices[i], i1 = source->indices[i + 1], i2 = source->indices[i + 2];
		SDVertex *v0 = vertices[i0], *v1 = vertices[i1], *v2 = vertices[i2];

		auto e0 = GetEdge(v0, v1);
		auto e1 = GetEdge(v1, v2);
		auto e2 = GetEdge(v2, v0);
		auto f = new Triangle(v0, v1, v2, e0, e1, e2);

		this->triangles.push_back(f);
		v0->AddTriangle(f); v1->AddTriangle(f); v2->AddTriangle(f);
		e0->AddTriangle(f); e1->AddTriangle(f); e2->AddTriangle(f);
	}

	printf("Model Build: triangles: %d, vertices: %d\n", triangles.size(), vertices.size());
}

// SubDiv::Edge* SubDiv::SDModel::GetEdge(std::vector<Edge*> edges, SDVertex* v0, SDVertex* v1)
// {
//
// 	Edge* match=nullptr;
// 	for (auto e : v0->edges)
// 	{
// 		if(e->Has(v1))
// 		{
// 			match = e;
// 			break;
// 		}
// 	}
// 	if (match != nullptr) return match;
//
// 	const auto ne = new Edge(v0, v1);
// 	v0->AddEdge(ne);
// 	v1->AddEdge(ne);
// 	edges.push_back(ne);
// 	return ne;
// }

void SubDiv::SDModel::AddTriangle(SDVertex* v0, SDVertex* v1, SDVertex* v2)
{
	if(std::find(vertices.begin(),vertices.end(),v0)==vertices.end())vertices.push_back(v0);
	if(std::find(vertices.begin(),vertices.end(),v1)==vertices.end())vertices.push_back(v1);
	if(std::find(vertices.begin(),vertices.end(),v2)==vertices.end())vertices.push_back(v2);


	auto e0 = GetEdge(v0, v1);
	auto e1 = GetEdge(v1, v2);
	auto e2 = GetEdge(v2, v0);
	auto f = new Triangle(v0, v1, v2, e0, e1, e2);

	triangles.push_back(f);
	v0->AddTriangle(f); v1->AddTriangle(f); v2->AddTriangle(f);
	e0->AddTriangle(f); e1->AddTriangle(f); e2->AddTriangle(f);
}

SubDiv::Edge* SubDiv::SDModel::GetEdge(SDVertex* v0, SDVertex* v1)
{
	Edge* match=nullptr;
	for (auto e : v0->edges)
	{
		if (e->Has(v1))
		{
			match = e;
			break;
		}
	}
	if (match != nullptr) return match;

	const auto ne = new Edge(v0, v1);
	v0->AddEdge(ne);
	v1->AddEdge(ne);
	edges.push_back(ne);
	return ne;
}

ALightCreator::Mesh* SubDiv::SDModel::Build(bool weld)
{
	auto mesh = new ALightCreator::Mesh();
	//auto triangles = new int[this->triangles.size() * 3];
	std::vector<unsigned> is;


	std::vector<ALightCreator::Vertex>vertices;
	for (int i = 0, n = this->triangles.size(); i < n; i++)
	{
		auto f = this->triangles[i];
		int i0 = i * 3, i1 = i * 3 + 1, i2 = i * 3 + 2;
		//printf("[%f,%f,%f]\n", f->v0->p->Position.x, f->v0->p->Position.y, f->v0->p->Position.z);
		vertices.push_back(*f->v0->p);
		vertices.push_back(*f->v1->p);
		vertices.push_back(*f->v2->p);
		is.push_back(i0);
		is.push_back(i1);
		is.push_back(i2);
	}
	mesh->vertices = vertices;

	
	mesh->indices = is;


	return mesh;
}





