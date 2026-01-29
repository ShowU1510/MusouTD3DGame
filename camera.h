#pragma once

#include "vector3.h"
#include "gameObject.h"

class Camera : public GameObject
{
private:

	XMMATRIX m_Projection;
	XMMATRIX m_View;

	Vector3 m_Target{ 0.0f, 0.0f, 0.0f };

	float m_ShakeTime{ 0.0f };
	Vector3 m_ShakeVector{ 0.0f, 0.0f, 0.0f };

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Shake(Vector3 ShakeVector);
	bool CheckView(Vector3 Position);

	XMMATRIX GetViewMatrix() { return m_View; }

	Vector3 GetForward() override
	{
		Vector3 forward = m_Target - m_Position;
		forward.normalize();

		return forward;
	}
};
