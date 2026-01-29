#include "main.h"
#include "renderer.h"
#include "particleInstance.h"
#include "camera.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "player.h"

void ParticleInstance::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読込
	m_Texture = Texture::Load("asset\\texture\\particle.png");

	//ストラクチャードバッファ生成
	{
		// インスタンス最大数
		constexpr UINT INSTANCE_MAX = PARTICLE_MAX;

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector3) * INSTANCE_MAX;
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bd.StructureByteStride = sizeof(Vector3);

		Renderer::GetDevice()->CreateBuffer(&bd, nullptr, &m_PositionBuffer);

		// SRV
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd{};
		srvd.Format = DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = INSTANCE_MAX;

		Renderer::GetDevice()->CreateShaderResourceView(
			m_PositionBuffer,
			&srvd,
			&m_PositionSRV
		);
	}

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\particleInstanceVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\particleInstancePS.cso");

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		m_Particle[i].Enable = false;
	}

	m_Scale = Vector3(0.2f, 0.2f, 0.2f);

	IsParticleSpawn = false;

	m_InstancePositions.reserve(PARTICLE_MAX);

}

void ParticleInstance::Uninit()
{
	m_VertexBuffer->Release();

	m_PositionBuffer->Release();
	m_PositionSRV->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ParticleInstance::Update()
{
	if (IsParticleSpawn == false)
	{
		int count = 100;
		for (int i = 0; i < PARTICLE_MAX; i++)
		{
			if (m_Particle[i].Enable == false)
			{
				m_Particle[i].Enable = true;
				m_Particle[i].Life = 300;
				m_Particle[i].Position = m_Position;
				m_Particle[i].Velocity.x = (rand() % 100 - 50) / 500.0f;
				m_Particle[i].Velocity.y = (rand() % 100) / 500.0f;
				m_Particle[i].Velocity.z = (rand() % 100 - 50) / 500.0f;

				count--;
				if (count == 0)
				{
					break;
				}
			}
		}
		IsParticleSpawn = true;
		m_Life = 300;
	}

	Player* player = Manager::GetScene()->GetGameObject<Player>();

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == true)
		{
			m_Particle[i].Velocity += Vector3(0.0f, -0.01f, 0.0f);


			if (m_Particle[i].Position.y <= 0.0f)
			{
				m_Particle[i].Velocity.y *= -0.9f;
			}

			if (m_Particle[i].Velocity.y < 0.001f)
			{
				if (m_Particle[i].Velocity.y > -0.001f)
				{
					m_Particle[i].Velocity.y = 0.0f;
					m_Particle[i].Position.y = 0.1f;
				}
			}

			m_Particle[i].Position += m_Particle[i].Velocity;


			//プレイヤーが近くにいたら引き寄せられて、一定距離内で取得されて消える
			Vector3 d = player->GetPosition() + Vector3(0.0f, 1.0f, 0.0f) - m_Particle[i].Position;
			float length = d.length();
			if (length < 10.0f)
			{
				Vector3 direction = player->GetPosition() + Vector3(0.0f, 1.0f, 0.0f) - m_Particle[i].Position;
				direction.normalize();
				m_Particle[i].Position += direction * 0.3f;
			}

			if (length < 0.1f)
			{
				m_Particle[i].Enable = false;
				player->AddPlayerEXP(1);
			}

			//それぞれのパーティクルの寿命
			m_Particle[i].Life--;
			if (m_Particle[i].Life == 0)
				m_Particle[i].Enable = false;

		}
	}

	//パーティクルを出した親の寿命
	m_Life--;
	if (m_Life == 0)
	{
		SetDestroy();
	}

	m_InstancePositions.clear();
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable)
		{
			m_InstancePositions.push_back(m_Particle[i].Position);
		}
	}

	m_DrawCount = (UINT)m_InstancePositions.size();

	if (m_DrawCount > 0)
	{
		Renderer::GetDeviceContext()->UpdateSubresource(
			m_PositionBuffer,
			0,
			nullptr,
			m_InstancePositions.data(),
			0,
			0
		);
	}
}

void ParticleInstance::Draw()
{

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ビューの逆行列
	Camera* camera = Manager::GetScene()->GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);//逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	// Scale + Billboard のみ（平行移動なし）
	XMMATRIX scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	Renderer::SetWorldMatrix(scale * invView);

	//マテリアル設定
	MATERIAL material{};
	material.Diffuse = { 0.2f, 1.2f, 1.2f, 1.0f };
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//ストラクチャードバッファ設定
	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &m_PositionSRV);

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::SetDepthEnable(false);
	Renderer::SetAddBlendEnable(true);


	if (m_DrawCount > 0)
	{
		Renderer::GetDeviceContext()->DrawInstanced(
			4,              // 頂点数
			m_DrawCount,    // インスタンス数
			0,
			0
		);
	}

	Renderer::SetAddBlendEnable(false);
	Renderer::SetDepthEnable(true);
}
