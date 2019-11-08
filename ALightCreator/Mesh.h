#pragma once
#include "Texture.h"
#include "Vertex.h"
#include <vector>
#include <iostream>
#include "SubdivisionModifier.h"

#include <glm/glm.hpp>
#include "Engine.h"


namespace ALightCreator
{
	static int LOD = 0;
	class Mesh {
	public:

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		//static int LOD;
		std::vector<int> texturesID;

		Mesh(){}
		Mesh(std::vector<Vertex> vs, std::vector<unsigned int> is, std::vector<int> tid)
		{
			this->vertices = vs;
			this->indices = is;
			this->texturesID = tid;

			//Subdivided();
			printf("Model Loaded: triangles: %d, vertices: %d\n", indices.size(), vertices.size());
			
			
			if (LOD != 0)Subdivided(LOD);
			RecalculateNormal();
			LOD++;
		}

		void RecalculateNormal()
		{
			for (auto v : vertices)v.Normal.x = v.Normal.y = v.Normal.z = 0;
			for (int i=0;i<indices.size();i+=3)
			{
				auto normal = glm::cross(vertices[i + 1].Position - vertices[i].Position, vertices[i + 2].Position - vertices[i].Position);
				vertices[i].Normal = normal;
				vertices[i+1].Normal = normal;
				vertices[i+2].Normal = normal; 
			}
			for (auto v : vertices)
			{
				v.Normal = glm::normalize(v.Normal);
				//printf("[%f,%f,%f  - %f] \n", v.Normal.x, v.Normal.y, v.Normal.z,glm::length(v.Normal));
			}
		}

		Vertex Mid(Vertex& a, Vertex& b)
		{
			return { (a.Position + b.Position) / 2.0f,
				(a.Normal + b.Normal) / 2.0f,
				(a.TexCoords + b.TexCoords) / 2.0f,
				(a.Tangent + b.Tangent) / 2.0f };
		}



		
		void Subdivided(int detail)
		{
			auto result =
				SubDiv::SubdivisionModifier::
				Subdivide(SubDiv::SubdivisionModifier::Weld(this, 1.401298E-45, 6), detail);

			this->indices = result->indices;
			this->vertices = result->vertices;
			printf("[vertices %d - indices %d]\n", vertices.size(), indices.size());
			//RecalculateNormal();

			return;
			std::vector<unsigned int> new_indices;
			for (int i = 0; i < indices.size(); i += 3)
			{
				int a = vertices.size();
				vertices.push_back(Mid(vertices[i], vertices[i + 1]));
				
				int b = vertices.size();
				
				vertices.push_back(Mid(vertices[i + 1], vertices[i + 2]));

				
				int c = vertices.size();
				vertices.push_back(Mid(vertices[i + 2], vertices[i]));


				
				new_indices.push_back(i);
				new_indices.push_back(a);
				new_indices.push_back(c);
				
				new_indices.push_back(a);
				new_indices.push_back(i+1);
				new_indices.push_back(b);
				
				
				new_indices.push_back(c);
				new_indices.push_back(b);
				new_indices.push_back(i + 2);
				
				new_indices.push_back(a);
				new_indices.push_back(b);
				new_indices.push_back(c);

			}
		
			this->indices = new_indices;
			
		}
		
	};
	
	
     
}
