#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void * data, UINT count)
	: data(data), count(count)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(UINT) * count;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = data;
	Check(D3D::GetDevice()->CreateBuffer(&desc, data != NULL ? &subResource : NULL, &buffer));
}

IndexBuffer::~IndexBuffer()
{
	SafeRelease(buffer);
}

void IndexBuffer::Render()
{
	UINT offset = 0;
	D3D::GetDC()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}
