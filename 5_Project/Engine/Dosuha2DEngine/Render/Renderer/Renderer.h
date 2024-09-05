#pragma once

namespace Render
{
    class Renderer : public IRenderer
    {
    public:
        explicit Renderer(const Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>& renderTarget);

        HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
        ULONG AddRef() override;
        ULONG Release() override;

        void SetTransform(const D2D1_MATRIX_3X2_F& transform) override;
        void DrawRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color, float strokeWidth = 1.0f) const override;
        void FillRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color) const override;
        void DrawRoundedRectangle(const D2D1_ROUNDED_RECT& roundrect, const D2D1_COLOR_F& color, float strokeWidth = 1.0f) const override;
        void FillRoundedRectangle(const D2D1_ROUNDED_RECT& roundrect, const D2D1_COLOR_F& color) const override;
        void DrawEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_COLOR_F& color, float strokeWidth = 1.0f) const override;
        void FillEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_COLOR_F& color) const override;
        void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap) const override;
        void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, float opacity) const override;
        void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect) const override;
        void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect, const D2D1_RECT_F& sourceRect) override;
        void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRect) const override;
        void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect, float opacity) const override;

    private:
        ULONG _refCount;

        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> _renderTarget;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> _brush;

    };
}
