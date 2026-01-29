#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "audio.h"

#include "polygon.h"
#include "enterText.h"

#include "title.h"
#include "game.h"
#include "result.h"

#include "score.h"


void Result::Init()
{
	AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\resultBG.png");

	AddGameObject<EnterText>(2)->Init(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 70, 400, 70, true);

	AddGameObject<Polygon2D>(2)->Init((SCREEN_WIDTH / 2) - 350.0f, 50.0f, 700, 350, "asset\\texture\\rizaruto.png");
	AddGameObject<Polygon2D>(2)->Init(450.0f + 200.0f + 10.0f, SCREEN_HEIGHT / 2 + 50.0f, 200, 60, "asset\\texture\\taitaosita.png");

	AddGameObject<Score>(2)->SetScore(GetScoreValue());
	GetGameObject<Score>()->SetPosition({ 450.0f, SCREEN_HEIGHT / 2 + 50.0f, 0.0f });

	m_BGM = new Audio();
	m_BGM->Load("asset\\audio\\TitleResultEtc.wav");
	m_BGM->Play(true);

}

void Result::Uninit()
{
	m_BGM->Uninit();
	delete m_BGM;

	Scene::Uninit();
}

void Result::Update()
{
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}

	Scene::Update();
}
