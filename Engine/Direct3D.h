#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

using namespace DirectX;


enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_TOON,
	SHADER_TOONOUTLINE,
	SHADER_MAX,
};

namespace Direct3D
{
	extern ID3D11Device* pDevice_;		                //�f�o�C�X
	extern ID3D11DeviceContext* pContext_;		        //�f�o�C�X�R���e�L�X�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();
	HRESULT InitShaderToon();
	HRESULT InitShaderToonOutLine();

	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();



	//�`��I��
	void EndDraw();



	//���
	void Release();

};

