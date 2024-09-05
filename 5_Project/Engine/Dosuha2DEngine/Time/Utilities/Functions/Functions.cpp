#include "pch.h"
#include "Functions.h"
#include "../../System/System.h"

Time::ISystem* Time::CreateSystem()
{
    return new System();
}
