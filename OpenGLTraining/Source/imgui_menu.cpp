#include "../Headers/imgui_menu.h"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"

#include "glm/vec3.hpp"

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
    menu_data.render_mode = Solid;

    menu_data.light_intensity = glm::vec3(1.0f, 1.0f, 1.0f);
    menu_data.shininess = 30;
}

void ImguiMenu::CreateFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiMenu::DefineFrameContent(float fps) {
    ImGui::Begin("Test");
    ImGui::Text("FPS: %.1f", fps);
    RenderingModeContent();
    LightningContent();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImguiMenu::~ImguiMenu() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImguiMenu::RenderingModeContent() {
    if (ImGui::TreeNode("Rendering Mode")) {
        ImGui::RadioButton("Solid", &menu_data.render_mode, Solid); ImGui::SameLine();
        ImGui::RadioButton("Wireframe", &menu_data.render_mode, Wireframe); ImGui::SameLine();
        ImGui::RadioButton("Points", &menu_data.render_mode, Points);
        ImGui::TreePop();
    }
}

void ImguiMenu::LightningContent() {
    if (ImGui::TreeNode("Lightning")) {
        ImGui::SliderInt("Shininess", &menu_data.shininess, 1, 50);

        ImGui::PushItemWidth(60.0f);
        ImGui::Text("Light position:"); ImGui::SameLine();
        ImGui::InputFloat("x", &menu_data.light_pos.x); ImGui::SameLine();
        ImGui::InputFloat("y", &menu_data.light_pos.y); ImGui::SameLine();
        ImGui::InputFloat("z", &menu_data.light_pos.z);
        ImGui::PopItemWidth();

        ImGui::Text("Light Intensity:");
        ImGui::ColorEdit4("", &menu_data.light_intensity.r, ImGuiColorEditFlags_PickerHueWheel);
        ImGui::TreePop();
    }
}


















