#pragma once
#include "vector4.h"
#include "vector2.h"
#include "Utility.h"
struct Points
{
public:
	unsigned int color;
public:
	Points() { color = 0xffffffff; };
	Points(unsigned int color) : color(color) {}
	virtual ~Points() {};
};

struct Line : virtual Points
{
	vector4 start;
	vector4 end;
	//unsigned int color;

	Line() {};
	Line(vector4 _start, vector4 _end, unsigned int _color) : Points(_color) { start = _start; end = _end; }
	~Line() {};
};

struct Tri : virtual Points {
	vector4 a;
	vector4 b;
	vector4 c;
	vector2 uv_a;
	vector2 uv_b;
	vector2 uv_c;

	Tri() {};
	Tri(vector4 _a, vector4 _b, vector4 _c, unsigned int color) : Points(color) { a = _a; b = _b; c = _c; }
	~Tri() {};
	void SetUV(vector2 _a, vector2 _b, vector2 _c) { uv_a = _a; uv_b = _b; uv_c = _c; }
};