
// Library includes //
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "ImGuiFileDialog.h"
#include <vec3.hpp>

// Engine includes //
#include "editor.hpp"
#include "graphics.hpp"
#include "model.hpp"
#include "object_manager.hpp"
#include "physics.hpp"
#include "trace.hpp"
#include "transform.hpp"

using namespace glm;

static Editor* editor = nullptr;

bool Editor::Initialize() {
    editor = new Editor;
    if (!editor) {
        Trace::Message("Editor failed to initialize.\n");
        return false;
    }
    editor->selected_object = -1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::GetStyle().WindowRounding = 0.f;
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 1.f;
    }

    ImGui_ImplGlfw_InitForOpenGL(Graphics::GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    return true;
}

void Editor::Update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();
    
    editor->Display_Dockspace();
    editor->Display_Scene();
    editor->Display_Components();
}

void Editor::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Editor::Shutdown() {
    if (!editor) return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete editor;
    editor = nullptr;
}

void Editor::Display_Dockspace() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin("Editor Window", &editor->isOpen, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dockspace_id = ImGui::GetID("Editor");
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    ImGui::End();
}

void Editor::Display_Scene() {
    ImGui::Begin("Scene");

    for (int i = 0; i < Object_Manager::GetSize(); ++i) {
        if (ImGui::Selectable(Object_Manager::FindObject(i)->GetName().c_str(), selected_object == i))
            selected_object = i;
    }
    
    ImGui::End();
}

void Editor::Display_Components() {
    ImGui::Begin("Components");

    if (selected_object != -1) {
        Object* object = Object_Manager::FindObject(selected_object);

        Display_Transform(object);
        Display_Physics(object);
        Display_Model(object);
    }

    ImGui::End();
}

void Editor::Display_Behavior(Object*) {

}

void Editor::Display_Model(Object* object) {
    Model* model = object->GetComponent<Model>();
    string modelName = model->GetModelName();

    if (ImGui::TreeNode("Model")) {
        if (ImGui::Button(modelName.c_str())) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", "./data/models/");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName = ImGuiFileDialog::Instance()->GetCurrentFileName();;
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                Trace::Message(filePathName + "\n");
                Trace::Message(filePath + "\n");
                model->SwitchModel(filePathName);
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::TreePop();
    }
}

void Editor::Display_Physics(Object* object) {
    Physics* physics = object->GetComponent<Physics>();
    vec3 velocity = physics->GetVelocity();

    if (ImGui::TreeNode("Physics")) {
        ImGui::Text("Velocity");

        ImGui::PushItemWidth(50);
        ImGui::SameLine(100); ImGui::InputFloat("x##1", &velocity.x);
        ImGui::SameLine(175); ImGui::InputFloat("y##1", &velocity.y);
        ImGui::SameLine(250); ImGui::InputFloat("z##1", &velocity.z);
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

void Editor::Display_Transform(Object* object) {
    Transform* transform = object->GetComponent<Transform>();
    vec3& position = transform->GetPosition();
    vec3& scale = transform->GetScale();
    vec3& rotation = transform->GetRotation();

    if (ImGui::TreeNode("Transform")) {
        ImGui::Text("Position");

        ImGui::PushItemWidth(50);
        ImGui::SameLine(100); ImGui::InputFloat("x##1", &position.x);
        ImGui::SameLine(175); ImGui::InputFloat("y##1", &position.y);
        ImGui::SameLine(250); ImGui::InputFloat("z##1", &position.z);
        ImGui::PopItemWidth();

        ImGui::Text("Scale");

        ImGui::PushItemWidth(50);
        ImGui::SameLine(100); ImGui::InputFloat("x##2", &scale.x);
        ImGui::SameLine(175); ImGui::InputFloat("y##2", &scale.y);
        ImGui::SameLine(250); ImGui::InputFloat("z##2", &scale.z);
        ImGui::PopItemWidth();

        ImGui::Text("Rotation");

        ImGui::PushItemWidth(50);
        ImGui::SameLine(100); ImGui::InputFloat("x##3", &rotation.x);
        ImGui::SameLine(175); ImGui::InputFloat("y##3", &rotation.y);
        ImGui::SameLine(250); ImGui::InputFloat("z##3", &rotation.z);
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}
