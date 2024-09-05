#pragma once

namespace Client::UI
{
    class Number : public Engine::UI::Wrapper::Image
    {
    public:
        Number(const Engine::Math::Vector2& size);
        void Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect) override;
        void SetNumber(int number);
        int GetNumber() const;

    private:
        [[nodiscard]] float GetSourceLeft() const;
        Engine::Math::Rect _sourceRect;
        int _number;
    };
}
