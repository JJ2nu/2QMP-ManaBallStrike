#pragma once

namespace Client
{
    class BackgroundMusic
    {
    public:
        explicit BackgroundMusic(std::filesystem::path path);

    protected:
        void Load();
        void Load(bool isLoop);
        void Load(std::filesystem::path path);
        void Release();
        void Play() const;
        bool IsPlaying() const;
        
    private:
        std::filesystem::path _path;
        std::unique_ptr<::Audio::ISound> _backgroundMusic;
    };
}
