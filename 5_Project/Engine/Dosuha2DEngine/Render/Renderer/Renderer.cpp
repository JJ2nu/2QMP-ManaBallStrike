#include "pch.h"
#include "Renderer.h"

Render::Renderer::Renderer(const Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>& renderTarget)
    : _refCount(1), _renderTarget(renderTarget)
{
    ThrowResultErrorIf<Exception::ResultException>()
    (_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), _brush.GetAddressOf()),
     L"Failed to create a solid color brush.");
}

void Render::Renderer::SetTransform(const D2D1_MATRIX_3X2_F& transform)
{
    _renderTarget->SetTransform(transform);
}

void Render::Renderer::DrawRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color, const float strokeWidth) const
{
    _brush->SetColor(color);
    _renderTarget->DrawRectangle(rect, _brush.Get(), strokeWidth);
}

void Render::Renderer::FillRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color) const
{
    _brush->SetColor(color);
    _renderTarget->FillRectangle(rect, _brush.Get());
}

void Render::Renderer::DrawRoundedRectangle(const D2D1_ROUNDED_RECT& roundrect, const D2D1_COLOR_F& color, float strokeWidth) const
{
    _brush->SetColor(color);
    _renderTarget->DrawRoundedRectangle(roundrect, _brush.Get(), strokeWidth);
}

void Render::Renderer::FillRoundedRectangle(const D2D1_ROUNDED_RECT& roundrect, const D2D1_COLOR_F& color) const
{
    _brush->SetColor(color);
    _renderTarget->FillRoundedRectangle(roundrect, _brush.Get());
}

void Render::Renderer::DrawEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_COLOR_F& color, float strokeWidth) const
{
    _brush->SetColor(color);
    _renderTarget->DrawEllipse(ellipse, _brush.Get(), strokeWidth);
}

void Render::Renderer::FillEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_COLOR_F& color) const
{
    _brush->SetColor(color);
    _renderTarget->FillEllipse(ellipse, _brush.Get());
}

void Render::Renderer::DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap) const
{
    _renderTarget->DrawBitmap(bitmap.Get());
}

void Render::Renderer::DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, float opacity) const
{
    _renderTarget->DrawBitmap(bitmap.Get(), nullptr, opacity);
}

void Render::Renderer::DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect) const
{
    _renderTarget->DrawBitmap(bitmap.Get(), destRect);
}

void Render::Renderer::DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect,
                                  const D2D1_RECT_F& sourceRect)
{
    _renderTarget->DrawBitmap(bitmap.Get(), destRect, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);
}

void Render::Renderer::DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect,
                                  const float opacity, const D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
                                  const D2D1_RECT_F& sourceRect) const
{
    _renderTarget->DrawBitmap(bitmap.Get(), destRect, opacity, interpolationMode, sourceRect);
}

void Render::Renderer::DrawBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap>& bitmap, const D2D1_RECT_F& destRect,
    float opacity) const
{
    _renderTarget->DrawBitmap(bitmap.Get(), destRect, opacity);
}

HRESULT Render::Renderer::QueryInterface(const IID& riid, void** ppvObject)
{
    if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
    else if (riid == IID_IRenderer) *ppvObject = static_cast<IRenderer*>(this);
    else
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

ULONG Render::Renderer::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

ULONG Render::Renderer::Release()
{
    const ULONG newRefCount = InterlockedDecrement(&_refCount);
    if (newRefCount == 0) delete this;
    return newRefCount;
}
