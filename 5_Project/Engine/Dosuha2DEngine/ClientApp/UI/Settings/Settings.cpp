#include "pch.h"
#include "Settings.h"

Client::UI::Settings::Settings(const Engine::Math::Vector2& size)
    : Anchor(size), _isShown(false), _backgroundSize(size), _maxValue(709.f), _defaultRightPadding(47.0f)
{
    auto [anchorChild, overlay]
        = CreateChild<Engine::UI::Panel::Overlay>(_backgroundSize);
    anchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Center);
    auto [backgroundOverlayChild, background]
        = overlay->CreateChild<Engine::UI::Wrapper::Box>(Engine::Math::Vector2{_backgroundSize},
                                                         D2D1::ColorF(D2D1::ColorF(D2D1::ColorF::Black, 0.7f)));
    auto [anchorOverlayChild, anchor]
        = overlay->CreateChild<Anchor>(_backgroundSize);
    auto [stackAnchorChild, stack] = anchor->CreateChild<Engine::UI::Panel::Stack>(Engine::Math::Vector2{
        Engine::Math::Vector2{1000, 800}
    });
    stackAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Center);
    stack->SetOrientation(Engine::UI::Panel::Stack::Orientation::Vertical);
    auto [titleAnchorStackChild, titleAnchor]
        = stack->CreateChild<Anchor>(Engine::Math::Vector2{1000, 200});
    auto [titleAnchorChild, title]
        = titleAnchor->CreateChild<Engine::UI::Wrapper::Image>(Engine::Math::Vector2{486, 114},
                                                               L"Resources/Sprites/UI/UI_013.png");
    titleAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Center);
    auto [masterStackStackChild, masterStack] = stack->CreateChild<Engine::UI::Panel::Stack>(Engine::Math::Vector2{
        1000, 200
    });
    masterStack->SetOrientation(Engine::UI::Panel::Stack::Orientation::Horizontal);
    auto [masterIconChild, masterIcon] = masterStack->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{200, 200}, L"Resources/Sprites/UI/UI_012.png");
    masterIcon->SetPadding({22.5f, 15.5f, 22.5f, 15.5});
    auto [masterOverlayChild, masterOverlay] = masterStack->CreateChild<Engine::UI::Panel::Overlay>(
        Engine::Math::Vector2{800, 200});
    auto [masterCaseChild, masterCase] = masterOverlay->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{800, 200}, L"Resources/Sprites/UI/UI_006_1.png");
    masterCase->SetPadding({0, 83, 0, 83});
    auto [masterBarChild, masterBar] = masterOverlay->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{800, 200}, L"Resources/Sprites/UI/UI_006.png");
    _masterBar = masterBar;
    _masterBar->SetPadding({44, 96, _defaultRightPadding, 96});
    auto [masterSliderChild, masterSlider] = masterOverlay->CreateChild<Engine::UI::Element::SlideButton>(
        Engine::Math::Vector2{_maxValue, 8});
    masterSlider->SetPadding({44, 96, _defaultRightPadding, 96});
    masterSlider->BindOnSlide([this](const float value)
    {
        _masterBar->SetPadding({44, 96, _defaultRightPadding + _maxValue * (1 - value), 96});
        Engine::Manager::Audio::SetVolume(value);
    });

    auto [backgroundStackStackChild, backgroundStack] = stack->CreateChild<Engine::UI::Panel::Stack>(
        Engine::Math::Vector2{1000, 200});
    backgroundStack->SetOrientation(Engine::UI::Panel::Stack::Orientation::Horizontal);
    auto [backgroundIconChild, backgroundIcon] = backgroundStack->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{200, 200}, L"Resources/Sprites/UI/UI_011.png");
    backgroundIcon->SetPadding({24.f, 11.f, 24.f, 11.f});
    auto [backgroundOverlayChild2, backgroundOverlay] = backgroundStack->CreateChild<Engine::UI::Panel::Overlay>(
        Engine::Math::Vector2{800, 200});
    auto [backgroundCaseChild, backgroundCase] = backgroundOverlay->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{800, 200}, L"Resources/Sprites/UI/UI_006_1.png");
    backgroundCase->SetPadding({0, 83, 0, 83});
    auto [backgroundBarChild, backgroundBar] = backgroundOverlay->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{800, 200}, L"Resources/Sprites/UI/UI_006.png");
    _backgroundBar = backgroundBar;
    _backgroundBar->SetPadding({44, 96, _defaultRightPadding, 96});
    auto [backgroundSliderChild, backgroundSlider] = backgroundOverlay->CreateChild<Engine::UI::Element::SlideButton>(
        Engine::Math::Vector2{_maxValue, 8});
    backgroundSlider->SetPadding({44, 96, _defaultRightPadding, 96});
    backgroundSlider->BindOnSlide([this](const float value)
    {
        _backgroundBar->SetPadding({44, 96, _defaultRightPadding + _maxValue * (1 - value), 96});
        Engine::Manager::Audio::SetVolume(Audio::ChannelGroupType::Background, value);
    });

    auto [restartAndQuitStackChild, restartAndQuit] = stack->CreateChild<Anchor>(Engine::Math::Vector2{800, 200});
    restartAndQuit->SetPadding({150, 0, 0, 0});
    auto [restartAnchorChild, restart] = restartAndQuit->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{309, 134}, L"Resources/Sprites/UI/icon_007.png");
    restartAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Left, AnchorChild::VerticalAnchoring::Center);
    _restartButton = restart->CreateChild<Engine::UI::Wrapper::Button>(Engine::Math::Vector2{400, 134});
    auto [quitAnchorChild, quit] = restartAndQuit->CreateChild<Engine::UI::Wrapper::Image>(
        Engine::Math::Vector2{198, 126}, L"Resources/Sprites/UI/icon_011.png");
    quitAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Right, AnchorChild::VerticalAnchoring::Center);
    _quitButton = quit->CreateChild<Engine::UI::Wrapper::Button>(Engine::Math::Vector2{192, 126});
}

void Client::UI::Settings::Update(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isShown) Anchor::Update(deltaMetaTime, deltaGameTime);
}

void Client::UI::Settings::LazyUpdate(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isShown) Anchor::LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Client::UI::Settings::Render(const Engine::Manager::Render::Renderer renderer, const Engine::Math::Rect baseRect)
{
    if (_isShown) Anchor::Render(renderer, baseRect);
}

void Client::UI::Settings::Hide()
{
    _isShown = false;
}

void Client::UI::Settings::Show()
{
    _isShown = true;
}

bool Client::UI::Settings::IsShown() const
{
    return _isShown;
}

void Client::UI::Settings::BindOnQuit(const Event& event) const
{
    _quitButton->BindOnClick(event);
}

void Client::UI::Settings::BindOnRestart(const Event& event) const
{
    _restartButton->BindOnClick(event);
}
