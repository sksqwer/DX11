#pragma once

#include "Systems//IExecute.h"

class DrawVertex : public IExecute
{
public:

	DrawVertex();
	

	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	//VertexShader, PixelShader
	Shader* shader;

	UINT width = 256;
	UINT height = 256;

	UINT vertexCount;

	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	Color color;

	UINT number = 0;
};
