#pragma once

namespace Dosuha 
{
    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    class Pointer 
    {
    public:
        using InterfaceType = T;

        Pointer() noexcept;
        explicit Pointer(decltype(nullptr)) noexcept;
        explicit Pointer(T* pointer) noexcept;
        Pointer(const Pointer& other);
        Pointer(Pointer&& other) noexcept;
        Pointer& operator=(const Pointer& other);
        Pointer& operator=(Pointer&& other) noexcept;
        Pointer& operator=(decltype(nullptr)) noexcept;
        ~Pointer();

        T* Get() const noexcept;

        T* operator->() const noexcept;

        PointerReference<Pointer> operator&() noexcept;

        T** GetAddressOf() noexcept;
        
        T** ReleaseAndGetAddressOf() noexcept;

    private:
        void InternalAddRef() noexcept;
        size_t InternalRelease() noexcept;
        void Swap(Pointer&& other) noexcept;
        void Swap(Pointer& other) noexcept;


        T* _pointer;
    };

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>::Pointer(const Pointer& other) : _pointer(other._pointer)
    {
        InternalAddRef();
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>::Pointer(Pointer&& other) noexcept
    {
        if (this != reinterpret_cast<Pointer*>(&reinterpret_cast<unsigned char&>(other)))
        {
            Swap(other);
        }
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>& Pointer<T>::operator=(const Pointer& other)
    {
        if (this == &other) return *this;
        Pointer(other).Swap(*this);
        return *this;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>& Pointer<T>::operator=(Pointer&& other) noexcept
    {
        Pointer(static_cast<Pointer&&>(other)).Swap(*this);
        return *this;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>& Pointer<T>::operator=(decltype(nullptr)) noexcept
    {
        InternalRelease();
        return *this;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>::~Pointer()
    {
        InternalRelease();
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    T* Pointer<T>::Get() const noexcept
    {
        return _pointer;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    T* Pointer<T>::operator->() const noexcept
    {
        return _pointer;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    PointerReference<Pointer<T>> Pointer<T>::operator&() noexcept
    {
        return Dosuha::PointerReference<Pointer>(this);
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    T** Pointer<T>::GetAddressOf() noexcept
    {
        return &_pointer;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    T** Pointer<T>::ReleaseAndGetAddressOf() noexcept
    {
        InternalRelease();
        return &_pointer;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    void Pointer<T>::InternalAddRef() noexcept
    {
        if (_pointer != nullptr) _pointer->AddReference();
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    size_t Pointer<T>::InternalRelease() noexcept
    {
        size_t reference = 0;
        T* pointer = _pointer;
        if (pointer != nullptr)
        {
            _pointer = nullptr;
            reference = pointer->Release();
        }
        return reference;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    void Pointer<T>::Swap(Pointer&& other) noexcept
    {
        T* temp = _pointer;
        _pointer = other._pointer;
        other._pointer = temp;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    void Pointer<T>::Swap(Pointer& other) noexcept
    {
        T* temp = _pointer;
        _pointer = other._pointer;
        other._pointer = temp;
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>::Pointer() noexcept
        : _pointer(nullptr)
    {
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>::Pointer(T* pointer) noexcept
        : _pointer(pointer)
    {
    }

    template <typename T> requires std::is_base_of_v<IReferenceCounter, T>
    Pointer<T>::Pointer(decltype(nullptr)) noexcept : _pointer(nullptr)
    {
    }
}
