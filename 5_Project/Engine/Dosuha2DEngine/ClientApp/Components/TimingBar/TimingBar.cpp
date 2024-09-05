#include "pch.h"
#include "TimingBar.h"

Client::Component::TimingBar::TimingBar()
    : UI(Engine::Math::Vector2{300, 55}), _width(272), _perfectZoneStart(168), _perfectZoneEnd(225), _makerSpeed(230),
      _startMargin(-3), _currentMargin(_startMargin), _isShow(false), _isMakerMove(false)
{
    auto [anchorChild, overlay]
        = GetRootPanel()->CreateChild<Engine::UI::Panel::Overlay>(Engine::Math::Vector2{300, 54});
    auto [overlayBarChild, bar] = overlay->CreateChild<Engine::UI::Wrapper::Image>(L"Resources/Sprites/UI/UI_004.png");
    auto [overlayCoverChild, cover] = overlay->CreateChild<Engine::UI::Wrapper::Image>(
        L"Resources/Sprites/UI/UI_004_1.png");
    auto [overlayMakerChild, maker] = overlay->CreateChild<Engine::UI::Wrapper::Image>(
        L"Resources/Sprites/UI/UI_005.png");
    _maker = maker;
    bar->SetMargin({5, 8, 0, 0});
    cover->SetMargin({0, 8, 0, 0});

    Reset();
}

void Client::Component::TimingBar::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateMaker(deltaGameTime);
    UI::Update(deltaMetaTime, deltaGameTime);
}

void Client::Component::TimingBar::Render(const Engine::Manager::Render::Renderer renderer,
                                          const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_isShow) UI::Render(renderer, cameraMatrix);
}

void Client::Component::TimingBar::Hide()
{
    _isShow = false;
}

void Client::Component::TimingBar::Show()
{
    _isShow = true;
}

void Client::Component::TimingBar::Start()
{
    _isMakerMove = true;
}

void Client::Component::TimingBar::Stop()
{
    _isMakerMove = false;
    if (_onPerfect != nullptr && _currentMargin > _perfectZoneStart && _currentMargin < _perfectZoneEnd) _onPerfect();
    else if (_onFail != nullptr) _onFail();
}

void Client::Component::TimingBar::Reset()
{
    _currentMargin = _startMargin;
    _maker->SetMargin({_currentMargin, 0, 0, 0});
    _isMakerMove = false;
}

void Client::Component::TimingBar::BindOnPerfect(const Event& event)
{
    _onPerfect = event;
}

void Client::Component::TimingBar::BindOnFail(const Event& event)
{
    _onFail = event;
}

bool Client::Component::TimingBar::IsMakerMove() const
{
    return _isMakerMove;
}

bool Client::Component::TimingBar::IsShow() const
{
    return _isShow;
}

void Client::Component::TimingBar::UpdateMaker(const float deltaTime)
{
    if (!_isMakerMove) return;
    _currentMargin += _makerSpeed * deltaTime;
    _maker->SetMargin({_currentMargin, 0, 0, 0});
    if (_currentMargin > _width) Stop();
}
