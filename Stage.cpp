#include "Engine/Model.h"
#include "Engine/Sprite.h"
#include "Stage.h"

Transform trans_G;
Transform trans_A;
Transform trans_B;

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1, -1, 0}
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
    trans_A.rotate_.z = 90;
    trans_A.position_.y = 0.5;
    trans_G.position_.y = 0;
    trans_B.position_.x = 2;
    trans_B.position_.z = 2;
    trans_B.position_.y = 1;
    trans_B.rotate_.y += 0.5;
    //CBUFF_STAGESCENE cb;
    //cb.lightPosition = lightSourcePosition_;
    //XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());
    //Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);
    //Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);   //���_�V�F�[�_�[
    //Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);   //�s�N�Z���V�F�[�_�[
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], trans_A);
    Model::Draw(hModel_[0]);

    Model::SetTransform(hModel_[1], trans_G);
    Model::Draw(hModel_[1]);

    Model::SetTransform(hModel_[2], trans_B);
    Model::Draw(hModel_[2]);
}

//�J��
void Stage::Release()
{
}