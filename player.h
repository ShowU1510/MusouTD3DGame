#pragma once

#include "gameObject.h"
#include <string>

class Player : public GameObject //åpè≥
{
private:
	ID3D11InputLayout* m_VertexLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;

	class ModelRenderer* m_ModelRenderer;

	class Audio* m_SE;

	float m_Time;
	float m_BulletCoolTime;

	bool m_IsMoveFront;
	bool m_IsMoveBack;
	bool m_IsMoveSide;

	unsigned int m_Level;
	unsigned int m_PlayerEXP;
	unsigned int m_NextLevelEXP;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	unsigned int GetLevel() { return m_Level; }
	unsigned int GetPlayerEXP() { return m_PlayerEXP; }
	void AddPlayerEXP(int add) { m_PlayerEXP += add; }
	unsigned int GetNextLevelExp() { return m_NextLevelEXP; }
};