#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Sprite.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1}
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
    hModel_[1] = Model::Load("Assets/Ball.fbx");
    assert(hModel_[2] >= 0);
}

//更新
void Stage::Update()
{
    transform_.rotate_.y += 0.5;
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);

    Model::SetTransform(hModel_[1], transform_);
    Model::Draw(hModel_[1]);
}

//開放
void Stage::Release()
{
}