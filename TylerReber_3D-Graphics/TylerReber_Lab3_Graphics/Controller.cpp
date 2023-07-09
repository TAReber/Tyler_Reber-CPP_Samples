#include "Controller.h"

Controller::Controller(View* _view, Model* _model)
{
	view = _view;
	model = _model;

	angle = vector3(0, 0, 0);
	//translation = vector3(0, 0, 0);
	Update_Rotation_Matrices();
	
}

Controller::~Controller() {
	delete model;
}
//Failed static rotation matric code
//Transform Controller::x_rotation_matrix = { 
//	{1, 0, 0, 0}, 
//	{0, 0, 0, 0},
//	{0, 0, 0, 0}, 
//	{0, 0, 0, 0} 
//};


void Controller::UpdateAngle(vector3 _eulerAngles)
{
	//Update angle vector
	angle = angle + _eulerAngles;

	Update_Rotation_Matrices();

	Transform result = translation * rotation;

	WireFrame* lines = dynamic_cast<WireFrame*>(model);
	if (lines) {
		for (auto& mod : lines->Get_Object()) {
			view->ApplyLineToRaster(Line(mod.start, mod.end, 0xffffffff), &result);
		}
	}

	Polygonal* mesh = dynamic_cast<Polygonal*>(model);
	if (mesh) {
		for (auto& model : mesh->Get_Object()) {
			//view->ApplyLineToRaster(model, &result);
			view->SchoolBarametricTriangle(&model, &result);
		}
	}

}


void Controller::SetModel(Model* _object)
{
	model = _object;
}

void Controller::SetTranslation(vector3 _trans) {
	translation.transform[3][0] = _trans.x;
	translation.transform[3][1] = _trans.y;
	translation.transform[3][2] = _trans.z;
	translation.transform[3][3] = 1;
}

void Controller::SetScale(vector3 _scale) {
	translation.transform[0][0] = _scale.x;
	translation.transform[1][1] = _scale.y;
	translation.transform[2][2] = _scale.z;
	translation.transform[3][3] = 1;
}

void Controller::Update_Rotation_Matrices()
{
	float x_rot[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, std::cos(angle.x * RAD), -sin(angle.x * RAD), 0},
		{ 0, std::sin(angle.x * RAD), std::cos(angle.x * RAD), 0},
		{ 0, 0, 0, 1 } };
	Transform x_rotation_matrix;
	x_rotation_matrix.SetTransform(x_rot);

	float y_rot[4][4] = {
		{ std::cos(angle.y * RAD), 0, std::sin(angle.y * RAD), 0},
		{ 0, 1, 0, 0},
		{ -std::sin(angle.y * RAD), 0, std::cos(angle.y * RAD), 0},
		{ 0, 0, 0, 1 } };
	Transform y_rotation_matrix;
	y_rotation_matrix.SetTransform(y_rot);

	float z_rot[4][4] = {
		{ std::cos(angle.z * RAD), -std::sin(angle.z * RAD), 0, 0},
		{ std::sin(angle.z * RAD), std::cos(angle.z * RAD), 0, 0},
		{ 0, 0, 1, 0},
		{ 0, 0, 0, 1 } };
	Transform z_rotation_matrix;
	z_rotation_matrix.SetTransform(z_rot);

	rotation = z_rotation_matrix * y_rotation_matrix * x_rotation_matrix;
}
