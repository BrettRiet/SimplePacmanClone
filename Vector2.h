#pragma once
class Vector2 {

public:
	float x;
	float y;
	int cornerType;

	Vector2() :x(0), y(0), cornerType(0){
		//default
		x = 0;
		y = 0;
		cornerType = 0;
	}
	Vector2(float X, float Y, int c) {
		x = X;
		y = Y;
		cornerType = c;
	}

	int getIntX()
	{
		return (int)x;
	}
	int getIntY()
	{
		return (int)y;
	}
	int getCornerType()
	{
		return cornerType;
	}

	bool Vector2::operator==(const Vector2& other){
		return (other.x == x && other.y == y);
}

};