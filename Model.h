#pragma once
#include<string>
#include<vector>
#include"Engine/Transform.h"
#include"Engine/Fbx.h"
//必要なincludeを書く

namespace Model
{
	struct ModelData {
		//FBX
		Fbx* pfbx_;
		//トランスフォーム
		Transform transform_;
		std::string filename_;	//ファイル名
	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);

	//モデルのポインタをぶち込んでおくベクタ
	std::vector<ModelData * >modelList;
};