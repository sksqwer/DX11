#pragma once

#include "Systems///IExecute.h"

class DrawTexture2 : public IExecute
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

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	Texture* texture;
};
