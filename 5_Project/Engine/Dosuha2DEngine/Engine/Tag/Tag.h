#pragma once

namespace Engine
{
    class Tag
    {
    public:
        Tag(std::wstring_view name);
        Tag(std::wstring_view name, float value);

        [[nodiscard]] std::wstring_view GetName() const;
        [[nodiscard]] std::optional<float> GetValue() const;

        std::strong_ordering operator<=>(const Tag& lhs) const;

        bool operator==(const Tag& lhs) const;

    private:
        std::wstring_view _name;
        std::optional<float> _value;
    };
}
