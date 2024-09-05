#include "pch.h"
#include "Loader.h"

#include "../Asset/Asset.h"

Animation::Loader::Loader()
    : _referenceCount(1)
{
}

void Animation::Loader::AddReference()
{
    ++_referenceCount;
}

long Animation::Loader::Release()
{
    if (--_referenceCount > 0) return _referenceCount;
    delete this;
    return 0;
}

void Animation::Loader::CreateAsset(const std::wstring& path, IAsset** asset) const
{
    Asset* tempAsset = new Asset();

    std::wifstream file(path);
    ThrowRuntimeErrorIf<Exception::RuntimeException>()(!file.is_open(), L"Failed to open file: " + path);
    std::wstring line;
    size_t motionCount = 0;
    {
        std::getline(file, line);
        std::wstringstream wss(line);
        wss >> motionCount;
    }
    for (size_t i = 0; i < motionCount; ++i)
    {
        std::getline(file, line);
        {
            std::wstringstream wss(line);
            std::wstring motionName;
            std::getline(wss, motionName, L',');
            std::wstring motionLoop;
            std::getline(wss, motionLoop, L',');
            bool loop = static_cast<bool>(std::stoi(motionLoop));
            std::wstring motionFile;
            std::getline(wss, motionFile, L',');
            std::wstring motionPath = path.substr(0, path.find_last_of(L"/\\") + 1).append(motionFile);
            tempAsset->LoadMotion(motionName, loop, motionPath);
        }
    }
    *asset = tempAsset;
}
