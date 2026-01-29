#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"



void Scene::Init()
{

}

void Scene::Uninit()
{
	for (int i = 0; i < 3; i++)
	{
		for (auto gameObject : m_GameObject[i])
		{
			gameObject->SetDestroy();
		}

		m_GameObject[i].clear();
	}

}

void Scene::Update()
{
	for (int i = 0; i < 3; i++)
	{
		for (auto gameObject : m_GameObject[i])//範囲forループ
		{
			gameObject->Update();//ポリモフィズム
		}

	}

	for (int i = 0; i < 3; i++)
	{
		//ラムダ式
		m_GameObject[i].remove_if([](GameObject* object)
			{
				return object->Destroy();
			});
	}


}

void Scene::Draw()
{
	//Zソート
	Camera* camera = GetGameObject<Camera>();

	if (camera != nullptr)
	{
		Vector3 cameraPosition = camera->GetPosition();
		Vector3 cameraForward = camera->GetForward();

		m_GameObject[1].sort([&](GameObject* object1, GameObject* object2)
			{
				return object1->GetZ(cameraPosition, cameraForward)
						> object2->GetZ(cameraPosition, cameraForward);
			});
	}

	for (int i = 0; i < 3; i++)
	{
		for (auto gameObject : m_GameObject[i])//範囲forループ
		{
			gameObject->Draw();//ポリモフィズム
		}
	}

}
