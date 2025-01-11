

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include "CitroFlex.hpp"

/*
EXAMPLE CODE
*/

class Player : public Objects::Rectangle {
protected:
	void OnUpdate(Scene::Scene* scene) override {
		auto input = GetInputManager();

		if (!input) return;

		auto buttonState = input->GetButtonState(Input::Button::A);
		if (buttonState == Input::ButtonState::PRESSED) {
			printf("\x1b[10;1HButton A pressed!");
			scene->GetSceneManager()->LoadScene("Level2", Scene::Screen::TOP);
		}

		if (input->GetButtonState(Input::Button::Y) == Input::ButtonState::PRESSED) {
			scene->SetBackgroundColor(Colors::clrRed);
		}

		// Movement with Circle Pad
		auto stick = input->GetCirclePadPosition();
		AddX(stick.x * 5.0f);
		AddY(stick.y * 5.0f);

		// Or with directional buttons
		if (input->GetButtonState(Input::Button::LEFT) == Input::ButtonState::HELD) AddX(-0.5);
		if (input->GetButtonState(Input::Button::RIGHT) == Input::ButtonState::HELD) AddX(0.5);
		if (input->GetButtonState(Input::Button::UP) == Input::ButtonState::HELD) AddY(-0.5);
		if (input->GetButtonState(Input::Button::DOWN) == Input::ButtonState::HELD) AddY(0.5);
	}
};

class ReturnButton : public Objects::Rectangle {
protected:
	void OnUpdate(Scene::Scene* scene) override {
		hidScanInput();
		u32 kDown = hidKeysDown();
		
		if (kDown & KEY_A) {
			scene->GetSceneManager()->LoadScene("Level1", Scene::Screen::TOP);
		}
	}
};

// First scene with a player that can change scene
class Level1Scene : public Scene::Scene {
private:
	Player player;
	Objects::Circle* portal;  // Changed to pointer to be able to delete it

public:
	Level1Scene() : Scene("Level1") {
		SetCanExitWithKey(true);
		portal = new Objects::Circle();
	}

	~Level1Scene() {
		delete portal;  // Don't forget to free memory
	}

	void OnLoad() override {
		// Player configuration
		player.width = 20;
		player.height = 20;
		player.color = Colors::clrBlue;
		player.SetX(100);
		player.SetY(100);

		// Portal configuration
		portal->radius = 15;
		portal->color = Colors::clrPurple;
		portal->SetX(200);
		portal->SetY(120);

		AddElement(portal);
		AddElement(&player);
	}
};

// Second scene with different objects
class Level2Scene : public Scene::Scene {
private:
	ReturnButton returnBtn;
	Objects::Circle ball;
	Objects::Line line;

public:
	Level2Scene() : Scene("Level2") {}

	void OnLoad() override {
		// Return button configuration
		returnBtn.width = 30;
		returnBtn.height = 30;
		returnBtn.color = Colors::clrRed;
		returnBtn.SetX(20);
		returnBtn.SetY(20);

		ball.radius = 10;
		ball.color = Colors::clrBlue;
		ball.SetX(180);
		ball.SetY(150);

		line.SetX(50);
		line.SetY(50);
		line.SetEndPoint(250, 50);
		line.color = Colors::clrYellow;

		AddElement(&returnBtn);
		AddElement(&ball);
		AddElement(&line);
	}
};

// Example scene for bottom screen
class ConsoleScene : public Scene::Scene {
public:
	ConsoleScene() : Scene("Console") {}

	void OnLoad() override {
		printf("\x1b[1;1HConsole Scene Loaded!");
		printf("\x1b[2;1HPress START to exit.");
	}
};

int main(int argc, char* argv[]) {
	Scene::SceneManager sceneManager;

	sceneManager.AddScene(new Level1Scene());
	sceneManager.AddScene(new Level2Scene());
	sceneManager.AddScene(new ConsoleScene());

	sceneManager.LoadScene("Level1", Scene::Screen::TOP);
	sceneManager.LoadScene("Console", Scene::Screen::BOTTOM);

	sceneManager.Run();
	return 0;
}
