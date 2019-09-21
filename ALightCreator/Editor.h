#pragma once
#include "imgui/imgui.h"
#include "Gizmo/ImGuizmo.h"
struct ImVec2;

namespace ALightCreator
{
	class  Editor
	{
	public:
		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		bool useSnap = false;
		float snap[3] = { 1.f, 1.f, 1.f };
		float bounds[6] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
		float boundsSnap[3] = { 0.1f, 0.1f, 0.1f };
		bool boundSizing = false;
		bool boundSizingSnap = false;
		static ImGuizmo::OPERATION mCurrentGizmoOperation;
		static ImGuizmo::MODE mCurrentGizmoMode;
		static Editor& GetInstance() { static Editor instance; return instance; }
		void EditTransform(const float* cameraView, float* cameraProjection, float* matrix, ImVec2 size);
	};


}