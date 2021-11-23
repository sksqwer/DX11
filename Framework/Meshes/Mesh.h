#pragma once
class Mesh
{
public:
	Mesh(Shader* shader);
	virtual ~Mesh();

	typedef VertexNormal MeshVertex;

protected:
	MeshVertex*			vertices;
	UINT*			indices;

	UINT			vertexCount;
	UINT			indexCount;

	Shader*			shader;

	D3DXCOLOR			color;
private:
	ID3D11Buffer*	vertexBuffer;
	ID3D11Buffer*	indexBuffer;

	UINT			pass;
	Vector3			position;
	Vector3			scale;
	Vector3			rotation;

	D3DXMATRIX			world;

	ID3DX11EffectMatrixVariable *sWorld, *sView, *sProjection;
	ID3DX11EffectVectorVariable *sColor;

public:
	void Render();

	Shader* GetShader() { return shader;}

	//
	void Position(float x, float y, float z);
	void Position(D3DXVECTOR3& vec);
	void Position(D3DXVECTOR3* vec);

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	void Rotation(D3DXVECTOR3* vec);

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	void RotationDegree(D3DXVECTOR3* vec);

	void Scale(float x, float y, float z);
	void Scale(D3DXVECTOR3& vec);
	void Scale(D3DXVECTOR3* vec);

	void Matrix(D3DXMATRIX* mat);
	void Pass(UINT val) { pass = val; }

	void Color(D3DXCOLOR& val);
	void Color(float r, float g, float b);

protected:
	virtual void Create() = 0;
	void CreateBuffer();

private:
	void UpdateWorld();

	
};

