#pragma once

namespace Render
{
    class System : public ISystem
    {
        friend void CreateSystem(ISystem** system);

    public:
        HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
        ULONG AddRef() override;
        ULONG Release() override;

        void CreateRenderer(IRenderer** renderer) override;
        void CreateLoader(ILoader** loader) override;
        void CreateShader(IShader** shader) override;

        void Initialize(HWND windowHandle, D2D1_SIZE_U size) override;

        void BeginDraw() override;
        void Clear(D2D1_COLOR_F color) override;
        void EndDraw() override;

    private:
        System();
        void InitializeFactory();
        void InitializeRenderTarget(HWND windowHandle, D2D1_SIZE_U size);
        void InitializeImagingFactory();

        ULONG _refCount;

        Microsoft::WRL::ComPtr<IWICImagingFactory2> _imagingFactory;
        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> _renderTarget;
        Microsoft::WRL::ComPtr<ID2D1Factory> _factory;

    };
}
