#pragma once
class Vec2
{
public:
	int x;
	int y;
	float size;
	Vec2();
	Vec2(int x, int y);
	bool operator<(const Vec2 other);
	bool operator>(const Vec2 other);
	Vec2 operator+(const Vec2 other);
	Vec2 operator*(int n);
	void operator=(const Vec2 other);
	Vec2 operator-(const Vec2 other);
	Vec2 operator/(int n);
	bool operator==(const Vec2 other);
	void operator+=(const Vec2 other);
	void operator-=(const Vec2 other);
	Vec2 normalize();
	~Vec2();
private:
	void setSize();
};

