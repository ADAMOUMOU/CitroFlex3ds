/**
 * @file Input.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex input management
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#pragma once

#include <3ds.h>
#include <map>

/**
 * @namespace Input
 * @brief Handles input management for the 3DS console
 */
namespace Input {
    /**
     * @brief Enumeration of all available buttons
     */
    enum class Button {
        A, B, X, Y,
        LEFT, RIGHT, UP, DOWN,
        L, R, ZL, ZR,
        START, SELECT,
        CSTICK_LEFT, CSTICK_RIGHT, CSTICK_UP, CSTICK_DOWN,
        CPAD_LEFT, CPAD_RIGHT, CPAD_UP, CPAD_DOWN
    };

    /**
     * @brief Represents the current state of a button
     */
    enum class ButtonState {
        NONE,       ///< Button is not pressed
        PRESSED,    ///< Button was just pressed this frame
        HELD,       ///< Button is being held down
        RELEASED    ///< Button was just released this frame
    };

    /**
     * @brief Represents a 2D vector for stick positions
     */
    struct Vector2D {
        float x = 0.0f;  ///< X coordinate
        float y = 0.0f;  ///< Y coordinate
    };

    /**
     * @brief Represents the touch screen input state
     */
    struct TouchPosition {
        bool isPressed = false;  ///< Whether the screen is being touched
        Vector2D position;       ///< Position of the touch
    };

    /**
     * @brief Contains the complete state of all inputs
     */
    struct InputState {
        std::map<Button, ButtonState> buttons;  ///< State of all buttons
        Vector2D circleStick;                   ///< Position of the Circle Pad
        Vector2D cStick;                        ///< Position of the C-Stick
        TouchPosition touch;                    ///< Touch screen state
    };

    /**
     * @brief Converts a Button enum to its corresponding 3DS key code
     * @param button The button to convert
     * @return The corresponding KEY_ value
     */
    u32 GetKeyForButton(Button button);

    /**
     * @brief Manages all input handling for the 3DS
     */
    class InputManager {
    private:
        InputState currentState;
        u32 kDown, kHeld, kUp;
        circlePosition circlePos;
        circlePosition cStickPos;
        touchPosition touchPos;

    public:
        /**
         * @brief Constructor that initializes all button states
         */
        InputManager() {
            for (int i = 0; i < static_cast<int>(Button::CPAD_DOWN) + 1; i++) {
                currentState.buttons[static_cast<Button>(i)] = ButtonState::NONE;
            }
        }

        /**
         * @brief Updates the state of all inputs
         */
        void Update();
        
        /**
         * @brief Gets the current state of a specific button
         * @param button The button to check
         * @return The current state of the button
         */
        ButtonState GetButtonState(Button button) const;

        /**
         * @brief Gets the current position of the Circle Pad
         * @return A Vector2D containing the normalized (-1 to 1) position
         */
        Vector2D GetCirclePadPosition() const;

        /**
         * @brief Gets the current position of the C-Stick
         * @return A Vector2D containing the normalized (-1 to 1) position
         */
        Vector2D GetCStickPosition() const;

        /**
         * @brief Gets the current touch screen state
         * @return The current touch position and state
         */
        TouchPosition GetTouchPosition() const;
        
        /**
         * @brief Gets the complete current input state
         * @return A reference to the current InputState
         */
        const InputState& GetCurrentState() const;
    };
}
