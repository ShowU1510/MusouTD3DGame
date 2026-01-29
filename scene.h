#pragma once

#include <list>
#include <vector>
#include "gameObject.h"


class Scene
{
private:
	std::list<GameObject*> m_GameObject[3];

	static unsigned int m_ScoreValue;

public:
	virtual void Init();//初期化
	virtual void Uninit();//終了処理
	virtual void Update();//更新
	virtual void Draw();//描画

	static void SetScoreValue(unsigned int scoreValue) { m_ScoreValue = scoreValue; }
	static unsigned int GetScoreValue() { return m_ScoreValue; }

	template <typename T>//テンプレート
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>//テンプレート
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++)
		{
			for (auto gameObject : m_GameObject[i])
			{
				T* find = dynamic_cast<T*>(gameObject);
				if (find != nullptr)
					return find;
			}
		}
		return nullptr;
	}

	template <typename T>//テンプレート
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> finds;
		for (int i = 0; i < 3; i++)
		{
			for (auto gameObject : m_GameObject[i])
			{
				T* find = dynamic_cast<T*>(gameObject);
				if (find != nullptr)
					finds.push_back(find);
			}
		}
		return finds;
	}

	void DestroyAllObjects()
	{
		for (int i = 0; i < 3; i++)
		{
			for (auto obj : m_GameObject[i])
			{
				obj->SetDestroy();
			}
		}
	}

};