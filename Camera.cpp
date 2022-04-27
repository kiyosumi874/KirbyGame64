#include "Camera.h"
#include "EffekseerForDXLib.h"

Camera::Camera(VECTOR transform, VECTOR rotate, float nearr, float farr, Input& input)
	: GameObject(transform, game::tag::CAMERA)
	, m_input(&input)
{
	m_near = nearr;
	m_far = farr;
	m_rotate = rotate;
	SetCameraNearFar(m_near, m_far);
	SetCameraPositionAndAngle(m_transform, m_rotate.x, m_rotate.y, m_rotate.z);

}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (m_input->IsPress(m_input->BUTTON_ID_RIGHT))
	{
		m_rotate = VAdd(m_rotate, VGet(0, DX_PI_F / 60.0f, 0));
	}
	if (m_input->IsPress(m_input->BUTTON_ID_LEFT))
	{
		m_rotate = VSub(m_rotate, VGet(0, DX_PI_F / 60.0f, 0));
	}
	if (m_input->IsPress(m_input->BUTTON_ID_UP))
	{
		m_rotate = VSub(m_rotate, VGet(DX_PI_F / 60.0f, 0, 0));
	}
	if (m_input->IsPress(m_input->BUTTON_ID_DOWN))
	{
		m_rotate = VAdd(m_rotate, VGet(DX_PI_F / 60.0f, 0, 0));
	}

	//if (m_input->IsPress(m_input->BUTTON_ID_W))
	//{
	//	m_transform = VAdd(m_transform, VGet(0, 0, 1));
	//}
	//if (m_input->IsPress(m_input->BUTTON_ID_A))
	//{
	//	m_transform = VAdd(m_transform, VGet(-1, 0, 0));
	//}
	//if (m_input->IsPress(m_input->BUTTON_ID_S))
	//{
	//	m_transform = VAdd(m_transform, VGet(0, 0, -1));
	//}
	//if (m_input->IsPress(m_input->BUTTON_ID_D))
	//{
	//	m_transform = VAdd(m_transform, VGet(1, 0, 0));
	//}
	if (m_input->IsPress(m_input->BUTTON_ID_E))
	{
		m_transform = VAdd(m_transform, VGet(0, 1, 0));
	}
	if (m_input->IsPress(m_input->BUTTON_ID_Q))
	{
		m_transform = VAdd(m_transform, VGet(0, -1, 0));
	}

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	SetCameraPositionAndAngle(m_transform, m_rotate.x, m_rotate.y, m_rotate.z);
}

void Camera::Draw()
{
#ifdef _DEBUG
	printfDx("\n");
	printfDx("CameraPosX:%f\n", m_transform.x);
	printfDx("CameraPosY:%f\n", m_transform.y);
	printfDx("CameraPosZ:%f\n", m_transform.z);
	printfDx("CameraRotateV:%f\n", m_rotate.x);
	printfDx("CameraRotateH:%f\n", m_rotate.y);
	printfDx("CameraRotateT:%f\n", m_rotate.z);
	printfDx("\n");
#endif // _DEBUG

	
}
