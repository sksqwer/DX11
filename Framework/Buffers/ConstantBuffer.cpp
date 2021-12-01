#include "Framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void * data, UINT dataSize)
	: data(data), dataSize(dataSize)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.ByteWidth = sizeof(UINT) * dataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Check(D3D::GetDevice()->CreateBuffer(&desc, NULL, &buffer));

}

ConstantBuffer::~ConstantBuffer()
{
	SafeRelease(buffer);
}

void ConstantBuffer::Apply()
{
	D3D11_MAPPED_SUBRESOURCE subResource;

	D3D::GetDC()->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, data, dataSize);
	}
	D3D::GetDC()->Unmap(buffer, 0);
}
