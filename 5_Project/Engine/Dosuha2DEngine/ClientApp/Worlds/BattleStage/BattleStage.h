#pragma once
#include "../Stage/Stage.h"

namespace Client
{
    namespace Object
    {
        class Spawner;
        class Boss;
    }

    namespace World
    {
        class BattleStage : public Stage
        {
        protected:
            BattleStage();
            void OnCreateObject() override;
            void OnSetup() override;
            void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
            void OnPreFinalize() override;

            Manager::StageData _stageData;

            std::shared_ptr<Client::Object::Boss> _boss;

        private:
            void UpdateWave() ;
            std::shared_ptr<Object::Spawner> _leftTop;
            std::shared_ptr<Object::Spawner> _rightTop;
            std::shared_ptr<Object::Spawner> _leftBottom;
            std::shared_ptr<Object::Spawner> _rightBottom;

            bool _wasWaveDone;
            bool _leftTopWaveDone;
            bool _rightTopWaveDone;
            bool _leftBottomWaveDone;
            bool _rightBottomWaveDone;
            int _monsterCountRegister;
        };
    }
}
