
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"

#include "title.h"
#include "game.h"
#include "result.h"

#include "camera.h"
#include "fade.h"
#include "field.h"
#include "flag.h"
#include "enemy.h"
#include "enemySpawner.h"
#include "expbar_out.h"
#include "expbar_in.h"
#include "player.h"
#include "playerLevel.h"
#include "polygon.h"
#include "score.h"
#include "sky.h"



void Game::Init()
{

	AddGameObject<Score>(2)->SetPosition({ SCREEN_WIDTH - 200.0f, 0.0f, 0.0f });
	
	AddGameObject<EXPBAR_IN>(2)->Init(10.0f + 5.0f, 10.0f + 1.5f, 290.0f, 50.0f, "asset\\texture\\EXPBar_In.png");
	AddGameObject<EXPBAR_OUT>(2)->Init(10.0f, 10.0f, 300.0f, 52.5f, "asset\\texture\\EXPBar_Out.png");

	AddGameObject<PlayerLevel>(2)->Init(10.0f + 300.0f + 20.0f, 10.0f, 185.0f, 65.0f);

	AddGameObject<Camera>(0);
	AddGameObject<EnemySpawner>(0);
	AddGameObject<Sky>(0)->SetScale({50.0f, 50.0f, 50.0f});
	
	AddGameObject<Field>(0);

	AddGameObject<Player>(1);
	AddGameObject<Flag>(1)->SetPosition({ 0.0f, 0.0f, 0.0f });

	AddGameObject<Fade>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\white.png", false);
	
	m_BGM = new Audio();
	m_BGM->Load("asset\\audio\\Game.wav");
	m_BGM->Play(true);

}

void Game::Uninit()
{
	m_BGM->Uninit();
	delete m_BGM;

	Scene::Uninit();
}

void Game::Update()
{
	Fade* fadeOut = GetGameObject<Fade>();
	fadeOut->UpdateFadeOut();

	Scene::Update();
}
