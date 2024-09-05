#pragma once

namespace Window
{
    class System : public ISystem
    {
    public:
        explicit System(HINSTANCE instanceHandle);

        void Register(LPCWSTR name, IClass** windowClass) const override;
        void Register(LPCWSTR name, IClass** windowClass, std::wstring cursorPath, std::wstring iconPath, std::wstring smallIconPath) const override;
        void Create(IClass* windowClass, RECT windowRect, IHandle** handle) const override;

        void AddReference() override;
        long Release() override;

    private:
        HINSTANCE _instanceHandle;
        std::atomic<long> _referenceCount;
    };
}
