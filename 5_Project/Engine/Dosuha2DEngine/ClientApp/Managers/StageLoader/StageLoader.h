#pragma once

namespace Client::Manager
{
    struct Wave
    {
        enum class EnemyType : uint8_t { Unknown, E1, E2, E3, E4 };
        static EnemyType GetEnemyType(std::wstring_view name);
        float spawnInterval;
        std::vector<EnemyType> enemies;
    };

    struct SpawnerData
    {
        float waveInterval;
        std::vector<Wave> waves;
        int GetMonsterCount();
    };

    struct StageData
    {
        SpawnerData leftTop;
        SpawnerData rightTop;
        SpawnerData leftBottom;
        SpawnerData rightBottom;
        int GetTotalMonsterCount();
    };

    class StageLoader : public Engine::Manager::Base<StageLoader>
    {
        friend const std::shared_ptr<StageLoader>& Engine::Manager::Base<StageLoader>::GetInstance();

    public:
        static void Initialize();
        static StageData GetStageData(int stageNumber);

    private:
        void LoadStageData(int stageNumber, const std::shared_ptr<Config::Section>& section);
        static SpawnerData LoadSpawnerData(const std::shared_ptr<Config::Section>& section, const std::wstring& position);
        static std::vector<Wave::EnemyType> LoadWaveData(const std::shared_ptr<Config::Section>& section,
                                                         int waveNumber, const std::wstring& position);

        std::map<int, StageData> _stageDataMap;
    };
}
