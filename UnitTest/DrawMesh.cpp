#include "stdafx.h"
#include "DrawMesh.h"
#include "Viewer/FreeCam.h"
#include "Environments/Terrain.h"


void DrawMesh::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);
	Context::Get()->GetCamera()->RotationDegree(10, 0, 0);
	Context::Get()->GetCamera()->Position(0, 0, -20);

	shader = new Shader(L"007_Mesh.fx");

	quad = new MeshQuad(shader);

	grid = new MeshGrid(shader);
	grid->Position(0, 0, 0);
	grid->Scale(20, 1, 20);
	grid->Color(1, 1, 1);

	cube = new MeshCube(shader);
	cube->Position(0, 5, 0);
	cube->Scale(20, 10, 20);
	cube->Color(1, 0, 0);

	for (UINT i = 0; i < 5; i++)
	{
		cylinder[i * 2] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2]->Position(-30, 6, -15.0f + (float)i * 15.0f);
		cylinder[i * 2]->Scale(5, 5, 5);
		cylinder[i * 2]->Color(0, 1, 0);

		cylinder[i * 2 + 1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2 + 1]->Position(30, 6, -15.0f + (float)i * 15.0f);
		cylinder[i * 2 + 1]->Scale(5, 5, 5);
		cylinder[i * 2 + 1]->Color(0, 1, 0);

		sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2]->Position(-30, 15.5f, -15.0f + (float)i * 15.0f);
		sphere[i * 2]->Scale(5, 5, 5);
		sphere[i * 2]->Color(0, 0, 1);

		sphere[i * 2 + 1] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2 + 1]->Position(30, 15.5f, -15.0f + (float)i * 15.0f);
		sphere[i * 2 + 1]->Scale(5, 5, 5);
		sphere[i * 2 + 1]->Color(0, 0, 1);
	}

}

void DrawMesh::Destroy()
{

}

void DrawMesh::Update()
{

}

void DrawMesh::Render()
{
	Vector3& direction = Context::Get()->LightDirection();
	ImGui::SliderFloat3("LightDirection", (float*)&direction, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(direction);

	//quad->Render();
	//grid->Render();
	//cube->Render();

	for (UINT i = 0; i < 10; i++)
	{
		cylinder[i]->Render();
		sphere[i]->Render();
	}
}
