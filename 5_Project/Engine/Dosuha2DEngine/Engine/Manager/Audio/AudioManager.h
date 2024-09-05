#pragma once

namespace Engine::Manager
{
    class Audio : public Base<Audio>
    {
        friend const std::shared_ptr<Audio>& Manager::Base<Audio>::GetInstance();
    public:
        static void Initialize();
        static std::unique_ptr<::Audio::ISound> CreateSound(const std::filesystem::path& path, ::Audio::ChannelGroupType type, bool isLoop);
        static void Update();
        static void Finalize();
        
        static void SetVolume(float volume);
        static void SetVolume(::Audio::ChannelGroupType group, float volume);

    private:
        std::unique_ptr<::Audio::ISystem> _system;
    };
}
