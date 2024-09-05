#pragma once

namespace Dosuha 
{
    struct IReferenceCounter
    {
        IReferenceCounter() = default;
        IReferenceCounter(const IReferenceCounter& other) = default;
        IReferenceCounter(IReferenceCounter&& other) noexcept = default;
        IReferenceCounter& operator=(const IReferenceCounter& other) = default;
        IReferenceCounter& operator=(IReferenceCounter&& other) noexcept = default;
        virtual ~IReferenceCounter() = default;

        virtual void AddReference() = 0;
        virtual long Release() = 0;
    };
}
