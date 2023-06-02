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
	//그래픽 루트 시그너쳐를 생성한다.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	//씬의 모든 조명과 재질을 생성
	void BuildLightsAndMaterials();

	//씬의 모든 조명과 재질을 위한 리소스를 생성하고 갱신
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
	//배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다.
	CObjectsShader* m_pShaders{ nullptr };
	int m_nShaders{};

	ID3D12RootSignature* m_pd3dGraphicsRootSignature{ nullptr };

	//씬의 조명
	LIGHTS* m_pLights{ nullptr };
	
	//조명을 나타내는 리소스와 리소스에 대한 포인터이다.
	ID3D12Resource* m_pd3dcbLights{ nullptr };
	LIGHTS* m_pcbMappedLights{ nullptr };
	
	//씬의 객체들에 적용되는 재질
	MATERIALS* m_pMaterials{ nullptr };

	//재질을 나타내는 리소스와 리소스에 대한 포인터이다.
	ID3D12Resource* m_pd3dcbMaterials{ nullptr };
	MATERIAL* m_pcbMappedMaterials{ nullptr };

private:
	CPlayer* m_pPlayer{ nullptr };
};

