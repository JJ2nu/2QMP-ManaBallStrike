#pragma once

namespace Engine::UI::Element
{
    class SlideButton : public Base
    {
    public:
        using Event = std::function<void(float)>;
        
        explicit SlideButton(const Math::Vector2& size);

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;

        void BindOnSlide(const Event& event);

    private:
        Math::Rect _bound;
        Event _onSlide;
    };
}
