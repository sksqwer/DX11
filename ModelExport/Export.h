#pragma once

#include "Systems/IExecute.h"

class Export : public IExecute
{
	// Inherited via IExecute
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override {};
	virtual void Update() override {};
	virtual void PreRender() override {};
	virtual void Render() override {};
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	void Tank();
	void Tower();
};
