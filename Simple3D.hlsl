//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gmodel:register(b0) //オブジェクトに関係あるやつ
{
	float4x4 matWVP;
	float4x4 matW;
	float4x4 matNormal;
	float4   diffuseColor;
	bool     isTextured;
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

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv	  : TEXCOORD;		//UV座標
	float4 color  : COLOR;			//色（明るさ）
	float4 eyev   : POSITION;
	float4 normal : NORMAL;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	outData.normal = normal;

	float4 light = normalize(lightPosition);
	light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
	float4 diffuse;// = lightsource * g_texture.sample(g_sampler, indata.uv) * indata.color;
	float4 ambient;// = lightsource * g_texture.sample(g_sampler, indata.uv) * ambientsource;
	float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
	float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), 8);

	if (isTextured == false) {
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambientSource;
	}
	else {
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}
	//return g_texture.sample(g_sampler, indata.uv);// (diffuse + ambient);
	return diffuse + ambient + specular;
	//float4 output = g_texture.Sample(g_sampler, inData.uv);
	//return output;
}