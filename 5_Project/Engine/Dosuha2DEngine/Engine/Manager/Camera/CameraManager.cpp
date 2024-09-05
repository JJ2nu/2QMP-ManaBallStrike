#include "pch.h"
#include "CameraManager.h"
#include "../../Camera/Camera.h"

void Engine::Manager::Camera::Initialize(const std::shared_ptr<Engine::Camera>& defaultCamera)
{
    GetInstance()->_activatedCamera = defaultCamera;
}

D2D1::Matrix3x2F Engine::Manager::Camera::GetCameraMatrix()
{
    return GetInstance()->_activatedCamera->GetCameraMatrix();
}

const Engine::Math::Rect& Engine::Manager::Camera::GetCullingBound()
{
    return GetInstance()->_activatedCamera->GetCullingBound();
}

void Engine::Manager::Camera::SetActivatedCamera(const std::shared_ptr<Engine::Camera>& camera)
{
    GetInstance()->_activatedCamera = camera;
}
