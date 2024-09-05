#pragma once

namespace Engine
{
    class Camera;
}

namespace Engine::Manager
{
    class Camera : public Base<Camera>
    {
        friend const std::shared_ptr<Camera>& Manager::Base<Camera>::GetInstance();

    public:
        static void Initialize(const std::shared_ptr<Engine::Camera>& defaultCamera);
        
        static D2D1::Matrix3x2F GetCameraMatrix();
        static const Math::Rect& GetCullingBound();

        static void SetActivatedCamera(const std::shared_ptr<Engine::Camera>& camera);

    private:
        std::shared_ptr<Engine::Camera> _activatedCamera;
    };
}
