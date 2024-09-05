#include "pch.h"
#include "BackgroundBitmap.h"

Client::Component::BackgroundBitmap::BackgroundBitmap(std::wstring path)
    : Bitmap(path)
{

}
void Client::Component::BackgroundBitmap::SetBackgroundBitmap()
{
    IsRenderable = false;
    Engine::Manager::Render::GetShader()->SetBackground(_bitmap.Get());
    Engine::Manager::Render::GetShader()->SetScreenSize(GetSize());
}