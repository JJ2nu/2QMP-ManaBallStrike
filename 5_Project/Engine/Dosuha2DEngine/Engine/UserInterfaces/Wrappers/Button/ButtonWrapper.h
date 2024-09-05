#pragma once

namespace Engine::UI::Wrapper
{
    class Button : public Base
    {
    public:
        using Event = std::function<void()>;
        
        explicit Button(const Math::Vector2& size);
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;

        void BindOnHoverBegin(const Event& event);
        void BindOnHoverEnd(const Event& event);
        void BindOnClick(const Event& event);

        void HoverCheck();
        void ClickCheck() const;

    private:
        Math::Rect _bound;

        Event _onHoverBegin;
        Event _onHoverEnd;
        bool _isHover;

        Event _onClick;
    };
}
