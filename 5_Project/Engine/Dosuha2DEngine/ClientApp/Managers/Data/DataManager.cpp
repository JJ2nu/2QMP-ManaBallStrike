#include "pch.h"
#include "DataManager.h"

void Client::Manager::Data::Initialize()
{
    GetInstance()->_maxHealthPoint = Engine::Manager::Observer<float>::CreateSubject(L"MaxHealthPoint");
    GetInstance()->_healthPoint = Engine::Manager::Observer<float>::CreateSubject(L"HealthPoint");
    GetInstance()->_maxManaBallCount = Engine::Manager::Observer<int>::CreateSubject(L"MaxManaBallCount");
    GetInstance()->_manaBallCount = Engine::Manager::Observer<int>::CreateSubject(L"ManaBallCount");
    GetInstance()->_speed = Engine::Manager::Observer<float>::CreateSubject(L"Speed");
    GetInstance()->_monsterCount = Engine::Manager::Observer<int>::CreateSubject(L"MonsterCount");

    GetInstance()->_initialHealth = Config::GetSection(L"Player")->GetFloat(L"Health");
    GetInstance()->_initialManaBall = Config::GetSection(L"ManaBall")->GetInt(L"BallCount");
    GetInstance()->_initialSpeed = Config::GetSection(L"Player")->GetFloat(L"Speed");
    GetInstance()->_speed->SetValue(GetInstance()->_initialSpeed);
    GetInstance()->_monsterCount->SetValue(0);
    
    Reset();
}

void Client::Manager::Data::UpgradeHealth()
{
    GetInstance()->_additionalHealth += 20.f;
    GetInstance()->_maxHealthPoint->SetValue(GetInstance()->_initialHealth + GetInstance()->_additionalHealth);
    ResetHealthPoint();
}

void Client::Manager::Data::UpgradeManaBall()
{
    GetInstance()->_additionalManaBall += 1;
    GetInstance()->_maxManaBallCount->SetValue(GetInstance()->_initialManaBall + GetInstance()->_additionalManaBall);
    ResetManaBallCount();
}

void Client::Manager::Data::UpgradeSpeed()
{
    GetInstance()->_additionalSpeedRatio += 0.2f;
    GetInstance()->_speed->SetValue(GetInstance()->_initialSpeed * GetInstance()->_additionalSpeedRatio);
}

void Client::Manager::Data::UpgradeManaBallBounce()
{
    GetInstance()->_additionalManaBallBounce += 3;
}

float Client::Manager::Data::GetMaxHealthPoint()
{
    return GetInstance()->_maxHealthPoint->GetValue();
}

float Client::Manager::Data::GetHealthPoint()
{
    return GetInstance()->_healthPoint->GetValue();
}

void Client::Manager::Data::SetHealthPoint(const float value)
{
    float newHp = value;
    newHp = Engine::Math::Helper::Max()(newHp, 0.f);
    newHp = Engine::Math::Helper::Min()(newHp, GetMaxHealthPoint());
    GetInstance()->_healthPoint->SetValue(newHp);
}

int Client::Manager::Data::GetMaxManaBallCount()
{
    return GetInstance()->_maxManaBallCount->GetValue();
}

int Client::Manager::Data::GetManaBallCount()
{
    return GetInstance()->_manaBallCount->GetValue();
}

void Client::Manager::Data::SetManaBallCount(const int value)
{
    GetInstance()->_manaBallCount->SetValue(value);
}

float Client::Manager::Data::GetSpeed()
{
    return GetInstance()->_speed->GetValue();
}

void Client::Manager::Data::ResetHealthPoint()
{
    GetInstance()->_healthPoint->SetValue(GetInstance()->_maxHealthPoint->GetValue());
}

void Client::Manager::Data::ResetManaBallCount()
{
    GetInstance()->_manaBallCount->SetValue(GetInstance()->_maxManaBallCount->GetValue());
}

void Client::Manager::Data::SetMonsterCount(const int count)
{
    GetInstance()->_monsterCount->SetValue(count);
}

void Client::Manager::Data::AddMonsterCount(const int count)
{
    GetInstance()->_monsterCount->SetValue(GetInstance()->_monsterCount->GetValue() + count);
}

void Client::Manager::Data::DecreaseMonsterCount()
{
    GetInstance()->_monsterCount->SetValue(GetInstance()->_monsterCount->GetValue() - 1);
}

int Client::Manager::Data::GetAdditionalManaBallCount()
{
    return GetInstance()->_additionalManaBallBounce;
}

void Client::Manager::Data::Reset()
{
    GetInstance()->_maxHealthPoint->SetValue(GetInstance()->_initialHealth);
    GetInstance()->_healthPoint->SetValue(GetInstance()->_initialHealth);
    GetInstance()->_maxManaBallCount->SetValue(GetInstance()->_initialManaBall);
    GetInstance()->_manaBallCount->SetValue(GetInstance()->_initialManaBall);

    GetInstance()->_additionalHealth = 0.f;
    GetInstance()->_additionalManaBall = 0;
    GetInstance()->_additionalSpeedRatio = 1.f;
    GetInstance()->_additionalManaBallBounce = 0;
}
