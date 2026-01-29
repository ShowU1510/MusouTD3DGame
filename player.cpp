#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"

#include "player.h"
#include "modelRenderer.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "enemy.h"
#include "scene.h"

void Player::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->LoadMagica("asset\\model\\PlayerModel.obj");


	m_Scale = { 0.5f, 0.5f, 0.5f };

	m_Time = 0.0f;
	m_BulletCoolTime = 1.0f;

	m_Level = 1;
	m_PlayerEXP = 0;
	m_NextLevelEXP = 300;

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\voxelVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\voxelPS.cso");

	m_SE = new Audio();
	m_SE->Load("asset\\audio\\se_shot.wav");

}


void Player::Uninit()
{
	m_SE->Uninit();
	delete m_SE;

	delete m_ModelRenderer;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Player::Update()
{
	Camera* camera = Manager::GetScene()->GetGameObject<Camera>();

	Vector3 rotation = camera->GetRotation();

	//プレイヤーの移動
	if (Input::GetKeyPress('W'))
	{
		m_IsMoveFront = true;

		Vector3 forward = camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();

		m_Position += forward * (0.1f + (m_Level * 0.01f));
		m_Rotation.y = rotation.y;
	}
	if (Input::GetKeyPress('S'))
	{
		m_IsMoveBack = true;

		Vector3 forward = camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();

		m_Position -= forward * (0.1f + (m_Level * 0.01f));
		m_Rotation.y = rotation.y + XM_PI;
	}
	if (Input::GetKeyPress('D'))
	{
		m_IsMoveSide = true;

		m_Position += camera->GetRight() * (0.1f + (m_Level * 0.01f));
		m_Rotation.y = rotation.y + XM_PIDIV2;

		if (m_IsMoveFront == true)
		{
			m_Rotation.y = rotation.y + XM_PIDIV4;
		}		
		if (m_IsMoveBack == true)
		{
			m_Rotation.y = rotation.y + XM_PIDIV2 + XM_PIDIV4;
			if (m_IsMoveFront == true)
			{
				m_Rotation.y = rotation.y + XM_PIDIV2;
			}
		}
	}
	if (Input::GetKeyPress('A'))
	{
		m_IsMoveSide = true;

		m_Position -= camera->GetRight() * (0.1f + (m_Level * 0.01f));
		m_Rotation.y = rotation.y - XM_PIDIV2;
	
		if (m_IsMoveFront == true)
		{
			m_Rotation.y = rotation.y - XM_PIDIV4;
			if (Input::GetKeyPress('D'))
			{
				m_Rotation.y = rotation.y;
			}
		}		
		if (m_IsMoveBack == true)
		{
			m_Rotation.y = rotation.y - XM_PIDIV2 - XM_PIDIV4;
			if (Input::GetKeyPress('D'))
			{
				m_Rotation.y = rotation.y + XM_PI;
			}
			if (m_IsMoveFront == true)
			{
				m_Rotation.y = rotation.y - XM_PIDIV2;
			}
		}
	}

	//カメラ回転とともにプレイヤーも回転させる
	if (Input::GetKeyPress(VK_LEFT))
	{
		m_Rotation.y -= 0.05f;
	}
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_Rotation.y += 0.05f;
	}



	m_Time += 1.0f / 60.0f;
	//弾発射
	if (Input::GetKeyTrigger(VK_SPACE)) //エンターはVK_RETURN
	{
		if (m_Time >= m_BulletCoolTime / m_Level)
		{
			Vector3 direction;
			Bullet* bullet;

			bullet = Manager::GetScene()->AddGameObject<Bullet>(1);
			bullet->SetPosition({ m_Position.x, m_Position.y + 0.7f, m_Position.z });
			direction = GetForward();
			bullet->SetVelocity(direction * 0.3f);

			m_SE->Play(false);

			m_Time = 0.0f;
		}
	}

	//レベル関連
	if (m_PlayerEXP >= m_NextLevelEXP)
	{
		m_Level += 1;
		m_PlayerEXP -= m_NextLevelEXP;
		m_NextLevelEXP += 100;
		if (m_Level > 15)
		{
			m_Level = 15;
		}
	}

	m_IsMoveFront = m_IsMoveBack = m_IsMoveSide = false;
}


void Player::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	XMMATRIX parentMatrix;

	//親の描画
	{
		//マトリクス設定
		XMMATRIX world, scale, rot, trans;
		scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;
		parentMatrix = world;

		Renderer::SetWorldMatrix(world);

		m_ModelRenderer->DrawMagica();
	}
}
