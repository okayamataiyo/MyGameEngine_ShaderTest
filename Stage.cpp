#include "Engine/Model.h"
#include "Stage.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1}
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("assets/BoxPappillon.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Stage::Update()
{
    transform_.rotate_.y += 0.5;
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}