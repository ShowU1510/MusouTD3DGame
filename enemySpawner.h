#pragma once

#include "gameObject.h"

class EnemySpawner : public GameObject //åpè≥
{
private:

	float m_Time;
	float m_SpawnTime;
	
	unsigned int m_SpawnNo;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};