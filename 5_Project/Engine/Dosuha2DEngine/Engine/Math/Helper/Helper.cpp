#include "pch.h"
#include "Helper.h"

std::random_device Engine::Math::Helper::Random::_rd;
std::mt19937 Engine::Math::Helper::Random::_gen(_rd());

float Engine::Math::Helper::InverseSquareRoot::operator()(float value) const
{
    const __m128 fOneHalf = _mm_set_ss(0.5f);
    __m128 y0, x0, x1, x2, fOver2;
    float temp;

    y0 = _mm_set_ss(value);
    x0 = _mm_rsqrt_ss(y0); // 1/sqrt estimate (12 bits)
    fOver2 = _mm_mul_ss(y0, fOneHalf);

    // 1st Newton-Raphson iteration
    x1 = _mm_mul_ss(x0, x0);
    x1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(fOver2, x1));
    x1 = _mm_add_ss(x0, _mm_mul_ss(x0, x1));

    // 2nd Newton-Raphson iteration
    x2 = _mm_mul_ss(x1, x1);
    x2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(fOver2, x2));
    x2 = _mm_add_ss(x1, _mm_mul_ss(x1, x2));

    _mm_store_ss(&temp, x2);
    return temp;
}

float Engine::Math::Helper::SquareRoot::operator()(float value) const
{
    if (value <= 0) return 0;
    if (const int intValue = *reinterpret_cast<int*>(&value); 0 == (intValue >> 23 & 255)) return 0;
    return value * InverseSquareRoot()(value);
}

float Engine::Math::Helper::Random::operator()(const float min, const float max) const
{
    std::uniform_real_distribution dist(min, max);
    return dist(_gen);
}

int Engine::Math::Helper::Random::operator()(const int min, const int max) const
{
    std::uniform_int_distribution dist(min, max);
    return dist(_gen);
}

float Engine::Math::Helper::Lerp::operator()(float start, float end, float t)
{
    return (1 - t) * start + t * end;
}

float Engine::Math::Helper::EaseIn::operator()(float start, float end, float t)
{
    end -= start;
    return (end * t * t * t * t * t + start);
}

float Engine::Math::Helper::EaseOut::operator()(float start, float end, float t)
{
    end -= start;
    return (end * (1 - (1 - t) * (1 - t) * (1 - t) * (1 - t) * (1 - t)) + start);
}

void Engine::Math::Helper::GetSinCos::operator()(float& sin, float& cos, float degree)
{
    float radian = degree * DegreeToRadian;
    float quotient = (InvPi * 0.5f) * radian;
    if (radian >= 0.0f)
    {
        quotient = (float)((int)(quotient + 0.5f));
    }
    else
    {
        quotient = (float)((int)(quotient - 0.5f));
    }
    float y = radian - (2.0f * Pi) * quotient;

    float sign = 0.f;
    if (y > HalfPi)
    {
        y = Pi - y;
        sign = -1.0f;
    }
    else if (y < -HalfPi)
    {
        y = -Pi - y;
        sign = -1.0f;
    }
    else
    {
        sign = +1.0f;
    }

    float y2 = y * y;

    sin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
    
    float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
    cos = sign * p;
}

float Engine::Math::Helper::ArcTangent2::operator()(float y, float x) const
{
    return std::atan2f(y, x);
}

float Engine::Math::Helper::SmoothDamp::operator()(float current, float target, float& currentVelocity, float smoothTime, float deltaTime)
{
    float omega = 2.0f / smoothTime;
    float x = omega * deltaTime;
    float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
    float change = current - target;
    float originalTo = target;
    float maxChange = FLT_MAX;
    change = std::clamp(change, -maxChange, maxChange);
    target = current - change;

    float temp = (currentVelocity + omega * change) * deltaTime;
    currentVelocity = (currentVelocity - omega * temp) * exp;
    float output = target + (change + temp) * exp;

    if ((originalTo - current > 0.0f) == (output > originalTo))
    {
        output = originalTo;
        currentVelocity = (output - originalTo) / deltaTime;
    }

    return output;
}
