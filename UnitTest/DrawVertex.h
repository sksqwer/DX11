#pragma once

#include "Systems///IExecute.h"

class DrawVertex : public IExecute
{
	// Inherited via IExecute
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	Shader* shader;

	UINT width = 256;
	UINT height = 256;

	UINT vertexCount = 4;
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount = 6;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	ID3D11ShaderResourceView* srv;
	Texture* texture;

	//Color color;

	//int number;
	// Input Assembly -> Vertex Shader -> Teccelation -> H -> D -> G -> Render(Rester) (2D) -> Pixel Shader -> OM
};
