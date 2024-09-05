#pragma once
namespace Engine::Component
{
    enum class ShadowType
    {
        Box,
        Circle
    };

    class Shadow : public Base , public Rect
    {
    public:
        explicit Shadow(ShadowType _shadowType);
        explicit Shadow(const Math::Vector2& size, ShadowType _shadowType);

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
        void SetSize(const Math::Vector2& size);
        void AddShadow();
        void SetFixed(bool isFixed = true);
        void Finalize();

        void DrawShadowBox(bool isRender = true);
        [[nodiscard]] const Math::Rect& GetBound();
    protected:

        void UpdateShadeBox();
        ShadowType _shadowType;
        int ObjectIndex =-1;
        bool _isFixed = true;
        bool _isAdded = false;
        bool _isRender;
        Math::Rect _shadebox;
    };
}
