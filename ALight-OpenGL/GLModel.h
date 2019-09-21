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
#include <map>
#include <vector>
#include "../ALightCreator/Model.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMesh.h"


namespace ALight_OpenGL {
	unsigned static  int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
	
	class GLModel
	{
	public:
		/*  Model Data */
		Model* model;
		std::vector<GLTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		std::vector<GLMesh> meshes;

		explicit GLModel(Model* m)
		{
			model = m;
			for (auto& mesh : model->meshes)meshes.push_back(GLMesh(&mesh));
			//LoadMaterialTextures();
		}

		// draws the model, and thus all its meshes
		void Draw(GLShader shader)
		{
			for (auto& mesh : meshes)mesh.Draw(shader);
		}


		// checks all material textures of a given type and loads the textures if they're not loaded yet.
		// the required info is returned as a Texture struct.
		void LoadMaterialTextures()
		{
			for (auto mesh : meshes)
			{
				for (unsigned int i = 0; i < mesh.textures.size(); i++)
				{


					bool skip = false;
					for (auto& j : textures_loaded)
					{
						if (std::strcmp(j.texture->path.c_str(), mesh.textures[i].texture->path.c_str()) == 0)
						{
							textures.push_back(j);
							skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
							break;
						}
					}
					if (!skip)
					{

						mesh.

						// if texture hasn't been loaded already, load it
						Texture texture(str.C_Str(), this->directory, false);
						//texture.id = TextureFromFile(str.C_Str(), this->directory, false);
						texture.type = typeName;
						texture.path = str.C_Str();
						textures.push_back(texture);
						textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
					}
				}
				return textures;
			}
			for (auto& i : model->textures_loaded)textures_loaded.emplace_back(&i);
		}
	};

}
#endif