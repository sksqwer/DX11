#include "stdafx.h"
#include "DrawVertex.h"

DrawVertex::DrawVertex()
	: shader(NULL)
	, vertexBuffer(NULL)
{

}

void DrawVertex::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);

	shader = new Shader(L"004_Quad.fx");

	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];

	for (UINT z = 0; z <= height; ++z)
	{
		for (UINT x = 0; x <= width; ++x)
		{
			UINT index = (width + 1) * z + x;
			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = 0.0f;
			vertices[index].Position.z = (float)z;
		}
	}

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	{
		indexCount = width * height * 6;
		indices = new UINT[indexCount];

		UINT index = 0;

		for (UINT z = 0; z < height; ++z)
		{
			for (UINT x = 0; x < width; ++x)
			{
				indices[index + 0] = (width + 1) * (z)+(x);
				indices[index + 1] = (width + 1) * (z + 1) + (x);
				indices[index + 2] = (width + 1) * (z)+(x + 1);

				indices[index + 3] = (width + 1) * (z)+(x + 1);
				indices[index + 4] = (width + 1) * (z + 1) + (x);
				indices[index + 5] = (width + 1) * (z + 1) + (x + 1);

				index += 6;
			}
		}

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

	color = Color(0, 0, 0, 1);
}

void DrawVertex::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawVertex::Update()
{
	ImGui::ColorEdit3("Color", (float*)&color);
	shader->AsVector("Color")->SetFloatVector(color);

	Matrix world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&world, 2, 2, 1);
	shader->AsMatrix("World")->SetMatrix(world);

	Matrix view = Context::Get()->View();
	shader->AsMatrix("View")->SetMatrix(view);

	Matrix projection = Context::Get()->Projection();
	shader->AsMatrix("Projection")->SetMatrix(projection);
}

void DrawVertex::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWireframe = false;
	ImGui::Checkbox("Wireframe", &bWireframe);

	//shader->Draw(0, bWireframe ? 0 : 1, 6, 0);
	shader->DrawIndexed(0, bWireframe ? 0 : 1, indexCount);
	//ImGui::Text("FPS : %f", Time::Get()->FPS());
}