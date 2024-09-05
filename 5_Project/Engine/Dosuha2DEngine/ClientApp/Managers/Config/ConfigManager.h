#pragma once

namespace Client::Manager
{
    class Config : public Engine::Manager::Base<Config>
    {
        friend const std::shared_ptr<Config>& Engine::Manager::Base<Config>::GetInstance();

    public:
        class Section;

        static void Initialize(const std::wstring& configPath);
        static const std::shared_ptr<Section>& GetSection(const std::wstring& name);

    private:
        std::filesystem::path _configPath;
        std::map<std::wstring, std::shared_ptr<Section>> _sections;

    public:
        class Section
        {
        public:
            explicit Section(std::wstring file, std::wstring name);

            [[nodiscard]] std::wstring GetString(const std::wstring& key, const std::wstring& defaultValue = L"");
            [[nodiscard]] int GetInt(const std::wstring& key, int defaultValue = 0);
            [[nodiscard]] float GetFloat(const std::wstring& key, float defaultValue = 0.f);

        private:
            std::wstring _file;
            std::wstring _name;

            size_t _bufferSize;
            wchar_t* _buffer;

            std::map<std::wstring, std::wstring> _stringProperties;
            std::map<std::wstring, int> _intProperties;
            std::map<std::wstring, float> _floatProperties;
        };
    };
}
