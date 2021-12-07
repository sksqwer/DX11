#include "Stdafx.h"
#include "Loader.h"

Loader::Loader()
{
	importer = new Assimp::Importer;
}

Loader::~Loader()
{
	SafeDelete(importer);
}

void Loader::ReadFile(wstring file)
{
	this->file = L"../../_Assets/" + file;
	scene = importer->ReadFile(
		String::ToString(this->file),
		aiProcess_ConvertToLeftHanded
		| aiProcess_Triangulate
		| aiProcess_GenUVCoords
		| aiProcess_GenNormals
		| aiProcess_CalcTangentSpace
		);
}
