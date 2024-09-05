#pragma once

namespace Engine::UI::Wrapper
{
    class Box : public Base, public Colored
    {
    public:
        Box(const Math::Vector2& size, D2D1_COLOR_F color);

        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
    };
}
