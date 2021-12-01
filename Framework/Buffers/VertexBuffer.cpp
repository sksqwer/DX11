#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void * data, UINT count, UINT stride, UINT slot, bool bCpuWrite, bool bGpuWrite)
	: data(data), count(count), stride(stride), slot(slot)
	, bCpuWrite(bCpuWrite), bGpuWrite(bGpuWrite)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = stride * count;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (bCpuWrite == false && bGpuWrite == false)
		desc.Usage = D3D11_USAGE_IMMUTABLE;
	else if (bCpuWrite == true && bGpuWrite == false)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else if (bCpuWrite == false && bGpuWrite == true)
		desc.Usage = D3D11_USAGE_DEFAULT;
	else
		assert(false);

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = data;
	Check(D3D::GetDevice()->CreateBuffer(&desc, data != NULL ? &subResource : NULL, &buffer));
}

VertexBuffer::~VertexBuffer()
{
	SafeRelease(buffer);
}

void VertexBuffer::Render()
{
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(slot, 1, &buffer, &stride, &offset);
}
