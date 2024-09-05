#include "pch.h"
#include "ManaBallCounter.h"

#include "UI/Number/Number.h"

Client::UI::ManaBallCounter::ManaBallCounter()
    : Stack(Engine::Math::Vector2(600, 64))
{
    auto [_5, overlay] = CreateChild<Engine::UI::Panel::Overlay>(Engine::Math::Vector2{64, 64});

    auto [_0, black] = overlay->CreateChild<Engine::UI::Wrapper::Hidable>(Engine::Math::Vector2(64, 64));
    _black = black;
    auto manaBallBlack = _black->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2(64, 64), L"Resources/Sprites/UI/UI_008_1.png");
    _black->Show();

    auto [_6, white] = overlay->CreateChild<Engine::UI::Wrapper::Hidable>(Engine::Math::Vector2{64, 64});
    _white = white;
    auto manaBallWhite = _white->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{64, 64}, L"Resources/Sprites/UI/UI_008_2.png");
    _white->Hide();

    auto [_8, animation] = overlay->CreateChild<Engine::UI::Wrapper::Hidable>(Engine::Math::Vector2{64, 64});
    _animationCover = animation;
    _animation= _animationCover->CreateChild<Engine::UI::Wrapper::Animation>(Engine::Math::Vector2{96,96}, L"Resources/Sprites/UI/UI_008.png", L"Resources/Animation/UI/ManaBall/ManaBall.csv" );
    _animation->SetMargin({-16,-16,-16,-16});

    auto [_4, x] = CreateChild<Number>(Engine::Math::Vector2(80, 64));
    x->SetNumber(-1);
    x->SetMargin({8, 0, 8, 0});
    auto [_1, currentBall] = CreateChild<Number>(Engine::Math::Vector2(64, 64));
    _ballCountUI = currentBall;
    auto [_2, slash] = CreateChild<Number>(Engine::Math::Vector2(64, 64));
    slash->SetNumber(-2);
    slash->SetPadding({8, 0, 0, 0});
    auto [_3, maxBall] = CreateChild<Number>(Engine::Math::Vector2(64, 64));
    _maxBallCountUI = maxBall;
}

void Client::UI::ManaBallCounter::Initialize(Engine::Manager::Resource::Loader loader)
{
    Stack::Initialize(loader);
    _restoreSound = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_014.wav", Audio::ChannelGroupType::Effect, false);
    
    _ballCountUI->SetNumber(Manager::Data::GetManaBallCount());
    _maxBallCountUI->SetNumber(Manager::Data::GetMaxManaBallCount());
    Engine::Manager::Observer<int>::Register(L"ManaBallCount", [this](const int value)
    {
        if (value > _ballCountUI->GetNumber())
        {
            _animation->SetMotion(L"Shine");
            _animationCover->Show();
            _restoreSound->Play();
            _restoreSound->SetVolume(0.2f);
        }
        _ballCountUI->SetNumber(value);
        if (value == 0)
        {
            _black->Show();
            _white->Hide();
        }
        else
        {
            _white->Show();
            _black->Hide();
        }
    });
    Engine::Manager::Observer<int>::Register(L"MaxManaBallCount", [this](const int value)
    {
        _maxBallCountUI->SetNumber(value);
    });
    _animation->BindLastFrameEvent(L"Shine", [this]
    {
        _animationCover->Hide();
    });
    _animation->SetMotion(L"Shine");
}

void Client::UI::ManaBallCounter::Finalize()
{
    Stack::Finalize();
    _restoreSound = nullptr;
}
