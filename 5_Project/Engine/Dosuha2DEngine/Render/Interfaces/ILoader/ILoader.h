#pragma once

DEFINE_GUID(IID_ILoader, 0xbdbbf36a, 0x806b, 0x418b, 0x95, 0xaa, 0x92, 0x6c, 0x6a, 0x7e, 0xfa, 0xe4);

namespace Render
{
    struct ILoader : IUnknown
    {
        ILoader() = default;
        ILoader(const ILoader& other) = default;
        ILoader(ILoader&& other) noexcept = default;
        ILoader& operator=(const ILoader& other) = default;
        ILoader& operator=(ILoader&& other) noexcept = default;
        virtual ~ILoader() = default;

        virtual void CreateBitmap(const std::wstring& path, ID2D1Bitmap** bitmap) = 0;
    };
}
