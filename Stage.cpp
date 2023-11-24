#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Sprite.h"

Transform transform_A;
Transform transform_G;
Transform transform_B;

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1, -1,0}
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
    transform_A.rotate_.z = 90;
    transform_A.position_.y = 0.5;
    transform_G.position_.y = 0;
    transform_B.position_.x = 2;
    transform_B.position_.z = 2;
    transform_B.position_.y = 1;
    transform_B.rotate_.y += 0.5;
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], transform_A);
    Model::Draw(hModel_[0]);

    Model::SetTransform(hModel_[1], transform_G);
    Model::Draw(hModel_[1]);

    Model::SetTransform(hModel_[2], transform_B);
    Model::Draw(hModel_[2]);
}

//開放
void Stage::Release()
{
}