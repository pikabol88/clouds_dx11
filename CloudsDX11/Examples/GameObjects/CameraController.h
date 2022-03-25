#pragma once

#include "../../Engine/Graphics/Camera.h"
#include "../../Engine/Graphics/CameraClass.h"

class CameraController {
private:
	Camera camera;
	//CameraClass camera2;

	float mouseSensitivity;
	float movementSpeed;

public:
	CameraController(int windowWidth, int windowHeight);
	~CameraController();

	void update();

	Camera& getCamera();
	//CameraClass& getCamera();
};