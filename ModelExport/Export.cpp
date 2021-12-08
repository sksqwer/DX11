#include "Stdafx.h"
#include "Export.h"
#include "Assimp/Loader.h"

void Export::Initialize()
{
	Tank();
	Tower();
}

void Export::Tank()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Tank/Tank.fbx");
	loader->ExportMaterial(L"Tank/Tank");
	loader->ExportMesh(L"Tank/Tank");

	SafeDelete(loader)
}

void Export::Tower()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Tower/Tower.fbx");
	loader->ExportMaterial(L"Tower/Tower");
	loader->ExportMesh(L"Tower/Tower");

	SafeDelete(loader)
}