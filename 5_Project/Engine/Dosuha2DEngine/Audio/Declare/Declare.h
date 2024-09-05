#pragma once

namespace Audio
{
    constexpr size_t ChannelGroupCount = 2;

    enum class ChannelGroupType : std::uint8_t
    {
        Background,
        Effect
    };
}
