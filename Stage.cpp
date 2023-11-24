#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Sprite.h"

Transform transform_A;
Transform transform_G;
Transform transform_B;

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1, -1,0}
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
    hModel_[2] = Model::Load("Assets/Ball.fbx");
    assert(hModel_[2] >= 0);
}

//�X�V
void Stage::Update()
{
    transform_A.rotate_.z = 90;
    transform_A.position_.y = 0.5;
    transform_G.position_.y = 0;
    transform_B.position_.x = 2;
    transform_B.position_.z = 2;
    transform_B.position_.y = 1;
    transform_B.rotate_.y += 0.5;
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], transform_A);
    Model::Draw(hModel_[0]);

    Model::SetTransform(hModel_[1], transform_G);
    Model::Draw(hModel_[1]);

    Model::SetTransform(hModel_[2], transform_B);
    Model::Draw(hModel_[2]);
}

//�J��
void Stage::Release()
{
}