#pragma once
#include "main.h"
#include "gameObject.h"

class WaveForTitle : public GameObject
{

private:

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};

	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_EnvTexture{};//環境マッピングテクスチャ

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	VERTEX_3D m_Vertex[21][21];

	float m_Time{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};