#include "pch.h"
#include "Functions.h"
#include "../../System/System.h"

void Render::COMInitialize()
{
    ThrowResultErrorIf<Exception::ResultException>()(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED),
                                                     L"Failed to initialize COM.");
}

void Render::COMUninitialize()
{
    CoUninitialize();
}

void Render::CreateSystem(ISystem** system)
{
    *system = new System();
}

