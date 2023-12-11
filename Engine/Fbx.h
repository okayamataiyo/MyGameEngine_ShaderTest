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
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};

	//コンスタントバッファー
	struct CONSTANT_BUFFER {
		XMMATRIX matWVP;			//mvp
		XMMATRIX matW;
		XMMATRIX matNormal;			//ワールド変換だけのやつ
		XMFLOAT4 diffuseColor;		//面の色
		//XMFLOAT4 lightPosition;		//光の視点
		//XMFLOAT4 eyePosition;		//目の視点
		BOOL isTextured;
	};

	//頂点情報
	struct VERTEX {
		XMVECTOR position;			//頂点数
		XMVECTOR uv;				//ポリゴン数
		XMVECTOR normal;			//マテリアルの個数
	};

	int vertexCount_;				//頂点数	FBXファイルを扱うために必要になる変数を宣言する。
	int polygonCount_;				//ポリゴン数
	int materialCount_;				//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer** pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
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
	//メンバ関数
	Fbx();
	void SetFlagColor(XMFLOAT4 col);
	HRESULT Load(std::string fileName);
	void Draw(Transform& transform);
	void SetLightPos(XMFLOAT4& pos);
	XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }
	void Release();
};

