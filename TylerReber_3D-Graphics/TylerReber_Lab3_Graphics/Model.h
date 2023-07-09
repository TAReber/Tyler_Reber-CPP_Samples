#pragma once
#include "vector3.h"
//#include "Transform.h"
#include "Points.h"
#include <vector>

class Model
{
public:
	//std::vector<Points> object;
	int size;
	//Model() {};
	Model(int _size){ size = _size; };
	virtual ~Model() {};
	//virtual void AddPoints(Points _pt) = 0;
	//virtual std::vector<> Get_Object() = 0;// { return object; };
	//virtual int GetSize();

};

class Polygonal : public Model
{
	std::vector<Tri> object;
public:
	//Polygon() {};
	Polygonal(int _size) : Model(_size) { object.reserve(_size); };
	~Polygonal() {};

	void AddPoints(Tri _tri) { object.push_back(_tri); };
	std::vector<Tri> Get_Object() { return object; };
};

class WireFrame : public Model
{
	std::vector<Line> object;
public:
	//WireFrame() {};
	WireFrame(int _size) : Model(_size) {};
	~WireFrame() {};
	void AddPoints(Line _ln) { object.push_back(_ln); };
	std::vector<Line> Get_Object() { return object; };

};