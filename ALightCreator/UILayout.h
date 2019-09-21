#pragma once
#include "imgui/imgui.h"
namespace ALightCreator {
	class UILayout
	{
	public:

		virtual void Init() {}
		virtual void Render() {};
		virtual void Terminate() {};
	};
}