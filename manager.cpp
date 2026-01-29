#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "audio.h"
#include "texture.h"

#include "scene.h"


Scene* Manager::m_Scene = nullptr;
Scene* Manager::m_SceneNext = nullptr;


void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();	


	m_Scene = new Title();
	m_Scene->Init();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Texture::UnloadAll();
	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}


void Manager::Update()
{
	Input::Update();

	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();


	//‰æ–Ê‘JˆÚ
	if (m_SceneNext != nullptr)
	{
		m_Scene->Uninit();
		delete m_Scene;

		m_Scene = m_SceneNext;
		m_Scene->Init();

		m_SceneNext = nullptr;
	}
}
