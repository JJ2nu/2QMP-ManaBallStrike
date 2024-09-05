#include "pch.h"
#include "Functions.h"
#include "../../System/System.h"

Input::ISystem* Input::CreateSystem()
{
    return new System();
}
