#pragma once

#include "Stdafx.h"

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