#pragma once

namespace Engine::Math
{
	struct Vector2 : D2D1_VECTOR_2F
	{
		static Vector2 Zero();
		static Vector2 One();
		static Vector2 Half();
		static Vector2 Right();
		static Vector2 Left();
		static Vector2 Up();
		static Vector2 Down();

		Vector2();
		Vector2(float x, float y);
		Vector2(D2D1_SIZE_F size);
		Vector2(D2D1_POINT_2F point);
		Vector2(Animation::Center center);
		Vector2(Input::Value value);

		operator D2D1_POINT_2F() const;
		operator D2D1_SIZE_F() const;
		operator D2D1_SIZE_U() const;
		operator SIZE() const;
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(float scala) const;
		Vector2 operator/(float scala) const;
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		Vector2 operator-() const;
		Vector2& operator=(const Vector2& other);
		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);
		Vector2& operator*=(float scala);
		Vector2& operator/=(float scala);
		const Vector2& operator()(const Vector2& vector1, const Vector2& vector2);
		friend Vector2 operator*(float scala, const Vector2& vector);

		[[nodiscard]] float SquareMagnitude() const;
		[[nodiscard]] float Magnitude() const;
		[[nodiscard]] Vector2 Normalize() const;

		static float DotProduct(const Vector2& lhs, const Vector2& rhs);
		[[nodiscard]] float DotProduct(const Vector2& other) const;

		static float CrossProduct(const Vector2& lhs, const Vector2& rhs);
		[[nodiscard]] float CrossProduct(const Vector2& other) const;

		static Vector2 SplitProduct(const Vector2& lhs, const Vector2& rhs);
		[[nodiscard]] Vector2 SplitProduct(const Vector2& other) const;

		static float Distance(const Vector2& lhs, const Vector2& rhs);
		[[nodiscard]] float Distance(const Vector2& other) const;

		[[nodiscard]] Vector2 Reflect(const Vector2& normal) const;

		static float AngleByAxisX(const Vector2& vector);
		[[nodiscard]] float AngleByAxisX() const;

		[[nodiscard]] Vector2 Rotate(float degree) const;

		static Vector2 UnitVectorFromAngle(float degree);

		static const Vector2& Lerp(const Vector2& start, const Vector2& end, const float t);
		static const Vector2& BezierInterpolate(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float t);
	};
}
