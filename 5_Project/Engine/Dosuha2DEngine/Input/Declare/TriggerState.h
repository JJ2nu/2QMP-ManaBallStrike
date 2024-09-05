#pragma once

namespace Input
{
    enum class TriggerState
    {
        Triggered = 4,
        Started = 2,
        Ongoing = 0,
        Completed = 1,
        Canceled = 3
    };
}
