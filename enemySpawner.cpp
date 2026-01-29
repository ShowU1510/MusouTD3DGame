#include "main.h"
#include "renderer.h"
#include "enemy.h"
#include "enemySpawner.h"
#include "manager.h"
#include "scene.h"

#include "player.h"
#include "flag.h"

#include <random>
#include <cmath>

void EnemySpawner::Init()
{
	m_Time = 13.0f;
	m_SpawnTime = 15.0f;
	m_SpawnNo = 3;
}


void EnemySpawner::Uninit()
{

}


void EnemySpawner::Update()
{
	m_Time += 1.0f / 60.0f;

	if (m_Time > m_SpawnTime)
	{
		Player* player = Manager::GetScene()->GetGameObject<Player>();

		for (int i = 0; i < m_SpawnNo * player->GetLevel(); i++)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * XM_PI);
			std::uniform_real_distribution<float> distRadius(0.0f, 1.0f);

			float angle = distAngle(gen);
			float r = std::sqrt(distRadius(gen)) * 50.0f;

			Vector3 position;
			position.x = r * std::cos(angle);
			position.y = 0.0f;
			position.z = r * std::sin(angle);

			if (position.length() > 20)
			{
				Manager::GetScene()->AddGameObject<Enemy>(1)->SetPosition(position);
			}
		}

		m_Time = 0.0f;

		m_SpawnTime -= 0.7f;
		if (m_SpawnTime < 8.0f)
			m_SpawnTime = 8.0f;

		m_SpawnNo += 2;
	}
}


void EnemySpawner::Draw()
{

}
