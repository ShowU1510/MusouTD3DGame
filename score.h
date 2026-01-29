#pragma once

#include "gameObject.h"

class Score : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	ID3D11ShaderResourceView* m_Texture;

	unsigned int m_Value;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Add(int Value) { m_Value += Value; }
	void SetScore(unsigned int value) { m_Value = value; }
	unsigned int GetScore() { return m_Value; }
};