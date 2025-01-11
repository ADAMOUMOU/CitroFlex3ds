/**
 * @file Scene.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex scene management
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Objects.hpp"
#include "Input.hpp"

namespace Scene {
    // Forward declarations
    class Scene;
    class SceneManager;

    /** @brief Enum for screen selection */
    enum class Screen {
        TOP,    ///< Top screen
        BOTTOM  ///< Bottom screen
    };

    /** @brief Base class for managing game scenes
     *  Handles objects, updates, etc...
     */
    class Scene {
    protected:
        std::vector<Objects::Object*> elements;     ///< List of objects in the scene
        bool isLoaded = false;                      ///< Flag indicating if scene is loaded
        std::string name;                           ///< Unique name of the scene
        bool canExit = false;                       ///< Flag indicating if scene can be exited
        SceneManager* sceneManager = nullptr;       ///< Pointer to scene manager
        Input::InputManager* inputManager = nullptr; ///< Pointer to input manager
        u32 backgroundColor = Colors::clrBlack;     ///< Background color of the scene

    public:
        /** @brief Constructor
         *  @param sceneName Unique name for the scene
         */
        Scene(const std::string& sceneName) : name(sceneName) {}
        
        /** @brief Virtual destructor */
        virtual ~Scene() = default;
        
        /** @brief Get scene name
         *  @return Const reference to scene name
         */
        const std::string& GetName() const { return name; }

        /** @brief Check if scene can be exited with a key
         *  @return True if scene can be exited
         */
        bool CanExitWithKey() const { return canExit; }

        /** @brief Set if scene can be exited with a key
         *  @param value New exit permission value
         */
        void SetCanExitWithKey(bool value) { canExit = value; }
        
        /** @brief Get scene manager
         *  @return Pointer to current scene manager
         */
        SceneManager* GetSceneManager() const { return sceneManager; }

        /** @brief Set scene manager
         *  @param manager Pointer to scene manager
         */
        void SetSceneManager(SceneManager* manager) { sceneManager = manager; }

        /** @brief Set input manager for scene and all elements
         *  @param manager Pointer to input manager
         */
        void SetInputManager(Input::InputManager* manager);

        /** @brief Add new element to scene
         *  @param element Pointer to object to add
         */
        void AddElement(Objects::Object* element);

        /** @brief Updates scene and all elements
         */
        virtual void Update();

        /** @brief Remove element at specified index
         *  @param index Index of element to remove
         */
        void RemoveElement(size_t index);

        /** @brief Remove specific element instance
         *  @param element Pointer to element to remove
         */
        void RemoveElementByInstance(Objects::Object* element);

        /** @brief Get index of specific element
         *  @param element Pointer to element to find
         *  @return Index of element or -1 if not found
         */
        int GetElementIndex(Objects::Object* element) const;

        /** @brief Get all elements in scene
         *  @return Vector of object pointers
         */
        std::vector<Objects::Object*> GetElements() const {
            return elements; 
        }

        /** @brief Get element at specific index
         *  @param index Index of element
         *  @return Pointer to object at index
         */
        Objects::Object* GetElement(size_t index) const {
            return elements[index]; 
        }

        /** @brief Get background color
         *  @return Current background color
         */
        u32 GetBackgroundColor() const { return backgroundColor; }

        /** @brief Set background color
         *  @param newColor New background color
         */
        void SetBackgroundColor(u32 newColor) { backgroundColor = newColor; }

        /** @brief Called when scene is loaded
         */
        virtual void OnLoad() {}

        /** @brief Called when scene is unloaded
         */
        virtual void OnUnload() {}
    };

    /** @brief Manages multiple scenes and handles rendering
     *  Controls scene lifecycle and screen rendering
     */
    class SceneManager {
    private:
        C3D_RenderTarget* topScreen;                    ///< Top screen render target
        C3D_RenderTarget* bottomScreen;                 ///< Bottom screen render target
        std::vector<Scene*> scenes;                     ///< List of all scenes
        int currentTopSceneIndex = -1;                  ///< Index of current top screen scene
        int currentBottomSceneIndex = -1;               ///< Index of current bottom screen scene
        Input::InputManager inputManager;               ///< Input manager instance
        Input::Button exitKey = Input::Button::START;   ///< Exit key

    public:
        /** @brief Get input manager
         *  @return Reference to input manager
         */
        Input::InputManager& GetInputManager() { return inputManager; }

        /** @brief Constructor - initializes C2D and C3D */
        SceneManager();

        /** @brief Destructor - cleans up C2D and C3D */
        virtual ~SceneManager();

        /** @brief Add new scene to manager
         *  @param scene Pointer to scene to add
         *  @return Index of the scene in the scenes vector
         */
        int AddScene(Scene* scene);

        /** @brief Load scene by name
         *  @param sceneName Name of scene to load
         *  @param targetScreen Screen to load scene on
         */
        void LoadScene(const std::string& sceneName, Screen targetScreen);

        /** @brief Load scene by index
         *  @param index Index of scene to load
         *  @param targetScreen Screen to load scene on
         */
        void LoadScene(int index, Screen targetScreen);

        /** @brief Update and render current scenes */
        void Update();

        /** @brief Main game loop */
        void Run();
    };
}