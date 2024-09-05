#pragma once

namespace Input
{
    class Action;

    class MappingContext : public IMappingContext
    {
    public:
        void Update(float deltaTime) override;
        void Reset() override;

        std::shared_ptr<Action> CreateAction(const std::wstring_view& name) override;
        std::shared_ptr<Action> GetAction(const std::wstring_view& name) override;

    private:
        std::unordered_map<std::wstring_view, std::shared_ptr<Action_>> _actions;
    };
}
