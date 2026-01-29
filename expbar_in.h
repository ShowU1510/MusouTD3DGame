#pragma once

#include "gameObject.h"

class EXPBAR_IN : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	ID3D11ShaderResourceView* m_Texture;


public:
	void Init() {};//âºëzä÷êî
	void Init(float x, float y, float Width, float Height, const char* FileName);
	void Uninit();
	void Update();
	void Draw();
};