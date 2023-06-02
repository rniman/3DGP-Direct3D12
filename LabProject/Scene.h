#pragma once
#include "Timer.h"

class CObjectsShader;
class CCamera;
//class CPlayer;

struct LIGHT
{
	XMFLOAT4 m_xmf4Ambient;
	XMFLOAT4 m_xmf4Diffuse;
	XMFLOAT4 m_xmf4Specular;
	XMFLOAT3 m_xmf3Position;
	float m_fFalloff;
	XMFLOAT3 m_xmf3Direction;
	float m_fTheta; //cos(m_fTheta)
	XMFLOAT3 m_xmf3Attenuation;
	float m_fPhi; //cos(m_fPhi)
	bool m_bEnable;
	int m_nType;
	float m_fRange;
	float padding;
};

struct LIGHTS
{
	LIGHT m_pLights[MAX_LIGHTS];
	XMFLOAT4 m_xmf4GlobalAmbient;
};

struct MATERIALS
{
	MATERIAL m_pReflections[MAX_MATERIALS];
};

class CScene
{
public:
	CScene();
	~CScene();
	
	ID3D12RootSignature* GetGraphicsRootSignature() const;

	void ReleaseUploadBuffers();
	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	//���� ��� ����� ������ ����
	void BuildLightsAndMaterials();

	//���� ��� ����� ������ ���� ���ҽ��� �����ϰ� ����
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();

	bool ProcessInput(UCHAR* pKeysBuffer);
	void UpdateObjects(const float deltaTime);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM	lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	
	void SetPlayer(CPlayer* player) { m_pPlayer = player; };

protected:
	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�.
	CObjectsShader* m_pShaders{ nullptr };
	int m_nShaders{};

	ID3D12RootSignature* m_pd3dGraphicsRootSignature{ nullptr };

	//���� ����
	LIGHTS* m_pLights{ nullptr };
	
	//������ ��Ÿ���� ���ҽ��� ���ҽ��� ���� �������̴�.
	ID3D12Resource* m_pd3dcbLights{ nullptr };
	LIGHTS* m_pcbMappedLights{ nullptr };
	
	//���� ��ü�鿡 ����Ǵ� ����
	MATERIALS* m_pMaterials{ nullptr };

	//������ ��Ÿ���� ���ҽ��� ���ҽ��� ���� �������̴�.
	ID3D12Resource* m_pd3dcbMaterials{ nullptr };
	MATERIAL* m_pcbMappedMaterials{ nullptr };

private:
	CPlayer* m_pPlayer{ nullptr };
};

