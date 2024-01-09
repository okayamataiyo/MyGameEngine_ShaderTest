#include "Input.h"
#include "Direct3D.h"

namespace Input
{
	HWND	hWnd_;			//�E�B���h�E�n���h��

	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE KeyState[256] = { 0 };
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	XMVECTOR mousePosition;					//�}�E�X�J�[�\���̈ʒu

	void Initialize(HWND hWnd)
	{
		hWnd_ = hWnd;

		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, 
			(VOID**)&pDInput, nullptr);

		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(NULL,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//�}�E�X
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState,KeyState,sizeof(prevKeyState));

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(KeyState), &KeyState);

		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

	}

	bool IsKey(int keyCode)
	{
		if (KeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����ĂȂ��āA�O��͉����Ă���
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButton(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);

	}
}