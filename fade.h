#pragma once

#include "gameObject.h"

class Fade : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	ID3D11ShaderResourceView* m_Texture;

	
	float m_AlphaScale = 0;

public:
	void Init() {};//âºëzä÷êî
	void Init(float x, float y, float Width, float Height, const char* FileName, bool IsFadeIn);
	void Uninit();
	void Update();
	void UpdateFadeIn();
	void UpdateFadeOut();
	void Draw();

	void AddAlphaScale(float add) { m_AlphaScale += add; }
	float GetAlphaScale() { return m_AlphaScale; }
};