#pragma once

namespace Client::UI
{
    class Number;
    class ManaBallCounter : public Engine::UI::Panel::Stack
    {
    public:
        ManaBallCounter();
        void Initialize(Engine::Manager::Resource::Loader loader) override;
        void Finalize() override;

    private:
        std::shared_ptr<Number> _ballCountUI;
        std::shared_ptr<Number> _maxBallCountUI;
        std::shared_ptr<Engine::UI::Wrapper::Hidable> _black;
        std::shared_ptr<Engine::UI::Wrapper::Hidable> _white;
        std::shared_ptr<Engine::UI::Wrapper::Hidable> _animationCover;
        std::shared_ptr<Engine::UI::Wrapper::Animation> _animation;

        std::unique_ptr<::Audio::ISound> _restoreSound;
    };
}
