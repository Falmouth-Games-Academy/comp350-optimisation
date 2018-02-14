#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	enum {
		TARGET_MODE_NORMAL = 0,
		TARGET_MODE_CENTER
	};
	void OnMove(int MoveX, int MoveY);

	int TargetMode;

	int getX();
	int getY();

	int setX(int newX) { return X = newX; }
	int setY(int newY) { return Y = newY; }

	float getCameraSpeed() { return cameraSpeed; }
	float setCameraSpeed(float newSpeed) { return cameraSpeed = newSpeed; }

	void SetPos(int X, int Y);

	void SetTarget(int* X, int* Y);

	int xoffset = 0, yoffset = 0;
	int WindowWidth = 0;
	int WindowHeight = 0;
	glm::vec2 ChunksOnScreen;

	//! Lerp to target
	void Camera::Lerp_To(glm::vec2 target, float increment);

	

	static Camera CameraControl;

private:
	int X;
	int Y;

	

	float cameraSpeed = 0.25;

	int* TargetX;
	int* TargetY;

	




};


