#include "pch.h"
#include "System.h"

#include "../../Input/Exception/Exception.h"
#include "../Loader/Loader.h"
#include "../Renderer/Renderer.h"
#include "../Shader/Shader.h"

HRESULT Render::System::QueryInterface(const IID& riid, void** ppvObject)
{
    if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
    else if (riid == IID_ISystem) *ppvObject = static_cast<ISystem*>(this);
    else
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

ULONG Render::System::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

ULONG Render::System::Release()
{
    const ULONG newRefCount = InterlockedDecrement(&_refCount);
    if (newRefCount == 0)
    {
        delete this;
    }
    return newRefCount;
}

void Render::System::CreateRenderer(IRenderer** renderer)
{
    *renderer = new Renderer(_renderTarget);
}

void Render::System::CreateLoader(ILoader** loader)
{
    *loader = new Loader(_imagingFactory, _renderTarget);
}

void Render::System::CreateShader(IShader** shader)
{
    *shader = new Shader(_renderTarget, _factory);

}
void Render::System::Initialize(const HWND windowHandle, const D2D1_SIZE_U size)
{
    InitializeFactory();
    InitializeRenderTarget(windowHandle, size);
    InitializeImagingFactory();
}

void Render::System::BeginDraw()
{
    _renderTarget->BeginDraw();
}

void Render::System::Clear(const D2D1_COLOR_F color)
{
    _renderTarget->Clear(color);
}

void Render::System::EndDraw()
{
    ThrowResultErrorIf<Exception::ResultException>()(_renderTarget->EndDraw(), L"Failed to end draw.");
}

Render::System::System()
    : _refCount(1)
{
}

void Render::System::InitializeFactory()
{
    ThrowResultErrorIf<Exception::ResultException>()(
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, _factory.GetAddressOf()),
        L"Failed to create D2D1 factory.");
}

void Render::System::InitializeRenderTarget(const HWND windowHandle, const D2D1_SIZE_U size)
{
    ThrowResultErrorIf<Exception::ResultException>()(
        _factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                         D2D1::HwndRenderTargetProperties(windowHandle, size), &_renderTarget),
        L"Failed to create D2D1 render target.");
}

void Render::System::InitializeImagingFactory()
{
    ThrowResultErrorIf<Exception::ResultException>()(
        CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_imagingFactory)),
        L"Failed to create WIC imaging factory.");
}

