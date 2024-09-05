#pragma once

namespace Client::Component
{
    class BackgroundBitmap;
}

namespace Client::Object
{
    class LoadingBackground : public Engine::Object::Base
    {
    public:
        LoadingBackground(float initialYLocation);
        const Engine::Math::Rect& GetBound() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Component::BackgroundBitmap> _bitmapComponent;
        float _initialYLocation;
    };
}
