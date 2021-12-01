#pragma once
class Renderer
{
public:
	Renderer(Shader* shader);
	Renderer(wstring shaderFile);

	virtual ~Renderer();

	Shader* GetShader() { return shader; }
	Transform* GetTransform() { return transform; }

	UINT & Pass() { return pass; }
	void Pass(UINT val) { pass = val; }

	virtual void Update();
	virtual void Render();

private:
	void Initialize();

protected:
	void Topolody(D3D11_PRIMITIVE_TOPOLOGY val) { topology = val; }

protected:
	Shader* shader;
	Transform* transform;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	UINT vertexCount;
	UINT indexCount;

private:
	bool bCreateShader;
	D3D11_PRIMITIVE_TOPOLOGY topology;
	UINT pass;

	PerFrame* perFrame;
};

