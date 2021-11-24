#pragma once
#include "Mesh.h"
class MeshSphere :
	public Mesh
{
public:
	MeshSphere(Shader* shader, float radius, UINT sliceCount = 10, UINT stackCount = 10);
	~MeshSphere();

protected:
	void Create() override;

private:
	float radius;

	UINT sliceCount;
	UINT stackCount;
};

