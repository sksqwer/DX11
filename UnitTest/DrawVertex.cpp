
#include "Stdafx.h"
#include "DrawVertex.h"

void DrawVertex::Initialize()
{
	shader = new Shader(L"003_World.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(0.0f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.0f, 0.0f);

	vertices[3].Position = Vector3(0.5f, 0.0f, 0.0f);
	vertices[4].Position = Vector3(0.0f, 0.5f, 0.0f);
	vertices[5].Position = Vector3(0.5f, 0.5f, 0.0f);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(Vertex) * 6;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;
	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));

	color = Color(0, 0, 0, 1);

}
void DrawVertex::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void DrawVertex::Update()
{
	//ImGui::ColorEdit3("Color", (float*)&color);
	//shader->AsVector("Color")->SetFloatVector(color);

	//  << : move each vertex 
	//ImGui::InputInt("Number", (int*)&number);
	//number %= 6;

	//if (Keyboard::Get()->Press(VK_LEFT))
	//{
	//	for(int i =0 ; i < 6; i++)
	//		vertices[i].Position.x -= 2.0f * Time::Delta();
	//}
	//else if (Keyboard::Get()->Press(VK_RIGHT))
	//	for (int i = 0; i < 6; i++)
	//	vertices[i].Position.x += 2.0f * Time::Delta();

	//if (Keyboard::Get()->Press(VK_DOWN))
	//	for (int i = 0; i < 6; i++)
	//	vertices[i].Position.y -= 2.0f * Time::Delta();

	//else if (Keyboard::Get()->Press(VK_UP))
	//	for (int i = 0; i < 6; i++)
	//	vertices[i].Position.y += 2.0f * Time::Delta();

	//D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0);

	//Matrix world;
	//D3DXMatrixIdentity(&world);
	//{
	//	static Vector3 position(0, 0, 0);
	//	if (Keyboard::Get()->Press(VK_LEFT))
	//		position.x -= 2.0f * Time::Delta();
	//	else if (Keyboard::Get()->Press(VK_RIGHT))
	//		position.x += 2.0f * Time::Delta();
	//	if (Keyboard::Get()->Press(VK_DOWN))
	//		position.y -= 2.0f * Time::Delta();

	//	else if (Keyboard::Get()->Press(VK_UP))
	//		position.y += 2.0f * Time::Delta();

	//	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
	//}
	//shader->AsMatrix("World")->SetMatrix(world);

	Matrix view = Context::Get()->View();
	shader->AsMatrix("View")->SetMatrix(view);

	Matrix projection = Context::Get()->Projection();
	shader->AsMatrix("Projection")->SetMatrix(projection);


	ImGui::Text("FPS : %f", Time::Get()->FPS());
	ImGui::Text("Vertices[%d]: %f, %f, %f", 0, vertices[0].Position, vertices[0].Position, vertices[0].Position);
	ImGui::Text("Vertices[%d]: %f, %f, %f", 1, vertices[1].Position, vertices[1].Position, vertices[1].Position);
	ImGui::Text("Vertices[%d]: %f, %f, %f", 2, vertices[2].Position, vertices[2].Position, vertices[2].Position);
}

void DrawVertex::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Rect 1
	{
		static Vector3 position(1, 0, 0);
		if (Keyboard::Get()->Press(VK_LEFT))
					position.x -= 2.0f * Time::Delta();
				else if (Keyboard::Get()->Press(VK_RIGHT))
					position.x += 2.0f * Time::Delta();
				if (Keyboard::Get()->Press(VK_DOWN))
					position.y -= 2.0f * Time::Delta();

				Matrix world;
				D3DXMatrixIdentity(&world);
				D3DXMatrixTranslation(&world, position.x, position.y, position.z);
				shader->AsMatrix("World")->SetMatrix(world);

				Color color(1, 0, 0, 1);
				shader->AsVector("Color")->SetFloatVector(color);
				shader->Draw(0, 0, 6);
	}

	// Rect 2
	{
		static Vector3 position(-1, 0, 0);

		Matrix world2;
		D3DXMatrixIdentity(&world2);
		D3DXMatrixTranslation(&world2, position.x, position.y, position.z);
		shader->AsMatrix("World")->SetMatrix(world2);

		Color color(1, 1, 0, 1);
		shader->AsVector("Color")->SetFloatVector(color);
		shader->Draw(0, 0, 6);
	}


	//ImGui::Text("FPS : %f", Time::Get()->FPS());
}