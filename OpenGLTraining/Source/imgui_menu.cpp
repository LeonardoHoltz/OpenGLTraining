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
    menuData.render_mode = Solid;
    menuData.lightIntensity = glm::vec3(1.0f, 1.0f, 1.0f);
    menuData.shininess = 30;
    menuData.isLightAttenuationOn = false;
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
        ImGui::RadioButton("Solid", &menuData.render_mode, Solid); ImGui::SameLine();
        ImGui::RadioButton("Wireframe", &menuData.render_mode, Wireframe); ImGui::SameLine();
        ImGui::RadioButton("Points", &menuData.render_mode, Points);
        ImGui::TreePop();
    }
}

void ImguiMenu::LightningContent() {
    if (ImGui::TreeNode("Lightning")) {
        ImGui::SliderInt("Shininess", &menuData.shininess, 1, 50);

        ImGui::PushItemWidth(60.0f);
        ImGui::Text("Light position:"); ImGui::SameLine();
        ImGui::InputFloat("x", &menuData.lightPos.x); ImGui::SameLine();
        ImGui::InputFloat("y", &menuData.lightPos.y); ImGui::SameLine();
        ImGui::InputFloat("z", &menuData.lightPos.z);
        ImGui::PopItemWidth();

        ImGui::Text("Light Intensity:");
        ImGui::ColorEdit4("", &menuData.lightIntensity.r, ImGuiColorEditFlags_PickerHueWheel);
        

        ImGui::Text("Light Attenuation:");
        ImGui::Checkbox("On / Off", &menuData.isLightAttenuationOn);


        ImGui::TreePop();
    }
}


















