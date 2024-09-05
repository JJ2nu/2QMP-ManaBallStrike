#pragma once
namespace Client
{
    namespace World
    {
        class MainStage;
        class LoadingStage;
        class Stage001;
        class Stage002;
        class Stage003;
        class Stage004;
        class CutSceneStage1;
        class CutSceneStage2;
        class EndingCredit;
    }

    namespace Canvas
    {
        class Main;
    }

    class System final : public Engine::System
    {
    public:
        System();
    
    protected:
        void CreateStages();
        void OnPreInitialize() override;
        void OnPostInitialize() override;
        //void OnPostFinalize() override;
        void KeyInitialize();
        void BindDeathThisStage() const;

    private:
        void DeclareInput();

        std::shared_ptr < Input::IMappingContext> playerContext;
        std::shared_ptr < Input::IMappingContext> cutSceneContext;
        
        std::shared_ptr<Canvas::Main> _mainCanvas;


        std::shared_ptr<World::MainStage> _mainStage;
        std::shared_ptr<World::Stage001> _stage001;
        std::shared_ptr<World::Stage002> _stage002;
        std::shared_ptr<World::Stage003> _stage003;
        std::shared_ptr<World::Stage004> _stage004;
        std::shared_ptr<World::CutSceneStage1> _cutScene1;
        std::shared_ptr<World::CutSceneStage2> _cutScene2;
        std::shared_ptr<World::EndingCredit> _EndingCredit;
 
        std::function<void()> _deathLogic;
    };
}
