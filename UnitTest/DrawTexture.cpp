#include "stdafx.h"
#include "DrawTexture.h"
#include "Viewer/FreeCam.h"

void DrawTexture::Initialize()
{
	//((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);

	Context::Get()->GetCamera()->Position(0, 0, -3);

	shader = new Shader(L"005_Texture.fx");

	#pragma region Vertex Buffer

	// #. Quad

	//vertexCount = (width + 1) * (height + 1);
	//vertices = new Vertex[vertexCount];
	//for (UINT z = 0; z <= height; z++)
	//{
	//	for (UINT x = 0; x <= width; x++)
	//	{
	//		UINT index = (width + 1) * z + x;
	//		vertices[index].Position.x = (float)x;
	//		vertices[index].Position.y = 0.0f;
	//		vertices[index].Position.z = (float)z;
	//	}
	//}

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
		desc.ByteWidth = sizeof(VertexTexture) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	#pragma endregion

	#pragma region Index Buffer
	
	// #. Quad

	//indexCount = width * height * 6;
	//indices = new UINT[indexCount];
	//UINT index = 0;
	//for (UINT z = 0; z < height; z++)
	//{
	//	for (UINT x = 0; x < width; x++)
	//	{
	//		indices[index + 0] = (width + 1) * (z + 0) + (x + 0); // 좌하
	//		indices[index + 1] = (width + 1) * (z + 1) + (x + 0); // 좌상
	//		indices[index + 2] = (width + 1) * (z + 0) + (x + 1); // 우하
	//		indices[index + 3] = (width + 1) * (z + 0) + (x + 1); // 우하
	//		indices[index + 4] = (width + 1) * (z + 1) + (x + 0); // 좌상
	//		indices[index + 5] = (width + 1) * (z + 1) + (x + 1); // 우상
	//		index += 6;
	//	}
	//}

	// #. Texture

	UINT indices[6] = { 0,1,2, 2,1,3 };

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

	#pragma endregion

	//color = Color(1, 1, 1, 1);

	#pragma region Texture
	//D3DX11CreateShaderResourceViewFromFile
	//	(D3D::GetDevice(), L"../../_Textures/Box.png", NULL, NULL, &srv, NULL);
	//shader->AsSRV("Map")->SetResource(srv);

	texture = new Texture(L"Box.png");
	shader->AsSRV("Map")->SetResource(texture->SRV());
	#pragma endregion
}

void DrawTexture::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawTexture::Update()
{
	#pragma region Color
	// #. 색변경
	//ImGui::ColorEdit3("Color", (float*)&color);
	//shader->AsVector("Color")->SetFloatVector(color);
	#pragma endregion

	#pragma region KeyBoard
	//ImGui::InputInt("Number", (int*)&number);
	//number %= 6;

	//if (Keyboard::Get()->Press(VK_LEFT))
	//	vertices[number].Position.x -= 2.0f * Time::Delta();
	//else if (Keyboard::Get()->Press(VK_RIGHT))
	//	vertices[number].Position.x += 2.0f * Time::Delta();

	//if (Keyboard::Get()->Press(VK_DOWN))
	//	vertices[number].Position.y -= 2.0f * Time::Delta();
	//else if (Keyboard::Get()->Press(VK_UP))
	//	vertices[number].Position.y += 2.0f * Time::Delta();

	//D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0);
	#pragma endregion

	#pragma region World, View, Projection
	// #. W V P
	Matrix world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&world, 1, 1, 1);
	//{
	//	// #. change world
	//	static Vector3 position(0, 0, 0);
	//	if (Keyboard::Get()->Press(VK_LEFT))
	//		position.x -= 1.0f * Time::Delta();
	//	else if (Keyboard::Get()->Press(VK_RIGHT))
	//		position.x += 1.0f * Time::Delta();
	//	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
	//}
	
	shader->AsMatrix("World")->SetMatrix(world);

	Matrix view = Context::Get()->View();
	shader->AsMatrix("View")->SetMatrix(view);

	Matrix projection = Context::Get()->Projection();
	shader->AsMatrix("Projection")->SetMatrix(projection);
	#pragma endregion
}

void DrawTexture::Render()
{
	#pragma region Init
	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	#pragma endregion

	#pragma region Line
	// #. 정점 2개 씩 연결
	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	// #. 모든 정점 연결
	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	#pragma endregion

	#pragma region Triangle
	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	#pragma endregion

	#pragma region Rect
	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//// #. Rect 1
	//{
	//	static Vector3 position(1, 0, 0);
	//	if (Keyboard::Get()->Press(VK_LEFT))
	//		position.x -= 1.0f * Time::Delta();
	//	else if (Keyboard::Get()->Press(VK_RIGHT))
	//		position.x += 1.0f * Time::Delta();

	//	Matrix world;
	//	D3DXMatrixTranslation(&world, position.x, position.y, position.z);

	//	Color color(1, 0, 0, 1);

	//	shader->AsVector("Color")->SetFloatVector(color);
	//	shader->AsMatrix("World")->SetMatrix(world);
	//	shader->Draw(0, 0, 6);
	//}

	//// #. Rect 2
	//{
	//	static Vector3 position(-1, 0, 0);

	//	Matrix world2;
	//	D3DXMatrixTranslation(&world2, position.x, position.y, position.z);

	//	Color color(1, 1, 0, 1);

	//	shader->AsVector("Color")->SetFloatVector(color);
	//	shader->AsMatrix("World")->SetMatrix(world2);
	//	shader->Draw(0, 0, 6);
	//}
	#pragma endregion

	#pragma region Quad(Rasterize)

	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//static bool bWireframe = true;
	//ImGui::Checkbox("Wireframe", &bWireframe);
	//shader->DrawIndexed(0, (bWireframe) ? 0 : 1, indexCount);
	#pragma endregion

	#pragma region Texture

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->DrawIndexed(0, 0, indexCount);

	#pragma endregion

	/*shader->Draw(0, 0, 6);
	//  GUI
	ImGui::Text("FPS : %f", Time::Get()->FPS());
	for (int i = 0; i < 6; i++)
	{
		ImGui::Text("vertices[%d] : %f, %f, %f", i, vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
	}
	*/
}