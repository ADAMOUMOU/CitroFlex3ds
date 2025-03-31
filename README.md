# CitroFlex3DS Engine

CitroFlex3DS is a lightweight game engine designed specifically for Nintendo 3DS homebrew development. It provides a simple framework for creating games and applications.

## Features

- **Scene Management**: Scene based architecture
- **Input Handling**: Class handling 3DS inputs (buttons, touch, circle pad)
- **Object System**: Object based game entities
- **Rendering**: Built-in support for both screens
- **Debug Tools**: File logging system
- **Misc**: Random number generator and color presets

## Getting Started

### Prerequisites

- DevkitPro with 3DS toolchain
- libctru
- citro2d/citro3d

### Installation

1. Clone the repository:
```bash
git clone https://github.com/ADAMOUMOU/CitroFlex3DS.git
```

2. Build the project:
```bash
make clean
make
```

### Basic Usage

Here's a simple example of creating a scene with a movable object:

```cpp
#include <CitroFlex.hpp>

class Player : public Objects::Rectangle {
protected:
    void OnUpdate(Scene::Scene scene) override {
        auto input = GetInputManager();
        
        // Move with Circle Pad
        auto stick = input->GetCirclePadPosition();
        AddX(stick.x * 5.0f);
        AddY(stick.y * 5.0f);
    }
};

class MainScene : public Scene::Scene {
private:
    Player player;
public:
    MainScene() : Scene("MainScene") {
        AddElement(&player);
    }
};

int main() {
    SceneManager manager;
    sceneManager.AddScene(new MainScene());

    sceneManager.LoadScene("MainScene", Scene::Screen::TOP);
    manager.Run();
    return 0;
}
```

This code creates a scene with a player object that can be moved around using the circle pad.


## Documentation

Full documentation is available [HERE](https://docs.hdoc.io/Adamoumou/CitroFlex3ds/).

### Key Components

- **Scene System**: Manages game scenes and object lifecycle
- **Input Manager**: Handles all input devices on the 3DS
- **Object System**: Base class for all game objects
- **Debug Logger**: File-based logging system for debugging

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Roadmap

- [x] Lua/Python scripting support
- [x] UI components
- [x] Collision detection system
- [x] Audio system
