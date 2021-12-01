#pragma once

class Context
{
public:
	static Context* Get();
	static void Create();
	static void Delete();

private:
	Context();
	~Context();

public:
	void Update();
	void Render();

	D3DXMATRIX View(); // { return view; }
	D3DXMATRIX Projection();
	Vector3&   LightDirection() { return lightDirection; }
	void   LightDirection(Vector3& dir) { lightDirection = dir; }

	Color& LightAmbient() { return lightAmbient; }
	Color& LightSpecular() { return lightSpecular; }
	Vector3& LightPosition() { return lightPosition; }

	class Perspective* GetPerspective() { return perspective; }
	class Viewport* GetViewport() { return viewport; }
	class Camera* GetCamera() { return camera; }

private:
	static Context* instance;

private:
	class Perspective* perspective;
	class Viewport* viewport;
	class Camera* camera;

	//D3DXVECTOR3 position;
	//D3DXMATRIX view;
	Vector3 lightDirection;

	Color lightAmbient;
	Color lightSpecular;
	Vector3 lightPosition;
};