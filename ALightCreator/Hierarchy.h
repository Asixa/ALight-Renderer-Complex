#pragma once
#include "Panel.h"

namespace ALightCreator {
	class Object;
	class Transform;

	class Hierarchy final :public Panel
	{

		void DrawTransform(Object* t);
	public:
		void Render() override;
	};
}