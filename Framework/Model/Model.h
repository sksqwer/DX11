#pragma once
#define MAX_MODEL_TRANSFORMS 128

class ModelBone;
class ModelMeshPart;
class ModelMesh;

class Model
{
public:
	Model();
	~Model();

	typedef VertexTextureNormal ModelVertex;

private:
	vector<Material*> materials;

public:
	UINT MaterialCount() { return materials.size(); }
	vector<Material*>& Materials() { return materials; }
	Material* MaterialByIndex(UINT index) { return materials[index]; }
	Material* MaterialByName(wstring name);

	void ReadMaterial(wstring file);
	void ReadMesh(wstring file);
};

