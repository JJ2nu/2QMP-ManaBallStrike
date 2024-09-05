#include "pch.h"
#include "Functions.h"
#include "../System/System.h"

void Audio::CreateSystem(ISystem** system)
{
    *system = new System();
}
