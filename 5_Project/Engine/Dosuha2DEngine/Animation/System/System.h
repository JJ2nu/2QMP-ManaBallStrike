#pragma once

namespace Animation
{
    class System : public ISystem
    {
    public:
        System();
        void CreateLoader(ILoader** loader) override;

        void AddReference() override;
        long Release() override;

    private:
        std::atomic<long> _referenceCount;
    };
}
