/**
 * @file Input.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex input management implementation
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#include "Input.hpp"

namespace Input {
    u32 GetKeyForButton(Button button) {
        switch(button) {
            case Button::A: return KEY_A;
            case Button::B: return KEY_B;
            case Button::X: return KEY_X;
            case Button::Y: return KEY_Y;
            case Button::LEFT: return KEY_LEFT;
            case Button::RIGHT: return KEY_RIGHT;
            case Button::UP: return KEY_UP;
            case Button::DOWN: return KEY_DOWN;
            case Button::L: return KEY_L;
            case Button::R: return KEY_R;
            case Button::ZL: return KEY_ZL;
            case Button::ZR: return KEY_ZR;
            case Button::START: return KEY_START;
            case Button::SELECT: return KEY_SELECT;
            case Button::CSTICK_LEFT: return KEY_CSTICK_LEFT;
            case Button::CSTICK_RIGHT: return KEY_CSTICK_RIGHT;
            case Button::CSTICK_UP: return KEY_CSTICK_UP;
            case Button::CSTICK_DOWN: return KEY_CSTICK_DOWN;
            case Button::CPAD_LEFT: return KEY_CPAD_LEFT;
            case Button::CPAD_RIGHT: return KEY_CPAD_RIGHT;
            case Button::CPAD_UP: return KEY_CPAD_UP;
            case Button::CPAD_DOWN: return KEY_CPAD_DOWN;
            default: return 0;
        }
    }

    void InputManager::Update() {
        // Inputs scan
        hidScanInput();
        kDown = hidKeysDown();
        kHeld = hidKeysHeld();
        kUp = hidKeysUp();
        
        // Circle Pad
        hidCircleRead(&circlePos);
        currentState.circleStick.x = circlePos.dx / 156.0f;
        currentState.circleStick.y = circlePos.dy / 156.0f;
        
        // C-Stick
        hidCstickRead(&cStickPos);
        currentState.cStick.x = cStickPos.dx / 156.0f;
        currentState.cStick.y = cStickPos.dy / 156.0f;
        
        // Touch
        hidTouchRead(&touchPos);
        currentState.touch.isPressed = (kDown & KEY_TOUCH) || (kHeld & KEY_TOUCH);
        currentState.touch.position.x = touchPos.px;
        currentState.touch.position.y = touchPos.py;
        
        // Update buttons states
        for(auto& [button, state] : currentState.buttons) {
            u32 key = GetKeyForButton(button);
            if (kDown & key) {
                state = ButtonState::PRESSED;
            }
            else if (kHeld & key) {
                state = ButtonState::HELD;
            }
            else if (kUp & key) {
                state = ButtonState::RELEASED;
            }
            else {
                state = ButtonState::NONE;
            }
        }
    }

    ButtonState InputManager::GetButtonState(Button button) const {
        auto it = currentState.buttons.find(button);
        if (it != currentState.buttons.end()) {
            return it->second;
        }
        return ButtonState::NONE;
    }

    Vector2D InputManager::GetCirclePadPosition() const {
        return currentState.circleStick;
    }

    Vector2D InputManager::GetCStickPosition() const {
        return currentState.cStick;
    }

    TouchPosition InputManager::GetTouchPosition() const {
        return currentState.touch;
    }

    const InputState& InputManager::GetCurrentState() const {
        return currentState;
    }
}
