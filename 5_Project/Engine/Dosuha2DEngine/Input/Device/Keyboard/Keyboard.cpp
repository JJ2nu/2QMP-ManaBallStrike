#include "pch.h"
#include "Keyboard.h"

Input::Device::Keyboard::Keyboard()
    : _keys(static_cast<size_t>(Key::Max))
{
}

void Input::Device::Keyboard::Update()
{
    for (unsigned char keyIndex = 0; keyIndex < static_cast<unsigned char>(Key::Max); ++keyIndex)
    {
        _keys[static_cast<Key>(keyIndex)].SetValue(GetAsyncKeyState(keyIndex) & 0x8000);
    }
}

void Input::Device::Keyboard::Reset()
{
    std::ranges::for_each(_keys, [](auto& key) { key.second.Reset(); });
}

Input::Component::IComponent* Input::Device::Keyboard::GetComponent(const Key key)
{
    return &_keys[key];
}
