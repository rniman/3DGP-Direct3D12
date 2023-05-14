#pragma once
#include "Timer.h"

class CScene
{
public:
	CScene();
	~CScene();
	
	void CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	void CreateGraphicsPipelineState(ID3D12Device* pd3dDevice);

	void BuildObjects(ID3D12Device& d3dDevice);
	void ReleaseObjects();

	bool ProcessInput();
	void UpdateObjects(const float deltaTime);

	void PrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);
	void RenderObjects(ID3D12GraphicsCommandList* commandList);

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	//루트 시그너쳐를 나타내는 인터페이스 포인터이다.
	ID3D12RootSignature* m_pd3dGraphicsRootSignature;
	
	//파이프라인 상태를 나타내는 인터페이스 포인터이다
	ID3D12PipelineState* m_pd3dPipelineState;
};

