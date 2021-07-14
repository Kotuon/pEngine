
// Library includes //
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "ImGuiFileDialog.h"
#include <vec3.hpp>

// Engine includes //
#include "camera.hpp"
#include "editor.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "object_manager.hpp"
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

    if (!ImGui::GetIO().WantCaptureKeyboard) {
        editor->takeKeyboardInput = true;
    }
    else {
        editor->takeKeyboardInput = false;
    }
    
    editor->Display_Dockspace();
    editor->Display_Scene();
    editor->Display_Components();
    editor->Display_World_Settings();
    editor->Display_Camera_Settings();
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
        if (ImGui::Selectable(Object_Manager::FindObject(i)->GetName().c_str(), selected_object == i, ImGuiSelectableFlags_AllowDoubleClick))
            selected_object = i;
    }

    ImGui::Separator();

    if (ImGui::Button("Add Object")) {
        Object* newObject = new Object;
        Transform* transform = new Transform;
        newObject->SetName("New_Object");
        newObject->AddComponent(transform);

        Object_Manager::AddObject(newObject);
    }
    
    ImGui::End();
}

void Editor::Display_Components() {
    ImGui::Begin("Components##1");

    if (selected_object == -1) { ImGui::End(); return; }
    Object* object = Object_Manager::FindObject(selected_object);
    string objectName = object->GetName();

    static char nameBuf[128] = "";
    sprintf(nameBuf, objectName.c_str());
    
    if (ImGui::InputText("Name", nameBuf, 128, ImGuiInputTextFlags_EnterReturnsTrue)) {
        object->SetName(string(nameBuf));
    }

    if (ImGui::IsItemDeactivatedAfterEdit()) {
        object->SetName(string(nameBuf));
    }

    Model* model = object->GetComponent<Model>();
    Physics* physics = object->GetComponent<Physics>();
    Transform* transform = object->GetComponent<Transform>();

    Display_Transform(transform);
    Display_Physics(physics);
    Display_Model(model);
    
    ImGui::Separator();
    
    if (ImGui::Button("Add Component##1")) {
        ImGui::OpenPopup("New Component##1");
    }

    if (ImGui::BeginPopup("New Component##1")) {
        if (!model) {
            if (ImGui::Selectable("Model##1")) {
                model = new Model;
                object->AddComponent(model);
            }
        }
        if (!physics) {
            if (ImGui::Selectable("Physics##1")) {
                physics = new Physics;
                object->AddComponent(physics);
            }
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void Editor::Display_World_Settings() {
    ImGui::Begin("World Settings");
    string presetName = Engine::GetPresetName();

    ImGui::Text("Presets"); ImGui::SameLine(120);
    if (ImGui::Button(presetName.c_str())) {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##3", "Choose File", ".json", "./data/json/preset/");
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##3")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            string filePathName = ImGuiFileDialog::Instance()->GetCurrentFileName();
            selected_object = -1;
            Engine::Restart(filePathName);
        }

        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::PushItemWidth(141);

    ImGui::Text("Light Power");
    ImGui::SameLine(120); ImGui::InputFloat("##1", &Engine::GetLightPower());

    ImGui::Text("Light Position");
    ImGui::PushItemWidth(50);
    ImGui::SameLine(120); ImGui::InputFloat("x##4", &Engine::GetLightPos().x);
    ImGui::SameLine(195); ImGui::InputFloat("y##4", &Engine::GetLightPos().y);
    ImGui::SameLine(270); ImGui::InputFloat("z##4", &Engine::GetLightPos().z);
    ImGui::PopItemWidth();

    ImGui::Text("Grav Const");
    ImGui::SameLine(120); ImGui::InputDouble("##5", &Engine::GetGravConst());

    ImGui::PopItemWidth();

    ImGui::End();
}

void Editor::Display_Camera_Settings() {
    ImGui::Begin("Camera Settings");

    ImGui::PushItemWidth(137);

    ImGui::Text("Move Speed");
    ImGui::SameLine(100); ImGui::InputFloat("##2", &Camera::GetOriginalMoveSpeed());

    ImGui::Text("Sprint Speed");
    ImGui::SameLine(100); ImGui::InputFloat("##3", &Camera::GetOriginalSprintSpeed());

    ImGui::Text("Sensitivity");
    ImGui::SameLine(100); ImGui::InputFloat("##4", &Camera::GetOriginalSensitivity());

    ImGui::PopItemWidth();

    ImGui::End();
}

void Editor::Display_Model(Model* model) {
    if (!model) return;
    
    string modelName = model->GetModelName();
    string textureName = model->GetTextureName();

    if (ImGui::TreeNode("Model")) {
        ImGui::Text("Model"); ImGui::SameLine(100);
        if (ImGui::Button(modelName.c_str())) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##1", "Choose File", ".obj", "./data/models/");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##1")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                string filePathName = ImGuiFileDialog::Instance()->GetCurrentFileName();
                model->SwitchModel(filePathName);
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::Text("Texture"); ImGui::SameLine(100);
        if (ImGui::Button(textureName.c_str())) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##2", "Choose File", ".dds,.DDS", "./data/textures/");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##2")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                string filePathName = ImGuiFileDialog::Instance()->GetCurrentFileName();
                model->SwitchTexture(filePathName);
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::TreePop();
    }
}

void Editor::Display_Physics(Physics* physics) {
    if (!physics) return;
    
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

void Editor::Display_Transform(Transform* transform) {
    if (!transform) return;
    
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

bool Editor::GetTakeKeyboardInput() { return editor->takeKeyboardInput; }