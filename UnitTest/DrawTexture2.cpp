#include "stdafx.h"
#include "DrawTexture2.h"
#include "Viewer/FreeCam.h"

void DrawTexture2::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 0, -3);
	shader = new Shader(L"008_Texture.fx");
	texture = new Texture(L"Bricks.png");

	VertexTexture vertices[4];
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0);

	vertices[0].Uv = Vector2(0, 1); // left down
	vertices[1].Uv = Vector2(0, 0); // left up 
	vertices[2].Uv = Vector2(1, 1); // right down 
	vertices[3].Uv = Vector2(1, 0); // right up

	{	// vertex buffer
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexTexture) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	UINT indices[6] = { 0, 1, 2, 2, 1, 3 };
	
	{	// index buffer
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
}

void DrawTexture2::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawTexture2::Update()
{
	Matrix world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&world, 10, 10, 10);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsSRV("DiffuseMap")->SetResource(texture->SRV());

	static Vector2 uv(1, 1);
	ImGui::SliderFloat2("UV", (float*)&uv, 0, 1);
	shader->AsVector("Uv")->SetFloatVector(uv);

	// address: wrap, mirror, clamp, border
	static UINT address = 0;
	ImGui::InputInt("Address", (int*)&address);
	address %= 4;
	shader->AsScalar("Address")->SetInt(address);

	// filter: point, linear
	static UINT filter = 0;
	ImGui::InputInt("Filter", (int*)&filter);
	filter %= 2;
	shader->AsScalar("Filter")->SetInt(filter);

}

void DrawTexture2::Render()
{
	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0); 
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 

	shader->DrawIndexed(0, 2, 6);
}
