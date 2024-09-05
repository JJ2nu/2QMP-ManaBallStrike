#pragma once

namespace Animation
{
    class Loader : public ILoader
    {
    public:
        Loader();
        
        void AddReference() override;
        long Release() override;

        void CreateAsset(const std::wstring& path, IAsset** asset) const override;

    private:
        std::atomic<long> _referenceCount;
    };
}
