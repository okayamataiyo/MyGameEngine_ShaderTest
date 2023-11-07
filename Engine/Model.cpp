#include "Model.h"
#include "Direct3D.h"

struct ModelData {
	//FBX
	Fbx* pfbx_;
	//�g�����X�t�H�[��
	Transform transform_;
	std::string filename_;	//�t�@�C����
};
	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData* >modelList;


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

void Model::Release()
{
	bool isReffered = false;	//�Q�Ƃ���Ă�?
	for (int i = 0; i < modelList.size(); i++) {
		for (int j = i + 1; j < modelList.size(); j++) {
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_) {
				isReffered = true;
				break;
			}
		}
		if (isReffered == false) {
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
	
}