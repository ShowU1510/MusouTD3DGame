#include "main.h"
#include "renderer.h"
#include "enemy.h"
#include "modelRenderer.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"

#include "player.h"
#include "flag.h"

void Enemy::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->LoadMagica("asset\\model\\EnemyModel.obj");

	m_Scale = { 0.5f, 0.5f, 0.5f };

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\voxelVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\voxelPS.cso");
}


void Enemy::Uninit()
{
	delete m_ModelRenderer;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Enemy::Update()
{
	SetHitPosition({ m_Position.x, m_Position.y + 1.0f, m_Position.z });

	Flag* flag = Manager::GetScene()->GetGameObject<Flag>();
	Player* player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 direction = flag->GetPosition() - m_Position;
	direction.normalize();
	m_Position += direction * 0.019f + direction * 0.001f * player->GetLevel();

	m_Rotation.y = atan2f(direction.x, direction.z);
}


void Enemy::Draw()
{
	Camera* camera = Manager::GetScene()->GetGameObject<Camera>();

	//	//視錐台カリング
	if (camera->CheckView(m_Position) == false)
		return;


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
