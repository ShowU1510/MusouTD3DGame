#include "main.h"
#include "cameraForTitle.h"
#include "renderer.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "scene.h"

void CameraForTitle::Init()
{
	m_Position = { 0.0f, 1.0f, -3.0f };
	m_TargetObject.SetPosition({ 0.0f, 0.0f, 0.0f });
}

void CameraForTitle::Uninit()
{

}

void CameraForTitle::Update()
{
	m_Target = m_TargetObject.GetPosition() + Vector3(0.0f, 1.5f, 0.0f);
}

void CameraForTitle::Draw()
{
	//プロジェクションマトリクス
	m_Projection = XMMatrixPerspectiveFovLH(1.0f,
					(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(m_Projection);

	//ビューマトリクス
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_View = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*) &m_Position),
								XMLoadFloat3((XMFLOAT3*) & m_Target),
								XMLoadFloat3(&up));

	Renderer::SetViewMatrix(m_View);
}
