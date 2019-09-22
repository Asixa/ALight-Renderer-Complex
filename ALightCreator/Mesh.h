#pragma once
#include "Texture.h"
#include "Vertex.h"
#include <vector>


namespace ALightCreator
{
	class Mesh {
	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<int> texturesID;
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<int> tid)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->texturesID = tid;
		}
	};
}
