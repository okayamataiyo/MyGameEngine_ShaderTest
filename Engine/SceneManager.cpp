#include "SceneManager.h"
#include "Model.h"
#include "../TestScene.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{

	//�V�[�������ۂɐ؂�ւ���
	//���݂̃V�[���ƁA�l�N�X�g�V�[�����ʂ�������؂�ւ�
	if (currentSceneID_ != nextSceneID_) {

		//���̃V�[���̃I�u�W�F�N�g��S�폜
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//���[�h�����f�[�^��S�폜
		Model::Release();
		//��Еt���I��
		switch (nextSceneID_) {

		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
	//���݂̃V�[���̌�Еt��
	//�V�����V�[���̏���
	//currentSceneID_��nextSCENEID
	
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// ���Ɏw�肵���V�[����nextSceneID_�ɐݒ肷��(=����Update�ŃV�[�����ς��)
/// </summary>
/// <param name="_next">���̃V�[��</param>
void SceneManager::ChangeScene(SCENE_ID _next)
{

	nextSceneID_ = _next;
}
