#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Resource.h"

namespace  ALightCreator {
	class Model
	{
	public:
	
		std::vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;

		/*  Functions   */
		// constructor, expects a filepath to a 3D model.
		Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
		{
			loadModel(path);
			
		}

		void Subdivied(int detail)
		{
			for (auto m : meshes)m.Subdivided(detail);
		}

	private:
		/*  Functions   */
		// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(std::string const& path)
		{
			// read file via ASSIMP
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
			// check for errors
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
				return;
			}
			// retrieve the directory path of the filepath
			directory = path.substr(0, path.find_last_of('/'));
		
			// process ASSIMP's root node recursively
			processNode(scene->mRootNode, scene);
		}

		// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		void processNode(aiNode* node, const aiScene* scene)
		{
			for (unsigned int i = 0; i < node->mNumMeshes; i++)meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
			for (unsigned int i = 0; i < node->mNumChildren; i++)processNode(node->mChildren[i], scene);
		}

		Mesh processMesh(aiMesh* mesh, const aiScene* scene)
		{
			
			// data to fill
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<int> textures;

			// Walk through each of the mesh's vertices
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				ALightCreator::Vertex vertex;
				glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
				// positions
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.Position = vector;
				// normals
				if(mesh->mNormals == nullptr)vector = glm::vec3(1);
				else if (mesh->mNormals->Length() < i)vector = glm::vec3(1);
				else
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
				}
				vertex.Normal = vector;
				// texture coordinates
				if (mesh->mTextureCoords == nullptr)vector = glm::vec3(1);
				else if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					glm::vec2 vec;
					// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.TexCoords = vec;
				}
				else vertex.TexCoords = glm::vec2(0.0f, 0.0f);
				// tangent
				
				if (mesh->mTangents == nullptr)vector = glm::vec3(1);
				else if (mesh->mTangents->Length() < i)vector = glm::vec3(1);
				else {
					vector.x = mesh->mTangents[i].x;
					vector.y = mesh->mTangents[i].y;
					vector.z = mesh->mTangents[i].z;
				}
				vertex.Tangent = vector;
				// bitangent
				if (mesh->mBitangents == nullptr)vector = glm::vec3(1);
				else if (mesh->mBitangents->Length() < i)vector = glm::vec3(1);
				else {
					vector.x = mesh->mBitangents[i].x;
					vector.y = mesh->mBitangents[i].y;
					vector.z = mesh->mBitangents[i].z;
				}
				vertex.Bitangent = vector;
				vertices.push_back(vertex);
			}
			// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
			// process materials
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// diffuse: texture_diffuseN
			// specular: texture_specularN
			// normal: texture_normalN
	
			// 1. diffuse maps
			std::vector<int> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			std::vector<int> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. normal maps
			std::vector<int> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. height maps
			std::vector<int> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
			// return a mesh object created from the extracted mesh data
		
			return Mesh(vertices, indices, textures);
		}

		// checks all material textures of a given type and loads the textures if they're not loaded yet.
		// the required info is returned as a Texture struct.
		std::vector<int> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
		{
		
			std::vector<int> texturesID;

			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
				bool skip = false;

				for (int j=0;j<Resource::GetInstance().textures.size();j++)
				{

					if (std::strcmp(Resource::GetInstance().textures[j]->path.c_str(), str.C_Str()) == 0)
					{

						texturesID.push_back(j);
						skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
						break;
					}
				}
				if (!skip)
				{   // if texture hasn't been loaded already, load it
	
					auto texture=new Texture(str.C_Str(), this->directory, false);
					int id =  Resource::GetInstance().textures.size();
					//Resource::GetInstance().textures.push_back(texture);
					//texture.id = TextureFromFile(str.C_Str(), this->directory, false);
					texture->type = typeName;
					texture->path = str.C_Str();
					texturesID.push_back(id);
					Resource::GetInstance().textures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
				}
			}
			return texturesID;
		}
	};
}
