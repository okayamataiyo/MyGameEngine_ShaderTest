#pragma once
#include<string>
#include<vector>
#include"Engine/Transform.h"
#include"Engine/Fbx.h"
//�K�v��include������

namespace Model
{
	struct ModelData {
		//FBX
		Fbx* pfbx_;
		//�g�����X�t�H�[��
		Transform transform_;
		std::string filename_;	//�t�@�C����
	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);

	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData * >modelList;
};