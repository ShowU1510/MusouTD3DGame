#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "scene.h"

void Camera::Init()
{
	m_Position = { 0.0f, 1.0f, -5.0f };
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();

	if (Input::GetKeyPress(VK_LEFT))
	{
		m_Rotation.y -= 0.05f;
	}
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_Rotation.y += 0.05f;
	}



	m_Target = player->GetPosition() + Vector3(0.0f, 1.5f, 0.0f);

	m_Target += m_ShakeVector * cosf(m_ShakeTime);
	m_ShakeTime += 1.5f;//揺らす速さ
	m_ShakeVector *= 0.9f;

	m_Position = m_Target
		+ Vector3(-sinf(m_Rotation.y), 0.5f, -cosf(m_Rotation.y)) * 5.0f;
}

void Camera::Draw()
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

	//カメラの座標設定
	Renderer::SetCameraPosition(m_Position);
}

void Camera::Shake(Vector3 ShakeVector)
{
	m_ShakeVector = ShakeVector;
	m_ShakeTime = 0.0f;
}

//視錐台カリング用
//カメラの見える範囲内にあるかどうか
bool Camera::CheckView(Vector3 Position)
{
	XMMATRIX vp;
	vp = m_View * m_Projection;

	XMMATRIX invVp;
	invVp = XMMatrixInverse(nullptr, vp);//逆行列

	XMFLOAT3 vpos[4];
	vpos[0] = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vpos[1] = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vpos[2] = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vpos[3] = XMFLOAT3(1.0f, -1.0f, 1.0f);

	XMVECTOR vposv[4];
	vposv[0] = XMLoadFloat3(&vpos[0]);
	vposv[1] = XMLoadFloat3(&vpos[1]);
	vposv[2] = XMLoadFloat3(&vpos[2]);
	vposv[3] = XMLoadFloat3(&vpos[3]);

	XMVECTOR wposv[4];
	wposv[0] = XMVector3TransformCoord(vposv[0], invVp);
	wposv[1] = XMVector3TransformCoord(vposv[1], invVp);
	wposv[2] = XMVector3TransformCoord(vposv[2], invVp);
	wposv[3] = XMVector3TransformCoord(vposv[3], invVp);

	XMFLOAT3 wpos[4];
	XMStoreFloat3(&wpos[0], wposv[0]);
	XMStoreFloat3(&wpos[1], wposv[1]);
	XMStoreFloat3(&wpos[2], wposv[2]);
	XMStoreFloat3(&wpos[3], wposv[3]);

	Vector3 v;
	v = Position - m_Position;

	Vector3 wp[4];
	wp[0] = Vector3(wpos[0].x, wpos[0].y, wpos[0].z);
	wp[1] = Vector3(wpos[1].x, wpos[1].y, wpos[1].z);
	wp[2] = Vector3(wpos[2].x, wpos[2].y, wpos[2].z);
	wp[3] = Vector3(wpos[3].x, wpos[3].y, wpos[3].z);

	//左面
	{
		Vector3 v1, v2;
		v1 = wp[0] - m_Position;
		v2 = wp[2] - m_Position;

		Vector3 n;
		n = Vector3::cross(v1, v2);
		n.normalize();//正規化（長さ1にする）

		float d;
		d = Vector3::dot(n, v);//面からの距離

		if (d < 0.0f)
			return false;
	}

	//右面
	{
		Vector3 v1, v2;
		v1 = wp[3] - m_Position;
		v2 = wp[1] - m_Position;

		Vector3 n;
		n = Vector3::cross(v1, v2);
		n.normalize();

		float d;
		d = Vector3::dot(n, v);

		if (d < 0.0f)
			return false;
	}

	return true;

}