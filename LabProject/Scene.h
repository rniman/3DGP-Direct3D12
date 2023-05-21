#pragma once
#include "Timer.h"

class CGameObject;
class CCamera;

class CScene
{
public:
	CScene();
	~CScene();
	
	ID3D12RootSignature* GetGraphicsRootSignature() const;

	void ReleaseUploadBuffers();
	//그래픽 루트 시그너쳐를 생성한다.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR* pKeysBuffer);
	void UpdateObjects(const float deltaTime);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM	lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	//씬은 게임 객체들의 집합이다. 게임 객체는 셰이더를 포함한다.
	CGameObject** m_ppObjects{ nullptr };
	int m_nObjects{};
	ID3D12RootSignature* m_pd3dGraphicsRootSignature{ nullptr };
};

