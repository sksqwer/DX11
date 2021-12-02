#pragma once
class Terrain : public Renderer
{
public:
	Terrain(Shader* shader, wstring heightmap);
	~Terrain();

public:
	typedef VertexTextureNormal	TerrainVertex;

private:
	Texture*	heightMap;
	UINT width, height;

	struct BrushDesc
	{
		Color Color = D3DXCOLOR(0, 1, 0, 1);
		Vector3 Location;
		UINT Type = 0;
		UINT Range = 1;
		float Padding[3];
	} brushDesc;

	ConstantBuffer* brushBuffer;
	ID3DX11EffectConstantBuffer* sBrushBuffer;

	TerrainVertex* vertices;

	UINT* indices;

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();
	void CreateBuffer();

public:
	void Update();
	void Render();
	void BaseMap(wstring file);
	float GetHeight(Vector3& position);
	float GetPickedHeight(Vector3& position);
	Vector3 GetPickedPosition();

	void RaiseHeight(Vector3 & position, UINT type, UINT range);

private:
	Texture* baseMap;
	ID3DX11EffectShaderResourceVariable* sBaseMap;

	Vector2 spacing;
};