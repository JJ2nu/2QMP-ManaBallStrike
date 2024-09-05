#include "pch.h"
#include "System.h"

#include "../Canvas/Canvas.h"
#include "../World/World.h"

void Engine::System::Initialize(const HINSTANCE instanceHandle, const int showCommand)
{
    Manager::Time::Initialize();
    Manager::Window::Initialize(instanceHandle, _gameName.c_str(), _clientSize, showCommand);
    Manager::System::Initialize(Manager::Window::GetWindowHandle(), _clientSize);
    Manager::Resource::Initialize(Manager::System::GetRenderSystem(), Manager::System::GetAnimationSystem());
    Manager::Render::Initialize(Manager::System::GetRenderSystem());
    Manager::Input::Initialize();
    Manager::Input::GetMouse().SetHandle(Manager::Window::GetWindowHandle());
    Manager::Camera::Initialize(_world->CreateObject<Object::Camera>(_clientSize));
    Microsoft::WRL::ComPtr<ID2D1Bitmap> lightmask;
    Manager::Resource::GetLoader()->CreateBitmap(L"Resources/Sprites/lightmask.png", &lightmask);
    Manager::Render::GetShader()->SetLightMask(lightmask);
    Manager::Audio::Initialize();


    OnPreInitialize();
    _world->Initialize(Manager::Resource::GetLoader());
    _canvas->Initialize(Manager::Resource::GetLoader());
    OnPostInitialize();
    _isRun = true;
}

void Engine::System::Run()
{
    MSG message;
    while (_isRun)
    {
        if (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
            {
                _isRun = false;
                break;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            Manager::Time::Update();
            Manager::Input::Update(Manager::Time::GetDeltaMetaTime());
            Manager::Audio::Update();
            _fixedUpdateElapsedTime += Manager::Time::GetDeltaMetaTime();
            while (_fixedUpdateElapsedTime >= _fixedUpdateInterval)
            {
                FixedUpdate(_fixedUpdateInterval);
                _fixedUpdateElapsedTime -= _fixedUpdateInterval;
            }
            Update(Manager::Time::GetDeltaMetaTime(), Manager::Time::GetDeltaGameTime());
            LazyUpdate(Manager::Time::GetDeltaMetaTime(), Manager::Time::GetDeltaGameTime());
            Manager::Render::GetShader()->SetCameraMatrix(Manager::Camera::GetCameraMatrix());
            Manager::Render::BeginDraw();
            Manager::Render::Clear(D2D1::ColorF(D2D1::ColorF::Black));
            if(Manager::Render::GetShader()->IsBackgroundOn() && Manager::Render::GetShader()->IsLightMaskOn())
                Manager::Render::GetShader()->Shade();
            Render(Manager::Render::GetRenderer(), Manager::Camera::GetCameraMatrix(),
                   Manager::Camera::GetCullingBound(), {Math::Vector2::Zero(), Manager::Window::GetSize()});
            Manager::Render::EndDraw();
            Manager::Input::Reset();
        }
    }
}

void Engine::System::Finalize()
{
    OnPreFinalize();
    _canvas->Finalize();
    _canvas = nullptr;
    _world->Finalize();
    _world = nullptr;
    OnPostFinalize();
    Manager::Audio::Finalize();
    Manager::Resource::Finalize();
    Manager::Render::Finalize();
    Manager::System::Finalize();
    _isRun = false;
    ClipCursor(NULL);

}

void Engine::System::ChangeWorld(const std::shared_ptr<World>& world)
{
    _world->Finalize();
    world->Initialize(Manager::Resource::GetLoader());
    _world = world;
}

void Engine::System::OnPreInitialize()
{
}

void Engine::System::OnPostInitialize()
{
}

void Engine::System::OnPreFinalize()
{
}

void Engine::System::OnPostFinalize()
{
}

void Engine::System::SetFixedUpdateInterval(const float interval)
{
    _fixedUpdateInterval = interval;
}

Engine::System::System(const std::wstring& gameName, const Math::Vector2& clientSize)
    : System(gameName, clientSize, std::make_shared<World>(), std::make_shared<Canvas>(clientSize))
{
}

Engine::System::System(const std::wstring& gameName, const Math::Vector2& clientSize,
                       const std::shared_ptr<World>& world)
    : System(gameName, clientSize, world, std::make_shared<Canvas>(clientSize))
{
}

Engine::System::System(const std::wstring& gameName, const Math::Vector2& clientSize,
                       const std::shared_ptr<Canvas>& canvas)
    : System(gameName, clientSize, std::make_shared<World>(), canvas)
{
}

Engine::System::System(const std::wstring& gameName, const Math::Vector2& clientSize,
                       const std::shared_ptr<World>& world,
                       const std::shared_ptr<Canvas>& canvas)
    : _gameName(gameName), _clientSize(clientSize), _world(world), _isRun(false),
      _fixedUpdateElapsedTime(0.0f), _fixedUpdateInterval(0.2f),
      _canvas(canvas)
{
}


void Engine::System::Update(const float deltaMetaTime, const float deltaGameTime) const
{
    _canvas->Update(deltaMetaTime, deltaGameTime);
    _world->Update(deltaMetaTime, deltaGameTime);
}

void Engine::System::FixedUpdate(const float interval) const
{
    _world->FixedUpdate(interval);
}

void Engine::System::LazyUpdate(const float deltaMetaTime, const float deltaGameTime) const
{
    _canvas->LazyUpdate(deltaMetaTime, deltaGameTime);
    _world->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::System::Render(const Manager::Render::Renderer& renderer, const D2D1_MATRIX_3X2_F& cameraMatrix,
                            const Math::Rect& cullingBound, const Math::Rect& viewportRect) const
{
    _world->Render(renderer, cameraMatrix, cullingBound);
    _canvas->Render(renderer, viewportRect);
}
