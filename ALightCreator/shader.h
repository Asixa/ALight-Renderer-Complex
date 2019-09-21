#pragma once
namespace ALightCreator
{
	class Shader
	{
	public:
		const char* vertexPath = nullptr;
		const char* fragmentPath = nullptr;
		const char* geometryPath = nullptr;
		Shader(const char*v, const char* f, const char* g = nullptr):vertexPath(v),fragmentPath(f),geometryPath(g)
		{
			
		}
	};
}