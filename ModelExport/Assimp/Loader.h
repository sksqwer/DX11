#pragma once
class Loader
{
public:
	Loader();
	~Loader();

	void ReadFile(wstring file);

private:
	wstring file;
	Assimp::Importer* importer;
	const aiScene* scene;

};

