#include "pch.h"
#include "Functions.h"
#include "../../System/System.h"

void Animation::CreateSystem(ISystem** system)
{
    *system = new System();
}
