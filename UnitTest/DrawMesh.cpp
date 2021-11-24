#include "stdafx.h"
#include "Viewer/FreeCam.h"
#include "DrawMesh.h"

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
	cube->Color(1, 1, 1);

}

void DrawMesh::Destroy()
{
}

void DrawMesh::Update()
{
}

void DrawMesh::Render()
{
	//quad->Render();
	//grid->Render();
	cube->Render();
}