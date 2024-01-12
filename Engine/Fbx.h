#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include <vector>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

class Texture;

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 specular;
		float shineness;
	};

	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER_MODEL {
		XMMATRIX matWVP;			//wvp
		XMMATRIX matW;				//wvp
		XMMATRIX matNormal;			//���[���h�ϊ������̂��
		XMFLOAT4 diffuseColor;		//�ʂ̐F
		XMFLOAT4 ambientColor;
		XMFLOAT4 specularColor;
		float  shineness;
		BOOL isTextured;
	};

	//���_���
	struct VERTEX {
		XMVECTOR position;			//���_��
		XMVECTOR uv;				//�|���S����
		XMVECTOR normal;			//�}�e���A���̌�
	};

	int vertexCount_;				//���_��	FBX�t�@�C�����������߂ɕK�v�ɂȂ�ϐ���錾����B
	int polygonCount_;				//�|���S����
	int materialCount_;				//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer** pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	MATERIAL* pMaterialList_;
	vector<int> indexCount_;
//	int* indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	bool IsFloatColor_;
	XMFLOAT4 dColor_;
	XMFLOAT4 lightSourcePosition_;

public:
	//�����o�֐�
	Fbx();
	void SetFlagColor(XMFLOAT4 col);
	HRESULT Load(std::string fileName);
	void Draw(Transform& transform);
	void DrawToon(Transform& transform);
	void Release();
};

