#include "../Headers/imgui_menu.h"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"

ImguiMenu::ImguiMenu(GLFWwindow* window) {
    // Setup Dear ImGui context:
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    DefineDefaultMenuData();
}

void ImguiMenu::DefineDefaultMenuData() {
    menu_data.triangle_color = { 1.0f, 1.0f, 1.0f, 1.0f};
}

void ImguiMenu::CreateFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiMenu::DefineFrameContent() {
    ImGui::Begin("Test");
    ImGui::Text("This is a test");
    ImGui::ColorEdit4("Triangle color", &menu_data.triangle_color.r, ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImguiMenu::~ImguiMenu() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


















