#pragma once
#include "scene.h"

class Manager
{
private:
	static class Scene* m_Scene;
	static class Scene* m_SceneNext;

public:
	static void Init();//‰Šú‰»
	static void Uninit();//I—¹ˆ—
	static void Update();//XV
	static void Draw();//•`‰æ

	static Scene* GetScene() { return m_Scene; }

	template<typename T>
	static void SetScene()
	{
		m_SceneNext = new T();
	}

};