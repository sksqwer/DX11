#include "Stdafx.h"
#include "Loader.h"
#include "Type.h"
#include "Utilities/Xml.h"
#include "Utilities/BinaryFile.h"

Loader::Loader()
{
	importer = new Assimp::Importer;
}

Loader::~Loader()
{
	SafeDelete(importer)
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
	assert(scene != NULL);
}

void Loader::ExportMaterial(wstring savePath, bool bOverwrite)
{
	savePath = L"../../_Textures/" + savePath + L".material";
	ReadMaterial();

	WriteMaterial(savePath, bOverwrite);
}

void Loader::ExportMesh(wstring savePath, bool bOverwrite)
{
	savePath = L"../../_Models/" + savePath + L".Mesh";
	ReadBoneData(scene->mRootNode, -1, -1);
	
	WriteMeshData(savePath, bOverwrite);
}

void Loader::ReadBoneData(aiNode* node, int index, int parent)
{
	AsBone* bone = new AsBone();
	bone->Index = index;
	bone->Parent = parent;
	bone->Name = node->mName.C_Str();

	Matrix transform(node->mTransformation[0]);

	D3DXMatrixTranspose(&bone->Transform, &transform);

	Matrix temp;
	if (parent == -1)
		D3DXMatrixIdentity(&temp);
	else
		temp = bones[parent]->Transform;

	bone->Transform = bone->Transform*temp;
	bones.push_back(bone);

	ReadMeshData(node, index);

	for(UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadBoneData(node->mChildren[i], bones.size(), index);
	}

}

void Loader::ReadMeshData(aiNode* node, int index)
{
}

void Loader::WriteMeshData(wstring savePath, bool bOverwrite)
{
}

void Loader::ReadMaterial()
{
	for(UINT i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* readMaterial = scene->mMaterials[i];
		AsMaterial* material = new AsMaterial();
		material->Name = readMaterial->GetName().C_Str();

		//int breakpoint = 999;

		float val;
		aiColor3D color;

		readMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->Ambient = Color(color.r, color.g, color.b, 1.0f);

		readMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->Diffuse = Color(color.r, color.g, color.b, 1.0f);

		readMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->Specular = Color(color.r, color.g, color.b, 1.0f);

		readMaterial->Get(AI_MATKEY_SHININESS, material->Specular.a);

		aiString file;

		readMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->DiffuseFile = file.C_Str();

		readMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->SpecularFile = file.C_Str();

		readMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		material->NormalFile = file.C_Str();

		materials.push_back(material);


		SafeDelete(readMaterial)
	}
}

void Loader::WriteMaterial(wstring savePath, bool bOverwirte)
{
	if(!bOverwirte)
	{
		if (Path::ExistFile(savePath))
			return;
	}

	string folder = String::ToString(Path::GetDirectoryName(savePath));
	string file = String::ToString(Path::GetFileName(savePath));

	Path::CreateFolders(folder);

	Xml::XMLDocument* document = new Xml::XMLDocument();
	Xml::XMLDeclaration * decl = document->NewDeclaration();
	document->LinkEndChild(decl);

	Xml::XMLElement* root = document->NewElement("Materials");
	root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
	document->LinkEndChild(root);


	for (AsMaterial* material : materials)
	{
		Xml::XMLElement* node = document->NewElement("Material");
		root->LinkEndChild(node);

		Xml::XMLElement* element = NULL;
		element = document->NewElement("Name");
		element->SetText(material->Name.c_str());
		node->LinkEndChild(element);

		element = document->NewElement("DiffuseFile");
		element->SetText(WriteTexture(folder, material->DiffuseFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("SpecularFile");
		element->SetText(WriteTexture(folder, material->SpecularFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("NormalFile");
		element->SetText(WriteTexture(folder, material->NormalFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("Ambient");
		element->SetAttribute("R", material->Ambient.r);
		element->SetAttribute("G", material->Ambient.g);
		element->SetAttribute("B", material->Ambient.b);
		element->SetAttribute("A", material->Ambient.a);
		node->LinkEndChild(element);


		element = document->NewElement("Diffuse");
		element->SetAttribute("R", material->Diffuse.r);
		element->SetAttribute("G", material->Diffuse.g);
		element->SetAttribute("B", material->Diffuse.b);
		element->SetAttribute("A", material->Diffuse.a);
		node->LinkEndChild(element);


		element = document->NewElement("Specular");
		element->SetAttribute("R", material->Specular.r);
		element->SetAttribute("G", material->Specular.g);
		element->SetAttribute("B", material->Specular.b);
		element->SetAttribute("A", material->Specular.a);
		node->LinkEndChild(element);

		SafeDelete(material);
	}


	document->SaveFile((folder + file).c_str());



}

string Loader::WriteTexture(string savePath, string file)
{
	if (file.length() < 1) return "";

	string fileName = Path::GetFileName(file);

	const aiTexture* texture = scene->GetEmbeddedTexture(file.c_str());

	string path = "";

	if(texture != NULL)
	{
		path = savePath + Path::GetFileNameWithoutExtension(file) + ".png";
		if(texture->mHeight < 1)
		{
			BinaryWriter w;
			w.Open(String::ToWString(path));
			w.Byte(texture->pcData, texture->mWidth);
			w.Close();
		}
		else
		{
			ID3D11Texture2D* dest;
			D3D11_TEXTURE2D_DESC destDesc;
			ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
			destDesc.Width = texture->mWidth;
			destDesc.Height = texture->mHeight;
			destDesc.MipLevels = 1;
			destDesc.ArraySize = 1;
			destDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			destDesc.SampleDesc.Count = 1;
			destDesc.SampleDesc.Quality = 0;
			destDesc.Usage = D3D11_USAGE_IMMUTABLE;

			D3D11_SUBRESOURCE_DATA subResource = { 0 };
			subResource.pSysMem = texture->pcData;
			HRESULT hr;
			hr = D3D::GetDevice()->CreateTexture2D(&destDesc, &subResource, &dest);
			assert(SUCCEEDED(hr));

			D3DX11SaveTextureToFileA(D3D::GetDC(), dest, 
				D3DX11_IFF_PNG, savePath.c_str());
		}
	}
	else
	{
		string directory = Path::GetDirectoryName(String::ToString(this->file));
		string origin = directory + file;
		String::Replace(&origin, "\\", "/");

		if (!Path::ExistFile(origin))
			return "";

		path = savePath + fileName;
		CopyFileA(origin.c_str(), path.c_str(), FALSE);
		String::Replace(&path, "../../_Textures/", "");
		
	}

	return Path::GetFileName(path);

}
