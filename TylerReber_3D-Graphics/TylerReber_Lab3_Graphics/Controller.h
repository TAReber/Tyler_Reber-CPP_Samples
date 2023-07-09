#pragma once
#include "Transform.h"
#include "vector3.h"
#include "Model.h"
#include <vector>
#include "View.h"

//#include "Points.h"

class Controller
{
	View* view;
	Model* model;

	vector3 angle;

	Transform translation;
	Transform rotation;

public:
	

	Controller(View* _view, Model* _model);
	~Controller();

	void UpdateAngle(vector3 _eulerAngles);

	void SetModel(Model* _object);

	void SetTranslation(vector3 _vect);
	void SetScale(vector3 _vect);

	//void InitializeTransformMatrix();

	void Update_Rotation_Matrices();
	
	

};
