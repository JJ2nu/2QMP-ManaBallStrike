#pragma once

namespace Dosuha
{
    template <typename T>
    class PointerReference
    {
        using InterfaceType = typename T::InterfaceType;

    public:
        explicit PointerReference(T* pointer) noexcept;

        operator IReferenceCounter**() const noexcept;

        operator void**() const noexcept;

        operator T*() noexcept;

        operator InterfaceType**() noexcept;

        InterfaceType* operator*() noexcept;

        InterfaceType* const * GetAddressOf() const noexcept;

        InterfaceType** ReleaseAndGetAddressOf() noexcept;

    private:
        T* _pointer;
    };

    template <typename T>
    PointerReference<T>::PointerReference(T* pointer) noexcept
        : _pointer(pointer)
    {
    }

    template <typename T>
    PointerReference<T>::operator IReferenceCounter**() const noexcept
    {
        return reinterpret_cast<IReferenceCounter**>(_pointer->ReleaseAndGetAddressOf());
    }

    template <typename T>
    PointerReference<T>::operator void**() const noexcept
    {
        return reinterpret_cast<void**>(this->_pointer->ReleaseAndGetAddressOf());
    }

    template <typename T>
    PointerReference<T>::operator T*() noexcept
    {
        *this->_pointer = nullptr;
        return this->_pointer;
    }

    template <typename T>
    PointerReference<T>::operator typename T::InterfaceType**() noexcept
    {
        return _pointer->ReleaseAndGetAddressOf();
    }

    template <typename T>
    typename PointerReference<T>::InterfaceType* PointerReference<T>::operator*() noexcept
    {
        return this->_pointer->Get();
    }

    template <typename T>
    typename PointerReference<T>::InterfaceType* const* PointerReference<T>::GetAddressOf() const noexcept
    {
        return this->_pointer->GetAddressOf();
    }

    template <typename T>
    typename PointerReference<T>::InterfaceType** PointerReference<T>::ReleaseAndGetAddressOf() noexcept
    {
        return this->_pointer->ReleaseAndGetAddressOf();
    }
}
