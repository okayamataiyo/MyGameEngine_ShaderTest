#include "Model.h"


int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//ファイルネームが同じだったら、読まん
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
	return(modelList.size() - 1);	//今呼んだモデルのモデル番号を返す

}

void Model::SetTransform(int hModel, Transform transform)
{
	//モデル番号は、modelListのインデックス
	modelList[hModel]->transform_ = transform;
	
}

void Model::Draw(int hModel)
{
	//モデル番号は、modelListのインデックス
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
//	Transform& trf = modelList
}