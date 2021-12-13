#pragma once
// #. class ModelBone, ModelMeshPart, ModelMesh

// -------------------------------------------------------------------------
class ModelBone
{
public:
	ModelBone();
	~ModelBone();
	friend class Model;

private:
	int index;
	wstring name;

	int parentIndex;
	ModelBone* parent;

	D3DXMATRIX transform;
	vector<ModelBone*> childs;

public:
	int ParentIndex() { return parentIndex; }
	ModelBone* Parent() { return parent; }

	wstring Name() { return name; }

	D3DXMATRIX& Transform() { return transform; }
	void Transform(D3DXMATRIX& mat) { transform = mat; }

	vector<ModelBone*>& Childs() { return childs; }
};

// -------------------------------------------------------------------------

class ModelMeshPart
{
public:
	friend class Model;
	friend class ModelMesh;

private:
	ModelMeshPart();
	~ModelMeshPart();

private:
	struct BoneDesc
	{
		Matrix Transform[MAX_MODEL_TRANSFORMS];
		UINT Index;
		float padding[3];
	} boneDesc;

private:
	wstring name;

	Shader* shader;
	UINT pass;

	PerFrame* perFrame;
	Transform* transform;

	class ModelMesh* parent;
	Material* material;
	wstring materialName;

	UINT startVertex;
	UINT vertexCount;

	UINT startIndex;
	UINT indexCount;

	ConstantBuffer* boneBuffer;
	ID3DX11EffectConstantBuffer* sBoneBuffer;

public:
	void SetShader(Shader* shader);
	void Pass(UINT val) { pass = val; }

private:
	void Transforms(Matrix* transform);
	void SetTransform(Transform* transform);

	void Update();
	void Render();

	void Binding(Model* model);
};


// -------------------------------------------------------------------------
class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

	friend class Model;

	void Binding(Model* model);
private:
	wstring name;
	int boneIndex;
	class ModelBone* bone;

	vector<class ModelMeshPart*> meshParts;

	VertexBuffer* vertexBuffer;
	UINT vertexCount;
	Model::ModelVertex* vertices;

	IndexBuffer* indexBuffer;
	UINT indexCount;
	UINT* indices;

public:
	void Pass(UINT pass);
	void SetShader(Shader* shader);

	void Update();
	void Render();

	wstring Name() { return name; }

	int BoneIndex() { return boneIndex; }
	class ModelBone* Bone() { return bone; }

	void Transforms(Matrix* transform);
	void SetTransform(Transform* transform);
};

