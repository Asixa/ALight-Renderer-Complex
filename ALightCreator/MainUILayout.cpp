#include "MainUILayout.h"
#include "GLRenderer.h"
#include "Viewport.h"
#include "Project.h"
#include "Property.h"
#include "Hierarchy.h"
#include "Output.h"
#define  MenuBarHeight 20
#define  ToolBarHeight 32

MainUILayout::MainUILayout()
{
}

void MainUILayout::Init()
{
	panels.push_back(new Viewport(new GLRenderer()));
	panels.push_back(new Project());
	panels.push_back(new Property());
	panels.push_back(new Hierarchy());
	panels.push_back(new Output());
}
void ToolBar()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(60 / 255.0f, 60 / 255.0f, 60 / 255.0f, 1));
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y+20));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, ToolBarHeight));
	ImGui::SetNextWindowBgAlpha(1);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGuiWindowFlags window_flags = 
		ImGuiWindowFlags_NoScrollWithMouse
	| ImGuiWindowFlags_AlwaysAutoResize
	| ImGuiWindowFlags_NoScrollbar
	| ImGuiWindowFlags_NoTitleBar
	| ImGuiWindowFlags_NoCollapse
	| ImGuiWindowFlags_NoResize
	| ImGuiWindowFlags_NoMove
	| ImGuiWindowFlags_NoDocking
	//| ImGuiWindowFlags_NoBackground
	| ImGuiWindowFlags_NoNav
	;
	
	ImGui::Begin("233", nullptr,window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	auto CursorY = ImGui::GetCursorPosY();
	ImGui::SetCursorPos(ImVec2(10, CursorY ));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
	ImGui::Button(" ", ImVec2(30, 25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY));
	ImGui::Button(" ",ImVec2(30,25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY));
	ImGui::Button(" ",ImVec2(30,25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY));
	ImGui::Button(" ",ImVec2(30,25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY));
	ImGui::Button(" ",ImVec2(30,25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY));
	ImGui::Button(" ",ImVec2(30,25));ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() +30), CursorY+2));

	ImGui::Button(" ", ImVec2(50, 20)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY+2));
	ImGui::Button(" ", ImVec2(50, 20)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), CursorY));
	
	ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 30) * 0.5f - 30,  ImGui::GetCursorPosY()));
	ImGui::Button(" ", ImVec2(30, 25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), ImGui::GetCursorPosY()));
	ImGui::Button(" ", ImVec2(30, 25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), ImGui::GetCursorPosY()));
	ImGui::Button(" ", ImVec2(30, 25)); ImGui::SameLine(); ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPosX() - 5), ImGui::GetCursorPosY()));


	ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 300), ImGui::GetCursorPosY()));
	static int currentLayer; 
	static int currentLayout;
	ImGui::SetNextItemWidth(100);
	ImGui::Combo("", &currentLayer, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
	ImGui::Combo("", &currentLayout, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");


	
	ImGui::PopStyleVar();
	ImGui::End();

	
}
void MainUILayout::Render()
{
	MenuBar();
	ToolBar();
	DockingSpace(nullptr);
	if (show_demo_window)ImGui::ShowDemoWindow(&show_demo_window);
	for (auto element : panels)element->Render();
}

void MainUILayout::Terminate()
{
	for (auto element : panels)
	{
		element->Terminate();
		free(element);
	}
}

void Separator()
{
	ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
}

void MainUILayout::MenuBar() const
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(60 / 255.0f, 60 / 255.0f, 60 / 255.0f, 1));
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
			if (ImGui::MenuItem("Open Scene", "CTRL+O")) {}
			Separator();
			if (ImGui::MenuItem("Save Scene", "CTRL+S")) {}
			if (ImGui::MenuItem("Save Scene as...", "CTRL+SHIFT+Z")) {}
			Separator();
			if (ImGui::MenuItem("New Project" )) {}
			if (ImGui::MenuItem("Open Project" )) {}
			if (ImGui::MenuItem("Close Project")) {}
			Separator();
			if (ImGui::MenuItem("Build Settings", "CTRL+SHIFT+B")) {}
			if (ImGui::MenuItem("Build & Run", "CTRL+B")) {}
			Separator();
			if (ImGui::MenuItem("Exit")) {}
			//MenuItem();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			Separator();
			if (ImGui::MenuItem("Duplicate", "CTRL+D")) {}
			if (ImGui::MenuItem("Delete", "SHIFT+DEL")) {}
			Separator();
			if (ImGui::MenuItem("Frame Selected", "F")) {}
			if (ImGui::MenuItem("Find", "CTRL+F")) {}
			if (ImGui::MenuItem("Select All", "CTRL+A")) {}
			Separator();
			if (ImGui::MenuItem("Preferences")) {}
			Separator();
			if (ImGui::MenuItem("Play", "CTRL+P")) {}
			if (ImGui::MenuItem("Pause", "CTRL+SHIFT+P")) {}
			if (ImGui::MenuItem("Step", "CTRL+ALT+P")) {}
			Separator();
			if (ImGui::MenuItem("Load Selections")) {}
			if (ImGui::MenuItem("Save Selections")) {}
			Separator();
			if (ImGui::BeginMenu("Project Settings"))
			{
				if (ImGui::MenuItem("Input")) {}
				if (ImGui::MenuItem("Tag")) {}
				if (ImGui::MenuItem("Audio")) {}
				if (ImGui::MenuItem("Time")) {}
				if (ImGui::MenuItem("Player")) {}
				if (ImGui::MenuItem("Physics")) {}
				if (ImGui::MenuItem("Quality")) {}
				if (ImGui::MenuItem("Network")) {}
				if (ImGui::MenuItem("Editor")) {}
				if (ImGui::MenuItem("Script Execution Order")) {}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Render Setting")) {}
			Separator();
			if (ImGui::BeginMenu("Network Emulation"))
			{
				if (ImGui::MenuItem("None")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Graphics Emulation"))
			{
				if (ImGui::MenuItem("No Emulation")) {}
				ImGui::EndMenu();
			}
			Separator();
			if (ImGui::MenuItem("Snap Setting")) {}
			ImGui::EndMenu();
		}

		
		if (ImGui::BeginMenu("Assets"))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Folder")) {}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Show in Explorer")) {}
			if (ImGui::MenuItem("Open")) {}
			if (ImGui::MenuItem("Delete")) {}
			Separator();
			if (ImGui::MenuItem("Import New Asset...")) {}
			if (ImGui::MenuItem("Import Package")) {}
			if (ImGui::MenuItem("Export Package")) {}
			if (ImGui::MenuItem("Select Dependencies")) {}
			if (ImGui::MenuItem("Export compressed audio file",0,false,false)) {}
			Separator();
			if (ImGui::MenuItem("Refresh")) {}
			if (ImGui::MenuItem("Reimport")) {}
			Separator();
			if (ImGui::MenuItem("Reimport All")) {}
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("GameObject"))
		{
			if (ImGui::MenuItem("Create Empty","CTRL+SHIFT+N")) {}
			if (ImGui::BeginMenu("Create Other"))
			{
				if (ImGui::MenuItem("Camera")) {}
				Separator();
				if (ImGui::MenuItem("Directional Light")) {}
				if (ImGui::MenuItem("Point Light")) {}
				if (ImGui::MenuItem("Spot Light")) {}
				Separator();
				if (ImGui::MenuItem("Cube")) {}
				if (ImGui::MenuItem("Sphere")) {}
				if (ImGui::MenuItem("Capsule")) {}
				if (ImGui::MenuItem("Cylinder")) {}
				if (ImGui::MenuItem("Plane")) {}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Center On Children", nullptr, false, false)) {}
			Separator();
			if (ImGui::MenuItem("Make Parent", nullptr, false, false)) {}
			if (ImGui::MenuItem("Clear Parent", nullptr, false, false)) {}
			if (ImGui::MenuItem("Apply Changes To Prefab", nullptr, false, false)) {}
			Separator();
			if (ImGui::MenuItem("Move To View", "CTRL+ALT+F")) {}
			if (ImGui::MenuItem("Align With View", "CTRL+SHIFT+F")) {}
			if (ImGui::MenuItem("Align View to Selected")) {}
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Component"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Scene", "CTRL+1")) {}
			if (ImGui::MenuItem("Game", "CTRL+2")) {}
			if (ImGui::MenuItem("Inspector", "CTRL+3")) {}
			if (ImGui::MenuItem("Hierarchy", "CTRL+4")) {}
			if (ImGui::MenuItem("Project", "CTRL+5")) {}
			if (ImGui::MenuItem("Animation", "CTRL+6")) {}
			if (ImGui::MenuItem("Profiler", "CTRL+7")) {}
			Separator();
			if (ImGui::MenuItem("LightMapping", "CTRL+8")) {}
			if (ImGui::MenuItem("Occlusion Culling", "CTRL+9")) {}
			if (ImGui::MenuItem("Console", "CTRL+0")) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About ALight Creator")) {}
			ImGui::EndMenu();
		}
		ImGui::NewLine();
		if (ImGui::BeginMenu("Help2")){}
		ImGui::EndMainMenuBar();

	}

}

void MainUILayout::MenuItem() const
{

	ImGui::MenuItem("(dummy menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				//ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}
	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		static bool b = true;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::Checkbox("Check", &b);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Colors"))
	{
		float sz = ImGui::GetTextLineHeight();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			ImVec2 p = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			ImGui::Dummy(ImVec2(sz, sz));
			ImGui::SameLine();
			ImGui::MenuItem(name);
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {}

}

void MainUILayout::DockingSpace(bool* p_open) const
{
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None ^ ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags =  ImGuiWindowFlags_NoDocking;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + ToolBarHeight+20));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - ToolBarHeight));
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


	ImGui::Begin("DockSpace Demo", p_open, window_flags);
	ImGui::PopStyleVar(2);
	if (opt_fullscreen)
		ImGui::PopStyleVar(1);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		// ShowDockingDisabledMessage();
	}

	// if (ImGui::BeginMenuBar())
	// {
	// 	if (ImGui::BeginMenu("Docking"))
	// 	{
	// 		// Disabling fullscreen would allow the window to be moved to the front of other windows, 
	// 		// which we can't undo at the moment without finer window depth/z control.
	// 		//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
	//
	// 		if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
	// 		if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
	// 		if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
	// 		if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
	// 		if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
	// 		ImGui::Separator();
	// 		if (ImGui::MenuItem("Close DockSpace", NULL, false, p_open != NULL))
	// 			* p_open = false;
	// 		ImGui::EndMenu();
	// 	}
	// 	// HelpMarker(
	// 	// 	"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n\n"
	// 	// 	" > if io.ConfigDockingWithShift==false (default):" "\n"
	// 	// 	"   drag windows from title bar to dock" "\n"
	// 	// 	" > if io.ConfigDockingWithShift==true:" "\n"
	// 	// 	"   drag windows from anywhere and hold Shift to dock" "\n\n"
	// 	// 	"This demo app has nothing to do with it!" "\n\n"
	// 	// 	"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
	// 	// 	"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
	// 	// 	"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
	// 	// );
	//
	// 	ImGui::EndMenuBar();
	// }
	
	ImGui::End();
}
