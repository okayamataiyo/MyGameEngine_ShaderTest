#pragma once
#include "Engine/GameObject.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4 lightPosition;
    XMFLOAT4 eyePos;
};

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[4];    //���f���ԍ�
    ID3D11Buffer* pCBStageScene_;
    XMFLOAT4 lightSourcePosition_;

    void IntConstantBuffer();
public:
    //�R���X�g���N�^
    //����:parent �e�I�u�W�F�N�g(SceneManager)
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }

    //�w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
    //����:x,z  ���ׂ�ʒu
    //�߂�l:�ʂ�Ȃ�=true/�ʂ�Ȃ�=false
    //bool IsWall(int x, int z);
};