#pragma once

namespace Client::UI
{
    class HUD : public Engine::UI::Panel::Anchor
    {
    public:
        explicit HUD(const Engine::Math::Vector2& size);

        void Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect) override;

        void Hide();
        void Show();

        [[nodiscard]] bool IsShown() const;

    private:
        bool _isShown;
    };
}
