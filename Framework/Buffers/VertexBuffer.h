#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT count, UINT stride, UINT slot = 0,
		bool bCpuWrite = false, bool bGpuWrite = false);
	~VertexBuffer();

private:
	ID3D11Buffer* buffer;

	void *data;
	UINT count;
	UINT stride;
	UINT slot;

	bool bGpuWrite;
	bool bCpuWrite;

public:
	UINT Count() { return count; }
	UINT Stride() { return stride; }
	ID3D11Buffer* Buffer() { return buffer; }

	void Render();
};

