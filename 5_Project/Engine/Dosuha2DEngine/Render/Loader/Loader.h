#pragma once

namespace Render
{
    class Loader : public ILoader
    {
    public:
        Loader(const Microsoft::WRL::ComPtr<IWICImagingFactory2>& imagingFactory,
               const Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>& renderTarget);
        
        HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
        ULONG AddRef() override;
        ULONG Release() override;
        
        void CreateBitmap(const std::wstring& path, ID2D1Bitmap** bitmap) override;

    private:
        ULONG _refCount;

        Microsoft::WRL::ComPtr<IWICImagingFactory2> _imagingFactory;
        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> _renderTarget;
    };
}
