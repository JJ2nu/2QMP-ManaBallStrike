#pragma once

namespace Engine::Manager
{
    template <typename T>
    class Observer : public Base<Observer<T>>
    {
        friend const std::shared_ptr<Observer>& Base<Observer>::GetInstance();

    public:
        class Subject;
        using Receiver = std::function<void(const T&)>;

        static std::shared_ptr<Subject> CreateSubject(const std::wstring& name)
        {
            if (!Observer::GetInstance()->_subjects.contains(name))
                Observer::GetInstance()->_subjects[name] = std::make_shared<Subject>();
            return Observer::GetInstance()->_subjects[name];
        }

        static int Register(const std::wstring& name, const Receiver& receiver)
        {
            if (Observer::GetInstance()->_subjects.contains(name))
                return Observer::GetInstance()->_subjects[name]->Register(receiver);
            return CreateSubject(name)->Register(receiver);
        }

        static void ClearRegisters(const std::wstring& name)
        {
            if (Observer::GetInstance()->_subjects.contains(name))
                Observer::GetInstance()->_subjects[name]->ClearRegisters();
        }

        static void RemoveRegister(const std::wstring& name, int id)
        {
            if (Observer::GetInstance()->_subjects.contains(name)) Observer::GetInstance()->_subjects[name]->
                RemoveRegister(id);
        }

    private:
        std::map<std::wstring, std::shared_ptr<Subject>> _subjects;

    public:
        class Subject
        {
            struct Element
            {
                int id;
                Receiver receiver;
            };

        public:
            Subject()
                : _increaseId(0)
            {
            }

            void SetValue(const T& value)
            {
                _value = value;
                for (const auto& element : _elements) element.receiver(_value);
            }

            [[nodiscard]] const T& GetValue() const
            {
                return _value;
            }

            int Register(const Receiver& receiver)
            {
                int id = _increaseId++;
                _elements.push_back({id, receiver});
                return id;
            }

            void ClearRegisters()
            {
                _elements.clear();
            }

            void RemoveRegister(int removeId)
            {
                auto [begin, end] = std::ranges::remove_if(_elements, [removeId](const Element& element)
                {
                    return element.id == removeId;
                });
                _elements.erase(begin, end);
            }

            bool operator==(const Subject& lhs) const
            {
                return _value == lhs._value;
            }

            std::strong_ordering operator<=>(const Subject& lhs) const
            {
                return _value <=> lhs._value;
            }

            bool operator==(const T& lhs) const
            {
                return _value == lhs;
            }

            std::strong_ordering operator<=>(const T& lhs) const
            {
                return _value <=> lhs;
            }

        private:
            int _increaseId;
            T _value;
            std::list<Element> _elements;
        };
    };
}
