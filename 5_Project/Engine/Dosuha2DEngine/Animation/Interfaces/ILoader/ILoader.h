#pragma once

namespace Animation
{
    struct ILoader : Dosuha::IReferenceCounter
    {
        virtual void CreateAsset(const std::wstring& path, IAsset** asset) const = 0;
    };
}
