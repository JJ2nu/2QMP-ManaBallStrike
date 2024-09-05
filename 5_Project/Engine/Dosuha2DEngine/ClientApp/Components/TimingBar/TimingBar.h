#pragma once

namespace Client::Component
{
    class TimingBar : public Engine::Component::UI
    {
    public:
        using Event = std::function<void()>;
        TimingBar();

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Engine::Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;

        void Hide();
        void Show();
        void Start();
        void Stop();
        void Reset();

        void BindOnPerfect(const Event& event);
        void BindOnFail(const Event& event);

        bool IsMakerMove() const;

        bool IsShow() const;

    private:
        void UpdateMaker(float deltaTime);

        std::shared_ptr<Engine::UI::Wrapper::Image> _maker;
        float _width;
        float _perfectZoneStart;
        float _perfectZoneEnd;
        float _makerSpeed;
        float _startMargin;
        float _currentMargin;
        bool _isShow;
        bool _isMakerMove;
        Event _onPerfect;
        Event _onFail;
    };
}
