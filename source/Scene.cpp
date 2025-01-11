/**
 * @file Scene.cpp
 * @author ADAMOUMOU
 * @brief CitroFlex scene management implementation
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#include "Scene.hpp"

namespace Scene {

    void Scene::SetInputManager(Input::InputManager* manager) {
        inputManager = manager;
        for(auto element : elements) {
            element->SetInputManager(manager);
        }
    }

    void Scene::AddElement(Objects::Object* element) {
        elements.push_back(element);
        if (inputManager) {
            element->SetInputManager(inputManager);
        }
    }

    void Scene::Update() {
        for(auto element : elements) {
            element->Update(this);
        }
    }

    void Scene::RemoveElement(size_t index) {
        if (index < elements.size()) {
            elements.erase(elements.begin() + index);
        }
    }

    void Scene::RemoveElementByInstance(Objects::Object* element) {
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }

    int Scene::GetElementIndex(Objects::Object* element) const {
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            return std::distance(elements.begin(), it);
        }
        return -1;
    }

    SceneManager::SceneManager() {
        gfxInitDefault();
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();
        consoleInit(GFX_BOTTOM, NULL);

        topScreen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
        bottomScreen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    }

    SceneManager::~SceneManager() {
        C2D_Fini();
        C3D_Fini();
        gfxExit();
    }

    int SceneManager::AddScene(Scene* scene) {
        scene->SetSceneManager(this);
        scene->SetInputManager(&inputManager);
        scenes.push_back(scene);
        return scenes.size() - 1;
    }

    void SceneManager::LoadScene(const std::string& sceneName, Screen targetScreen) {
        for (size_t i = 0; i < scenes.size(); i++) {
            if (scenes[i]->GetName() == sceneName) {
                LoadScene(i, targetScreen);
                return;
            }
        }
    }

    void SceneManager::LoadScene(int index, Screen targetScreen) {
        if (index >= 0 && index < scenes.size()) {
            // Unload current scene
            if (targetScreen == Screen::TOP && currentTopSceneIndex >= 0) {
                scenes[currentTopSceneIndex]->OnUnload();
            }
            else if (targetScreen == Screen::BOTTOM && currentBottomSceneIndex >= 0) {
                scenes[currentBottomSceneIndex]->OnUnload();
            }

            // Load new scene
            if (targetScreen == Screen::TOP) {
                currentTopSceneIndex = index;
            } else {
                currentBottomSceneIndex = index;
            }
            scenes[index]->OnLoad();
        }
    }

    void SceneManager::Update() {
        // Updates top screen
        if (currentTopSceneIndex >= 0) {
            C2D_SceneBegin(topScreen);
            C2D_TargetClear(topScreen, scenes[currentTopSceneIndex]->GetBackgroundColor());
            scenes[currentTopSceneIndex]->Update();
        }

        // Updates bottom screen
        if (currentBottomSceneIndex >= 0) {
            C2D_SceneBegin(bottomScreen);
            C2D_TargetClear(bottomScreen, scenes[currentBottomSceneIndex]->GetBackgroundColor());
            scenes[currentBottomSceneIndex]->Update();
        }

        C2D_Flush();
    }

    void SceneManager::Run() {
        while (aptMainLoop()) {
            inputManager.Update();

            // Checks if we can exit
            bool canExitGame = false;
            if (currentTopSceneIndex >= 0) {
                canExitGame |= scenes[currentTopSceneIndex]->CanExitWithKey();
            }
            if (currentBottomSceneIndex >= 0) {
                canExitGame |= scenes[currentBottomSceneIndex]->CanExitWithKey();
            }

            if (canExitGame && (inputManager.GetButtonState(exitKey) == Input::ButtonState::PRESSED)) {
                break;
            }

            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            Update();
            C3D_FrameEnd(0);
        }
    }
}