#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"

#include "flag.h"
#include "modelRenderer.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "enemy.h"
#include "scene.h"
#include "score.h"
#include "result.h"

unsigned int Scene::m_ScoreValue = 0;

void Flag::Init()
{	
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->LoadMagica("asset\\model\\Flag.obj");
	
	m_Scale = { 0.2f, 0.2f, 0.2f };

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\voxelVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\voxelPS.cso");

}


void Flag::Uninit()
{
	m_ModelRenderer->Uninit();
	delete m_ModelRenderer;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void Flag::Update()
{
	//敵との衝突判定
	auto enemies = Manager::GetScene()->GetGameObjects<Enemy>();

	for (auto enemy : enemies)
	{
		Vector3 d = enemy->GetPosition() - m_Position;
		float length = d.length();
		if (length < 0.5f)
		{
			Score* score = Manager::GetScene()->GetGameObject<Score>();

			Scene::SetScoreValue(score->GetScore());

			Manager::SetScene<Result>();
		}
	}

}


void Flag::Draw()
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


	m_ModelRenderer->DrawMagica();
}
