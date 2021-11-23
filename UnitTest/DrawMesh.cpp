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
}

void DrawMesh::Destroy()
{
}

void DrawMesh::Update()
{
}

void DrawMesh::Render()
{
	quad->Render();
}