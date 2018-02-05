#include "stdafx.h"
#include "Camera.h"





Camera Camera::CameraControl;

Camera::Camera() {
	X = Y = 0;

	TargetX = TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;
}
Camera::~Camera()
{
}

void Camera::Lerp_To(glm::vec2 target, float increment)
{
	float lerp_x = X + (target.x - X) * increment;
	float lerp_y = Y + (target.y - Y) * increment;

	X = lerp_x;
	Y = lerp_y;


}
void Camera::OnMove(int MoveX, int MoveY) {
	X += MoveX;
	Y += MoveY;
}

int Camera::getX() {
	if (TargetX != NULL) {
		if (TargetMode == TARGET_MODE_CENTER) {
			return *TargetX - (WindowWidth / 2);
		}

		return *TargetX;
	}

	return X;
}

int Camera::getY() {
	if (TargetY != NULL) {
		if (TargetMode == TARGET_MODE_CENTER) {
			return *TargetY - (WindowHeight / 2);
		}

		return *TargetY;
	}

	return Y;
}

void Camera::SetPos(int X, int Y) {
	this->X = X;
	this->Y = Y;
}

void Camera::SetTarget(int* X, int* Y) {
	TargetX = X;
	TargetY = Y;
}