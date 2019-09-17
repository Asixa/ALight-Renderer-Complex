#pragma once
namespace ALightCreator {
	class  Transform;
	class  Object;
	class  Component
	{
	public:
		Transform* transform;
		Object* object;
		virtual void Start() {}
		virtual void Update() {}
		virtual void Renderer() {}
	};
}