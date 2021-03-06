/**
 * @file editor.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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

static Editor* editor = nullptr; //!< Editor object

/**
 * @brief Sets up the config and style of the editor
 * 
 * @return true 
 * @return false 
 */
bool Editor::Initialize() {
      // Initializing the editor
    editor = new Editor;
    if (!editor) {
        Trace::Message("Editor failed to initialize.\n");
        return false;
    }
    editor->selected_object = -1;
    editor->selected_component = -1;
    editor->object_to_copy = -1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

      // Setting up ImGui flags
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

      // Setting style for ImGui
    ImGui::StyleColorsDark();
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::GetStyle().WindowRounding = 0.f;
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 1.f;
    }

      // Setting up ImGui
    ImGui_ImplGlfw_InitForOpenGL(Graphics::GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    return true;
}

/**
 * @brief Updates the editor content and calls display functions
 * 
 * @return void
 */
void Editor::Update() {
      // ImGui update functions
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();

      // Updating whether program should ignore keyboard input
    if (!ImGui::GetIO().WantCaptureKeyboard) {
        editor->takeKeyboardInput = true;
    }
    else {
        editor->takeKeyboardInput = false;
    }

      // Keyboard shortcuts
    if (!editor->takeKeyboardInput) {
          // Save current settings as preset
        if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
                if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_S) == GLFW_RELEASE) {
                        Engine::Write();
                }
            }
        }
    }
    
      // Display the different windows
    editor->Display_Dockspace();
    editor->Display_Scene();
    editor->Display_Components();
    editor->Display_World_Settings();
    editor->Display_Camera_Settings();
}

/**
 * @brief Render the editor
 * 
 * @return void
 */
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

/**
 * @brief Destroy editor windows and systems
 * 
 * @return void
 */
void Editor::Shutdown() {
    if (!editor) return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete editor;
    editor = nullptr;
}

/**
 * @brief Sets selected object to invalid value
 * 
 * @return void
 */
void Editor::Reset() {
    editor->selected_object = -1;
}

/**
 * @brief Setup and display the editor's dockspace
 * 
 */
void Editor::Display_Dockspace() {
      // Setting up viewport
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);

      // Setting up window flags
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

      // Setting up window style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

      // Making the window
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin("Editor Window", &editor->isOpen, window_flags);
    ImGui::PopStyleVar(3);

      // Setting up window settings
    ImGuiID dockspace_id = ImGui::GetID("Editor");
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    editor->Display_Menu_Bar();
    ImGui::End();
}

/**
 * @brief Display the scene window
 * 
 */
void Editor::Display_Scene() {
    ImGui::Begin("Scene");

    if (!takeKeyboardInput && ImGui::IsWindowFocused()) {
        if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
              // Copy current selected object
            if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_C) == GLFW_PRESS) {
                if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_C) == GLFW_RELEASE) {
                    editor->object_to_copy = editor->selected_object;
                }
            }
              // Paste current selected object
            if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_V) == GLFW_PRESS) {
                if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_V) == GLFW_RELEASE) {
                    if (editor->object_to_copy != -1) {
                        Object* object = new Object(*Object_Manager::FindObject(editor->selected_object));
                        Object_Manager::AddObject(object);
                    }
                }
            }
        }
    }

      // Display all objects
    for (int i = 0; i < (int)Object_Manager::GetSize(); ++i) {
        if (ImGui::Selectable(Object_Manager::FindObject(i)->GetName().c_str(), selected_object == i, ImGuiSelectableFlags_AllowDoubleClick)) {
            if (selected_object != i) editor->selected_component = -1;
            selected_object = i;
            selected_component = -1;
        }

          // Checking for right click behavior
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            if (selected_object != i) editor->selected_component = -1;
            selected_object = i;
            selected_component = -1;
            ImGui::OpenPopup("ObjectSettings##1");
        }
    }

    if (ImGui::BeginPopup("ObjectSettings##1")) {
          // Removes selected object from scene
        if (ImGui::Selectable("Delete##1")) {
            Object_Manager::RemoveObject(selected_object);
            selected_object = -1;
            selected_component = -1;
        }
          // Copies selected object
        if (ImGui::Selectable("Copy##1")) {
            editor->object_to_copy = editor->selected_object;
        }
          // Pastes copied object into scene
        if (ImGui::Selectable("Paste##1")) {
            if (editor->object_to_copy != -1) {
                Object* object = new Object(*Object_Manager::FindObject(editor->selected_object));
                Object_Manager::AddObject(object);
            }
        }
        ImGui::EndPopup();
    }

    ImGui::Separator();

      // Button to add new object to the scene
    if (ImGui::Button("Add Object")) {
        Object* newObject = new Object;
        Transform* transform = new Transform;
        transform->SetStartPosition(glm::vec3(0.f));
        newObject->SetName("New_Object");
        newObject->AddComponent(transform);

        Object_Manager::AddObject(newObject);
    }
    
    ImGui::End();
}

/**
 * @brief Display all of the components of the current selected_object
 * 
 */
void Editor::Display_Components() {
    ImGui::Begin("Components##1");

    if (selected_object == -1) { ImGui::End(); return; }
    Object* object = Object_Manager::FindObject(selected_object);
    std::string objectName = object->GetName();

    ImGui::Text("Id: %d", object->GetId());
    
      // Display name box (allows changing the name of an object)
    static char nameBuf[128] = "";
    sprintf(nameBuf, objectName.c_str());
    
    if (ImGui::InputText("Name", nameBuf, 128, ImGuiInputTextFlags_EnterReturnsTrue)) {
        object->SetName(std::string(nameBuf));
    }

    if (ImGui::IsItemDeactivatedAfterEdit()) {
        object->SetName(std::string(nameBuf));
    }
    
      // Template used by the selected object
    ImGui::Text("Template:");
    ImGui::SameLine(100);
    std::string templateName = object->GetTemplateName();
    if (templateName.empty()) templateName = "No template##1";
    else templateName = Editor::Make_Display_String(templateName);

    if (ImGui::Button(templateName.c_str())) {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseTemplate##1", "Choose File", ".json", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/json/objects/");
    }

    ImGui::SameLine();
    if (ImGui::Button("New Template")) {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##6", "Choose File", ".json", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/json/objects/");
    }

    
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##6")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            object->Write(filePath);
        }

       ImGuiFileDialog::Instance()->Close();
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseTemplate##1")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
            object->ReRead(filePath);
        }

        ImGuiFileDialog::Instance()->Close();
    }

      // Getting all of the components
    Behavior* behavior = object->GetComponent<Behavior>();
    Model* model = object->GetComponent<Model>();
    Physics* physics = object->GetComponent<Physics>();
    Transform* transform = object->GetComponent<Transform>();

      // Display all of the components of the selected_object
    Display_Transform(transform);
    Display_Physics(physics);
    Display_Model(model);
    Display_Scripts(behavior);

    ImGui::Separator();

      // Button to add new components to the selected_object
    if (ImGui::Button("Add Component##1")) {
        ImGui::OpenPopup("New Component##1");
    }

      // Add new components to object (only ones that the object doesn't already have)
    if (ImGui::BeginPopup("New Component##1")) {
        if (!physics) {
            if (ImGui::Selectable("Physics##1")) {
                physics = new Physics;
                object->AddComponent(physics);
            }
        }
        if (!model) {
            if (ImGui::Selectable("Model##1")) {
                model = new Model;
                object->AddComponent(model);
            }
        }
        if (!behavior) {
            if (ImGui::Selectable("Scripts##1")) {
                behavior = new Behavior;
                object->AddComponent(behavior);
            }
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

/**
 * @brief Shows all of the settings of the engine itself
 * 
 */
void Editor::Display_World_Settings() {
    ImGui::Begin("World Settings");
    std::string presetName = Engine::GetPresetName();
    if (presetName.compare("no preset") != 0)
        presetName = Editor::Make_Display_String(presetName);

      // Allows user to change the preset that is loaded
    ImGui::Text("Presets"); ImGui::SameLine(120);
    if (ImGui::Button(presetName.c_str())) {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##5", "Choose File", ".json", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/json/preset/");
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##5")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();

            if (Engine::Restart(filePath)) {
                selected_object = -1;
                selected_component = -1;
                object_to_copy = -1;
            }
        }

        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::PushItemWidth(141);

      // Strength of the light being used
    ImGui::Text("Light Power");
    ImGui::SameLine(120); ImGui::InputFloat("##1", &Engine::GetLightPower());

      // Position of the light being used
    ImGui::Text("Light Position");
    ImGui::PushItemWidth(65);
    ImGui::SameLine(120); ImGui::InputFloat("x##4", &Engine::GetLightPos().x);
    ImGui::SameLine(205); ImGui::InputFloat("y##4", &Engine::GetLightPos().y);
    ImGui::SameLine(290); ImGui::InputFloat("z##4", &Engine::GetLightPos().z);
    ImGui::PopItemWidth();

      // Grav const of the engine
    ImGui::Text("Grav Const");
    ImGui::SameLine(120); ImGui::InputDouble("##5", &Engine::GetGravConst());

    ImGui::PopItemWidth();

    ImGui::End();
}

/**
 * @brief Displays the different camera settings, allows user to change them as needed
 * 
 */
void Editor::Display_Camera_Settings() {
    ImGui::Begin("Camera Settings");

    ImGui::PushItemWidth(137);

      // Default move speed
    ImGui::Text("Move Speed");
    ImGui::SameLine(100); ImGui::InputFloat("##2", &Camera::GetOriginalMoveSpeed());

      // Move speed when holding shift
    ImGui::Text("Sprint Speed");
    ImGui::SameLine(100); ImGui::InputFloat("##3", &Camera::GetOriginalSprintSpeed());

      // Mouse sensitivity when looking around
    ImGui::Text("Sensitivity");
    ImGui::SameLine(100); ImGui::InputFloat("##4", &Camera::GetOriginalSensitivity());

    ImGui::PopItemWidth();

    ImGui::End();
}

/**
 * @brief Displays the different lua scripts attached to the selected object
 * 
 * @param behavior Contains the script data
 */
void Editor::Display_Scripts(Behavior* behavior) {
    if (!behavior) return;
    
    // Setting up tree flags
    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (selected_component == CType::CBehavior) node_flags |= ImGuiTreeNodeFlags_Selected;
    
    const bool scripts_open = ImGui::TreeNodeEx((void*)(intptr_t)CType::CBehavior, node_flags, "Scripts");
    if (ImGui::IsItemClicked()) selected_component = CType::CBehavior;

      // Right click behavior to delete script component from object
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        selected_component = CType::CBehavior;
        ImGui::OpenPopup("DeleteScripts##1");
    }

    if (ImGui::BeginPopup("DeleteScripts##1")) {
        if (ImGui::Selectable("Delete##2")) {
            behavior->GetParent()->RemoveComponent<Behavior>();
            selected_component = -1;
        }
        ImGui::EndPopup();
    }

      // Displays the currently attached scripts
    if (scripts_open) {
        std::vector<std::string>& scripts = behavior->GetScripts();
        unsigned scriptNum = 1;
        for (std::string& script : scripts) {
            ImGui::Text(std::string("Script " + std::to_string(scriptNum) + ":").c_str());
            ImGui::SameLine(100);
            if (ImGui::Button(Editor::Make_Display_String(script).c_str())) {
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##3", "Choose File", ".lua", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/scripts/");
            }

            if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##3")) {
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                    filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
                    behavior->SwitchScript(scriptNum - 1, filePath);
                }

                ImGuiFileDialog::Instance()->Close();
            }
            ++scriptNum;
        }

          // Add new script to the object
        ImGui::Indent(71);
        if (ImGui::Button("New Script##1")) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##4", "Choose File", ".lua", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/scripts/");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##4")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
                behavior->AddScript(filePath);
            }

            ImGuiFileDialog::Instance()->Close();
        }

          // Popup to say that the selected script to add is already attached to the object
        if (ImGui::BeginPopup("ExistingScript##1")) {
            ImGui::Text(std::string("Script already being used or doesn't exist").c_str(),
                ImGui::GetFontSize() * 2);
            ImGui::EndPopup();
        }

        ImGui::TreePop();
    }
}

/**
 * @brief Displays the data of the model being used
 * 
 * @param model 
 */
void Editor::Display_Model(Model* model) {
    if (!model) return;
    
    std::string modelName = Editor::Make_Display_String(model->GetModelName());
    std::string textureName = Editor::Make_Display_String(model->GetTextureName());

    if (modelName.compare("") == 0) modelName = "no model";
    if (textureName.compare("") == 0) textureName = "no texture";
    
      // Setting up tree flags
    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (selected_component == CType::CModel) node_flags |= ImGuiTreeNodeFlags_Selected;
    
    const bool model_open = ImGui::TreeNodeEx((void*)(intptr_t)CType::CModel, node_flags, "Model");
    if (ImGui::IsItemClicked()) selected_component = CType::CModel;

      // Right click behavior to delete model component from selected object
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        selected_component = CType::CModel;
        ImGui::OpenPopup("DeleteModel##1");
    }

    if (ImGui::BeginPopup("DeleteModel##1")) {
        if (ImGui::Selectable("Delete##3")) {
            model->GetParent()->RemoveComponent<Model>();
            selected_component = -1;
        }
        ImGui::EndPopup();
    }

    if (model_open) {
          // Model that is being used
        ImGui::Text("Model"); ImGui::SameLine(100);
        if (ImGui::Button(modelName.c_str())) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##1", "Choose File", ".obj", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/models/");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##1")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
                model->SwitchModel(filePath);
            }

            ImGuiFileDialog::Instance()->Close();
        }

          // Texture that is being used
        ImGui::Text("Texture"); ImGui::SameLine(100);
        if (ImGui::Button(textureName.c_str())) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##2", "Choose File", ".dds,.DDS", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/textures/");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##2")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
                model->SwitchTexture(filePath);
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::TreePop();
    }
}

/**
 * @brief Shows the Physics component
 * 
 * @param physics 
 */
void Editor::Display_Physics(Physics* physics) {
    if (!physics) return;
    
    glm::vec3& velocity = physics->GetVelocityRef();
    glm::vec3& rotVel = physics->GetRotationalVelocityRef();

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (selected_component == CType::CPhysics) node_flags |= ImGuiTreeNodeFlags_Selected;
    
    const bool physics_open = ImGui::TreeNodeEx((void*)(intptr_t)CType::CPhysics, node_flags, "Physics");
    if (ImGui::IsItemClicked()) selected_component = CType::CPhysics;

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        selected_component = CType::CPhysics;
        ImGui::OpenPopup("DeletePhysics##1");
    }

    if (ImGui::BeginPopup("DeletePhysics##1")) {
        if (ImGui::Selectable("Delete##4")) {
            physics->GetParent()->RemoveComponent<Physics>();
            selected_component = -1;
        }
        ImGui::EndPopup();
    }

    if (physics_open) {
        ImGui::Text("Velocity");

        ImGui::PushItemWidth(65);
        ImGui::SameLine(100); ImGui::InputFloat("x##1", &velocity.x);
        ImGui::SameLine(185); ImGui::InputFloat("y##1", &velocity.y);
        ImGui::SameLine(270); ImGui::InputFloat("z##1", &velocity.z);

        ImGui::Text("RotVel");

        ImGui::PushItemWidth(65);
        ImGui::SameLine(100); ImGui::InputFloat("x##6", &rotVel.x);
        ImGui::SameLine(185); ImGui::InputFloat("y##6", &rotVel.y);
        ImGui::SameLine(270); ImGui::InputFloat("z##6", &rotVel.z);

        ImGui::Text("Mass");
        ImGui::SameLine(100); ImGui::InputFloat("##6", &physics->GetMassRef());
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

/**
 * @brief Display transform data, users can change any of it
 * 
 * @param transform 
 */
void Editor::Display_Transform(Transform* transform) {
    if (!transform) return;
    
    glm::vec3& position = transform->GetPositionRef();
    glm::vec3& scale = transform->GetScaleRef();
    glm::vec3& rotation = transform->GetRotationRef();
    glm::vec3& startPos = transform->GetStartPositionRef();

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (selected_component == CType::CTransform) node_flags |= ImGuiTreeNodeFlags_Selected;
    
    const bool transform_open = ImGui::TreeNodeEx((void*)(intptr_t)CType::CTransform, node_flags, "Transform");
    if (ImGui::IsItemClicked()) selected_component = CType::CTransform;

    if (transform_open) {
        ImGui::Text("Position");

        ImGui::PushItemWidth(65);
        ImGui::SameLine(100); ImGui::InputFloat("x##1", &position.x);
        ImGui::SameLine(185); ImGui::InputFloat("y##1", &position.y);
        ImGui::SameLine(270); ImGui::InputFloat("z##1", &position.z);
        ImGui::PopItemWidth();

        ImGui::Text("Scale");

        ImGui::PushItemWidth(65);
        ImGui::SameLine(100); ImGui::InputFloat("x##2", &scale.x);
        ImGui::SameLine(185); ImGui::InputFloat("y##2", &scale.y);
        ImGui::SameLine(270); ImGui::InputFloat("z##2", &scale.z);
        ImGui::PopItemWidth();

        ImGui::Text("Rotation");

        ImGui::PushItemWidth(65);
        ImGui::SameLine(100); ImGui::InputFloat("x##3", &rotation.x);
        ImGui::SameLine(185); ImGui::InputFloat("y##3", &rotation.y);
        ImGui::SameLine(270); ImGui::InputFloat("z##3", &rotation.z);
        ImGui::PopItemWidth();
        
        ImGui::Text("Start Pos");

        ImGui::PushItemWidth(65);
        ImGui::SameLine(100); ImGui::InputFloat("x##5", &startPos.x);
        ImGui::SameLine(185); ImGui::InputFloat("y##5", &startPos.y);
        ImGui::SameLine(270); ImGui::InputFloat("z##5", &startPos.z);
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

/**
 * @brief Displays menu bar that can be used to save the scene
 * 
 */
void Editor::Display_Menu_Bar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File##1")) {
            if (ImGui::MenuItem("Save##1")) {
                Engine::Write();
            }
            if (ImGui::MenuItem("Save As..##1")) {
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey##7", "Choose File", ".json", std::string(getenv("USERPROFILE")) + "/Documents/pEngine/json/preset");
            }

            ImGui::EndMenu();
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey##7")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                filePath += "/" + ImGuiFileDialog::Instance()->GetCurrentFileName() + ".json";
                Engine::SetPresetName(std::string(filePath));
                Engine::Write();
            }
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::EndMenuBar();
    }
}

/**
 * @brief Returns whether the program should ignore keyboard input
 * 
 * @return true 
 * @return false 
 */
bool Editor::GetTakeKeyboardInput() { return editor->takeKeyboardInput; }

/**
 * @brief Removes the filepath from a filename
 * 
 * @param inputString Original filename (with filepath)
 * @return std::string 
 */
std::string Editor::Make_Display_String(std::string inputString) {
    size_t slashLoc = inputString.find_last_of("/");
    size_t dotLoc = inputString.find_last_of(".");

    if (slashLoc == std::string::npos || dotLoc == std::string::npos)
        return inputString;

    std::string newString = inputString.substr(slashLoc + 1, dotLoc);

    return newString;
}