#pragma once
#include "../Stage/Stage.h"
#include "BackgroundMusic/BackgroundMusic.h"

namespace Client::Object
{
    class CutScene;
    class EndingBackground;
    class EndingCreditScroller;
}
namespace Client::Component
{

    class EventBindAnimation;
    class BackgroundBitmap;
}

namespace Client::World
{
    class CutSceneStage1 : public Engine::World, public BackgroundMusic
    {
    public:
        using Event = std::function<void()>;

        CutSceneStage1();
        void BindRequestOpenUI(const Event& event);
        void BindOnStageClear(Event event);

    protected:
        void OnCreateObject() override;
        void OnSetup() override;
        void OnPostUpdate(float d1,float d2) override;
        void OnPreFinalize();
        void OnPostFinalize() override;


    private:
        std::shared_ptr<Object::CutScene> _cutScene1;
        std::shared_ptr<Object::CutScene> _cutScene2;
        std::shared_ptr<Object::CutScene> _cutScene3;
        std::shared_ptr<Object::CutScene> _cutScene4;
        size_t _cutSceneIdx = 0;

        Event _onStageClear;
        Event _requestOpenUI;

    };
    
    class CutSceneStage2 : public Engine::World, public BackgroundMusic
    {
    public:
        using Event = std::function<void()>;
        CutSceneStage2();
        
        void BindRequestOpenUI(const Event& event);
        void BindOnStageClear(Event event);

    protected:
        void OnCreateObject() override;
        void OnSetup() override;
        void OnPostUpdate(float d1, float d2) override;
        void OnPreFinalize() override;
        void OnPostFinalize() override;


    private:
        std::shared_ptr<Object::CutScene> _cutScene1;
        std::shared_ptr<Object::CutScene> _cutScene2;
        std::shared_ptr<Object::CutScene> _cutScene3;
        std::shared_ptr<Object::CutScene> _cutScene4;
        std::shared_ptr<Object::CutScene> _cutScene5;
        std::shared_ptr<Object::CutScene> _cutScene6;
        std::shared_ptr<Object::CutScene> _cutScene7;
        size_t _cutSceneIdx = 0;

        Event _onStageClear;
        Event _requestOpenUI;
    };
    class EndingCredit : public Engine::World, public BackgroundMusic
    {
    public:
        using Event = std::function<void()>;
        EndingCredit();
        
        void BindRequestOpenUI(const Event& event);
        void BindOnStageClear(Event event);

    protected:
        void OnCreateObject() override;
        void OnSetup() override;
        void OnPostUpdate(float d1, float d2) override;
        void OnPostFinalize() override;


    private:
        std::shared_ptr<Object::EndingBackground> _background;
        std::shared_ptr<Object::EndingCreditScroller> _endingCredit;



        Event _onStageClear;
        Event _requestOpenUI;
    };
}
