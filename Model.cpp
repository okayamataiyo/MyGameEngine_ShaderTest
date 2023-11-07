#include "Model.h"


int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//�t�@�C���l�[����������������A�ǂ܂�
	for (auto& e : modelList) {
		if (e->filename_ == fileName) {
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}

	pData->pfbx_ = new Fbx;
	pData->pfbx_->Load(fileName);
	if (pData->pfbx_ == nullptr) {
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return(modelList.size() - 1);	//���Ă񂾃��f���̃��f���ԍ���Ԃ�

}

void Model::SetTransform(int hModel, Transform transform)
{
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->transform_ = transform;
	
}

void Model::Draw(int hModel)
{
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
//	Transform& trf = modelList
}