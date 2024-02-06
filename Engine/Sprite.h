#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include <vector>
#include "Transform.h"

using std::vector;

class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX    matW;     //ワールド行列
		XMMATRIX	uvTrans;
		XMFLOAT4	color;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;      //位置
		XMVECTOR uv;            //UV
	};
protected:
	UINT64 vertexNum_;                 //頂点数
	vector<VERTEX> vertices_;     //頂点情報
	ID3D11Buffer* pVertexBuffer_;    //頂点バッファ

	UINT64 indexNum;                 //インデックス数
	vector<int> index_;          //インデックス情報
	ID3D11Buffer* pIndexBuffer_;          //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;       //コンスタントバッファ
	Texture* pTexture_;                  //テクスチャ
public:
	Sprite();
	~Sprite();

	//初期化（ポリゴンを表示するための各種情報を準備）
	//戻り値：成功/失敗
	HRESULT Initialize();

	//描画
	//引数：worldMatrix　ワールド行列
	//void Draw(Transform& transform, RECT rect,float alpha);
	//void Draw(XMMATRIX& worldMatrix);

	//解放
	void Release();

	XMFLOAT2 GetTextureSize() { return pTexture_->GetTextureSize(); }

private:
	//---------Initiallizeから呼ばれる関数---------
	virtual void InitVertexData();       //頂点情報の準備
	HRESULT CreateVertexBuffer();         //頂点バッファを作成

	virtual void InitIndexData();        //インデックス情報を準備
	HRESULT CreateIndexBuffer();         //インデックスバッファを作成

	HRESULT CreateConstantBuffer();      //コンスタントバッファ作成

	HRESULT LoadTexture(string fileName);               //テクスチャをロード

	//---------Draw関数から呼ばれる関数----------
	void PassDataToCB(XMMATRIX worldMatrix);     //コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();                            //各バッファをパイプラインにセット
};

