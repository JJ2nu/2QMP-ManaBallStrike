#include "pch.h"
#include "Upgrade.h"
#include "../../UI/Card/Card.h"

Client::UI::Upgrade::Upgrade(const Engine::Math::Vector2& size)
    : Anchor(size), _isShown(false), _cardOpenElapsedTime(0), _cardOpenDelay(2.0f), _isCardOpen(false),
      _isUpgrade(false), _upgradeCompleteDelay(1.0f), _upgradeCompleteElapsedTime(0)
{
    auto [anchorAnchorChild, anchor] = CreateChild<Anchor>(Engine::Math::Vector2{1200, 900});
    anchorAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Center);

    auto [bookAnchorChild, book] = anchor->CreateChild<Engine::UI::Wrapper::Animation>(
        Engine::Math::Vector2{1200, 640}, L"Resources/Sprites/Illust/mon_005_3_1.png",
        L"Resources/Animation/Book/Book.csv");
    bookAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Bottom);
    _book = book;

    auto [card1AnchorChild, card1]
        = anchor->CreateChild<Card>(Engine::Math::Vector2{300, 600},
                                    L"Resources/Sprites/Illust/illust_002.png",
                                    L"Resources/Sprites/Illust/illust_002_1.png");
    card1AnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Left, AnchorChild::VerticalAnchoring::Center);
    _healthCard = card1;

    auto [card2AnchorChild, card2]
        = anchor->CreateChild<Card>(Engine::Math::Vector2{300, 600},
                                    L"Resources/Sprites/Illust/illust_003.png",
                                    L"Resources/Sprites/Illust/illust_003_1.png");
    card2AnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Center);
    _manaBallCard = card2;

    auto [card3AnchorChild, card3]
        = anchor->CreateChild<Card>(Engine::Math::Vector2{300, 600},
                                    L"Resources/Sprites/Illust/illust_004.png",
                                    L"Resources/Sprites/Illust/illust_004_1.png");
    card3AnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Right, AnchorChild::VerticalAnchoring::Center);
    _speedCard = card3;

    auto [textAnchorChild, text] = anchor->CreateChild<Engine::UI::Wrapper::FadeImage>(
        Engine::Math::Vector2{1000, 200}, L"Resources/Sprites/Illust/illust_005_1.png");
    textAnchorChild->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Top);
    _text = text;
    _text->SetDuration(_cardOpenDelay);

    _healthCard->BindOnClick([this]
    {
        if (_isUpgrade) return;
        _manaBallCard->Deactivate();
        _speedCard->Deactivate();
        _isUpgrade = true;
        Manager::Data::UpgradeHealth();
        Manager::Data::UpgradeManaBallBounce();
    });

    _manaBallCard->BindOnClick([this]
    {
        if (_isUpgrade) return;
        _healthCard->Deactivate();
        _speedCard->Deactivate();
        _isUpgrade = true;
        Manager::Data::UpgradeManaBall();
        Manager::Data::UpgradeManaBallBounce();
    });

    _speedCard->BindOnClick([this]
    {
        if (_isUpgrade) return;
        _healthCard->Deactivate();
        _manaBallCard->Deactivate();
        _isUpgrade = true;
        Manager::Data::UpgradeSpeed();
        Manager::Data::UpgradeManaBallBounce();
    });
}

void Client::UI::Upgrade::Initialize(const Engine::Manager::Resource::Loader loader)
{
    Anchor::Initialize(loader);
    _book->SetMotion(L"Open");
    _book->BindLastFrameEvent(L"Open", [this] { _book->SetMotion(L"Shine"); });
    _book->BindLastFrameEvent(L"Shine", [this] { _book->SetMotion(L"Loop"); });
    _cardOpenSound = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_026.wav",
                                                         Audio::ChannelGroupType::Effect, false);
    _upgradeCompleteSound = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_027.wav",
                                                                Audio::ChannelGroupType::Effect, false);
}

void Client::UI::Upgrade::Update(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isShown)
    {
        Anchor::Update(deltaMetaTime, deltaGameTime);
        UpdateCardOpen(deltaGameTime);
        UpdateUpgradeComplete(deltaGameTime);
    }
}

void Client::UI::Upgrade::LazyUpdate(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isShown) Anchor::LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Client::UI::Upgrade::Render(const Engine::Manager::Render::Renderer renderer, const Engine::Math::Rect baseRect)
{
    if (_isShown) Anchor::Render(renderer, baseRect);
}

void Client::UI::Upgrade::Finalize()
{
    Anchor::Finalize();
    _cardOpenSound = nullptr;
    _upgradeCompleteSound = nullptr;
}

void Client::UI::Upgrade::Hide()
{
    _isShown = false;
}

void Client::UI::Upgrade::Show()
{
    _isShown = true;
    _text->FadeIn();
}

bool Client::UI::Upgrade::IsShown() const
{
    return _isShown;
}

void Client::UI::Upgrade::BindOnUpgradeComplete(const Event& event)
{
    _onUpgradeComplete = event;
}

void Client::UI::Upgrade::Reset()
{
    _healthCard->Reset();
    _manaBallCard->Reset();
    _speedCard->Reset();
    _isShown = false;
    _cardOpenElapsedTime = 0.0f;
    _isCardOpen = false;
    _isUpgrade = false;
    _upgradeCompleteElapsedTime = 0.0f;
    _book->SetMotion(L"Open");
    _text->Reset();
}

void Client::UI::Upgrade::UpdateCardOpen(const float deltaTime)
{
    if (_isCardOpen) return;
    _cardOpenElapsedTime += deltaTime;
    if (_cardOpenElapsedTime < _cardOpenDelay) return;
    _healthCard->Activate();
    _manaBallCard->Activate();
    _speedCard->Activate();
    _cardOpenSound->Play();
    _cardOpenElapsedTime = 0;
    _isCardOpen = true;
}

void Client::UI::Upgrade::UpdateUpgradeComplete(const float deltaTime)
{
    if (!_isUpgrade) return;
    _upgradeCompleteElapsedTime += deltaTime;
    if (_upgradeCompleteElapsedTime < _upgradeCompleteDelay) return;
    _upgradeCompleteSound->Play();
    _onUpgradeComplete();
    _isUpgrade = false;
}
