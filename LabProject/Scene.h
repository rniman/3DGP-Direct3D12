#pragma once
#include "Timer.h"
#include "Shader.h"

class CScene
{
public:
	CScene();
	~CScene();
	
	ID3D12RootSignature* GetGraphicsRootSignature() const;

	//void CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	void CreateGraphicsPipelineState(ID3D12Device* pd3dDevice);

	void ReleaseUploadBuffers();
	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR* pKeysBuffer);
	void UpdateObjects(const float deltaTime);

	void PrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);
	void RenderObjects(ID3D12GraphicsCommandList* pd3dCommandList);

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM	lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);



private:
	//���� ���̴����� �����̴�. ���̴����� ���� ��ü���� �����̴�.
	CShader** m_ppShaders{ nullptr };
	int m_nShaders{};

	//��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�.
	ID3D12RootSignature* m_pd3dGraphicsRootSignature;
	
	//���������� ���¸� ��Ÿ���� �������̽� �������̴�
	ID3D12PipelineState* m_pd3dPipelineState;
};

