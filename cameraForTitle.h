#pragma once
#include "main.h"
#include "vector3.h"
#include "gameObject.h"

class CameraForTitle : public GameObject
{
private:

	XMMATRIX m_Projection;
	XMMATRIX m_View;

	Vector3 m_Target{ 0.0f, 0.0f, 0.0f };

	GameObject m_TargetObject;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	XMMATRIX GetViewMatrix() { return m_View; }

	Vector3 GetForward() override
	{
		Vector3 forward = m_Target - m_Position;
		forward.normalize();

		return forward;
	}
};
