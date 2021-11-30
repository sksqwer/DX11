#include "stdafx.h"
#include "DrawTerrain.h"
#include "Viewer/FreeCam.h"
#include "Environments/Terrain.h"


void DrawTerrain::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(60, 10);

	shader = new Shader(L"009_Terrain.fx");

	terrain = new Terrain(shader, L"HeightMap/HeightMapTest.png");
	terrain->BaseMap(L"Terrain/Dirt.png");

	sphereShader = new Shader(L"007_Mesh.fx");
	sphere = new MeshSphere(sphereShader, 0.5f);
	sphere->Color(1, 0, 0);
	sphere->Position(0, 0, 0);
}

void DrawTerrain::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void DrawTerrain::Update()
{
	static Vector3 direction(-1, -1, 1);
	ImGui::SliderFloat3("Direction", (float*)&direction, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(direction);

	sphereShader->AsVector("LightDirection")->SetFloatVector(direction);

	Vector3 position;
	sphere->Position(&position);

	if (Keyboard::Get()->Press(VK_UP))
		position.z += 30.0f * Time::Delta();
	if (Keyboard::Get()->Press(VK_DOWN))
		position.z -= 30.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_RIGHT))
		position.x += 30.0f * Time::Delta();
	if (Keyboard::Get()->Press(VK_LEFT))
		position.x -= 30.0f * Time::Delta();

	position.y = terrain->GetHeight(position) + 0.5f;

	sphere->Position(position);

	terrain->Update();
}

void DrawTerrain::Render()
{
	terrain->Render();
	sphere->Render();
}
