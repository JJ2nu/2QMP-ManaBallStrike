#include "pch.h"
#include "System.h"

#include "Loader/Loader.h"


Animation::System::System()
    : _referenceCount(1)
{
}

void Animation::System::CreateLoader(ILoader** loader)
{
    *loader = new Loader();
}

void Animation::System::AddReference()
{
    ++_referenceCount;
}

long Animation::System::Release()
{
    if (--_referenceCount > 0) return _referenceCount;
    delete this;
    return 0;
}
