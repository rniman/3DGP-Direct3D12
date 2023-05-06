#pragma once

class CGameFramework
{
public:
	CGameFramework();
	~CGameFramework();
	
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);	//�����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ��̴�(�� �����찡 �����Ǹ� ȣ��ȴ�).
	void OnDestroy();
	
	//���� ü��, ����̽�, ������ ��, ��� ť/�Ҵ���/����Ʈ�� �����ϴ� �Լ�
	void CreateDirect3DDevice();
	void CreateSwapChain();
	void CreateCommandQueueAndList();
	void CreateRtvDescriptorHeap();
	void CreateDsvDescriptorHeap();

	//���� Ÿ�� ��� ����-���ٽ� �並 �����ϴ� �Լ�
	void CreateRenderTargetViews();
	void CreateDepthStencilView();

	//�������� �޽��� ���� ��ü�� �����ϰ� �Ҹ��ϴ� �Լ�
	void BuildObjects();
	void ReleaseObjects();

	//�����ӿ�ũ�� �ٽ�(����� �Է�, �ִϸ��̼�, ������)�� �����ϴ� �Լ�
	void ProcessInput();
	void UpdateObjects();
	void FrameAdvance();
	
	//CPU�� GPU�� ����ȭ�ϴ� �Լ�
	void WaitForGpuComplete();

	//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�.
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	//DXGI ���丮 �������̽��� ���� ������
	IDXGIFactory4* m_pdxgiFactory;

	//���� ü�� �������̽��� ���� ������ �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ�
	IDXGISwapChain3* m_pdxgiSwapChain;

	//Direct3D ����̽� �������̽��� ���� ������ �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ�
	ID3D12Device* m_pd3dDevice;

	//MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ ����
	bool m_bMsaa4xEnable{ false };
	UINT m_nMsaa4xQualityLevels{ 0 };

	//���� ü���� �ĸ� ������ �����̴�.
	static const UINT m_nSwapChainBuffers = 2;
	
	//���� ���� ü���� �ĸ� ���� �ε����̴�
	UINT m_nSwapChainBufferIndex;
	
	//���� Ÿ�� ����, ������ �� �������̽� ������, ���� Ÿ�� ������ ������ ũ��
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;

	//����-���ٽ� ����, ������ �� �������̽� ������, ����-���ٽ� ������ ������ ũ��
	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;

	//��� ť, ��� �Ҵ���, ��� ����Ʈ �������̽� ������
	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;
	
	//�׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� ������
	ID3D12PipelineState* m_pd3dPipelineState;
	
	//�潺 �������̽� ������, �潺�� ��, �̺�Ʈ �ڵ�
	ID3D12Fence* m_pd3dFence;
	UINT64 m_nFenceValue;
	HANDLE m_hFenceEvent;

	//����Ʈ�� ���� �簢��
	D3D12_VIEWPORT m_d3dViewport;
	D3D12_RECT m_d3dScissorRect;
	
};

