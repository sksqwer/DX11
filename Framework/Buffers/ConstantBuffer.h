#pragma once
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	~ConstantBuffer();

private:
	ID3D11Buffer* buffer;
	void* data;
	UINT dataSize;

public:
	ID3D11Buffer* Buffer() { return buffer; }

	void Apply();
};

