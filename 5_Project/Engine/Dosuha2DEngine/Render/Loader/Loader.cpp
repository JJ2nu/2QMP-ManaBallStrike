#include "pch.h"
#include "Loader.h"

Render::Loader::Loader(const Microsoft::WRL::ComPtr<IWICImagingFactory2>& imagingFactory,
                       const Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>& renderTarget)
    : _refCount(1), _imagingFactory(imagingFactory), _renderTarget(renderTarget)
{
}

HRESULT Render::Loader::QueryInterface(const IID& riid, void** ppvObject)
{
    if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
    else if (riid == IID_ILoader) *ppvObject = static_cast<ILoader*>(this);
    else
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

ULONG Render::Loader::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

ULONG Render::Loader::Release()
{
    const ULONG newRefCount = InterlockedDecrement(&_refCount);
    if (newRefCount == 0)
    {
        delete this;
    }
    return newRefCount;
}

void Render::Loader::CreateBitmap(const std::wstring& path, ID2D1Bitmap** bitmap)
{
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
    ThrowResultErrorIf<Exception::ResultException>()(
        _imagingFactory->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad,
                                                   &decoder), L"Create decoder from filename fail.");
    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    ThrowResultErrorIf<Exception::ResultException>()(decoder->GetFrame(0, &frame), L"Get frame fail.");
    Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
    ThrowResultErrorIf<Exception::ResultException>()(
        _imagingFactory->CreateFormatConverter(&converter), L"Create format converter fail.");
    ThrowResultErrorIf<Exception::ResultException>()(
        converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f,
                              WICBitmapPaletteTypeMedianCut)
        , L"Initialize converter fail.");
    ThrowResultErrorIf<Exception::ResultException>()(
        _renderTarget->CreateBitmapFromWicBitmap(converter.Get(), bitmap), L"Create bitmap from WIC bitmap fail.");
}
