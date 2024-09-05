#include "pch.h"
#include "StageLoader.h"


Client::Manager::Wave::EnemyType Client::Manager::Wave::GetEnemyType(const std::wstring_view name)
{
    if (name == L"E1") return EnemyType::E1;
    if (name == L"E2") return EnemyType::E2;
    if (name == L"E3") return EnemyType::E3;
    if (name == L"E4") return EnemyType::E4;
    return EnemyType::Unknown;
}

int Client::Manager::SpawnerData::GetMonsterCount()
{
    return std::accumulate(waves.begin(), waves.end(), 0, [](int value, const Wave& wave)
    {
        return value + wave.enemies.size();
    });
}

int Client::Manager::StageData::GetTotalMonsterCount()
{
    return leftTop.GetMonsterCount() + rightTop.GetMonsterCount() + leftBottom.GetMonsterCount() + rightBottom.
        GetMonsterCount();
}

void Client::Manager::StageLoader::Initialize()
{
    for (const auto& sectionName : {L"Stage 1", L"Stage 2", L"Stage 3", L"Stage 4"})
    {
        if (auto section = Config::GetSection(sectionName))
        {
            const int stageNumber = std::stoi(section->GetString(L"StageNumber"));
            GetInstance()->LoadStageData(stageNumber, section);
        }
    }
}

Client::Manager::StageData Client::Manager::StageLoader::GetStageData(const int stageNumber)
{
    if (GetInstance()->_stageDataMap.contains(stageNumber)) return GetInstance()->_stageDataMap[stageNumber];
    return {};
}

void Client::Manager::StageLoader::LoadStageData(const int stageNumber, const std::shared_ptr<Config::Section>& section)
{
    _stageDataMap[stageNumber] = {
        LoadSpawnerData(section, L"LT"),
        LoadSpawnerData(section, L"RT"),
        LoadSpawnerData(section, L"LB"),
        LoadSpawnerData(section, L"RB"),
    };
}

Client::Manager::SpawnerData Client::Manager::StageLoader::LoadSpawnerData(
    const std::shared_ptr<Config::Section>& section, const std::wstring& position)
{
    SpawnerData spawnerData;
    spawnerData.waveInterval = section->GetFloat(L"WaveInterval");
    const int waveCount = section->GetInt(L"WaveCount");
    for (int i = 0; i < waveCount; i++)
    {
        spawnerData.waves.push_back(Wave{
            Config::GetSection(L"Spawner")->GetFloat(L"SpawnInterval"), LoadWaveData(section, i + 1, position)
        });
    }
    return spawnerData;
}

std::vector<Client::Manager::Wave::EnemyType> Client::Manager::StageLoader::LoadWaveData(
    const std::shared_ptr<Config::Section>& section, const int waveNumber, const std::wstring& position)
{
    std::vector<Wave::EnemyType> information;
    const std::wstring text = section->GetString(L"W" + std::to_wstring(waveNumber) + L"_" + position);
    std::wstringstream wss(text);
    std::wstring token;
    while (!wss.eof())
    {
        std::getline(wss, token, L' ');
        information.push_back(Wave::GetEnemyType(token));
    }
    return information;
}
