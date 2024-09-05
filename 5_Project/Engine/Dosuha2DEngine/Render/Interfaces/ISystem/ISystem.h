#pragma once

DEFINE_GUID(IID_ISystem, 0xb9ecd7d5, 0x85b8, 0x45e2, 0x8e, 0xbf, 0xc1, 0x55, 0x41, 0xf6, 0x45, 0xb7);

namespace Render
{
    struct ISystem : IUnknown
    {
        ISystem() = default;
        ISystem(const ISystem& other) = default;
        ISystem(ISystem&& other) noexcept = default;
        ISystem& operator=(const ISystem& other) = default;
        ISystem& operator=(ISystem&& other) noexcept = default;
        virtual ~ISystem() = default;

        virtual void Initialize(HWND windowHandle, D2D1_SIZE_U size) = 0;

        virtual void CreateRenderer(IRenderer** renderer) = 0;
        virtual void CreateLoader(ILoader** loader) = 0;
        virtual void CreateShader(IShader** shader) = 0;

        virtual void BeginDraw() = 0;
        virtual void Clear(D2D1_COLOR_F color) = 0;
        virtual void EndDraw() = 0;
    };
}
