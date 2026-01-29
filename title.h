#pragma once

#include "scene.h"

class Title : public Scene
{
private:
	class Audio* m_BGM;
	class Audio* m_SE;

	unsigned int m_SceneCount;
	bool m_RequestTextUpdate;

public:
	void Init() override;//‰Šú‰»
	void Uninit() override;
	void Update() override;//XV

	void TextUpdate();
};