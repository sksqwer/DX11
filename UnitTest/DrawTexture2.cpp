#include "stdafx.h"
#include "DrawTexture2.h"
#include "Viewer/FreeCam.h"

void DrawTexture2::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 0, -3);

	shader = new Shader(L"008_Texture.fx");
	texture = new Texture(L"Bricks.png");

	#pragma region Vertex Buffer
	// #. Texture
	VertexTexture vertices[4];
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0, 1);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 0);

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexTexture) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	#pragma endregion

	#pragma region Index Buffer
	// #. Texture

	UINT indices[6] = { 0,1,2, 2,1,3 };

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
	#pragma endregion
}

void DrawTexture2::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawTexture2::Update()
{
	#pragma region World, View, Projection
	// #. W V P
	Matrix world;
	D3DXMatrixIdentity(&world);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsSRV("DiffuseMap")->SetResource(texture->SRV());
	#pragma endregion

	static Vector2 uv(1, 1);
	ImGui::SliderFloat2("UV", (float*)&uv, 0, 1);
	shader->AsVector("Uv")->SetFloatVector(uv);

	static UINT address = 0;
	ImGui::InputInt("Address", (int*)&address);
	address %= 4;
	shader->AsScalar("Address")->SetInt(address);

	static UINT filter = 0;
	ImGui::InputInt("Filter", (int*)&filter);
	filter %= 2;
	shader->AsScalar("Filter")->SetInt(filter);
}

void DrawTexture2::Render()
{
	#pragma region Init
	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	#pragma endregion

	#pragma region Texture

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->DrawIndexed(0, 2, 6);

	#pragma endregion
}