#pragma once

class Terrain
{
public:
	Terrain(Shader* shader, wstring heightmap);
	~Terrain();

public:
	typedef VertexTextureNormal TerrainVertex;

private:
	Shader * shader;
	Texture * heightMap;
	UINT width, height;

	UINT vertexCount;
	TerrainVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	UINT pass;


private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();
	void CreateBuffer();

public:
	void Update();
	void Render();
	void BaseMap(wstring file);
	float  GetHeight(Vector3 position);
private:
	Texture*	baseMap;
	ID3DX11EffectShaderResourceVariable *sBaseMap;

	Vector2 spacing;
};

