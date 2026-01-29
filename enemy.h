#pragma once

#include "gameObject.h"

class Enemy : public GameObject //åpè≥
{
private:
	ID3D11InputLayout* m_VertexLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;

	class ModelRenderer* m_ModelRenderer;

	Vector3 m_HitPosition{ 0.0f, 0.0f, 0.0f };

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetHitPosition(Vector3 hitPosition) { m_HitPosition = hitPosition; }
	Vector3 GetHitPosition() { return m_HitPosition; }
};