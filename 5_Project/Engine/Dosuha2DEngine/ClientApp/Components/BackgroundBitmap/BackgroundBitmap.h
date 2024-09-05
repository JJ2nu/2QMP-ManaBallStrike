#pragma once

namespace Client::Component
{
    class BackgroundBitmap : public Engine::Component::Bitmap 
    {
    public:
        explicit BackgroundBitmap(std::wstring path);
        void SetBackgroundBitmap();
    };
}
