#pragma once

namespace Client::Object
{
    class KeyInformation : public Engine::Object::Base
    {
    public:
        void OnCreateComponent() override;
        void OnSetup() override;

        const Engine::Math::Rect& GetBound() const override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Bitmap> _bitmapComponent;
    };
}
