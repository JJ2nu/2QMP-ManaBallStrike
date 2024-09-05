#pragma once

namespace Engine
{
    class World;
    class Canvas;

    class System
    {
    public:
        System(const System& other) = delete;
        System(System&& other) noexcept = delete;
        System& operator=(const System& other) = delete;
        System& operator=(System&& other) noexcept = delete;

        void Initialize(HINSTANCE instanceHandle, int showCommand);
        void Run();
        void Finalize();

        void ChangeWorld(const std::shared_ptr<World>& world);

    protected:
        virtual void OnPreInitialize();
        virtual void OnPostInitialize();
        virtual void OnPreFinalize();
        virtual void OnPostFinalize();

        void SetFixedUpdateInterval(float interval);

        System(const std::wstring& gameName, const Math::Vector2& clientSize);
        System(const std::wstring& gameName, const Math::Vector2& clientSize, const std::shared_ptr<World>& world);
        System(const std::wstring& gameName, const Math::Vector2& clientSize, const std::shared_ptr<Canvas>& canvas);
        System(const std::wstring& gameName, const Math::Vector2& clientSize, const std::shared_ptr<World>& world,
               const std::shared_ptr<Canvas>& canvas);
        ~System() = default;

        std::wstring _gameName;
        Math::Vector2 _clientSize;

        std::shared_ptr<World> _world;
        std::shared_ptr<Canvas> _canvas;
        bool _isRun;

    private:
        void FixedUpdate(float interval) const;
        void Update(float deltaMetaTime, float deltaGameTime) const;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) const;
        void Render(const Manager::Render::Renderer& renderer, const D2D1_MATRIX_3X2_F& cameraMatrix,
                    const Math::Rect& cullingBound, const Math::Rect& viewportRect) const;


        float _fixedUpdateElapsedTime;
        float _fixedUpdateInterval;
    };
}
