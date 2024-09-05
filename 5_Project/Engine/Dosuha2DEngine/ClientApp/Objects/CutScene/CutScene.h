#pragma once

namespace Client
{
    namespace Object
    {
        class CutScene : public Engine::Object::Base
        {
        public:
            using Event = std::function<void()>;

            CutScene(size_t idx, std::wstring path , bool isLastCut);
            [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
            void FadeIn();
            void FadeOut();
            void SetRender(bool isrender)
            {
                _bitmapComponent->IsRenderable = isrender;
            }
            size_t _idx = 0;
            bool _isLastCut = false;
        protected:
            void OnCreateComponent() override;
            void OnSetup() override;

        private:
            std::shared_ptr<Engine::Component::Bound> _boundComponent;
            std::shared_ptr<Engine::Component::FadeBitmap> _bitmapComponent;
            std::wstring _path;

        };
    }
}