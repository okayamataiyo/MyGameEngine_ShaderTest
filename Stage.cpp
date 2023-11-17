#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Sprite.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1}
{
    Sprite* s;
}

//�f�X�g���N�^
Stage::~Stage()
{

}

//������
void Stage::Initialize()
{

    //���f���f�[�^�̃��[�h
    hModel_[0] = Model::Load("Assets/Arrow.fbx");
    assert(hModel_[0] >= 0);

    //���f���f�[�^�̃��[�h
    hModel_[1] = Model::Load("Assets/Ground.fbx");
    assert(hModel_[1] >= 0);

    //���f���f�[�^�̃��[�h
    hModel_[1] = Model::Load("Assets/Ball.fbx");
    assert(hModel_[2] >= 0);
}

//�X�V
void Stage::Update()
{
    transform_.rotate_.y += 0.5;
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);

    Model::SetTransform(hModel_[1], transform_);
    Model::Draw(hModel_[1]);
}

//�J��
void Stage::Release()
{
}