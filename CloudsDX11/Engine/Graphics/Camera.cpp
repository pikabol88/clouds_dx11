#include "Camera.h"
#include "../SMath.h"

void Camera::updateDirectionVectors() {
	this->forward = XMVectorSubtract(this->lookAt, this->position);
	this->forward = XMVector3Normalize(this->forward);

	this->left = XMVector3Cross(this->forward, this->worldUp);
	this->left = XMVector3Normalize(this->left);

	this->up = XMVector3Cross(this->left, this->forward);
	this->up = XMVector3Normalize(this->up);
}

void Camera::updateViewMatrix() {
	this->viewMatrix = XMMatrixLookAtLH(
		this->position, 
		XMVectorAdd(this->position, this->forward), 
		this->worldUp
	);
}

Camera::Camera(float fov, float aspectRatio, float nearZ, float farZ, XMVECTOR startPos)
	: pitch(0.0f), yaw(0.0f) {
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);

	this->position = startPos;
	this->lookAt = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	this->worldUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	this->updateDirectionVectors();
	this->updateViewMatrix();
}

Camera::~Camera(){}

void Camera::setPosition(XMVECTOR newPos) {
	this->position = newPos;
}

void Camera::move(XMVECTOR dirV) {
	XMVECTOR delta = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	XMFLOAT4 dir;
	XMStoreFloat4(&dir, dirV);

	// Apply direction to delta
	delta = XMVectorAdd(this->left * dir.x, delta);
	delta = XMVectorAdd(this->worldUp * dir.y, delta);
	delta = XMVectorAdd(this->forward * dir.z, delta);

	// Apply movement to position
	this->position = XMVectorAdd(this->position, delta);
}

void Camera::rotate(XMVECTOR dirV) {
	XMFLOAT4 dir;
	XMStoreFloat4(&dir, dirV);

	this->yaw += dir.x;
	this->pitch += dir.y;

	// Clamp limit
	this->pitch = SMath::clamp(
		this->pitch, 
		-SMath::PI * 0.5f * 0.99f, 
		 SMath::PI * 0.5f * 0.99f
	);

	// Create rotation matrix from new pitch, yaw and roll
	this->lookAt = XMVectorAdd(this->position, 
		XMVectorSet(
			(float) (sin(yaw) * cos(pitch)),
			(float) sin(pitch),
			(float) (cos(yaw) * cos(pitch)),
			0.0f
		)
	);

	this->updateDirectionVectors();
}

const XMMATRIX& Camera::getProjectionMatrix() const {
	return this->projectionMatrix;
}

const XMMATRIX& Camera::getViewMatrix() {
	this->updateViewMatrix();

	return this->viewMatrix;
}

const XMFLOAT3 Camera::getPosition() const {
	XMFLOAT3 tempFloat3;

	XMStoreFloat3(&tempFloat3, this->position);

	return tempFloat3;
}

