#include <utility>

#pragma once

namespace Engine::UI::Wrapper
{
    class Hidable: public Base
    {
    public:
        using Event = std::function<void()>;
        explicit Hidable(const Math::Vector2& size);
        explicit Hidable(const Math::Vector2& size, bool isVisible);

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;

        void Show();
        void Hide();

        void BindOnShow(Event event);
        void BindOnHide(Event event);

    private:
        bool _isVisible;
        Event _onShow;
        Event _onHide;
    };
}
