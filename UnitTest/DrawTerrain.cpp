#include "stdafx.h"
#include "DrawTerrain.h"
#include "Viewer/FreeCam.h"
#include "Environments/Terrain.h"


void DrawTerrain::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);

	shader = new Shader(L"006_Terrain.fx");

	terrain = new Terrain(shader, L"HeightMap/HeightMapTest.png");
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
	shader->AsVector("Direction")->SetFloatVector(direction);

	terrain->Update();
}

void DrawTerrain::Render()
{
	terrain->Render();
}
