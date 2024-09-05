#pragma once

namespace Input
{
    class Action;

    struct IMappingContext
    {
        IMappingContext() = default;
        IMappingContext(const IMappingContext&) = default;
        IMappingContext& operator=(const IMappingContext&) = default;
        IMappingContext(IMappingContext&&) = default;
        IMappingContext& operator=(IMappingContext&&) = default;
        virtual ~IMappingContext() = default;

        virtual void Update(float deltaTime) = 0;
        virtual void Reset() = 0;

        virtual std::shared_ptr<Action> CreateAction(const std::wstring_view& name) = 0;
        virtual std::shared_ptr<Action> GetAction(const std::wstring_view& name) = 0;
    };
}
