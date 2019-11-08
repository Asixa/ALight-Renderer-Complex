#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


namespace ALightCreator
{


	struct Vertex {

		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;

		inline Vertex* operator+(Vertex a) {
			return new Vertex{ a.Position + Position,
				a.Normal + Normal,
			a.TexCoords+TexCoords,
			a.Tangent+Tangent,
			a.Bitangent+Bitangent};
		}
		inline Vertex  operator-(Vertex a) {
			return { Position-a.Position ,
				Normal-a.Normal,
			 TexCoords-a.TexCoords,
			Tangent-a.Tangent,
			 Bitangent-a.Bitangent };
		}
		inline void operator+=(Vertex a) {
			Position+=a.Position;
			Normal += a.Normal;
			TexCoords += a.TexCoords;
			Tangent += a.Tangent;
			Bitangent += a.Bitangent;
		}
		
		inline Vertex* operator*(float v) {
			return new Vertex{ Position*v,
				Normal* v,
			TexCoords* v,
		Tangent* v,
			Bitangent* v };
		}
	};
}
