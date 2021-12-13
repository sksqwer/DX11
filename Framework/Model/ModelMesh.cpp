#include "Framework.h"
#include "ModelMesh.h"

// -------------------------------------------------------------------------

ModelBone::ModelBone()
{
}

ModelBone::~ModelBone()
{
}

// -------------------------------------------------------------------------

ModelMeshPart::ModelMeshPart()
{
}

ModelMeshPart::~ModelMeshPart()
{
}

void ModelMeshPart::SetShader(Shader * shader)
{
}

void ModelMeshPart::Transforms(Matrix * transform)
{
}

void ModelMeshPart::SetTransform(Transform * transform)
{
}

void ModelMeshPart::Update()
{
}

void ModelMeshPart::Render()
{
}

void ModelMeshPart::Binding(Model * model)
{
}

// -------------------------------------------------------------------------

ModelMesh::ModelMesh()
{
}

ModelMesh::~ModelMesh()
{
}

void ModelMesh::Binding(Model * model)
{
}

void ModelMesh::Pass(UINT pass)
{
}

void ModelMesh::SetShader(Shader * shader)
{
}

void ModelMesh::Update()
{
}

void ModelMesh::Render()
{
}

void ModelMesh::Transforms(Matrix * transform)
{
}

void ModelMesh::SetTransform(Transform * transform)
{
}
