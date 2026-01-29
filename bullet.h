#pragma once

#include "gameObject.h"

class Bullet : public GameObject //åpè≥
{
private:
	ID3D11InputLayout* m_VertexLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;

	class ModelRenderer* m_ModelRenderer;

	Vector3 m_Velocity{};

	Vector3 m_StartPosition;
	Vector3 m_EndPosition;
	Vector3 m_StartVector;
	Vector3 m_EndVector;
	float m_Time;

	unsigned int m_FramePerExplosion = 4;
	unsigned int m_Frame = 0;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetVelocity(Vector3 vel) { m_Velocity = vel; }

	void Shot(Vector3 StartPosition, Vector3 EndPosition)
	{
		m_StartPosition = StartPosition;
		m_EndPosition = EndPosition;
		m_StartVector = Vector3(20.0f, 20.0f, 0.0f);
		m_EndVector = Vector3(20.0f, -20.0f, 0.0f);
		m_Time = 0.0f;
	}

};