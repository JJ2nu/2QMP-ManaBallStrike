#include "pch.h"
#include "Spawner.h"

#include <utility>
#include "../../Enemies/Enemies.h"

Client::Object::Spawner::Spawner(Manager::SpawnerData data, const Engine::Math::Vector2& location, const bool isBottom)
    : _data(std::move(data)), _isBottom(isBottom), _waveIndex(0), _isSpawning(true),
      _currentWave(_data.waves[_waveIndex].enemies.begin(), _data.waves[_waveIndex].enemies.end()),
      _waveElapsedTime(_data.waveInterval), _spawnElapsedTime(0.0f), _onWaveEnd(nullptr), _onFinish(nullptr), _location(location),
      _isFinish(false)
{
}

void Client::Object::Spawner::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);
    if (_isBottom) return;
    _bitmapComponent = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/door/doorback.png");
    _bitmapComponent->SetParentScene(_rootScene);
    _bitmapComponent->SetScale({0.95f, 1.08f});
    _bitmapComponent->SetLocation({0, -30});
    _doorEye = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/door/object_010.png",
                                                             L"Resources/Animation/door/DoorEye.csv");
    _doorEye->SetParentScene(_rootScene);
    _doorEye->SetScale({0.6f, 0.6f});
    _doorShadow = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/door/object_010_1.png",
                                                                L"Resources/Animation/door/DoorShadow.csv");
    _doorShadow->SetParentScene(_rootScene);
    _doorShadow->SetLocation({0, 125});
    _doorShadow->SetScale({0.8f, 0.8f});
}

void Client::Object::Spawner::OnSetup()
{
    _rootScene.lock()->SetLocation(_location);
    if (_isBottom) return;
    _boundComponent->SetSize(_bitmapComponent->GetSize() * 0.75f);
    _doorShadow->SetMotion(L"Idle");
    _doorEye->SetMotion(L"Idle");
}

void Client::Object::Spawner::SetTargetScene(const std::shared_ptr<Engine::Scene>& targetScene)
{
    _targetScene = targetScene;
}

const Engine::Math::Rect& Client::Object::Spawner::GetBound() const
{
    return _boundComponent->GetBound();
}

void Client::Object::Spawner::NextWave()
{
    _isSpawning = true;
    _waveElapsedTime = 0.0f;
    _waveIndex++;
    if (_waveIndex < _data.waves.size())
        _currentWave = std::deque(_data.waves[_waveIndex].enemies.begin(),
                                  _data.waves[_waveIndex].enemies.end());
    else _waveIndex = 0;
}

void Client::Object::Spawner::BindOnWaveEnd(Event event)
{
    _onWaveEnd = std::move(event);
}

void Client::Object::Spawner::BindOnFinish(Event event)
{
    _onFinish = std::move(event);
}

bool Client::Object::Spawner::IsFinished() const
{
    return _isFinish;
}

void Client::Object::Spawner::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    UpdateRenderOrder();
    SpawnWave(deltaGameTime);
}

void Client::Object::Spawner::SpawnWave(float deltaTime)
{
    if (!_isSpawning || _isFinish) return;
    _waveElapsedTime += deltaTime;
    if (_waveElapsedTime < _data.waveInterval) return;
    SpawnEnemy(deltaTime);
}

void Client::Object::Spawner::SpawnEnemy(const float deltaTime)
{
    _spawnElapsedTime += deltaTime;
    if (_spawnElapsedTime < _data.waves[_waveIndex].spawnInterval) return;
    if (_currentWave.empty())
    {
        _isSpawning = false;
        if (_onWaveEnd != nullptr)
        {
            _onWaveEnd();
        }
        if (_waveIndex == _data.waves.size() - 1)
        {
            _isFinish = true;
            if (_onFinish != nullptr) _onFinish();
        }
    }
    else
    {
        switch (_currentWave.front())
        {
        case Manager::Wave::EnemyType::E1:
            _owner.lock()->CreateObject<EnemyType001>(GetSpawnLocation(), _targetScene)->Initialize(
                Engine::Manager::Resource::GetLoader());
            break;
        case Manager::Wave::EnemyType::E2:
            _owner.lock()->CreateObject<EnemyType002>(GetSpawnLocation(), _targetScene)->Initialize(
                Engine::Manager::Resource::GetLoader());
            break;
        case Manager::Wave::EnemyType::E3:
            _owner.lock()->CreateObject<EnemyType003>(GetSpawnLocation(), _targetScene)->Initialize(
                Engine::Manager::Resource::GetLoader());
            break;
        case Manager::Wave::EnemyType::E4:
            _owner.lock()->CreateObject<EnemyType004>(GetSpawnLocation(), _targetScene)->Initialize(
                Engine::Manager::Resource::GetLoader());
            break;
        case Manager::Wave::EnemyType::Unknown:
            break;
        }
        _currentWave.pop_front();
        _spawnElapsedTime -= _data.waves[_waveIndex].spawnInterval;
    }
}

void Client::Object::Spawner::UpdateRenderOrder()
{
    if (!_isBottom) _renderOrder = GetBound().bottom - 20;
}

Engine::Math::Vector2 Client::Object::Spawner::GetSpawnLocation() const
{
    return _rootScene.lock()->GetLocation() + Engine::Math::Vector2(0, 50.0f);
}
