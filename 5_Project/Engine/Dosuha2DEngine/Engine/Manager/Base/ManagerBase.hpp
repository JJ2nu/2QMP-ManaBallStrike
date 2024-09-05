#pragma once

namespace Engine::Manager
{
    template <typename T>
    class Base
    {
    public:
        Base(const Base& other) = delete;
        Base(Base&& other) noexcept = delete;
        Base& operator=(const Base& other) = delete;
        Base& operator=(Base&& other) noexcept = delete;

        static const std::shared_ptr<T>& GetInstance()
        {
            std::call_once(_initFlag, []
            {
                T* prime = new T();
                _instance = std::shared_ptr<T>(prime, Deleter());
            });
            return _instance;
        }

        struct Deleter
        {
            void operator()(const T* instance)
            {
                delete instance;
            }
        };

    protected:
        Base() = default;
        virtual ~Base() = default;

    private:
        static std::shared_ptr<T> _instance;
        static std::once_flag _initFlag;
    };

    template <typename T>
    std::shared_ptr<T> Base<T>::_instance = std::shared_ptr<T>();

    template <typename T>
    std::once_flag Base<T>::_initFlag;
}
