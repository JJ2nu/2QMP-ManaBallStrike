#pragma once

namespace Engine::Math::Helper
{
	static constexpr float RadianToDegree = 57.295779513082320876798154814105f;
	static constexpr float DegreeToRadian = 0.01745329251994329576923690768489f;
	static constexpr float Pi = 3.1415926535897932384626433832795f;
	static constexpr float HalfPi = 1.5707963267948966192313216916398f;
	static constexpr float InvPi = 0.3183098861837906715377675267450f;

	struct InverseSquareRoot
	{
		float operator()(float value) const;
	};

	struct SquareRoot
	{
		float operator()(float value) const;
	};

	struct Abs
	{
		template <typename T>
		T operator()(const T& value) const
		{
			return value >= static_cast<T>(0) ? value : -value;
		}
	};

	struct Min
	{
		/*template <typename T>
		T operator()(const T& lhs, const T& rhs) const
		{
			return lhs <= rhs ? lhs : rhs;
		}*/

		template <typename T, typename... Args>
		T operator()(const T& lhs, const Args&... args) const
		{
			T rhs = operator()(args...);
			return lhs < rhs ? lhs : rhs;
		}

		template <typename T>
		T operator()(const T& lhs) const
		{
			return lhs;
		}
	};

	struct Max
	{
		// template <typename T>
		// T operator()(const T& lhs, const T& rhs) const
		// {
		// 	return lhs >= rhs ? lhs : rhs;
		// }
		template <typename T, typename... Args>
		T operator()(const T& lhs, const Args&... args) const
		{
			T rhs = operator()(args...);
			return lhs > rhs ? lhs : rhs;
		}

		template <typename T>
		T operator()(const T& lhs) const
		{
			return lhs;
		}
	};

	struct Random
	{
		int operator()(int min, int max) const;
		float operator()(float min, float max) const;

	private:
		static std::random_device _rd;
		static std::mt19937 _gen;
	};

	struct Lerp
	{
		float operator()(float start, float end, float t);
	};

	struct EaseIn
	{
		float operator()(float start, float end, float t);
	};

	struct EaseOut
	{
		float operator()(float start, float end, float t);
	};

	struct GetSinCos
	{
		void operator()(float& sin, float& cos, float degree);
	};

	struct ArcTangent2
	{
		float operator()(float y, float x) const;
	};

	struct SmoothDamp
	{
		float operator()(float current, float target, float& currentVelocity, float smoothTime, float deltaTime);
	};
}
