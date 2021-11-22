#pragma once

class Terrain
{
public:
	Terrain(Shader* shader, wstring heightmap);
	~Terrain();

public:
	typedef VertexNormal TerrainVertex;

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

};

