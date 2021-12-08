#pragma once
class Loader
{
public:
	Loader();
	~Loader();

	void ReadFile(wstring file);

	void ExportMaterial(wstring savePath, bool bOverwrite = true);
	void ExportMesh(wstring savePath, bool bOverwrite = true);
private:
	void ReadMaterial();
	void WriteMaterial(wstring savePath, bool bOverwirte);
	string WriteTexture(string savePath, string file);

	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void WriteMeshData(wstring savePath, bool bOverwrite);

private:
	wstring file;
	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct AsMaterial*> materials;
	vector<struct AsBone*> bones;

};

