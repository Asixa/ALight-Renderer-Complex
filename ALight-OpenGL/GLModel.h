#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include <iostream>
#include <vector>
#include "../ALightCreator/Model.h"
#include "GLShader.h"
#include "GLMesh.h"


namespace ALight_OpenGL {
	unsigned static  int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
	
	class GLModel
	{
	public:
		Model* origin;
		std::vector<GLMesh> meshes;

		explicit GLModel(Model* m)
		{
			origin = m;
			
			for (auto& mesh : origin->meshes)meshes.push_back(GLMesh(&mesh));
		}

		void Draw(GLShader shader)
		{
			for (auto& mesh : meshes)mesh.Draw(shader);
		}
	};

}
#endif