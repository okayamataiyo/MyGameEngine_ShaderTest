#pragma once
#include<string>
#include<vector>
#include"Transform.h"
#include"Fbx.h"
//�K�v��include������

namespace Model
{

	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
};