#include "pch.h"
#include "ConfigManager.h"

void Client::Manager::Config::Initialize(const std::wstring& configPath)
{
    GetInstance()->_configPath = std::filesystem::absolute(configPath);
}


const std::shared_ptr<Client::Manager::Config::Section>& Client::Manager::Config::GetSection(const std::wstring& name)
{
    auto& instance = GetInstance();
    if (!instance->_sections.contains(name))
        instance->_sections[name] = std::make_shared<Section>(
            instance->_configPath.wstring(), name);
    return instance->_sections[name];
}

Client::Manager::Config::Section::Section(std::wstring file, std::wstring name)
    : _file(std::move(file)), _name(std::move(name)), _bufferSize(1024), _buffer(new wchar_t[_bufferSize])
{
}

std::wstring Client::Manager::Config::Section::GetString(const std::wstring& key, const std::wstring& defaultValue)
{
    if (!_stringProperties.contains(key))
    {
        DWORD result = GetPrivateProfileString(_name.c_str(), key.c_str(), defaultValue.c_str(), _buffer, _bufferSize,
                                               _file.c_str());
        _stringProperties[key] = std::wstring(_buffer);
    }
    return _stringProperties[key];
}

int Client::Manager::Config::Section::GetInt(const std::wstring& key, int defaultValue)
{
    if (!_intProperties.contains(key))
    {
        _intProperties[key] = GetPrivateProfileInt(_name.c_str(), key.c_str(), defaultValue, _file.c_str());
    }
    return _intProperties[key];
}

float Client::Manager::Config::Section::GetFloat(const std::wstring& key, float defaultValue)
{
    if (!_floatProperties.contains(key))
    {
        DWORD result = GetPrivateProfileString(_name.c_str(), key.c_str(), std::to_wstring(defaultValue).c_str(), _buffer, _bufferSize,
                                               _file.c_str());
        _floatProperties[key] = std::wcstof(_buffer, nullptr);
    }
    return _floatProperties[key];
}
