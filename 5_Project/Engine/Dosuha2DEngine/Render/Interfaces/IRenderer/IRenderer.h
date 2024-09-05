#pragma once

DEFINE_GUID(IID_IRenderer, 0x3f4b3b1b, 0x7b1b, 0x4b1b, 0x8b, 0x3b, 0x1b, 0x7b, 0x4b, 0x3f, 0x1b, 0x7b);

namespace Render
{
    struct IRenderer : IUnknown
    {
        IRenderer() = default;
        IRenderer(const IRenderer& other) = default;
        IRenderer(IRenderer&& other) noexcept = default;
        IRenderer& operator=(const IRenderer& other) = default;
        IRenderer& operator=(IRenderer&& other) noexcept = default;
        virtual ~IRenderer() = default;

        virtual void SetTransform(const D2D1_MATRIX_3X2_F& transform) = 0;
        virtual void DrawRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color, float strokeWidth = 1.0f) const =0;
        virtual void FillRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color) const = 0;
        virtual void DrawRoundedRectangle(const D2D1_ROUNDED_RECT& roundrect, const D2D1_COLOR_F& color, float strokeWidth = 1.0f) const = 0;
        virtual void FillRoundedRectangle(const D2D1_ROUNDED_RECT& roundrect, const D2D1_COLOR_F& color) const = 0;
        virtual void DrawEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_COLOR_F& color, float strokeWidth = 1.0f) const = 0;
        virtual void FillEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_COLOR_F& color) const = 0;
        virtual void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap) const = 0;
        virtual void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, float opacity) const = 0;
        virtual void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect) const = 0;
        virtual void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect, float opacity) const = 0;
        virtual void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect, const D2D1_RECT_F& sourceRect) = 0;
        virtual void DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect,
                                float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
                                const D2D1_RECT_F& sourceRect) const = 0;
    };
}
