#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"

#include "scene.h"

#include "fade.h"
#include "polygon.h"
#include "enterText.h"
#include "title.h"
#include "game.h"

#include "cameraForTitle.h"
#include "skyForTitle.h"
#include "meshFieldForTitle.h"
#include "waveForTitle.h"

void Title::Init()
{
	AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.75f, "asset\\texture\\Title.png");

	AddGameObject<CameraForTitle>(0);
	AddGameObject<SkyForTitle>(0)->SetScale({ 50.0f, 50.0f, 50.0f });

	AddGameObject<MeshFieldForTitle>(0);

	AddGameObject<WaveForTitle>(1)->SetPosition({ 0.0f, -1.0f, 0.0f });
	
	AddGameObject<EnterText>(2)->Init(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 70, 400, 70, true);


	m_BGM = new Audio();
	m_BGM->Load("asset\\audio\\TitleResultEtc.wav");
	m_BGM->Play(true);

	m_SE = new Audio();
	m_SE->Load("asset\\audio\\se_click.wav");

	m_SceneCount = 0;
	m_RequestTextUpdate = false;
}

void Title::Uninit()
{
	Scene::Uninit();

	m_BGM->Uninit();
	delete m_BGM;

	m_SE->Uninit();
	delete m_SE;

	m_SceneCount = 0;
}

void Title::Update()
{
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_SE->Play(false);

		if (m_SceneCount == 0)
		{
			DestroyAllObjects();

			m_RequestTextUpdate = true;
			m_SceneCount = 1;
		}
		else if (m_SceneCount == 1)
		{
			DestroyAllObjects();

			m_RequestTextUpdate = true;
			m_SceneCount = 2;
		}
		else if (m_SceneCount == 2)
		{
			DestroyAllObjects();

			m_RequestTextUpdate = true;
			m_SceneCount = 3;
		}
		else if(m_SceneCount == 3)
		{
			Fade* fadeIn = AddGameObject<Fade>(2);
			fadeIn->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\white.png", true);
			
			m_SceneCount = 4;		
		}
	}

	Scene::Update();

	if (m_RequestTextUpdate == true)
	{
		TextUpdate();
		m_RequestTextUpdate = false;
	}

	if (m_SceneCount == 4)
	{
		Fade* fadeIn = GetGameObject<Fade>();
		fadeIn->UpdateFadeIn();
		if (fadeIn->GetAlphaScale() == 1.0f)
		{
			Manager::SetScene<Game>();
		}
	}
}

void Title::TextUpdate()
{
	if (m_SceneCount == 1)
	{
		AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\titleBG.png");

		AddGameObject<EnterText>(2)->Init(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 70, 400, 70, true);

		AddGameObject<Polygon2D>(2)->Init(100.0f, 0.0f, SCREEN_WIDTH - 200.0f, SCREEN_HEIGHT - 50, "asset\\texture\\kanban02.png");
		AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 250.0f, 25.0f, 500.0f, 150.0f, "asset\\texture\\kanban03.png");
		AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 200.0f, 50.0f, 400.0f, 125.0f, "asset\\texture\\sousasetumei.png");
		AddGameObject<Polygon2D>(2)->Init(300.0f, 175.0f + 30.0f, 320.0f, 70.0f, "asset\\texture\\wasdki-.png");
		AddGameObject<Polygon2D>(2)->Init(300.0f, 175.0f + 70.0f + 60.0f, 460.0f, 70.0f, "asset\\texture\\sayuuhoukouki-.png");
		AddGameObject<Polygon2D>(2)->Init(300.0f, 175.0f + 140.0f + 90.0f, 390.0f, 70.0f, "asset\\texture\\supe-suki-.png");
	}
	else if (m_SceneCount == 2)
	{
		AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\titleBG.png");

		AddGameObject<EnterText>(2)->Init(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 70, 400, 70, true);

		AddGameObject<Polygon2D>(2)->Init(100.0f, 0.0f, SCREEN_WIDTH - 200.0f, SCREEN_HEIGHT - 50, "asset\\texture\\kanban02.png");
		AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 250.0f, 25.0f, 500.0f, 150.0f, "asset\\texture\\kanban03.png");
		AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 200.0f, 50.0f, 400.0f, 125.0f, "asset\\texture\\ru-rusetumei.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 30.0f, 490.0f, 70.0f, "asset\\texture\\tugitugitowaitekuru.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 70.0f + 60.0f, 630.0f, 70.0f, "asset\\texture\\tekigachuusinnno.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 140.0f + 90.0f, 770.0f, 70.0f, "asset\\texture\\yoriookuno.png");
	}
	else if (m_SceneCount == 3)
	{
		AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\titleBG.png");

		AddGameObject<EnterText>(2)->Init(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 70, 400, 70, true);

		AddGameObject<Polygon2D>(2)->Init(100.0f, 0.0f, SCREEN_WIDTH - 200.0f, SCREEN_HEIGHT - 50, "asset\\texture\\kanban02.png");
		AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 250.0f, 25.0f, 500.0f, 150.0f, "asset\\texture\\kanban03.png");
		AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 200.0f, 50.0f, 400.0f, 125.0f, "asset\\texture\\reberunituite.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 30.0f, 690.0f, 70.0f, "asset\\texture\\tekiwotaositatokini.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 70.0f + 60.0f, 710.0f, 70.0f, "asset\\texture\\pureiya-noreberu.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 140.0f + 90.0f, 790.0f, 70.0f, "asset\\texture\\reberugaagaruto.png");
		AddGameObject<Polygon2D>(2)->Init(200.0f, 175.0f + 210.0f + 120.0f, 570.0f, 70.0f, "asset\\texture\\tekimoreberuni.png");
	}
}
