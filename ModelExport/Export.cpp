#include "Stdafx.h"
#include "Export.h"
#include "Assimp/Loader.h"

void Export::Initialize()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Tank/Tank.fbx");

	int breakpoint = 9999;
	
	SafeDelete(loader);

}	