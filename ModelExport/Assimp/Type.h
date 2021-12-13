#pragma once
#include "stdafx.h"

struct AsMaterial
{
	string Name;
	Color Ambient;
	Color Diffuse;
	Color Specular;

	string DiffuseFile;
	string SpecularFile;
	string NormalFile;
};

struct AsBone
{
	int Index;
	string Name;

	int Parent;
	Matrix Transform;
};

struct AsMeshPart
{
	string Name;
	string MaterialName;

	UINT StartVertex;
	UINT VertexCount;

	UINT StartIndex;
	UINT IndexCount;
};

struct AsMesh
{
	string Name;
	int BondIndex;

	aiMesh* Mesh;
	
	vector<Model::ModelVertex> Vertices;
	vector<UINT> Indices;
	vector<AsMeshPart*> MeshParts;
};