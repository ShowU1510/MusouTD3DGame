#include "main.h"
#include "renderer.h"
#include "bullet.h"
#include "modelRenderer.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "enemy.h"
#include "scene.h"
#include "score.h"
#include "player.h"
#include "particleInstance.h"

void Bullet::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->Load("asset\\model\\bullet.obj");

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

}


void Bullet::Uninit()
{
	delete m_ModelRenderer;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Bullet::Update()
{
	m_Position += m_Velocity;

	m_Frame++;

	if (m_Frame == m_FramePerExplosion)
	{
		m_Frame = 0;
	}

	if (m_Position.length() > 50.0f)
	{
		SetDestroy();
	}

	Player* player = Manager::GetScene()->GetGameObject<Player>();
	if (GetDistance(player->GetPosition()) > 30.0f)
	{
		SetDestroy();
	}


	//敵との衝突判定
	auto enemies = Manager::GetScene()->GetGameObjects<Enemy>();

	for (auto enemy : enemies)
	{
		Vector3 d = enemy->GetHitPosition() - m_Position;
		float length = d.length();
		if (length < 1.0f)
		{
			Manager::GetScene()->AddGameObject<ParticleInstance>(1)->SetPosition(enemy->GetPosition() + Vector3(0.0f, 1.0f, 0.0f));

			enemy->SetDestroy();

			if (player->GetLevel() < 5)
			{
				SetDestroy();
			}

			Camera* camera = Manager::GetScene()->GetGameObject<Camera>();
			camera->Shake({ 0.01f, 0.2f, 0.0f });

			Score* score = Manager::GetScene()->GetGameObject<Score>();
			score->Add(1);
		}
	}
}


void Bullet::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//マトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(world);

	m_ModelRenderer->Draw();
}
