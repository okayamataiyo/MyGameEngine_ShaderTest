#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Sprite.h"

Transform trans_G;
Transform trans_A;
Transform trans_B;

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1, -1, 0}
{
    Sprite* s;

}

//デストラクタ
Stage::~Stage()
{

}

//初期化
void Stage::Initialize()
{

    //モデルデータのロード
    hModel_[0] = Model::Load("Assets/Arrow.fbx");
    assert(hModel_[0] >= 0);

    //モデルデータのロード
    hModel_[1] = Model::Load("Assets/Ground.fbx");
    assert(hModel_[1] >= 0);

    //モデルデータのロード
    hModel_[2] = Model::Load("Assets/Ball.fbx");
    assert(hModel_[2] >= 0);
}

//更新
void Stage::Update()
{
    trans_A.rotate_.z = 90;
    trans_A.position_.y = 0.5;
    trans_G.position_.y = 0;
    trans_B.position_.x = 2;
    trans_B.position_.z = 2;
    trans_B.position_.y = 1;
    trans_B.rotate_.y += 0.5;
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], trans_A);
    Model::Draw(hModel_[0]);

    Model::SetTransform(hModel_[1], trans_G);
    Model::Draw(hModel_[1]);

    Model::SetTransform(hModel_[2], trans_B);
    Model::Draw(hModel_[2]);
}

//開放
void Stage::Release()
{
}