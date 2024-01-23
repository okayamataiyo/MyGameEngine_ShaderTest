//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gmodel:register(b0) //オブジェクトに関係あるやつ
{
	float4x4 matWVP;
	float4x4 matW;
	float4x4 matNormal;
	float4   diffuseColor;		//マテリアルの色＝拡散反射係数
	float4   ambientColor;		//環境光
	float4   specularColor;		//鏡面反射＝ハイライト
	float	 shineness;			//ハイライトの広がりの大きさ
	bool     isTexture;			//テクスチャーが貼られているかどうか
	bool	 isNormalMap;		//ノーマルマップがあるかどうか
}

cbuffer gmodel:register(b1)	//オブジェクトに関係ないやつ
{
	float4 lightPosition;
	float4 eyePosition;
}

//struct PS_IN
//{
//	float4 pos	  : SV_POSITION;	//位置
//	float2 uv	  : TEXCOORD;		//UV座標
//	float4 eyev   : POSITION1;
//	float4 normal : POSITION2;
//	float4 light  : POSITION3;
//};

//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー
Texture2D		normalTex: register(t1);

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv	  : TEXCOORD;		//UV座標
	float4 eyev   : POSITION;		//ワールド座標に変換された視線ベクトル
	float4 Neyev  : POSITION1;		//ノーマルマップ用の接空間
	float4 normal : POSITION2;		//法線ベクトル
	float4 light  : POSITION3;		//ライトを接空間に変換したベクトル
	float4 color  : POSITION4;		//色（明るさ）
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL,float4 tangent : TANGENT)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = (float2)uv;

	float3 binormal = cross(normal, tangent);

	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);				//法線ベクトルをローカル座標に変換したやつ

	tangent.w = 0;
	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);			//接線ベクトルをローカル座標に変換したやつ

	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);			//従法線ベクトルをローカル座標に変換したやつ

	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;

	outData.Neyev.x = dot(outData.eyev, tangent);	//接空間の視線ベクトル
	outData.Neyev.y = dot(outData.eyev, binormal);
	outData.Neyev.z = dot(outData.eyev, normal);
	outData.Neyev.w = 0;

	float4 light = normalize(lightPosition);
	light = normalize(light);

	outData.color = mul(light, normal);

	outData.light.x = dot(light, tangent);//接空間の光源ベクトル
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0,1.0,1.0,0.0);
	float4 diffuse;
	float4 ambient;

	if (isNormalMap)
	{
		float4 tmpNormal = normalTex.Sample(g_sampler, inData.uv) * 2 - 1;
		tmpNormal.w = 0;
		tmpNormal = normalize(tmpNormal);
		float4 NL = clamp(dot(tmpNormal, inData.light), 0, 1);
		float4 S = dot(tmpNormal, normalize(inData.light));
		S = clamp(S, 0, 1);
		
		float4 reflection = reflect(-inData.light, tmpNormal);
		float4 specular = pow(saturate(dot(reflection, inData.Neyev)), 2) * specularColor;
		/*if (isTexture != 0)
		{
			diffuse = g_texture.Sample(g_sampler, inData.uv) * S;
			ambient = g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else
		{
			diffuse = diffuseColor * S;
			ambient = diffuseColor * ambientColor;
		}*/
		diffuse = diffuseColor * NL;

		//return  diffuse + ambient + specular;
		return  diffuse;
	}
	else
	{
		float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));
		float4 reflection = reflect(normalize(-lightPosition), inData.normal);
		float4 specular = pow(saturate(dot(reflection, normalize(inData.eyev))), shineness) * specularColor;
		if (isTexture == 0)
		{
			diffuse = lightSource * diffuseColor * inData.color;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		else
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		//return diffuse + ambient + specular;
		return diffuse;
	}
}