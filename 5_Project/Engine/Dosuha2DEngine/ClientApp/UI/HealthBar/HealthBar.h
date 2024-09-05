#pragma once

namespace Client::UI
{
    class HealthBar : public Engine::UI::Panel::Overlay
    {
    public:
        HealthBar();
        void Initialize(Engine::Manager::Resource::Loader loader) override;

    private:
        std::shared_ptr<Engine::UI::Wrapper::Box> _bar;

        float _barWidth;
    };
}
