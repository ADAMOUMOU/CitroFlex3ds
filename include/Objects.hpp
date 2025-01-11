/**
 * @file Objects.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex game objects
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#pragma once

#include <vector>
#include <citro2d.h>
#include <citro3d.h>

#include "Colors.hpp"
#include "Input.hpp"
namespace Scene { class Scene; }  // Forward declaration

namespace Objects
{
    /** @brief Base abstract class for all Scene objects
     *  Cannot be instantiated directly due to pure virtual methods
     */
    class Object {
    private:
        double x;        ///< X position of the object
        double y;        ///< Y position of the object
        double relativeX = 0;  ///< Relative X position when attached to parent
        double relativeY = 0;  ///< Relative Y position when attached to parent
        Scene::Scene* currentScene = nullptr;  ///< Pointer to current scene
        Input::InputManager* inputManager = nullptr;  ///< Pointer to input manager

        /** @brief Sets the relative position of the object
         *  @param x: X position
         *  @param y: Y position
         */
        void SetRelativePosition(double x, double y);

	public:
        bool visible = true;
        std::vector<Objects::Object *> attachedElements;
        Object *parent = nullptr;
		int id = -1;	// ID given by the scene (-1: Not bound to a scene)
        
        /** @brief Get the X position
         *  @return Current X position
         */
        double get_x();

        /** @brief Set the X position
         *  @param new_x New X position
         */
        void SetX(double new_x);

        /** @brief Add to the X position
         *  @param add_x Value to add to X
         */
        void AddX(double add_x);

        /** @brief Get the Y position
         *  @return Current Y position
         */
        double get_y();

        /** @brief Set the Y position
         *  @param new_y New Y position
         */
        void SetY(double new_y);

        /** @brief Add to the Y position
         *  @param add_y Value to add to Y
         */
        void AddY(double add_y);

        /** @brief Initialize the object
         */
        virtual void Init();

        /** @brief Update and draw the object
         *  @param scene Pointer to the current scene passed by the Scene instance
         */
        virtual void Update(Scene::Scene* scene);

        /** @brief Updates the objects attached to this instance
         */
        void UpdateAttached();

        /** @brief Attach an object to this object and set its relative position
         *  @param obj: Object instance to attach
         */
        void Attach(Object *obj);

        /** @brief Setter for the currentscene (called by the Scene instance)
         *  @param scene: Scene instance
         */
        void SetScene(Scene::Scene* scene) { currentScene = scene; }

        /** @brief Getter for the currentscene (called by the Scene instance)
         *  @return Scene instance
         */
        Scene::Scene* GetScene() const { return currentScene; }

        /** @brief Setter for the inputmanager (called by the Scene instance)
         *  @param manager: InputManager instance
         */
        void SetInputManager(Input::InputManager* manager) { 
            inputManager = manager; 
        }

    protected:
        /** @brief Custom update logic (can be override to add custom logic before Drawing)
         *  @param scene: Scene instance
         */
        virtual void OnUpdate( Scene::Scene* scene ) {};

        /** @brief Getter for the InputManager
         *  @return InputManager instance
         */
        Input::InputManager* GetInputManager() const { return inputManager; }
	};

    /** @brief Rectangle shape object
     */
    class Rectangle : public Object
    {
    private:

    public:
        double width = 10;    ///< Width of the rectangle
        double height = 10;   ///< Height of the rectangle
        u32 color = Colors::clrWhite;  ///< Color of the rectangle

        /** @brief Update and draw the rectangle
         *  @param scene Pointer to the current scene
         */
        virtual void Update(Scene::Scene* scene) override final;
    };
    
    /** @brief Line object
     */
    class Line : public Object {
    private:
        double endX = 0;  ///< End X position of the line
        double endY = 0;  ///< End Y position of the line

    public:
        u32 color = Colors::clrWhite;  ///< Color of the line
        float thickness = 1.0f;        ///< Thickness of the line

        /** @brief Update and draw the line
         *  @param scene Pointer to the current scene
         */
        virtual void Update(Scene::Scene* scene) override;

        /** @brief Set the end point of the line
         *  @param x End X position
         *  @param y End Y position
         */
        void SetEndPoint(double x, double y);
    };

    /** @brief Circle shape object
     */
    class Circle : public Object {
    public:
        double radius = 10;   ///< Radius of the circle
        u32 color = Colors::clrWhite;  ///< Color of the circle

        /** @brief Update and draw the circle
         *  @param scene Pointer to the current scene
         */
        void Update(Scene::Scene* scene) override;
    };

    /** @brief Ellipse shape object
     */
    class Ellipse : public Object {
    public:
        double width = 20;    ///< Width of the ellipse
        double height = 10;   ///< Height of the ellipse
        u32 color = Colors::clrWhite;  ///< Color of the ellipse

        /** @brief Update and draw the ellipse
         *  @param scene Pointer to the current scene
         */
        virtual void Update(Scene::Scene* scene) override;
    };

    /** @brief Sprite object for displaying images
     */
    class Sprite : public Object {
    private:
        C2D_SpriteSheet spriteSheet = nullptr;  ///< Sprite sheet containing the image
        C2D_Sprite sprite;                      ///< Sprite instance
        int frameIndex = 0;                     ///< Current frame index
        double angle = 0;                       ///< Rotation angle

    public:
        float width = 0;   ///< Width of the sprite
        float height = 0;  ///< Height of the sprite

        /** @brief Destructor
         */
        ~Sprite();

        /** @brief Update and draw the sprite
         *  @param scene Pointer to the current scene
         */
        virtual void Update(Scene::Scene* scene) override;

        /** @brief Get the current rotation angle
         *  @return Current angle in degrees
         */
        double getAngle();

        /** @brief Set the rotation angle
         *  @param new_angle New angle in degrees
         */
        void SetAngle(double new_angle);

        /** @brief Add to the current rotation angle
         *  @param add_angle Angle to add in degrees
         */
        void AddAngle(double add_angle);

        /** @brief Load a sprite from a file
         *  @param path Path to the image file
         *  @return true if loading succeeded, false otherwise
         */
        bool LoadFromFile(const char* path);

        /** @brief Set the current frame of the sprite
         *  @param index Index of the frame to display
         */
        void SetFrame(int index);
    };
} // namespace Objects
