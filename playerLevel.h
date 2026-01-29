#pragma once

#include "gameObject.h"
#include "polygon.h"
#include "main.h"

class PlayerLevel : public Polygon2D
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	ID3D11ShaderResourceView* m_Texture[15];

public:
	void Init() {};//âºëzä÷êî
	void Init(float x, float y, float Width, float Height);
	void Uninit();
	void Update();
	void Draw();
};