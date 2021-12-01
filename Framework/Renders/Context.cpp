#include "Framework.h"
#include "Context.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"
#include "Viewer/FreeCam.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);
	camera = new FreeCam();
	lightDirection = Vector3(-1, -1, 1);

	//position = D3DXVECTOR3(0, 4, -10);
	//D3DXVECTOR3 forward(0, 0, 1);
	//D3DXVECTOR3 right(1, 0, 0);
	//D3DXVECTOR3 up(0, 1, 0);

	//D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
}

Context::~Context()
{
	SafeDelete(perspective);
	SafeDelete(viewport);
	SafeDelete(camera);
}

void Context::Update()
{
	camera->Update();
}

void Context::Render()
{
	string str = string("Frame Rate : ") + to_string(ImGui::GetIO().Framerate);
	Gui::Get()->RenderText(5, 5, 1, 1, 1, str);

	Vector3 camPos;
	Context::Get()->GetCamera()->Position(&camPos);

	Vector3 camDir;
	Context::Get()->GetCamera()->RotationDegree(&camDir);

	str = "Cam Position : ";
	str += to_string((int)camPos.x) + ", " + to_string((int)camPos.y) + ", " + to_string((int)camPos.z);
	Gui::Get()->RenderText(5, 20, 1, 1, 1, str);

	str = "Cam RotationDegree : ";
	str += to_string((int)camDir.x) + ", " + to_string((int)camDir.y) + ", " + to_string((int)camDir.z);
	Gui::Get()->RenderText(5, 35, 1, 1, 1, str);

	//ImGui::SliderFloat3("Camera", (float*)&position, -100, 100);
	//D3DXVECTOR3 forward(0, 0, 1);
	//D3DXVECTOR3 right(1, 0, 0);
	//D3DXVECTOR3 up(0, 1, 0);
	//D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);

	viewport->RSSetViewport();
}

D3DXMATRIX Context::View()
{
	Matrix view;
	camera->GetMatrix(&view);
	return view;
}

D3DXMATRIX Context::Projection()
{
	D3DXMATRIX projection;
	perspective->GetMatrix(&projection);

	return projection;
}
