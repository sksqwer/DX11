#pragma once

class IExecute
{
public:
	virtual void Initialize() = 0;	// : 초기화
	virtual void Ready() = 0;		
	virtual void Destroy() = 0;		// : 프로그램 종료

	virtual void Update() = 0;		// : 이동등의 값 변경
	virtual void PreRender() = 0;	// : 
	virtual void Render() = 0;		// : 
	virtual void PostRender() = 0;

	virtual void ResizeScreen() = 0;	// : 화면 사이즈 변경 
};