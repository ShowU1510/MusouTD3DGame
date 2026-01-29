#pragma once

#include "main.h"
#include "gameObject.h"
#include "vector3.h"

class ParticleInstance : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11Buffer* m_PositionBuffer;
	ID3D11ShaderResourceView* m_PositionSRV;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	ID3D11ShaderResourceView* m_Texture;

	struct PARTICLE
	{
		bool Enable;
		int Life;
		Vector3 Position;
		Vector3 Velocity;
	};
	std::vector<Vector3> m_InstancePositions;


	bool IsParticleSpawn;
	static const int PARTICLE_MAX = 10000;
	PARTICLE m_Particle[PARTICLE_MAX];

	unsigned int m_Life;

	unsigned int m_DrawCount;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;//オーバーライド

	void SetParticleOffset(Vector3 Offset)
	{
		for (int i = 0; i < PARTICLE_MAX; i++)
		{
			if (m_Particle[i].Enable == true)
			{
				m_Particle[i].Position += Offset;
			}
		}
	}
};