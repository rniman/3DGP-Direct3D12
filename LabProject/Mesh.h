#pragma once

//정점을 표현하기 위한 클래스를 선언한다.
class CVertex
{
public:
	CVertex();
	CVertex(XMFLOAT3 xmf3Position);
	~CVertex();

protected:
	//정점의 위치 벡터이다(모든 정점은 최소한 위치 벡터를 가져야 한다).
	XMFLOAT3 m_xmf3Position;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CDiffusedVertex : public CVertex
{
protected:
	//정점의 색상이다.
	XMFLOAT4 m_xmf4Diffuse;
public:
	CDiffusedVertex();
	CDiffusedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse);
	CDiffusedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse);

	~CDiffusedVertex();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMesh
{
public:
	CMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual ~CMesh();

	void AddRef();
	void Release();
	void ReleaseUploadBuffers();

	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);

protected:
		ID3D12Resource* m_pd3dVertexBuffer{ nullptr };
		ID3D12Resource* m_pd3dVertexUploadBuffer{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW m_d3dVertexBufferView;
		D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology{ D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST };
		UINT m_nSlot{};
		UINT m_nVertices{};
		UINT m_nStride{};
		UINT m_nOffset{};

protected:
	/*인덱스 버퍼(인덱스의 배열)와 인덱스 버퍼를 위한 업로드 버퍼에 대한 인터페이스 포인터이다. 인덱스 버퍼는 정점 버퍼(배열)에 대한 인덱스를 가진다.*/
	ID3D12Resource* m_pd3dIndexBuffer{ nullptr };
	ID3D12Resource* m_pd3dIndexUploadBuffer{ nullptr };
	D3D12_INDEX_BUFFER_VIEW m_d3dIndexBufferView;
	
	//인덱스 버퍼에 포함되는 인덱스의 개수이다.
	UINT m_nIndices{};
	//인덱스 버퍼에서 메쉬를 그리기 위해 사용되는 시작 인덱스이다.
	UINT m_nStartIndex{};	
	//인덱스 버퍼의 인덱스에 더해질 인덱스이다.
	int m_nBaseVertex{};
	

private:
	int m_nReferences {};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CTriangleMesh : public CMesh
{
public:
	CTriangleMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual ~CTriangleMesh();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CCubeMeshDiffused : public CMesh
{
public:
	//직육면체의 가로, 세로, 깊이의 길이를 지정하여 직육면체 메쉬를 생성한다.
	CCubeMeshDiffused(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshDiffused();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CAirplaneMeshDiffused : public CMesh
{
public:
	CAirplaneMeshDiffused(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f, XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~CAirplaneMeshDiffused();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CHeightMapImage
{
public:
	CHeightMapImage(LPCTSTR pFileName, int nWidth, int nLength, XMFLOAT3 xmf3Scale);
	~CHeightMapImage();
	
	//높이 맵 이미지에서 (x, z) 위치의 픽셀 값에 기반한 지형의 높이를 반환한다.
	float GetHeight(float x, float z);

	//높이 맵 이미지에서 (x, z) 위치의 법선 벡터를 반환한다.
	XMFLOAT3 GetHeightMapNormal(int x, int z);
	
	BYTE* GetHeightMapPixels() { return(m_pHeightMapPixels); }
	int GetHeightMapWidth() { return(m_nWidth); }
	int GetHeightMapLength() { return(m_nLength); }
	XMFLOAT3 GetScale() { return(m_xmf3Scale); }

private:
	//높이 맵 이미지 픽셀(8-비트)들의 이차원 배열이다. 각 픽셀은 0~255의 값을 갖는다.
	BYTE* m_pHeightMapPixels;
	//높이 맵 이미지의 가로와 세로 크기이다
	int m_nWidth;
	int m_nLength;
	//높이 맵 이미지를 실제로 몇 배 확대하여 사용할 것인가를 나타내는 스케일 벡터이다.
	XMFLOAT3 m_xmf3Scale;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CHeightMapGridMesh : public CMesh
{
public:
	CHeightMapGridMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		int xStart, int zStart, int nWidth, int nLength, XMFLOAT3 xmf3Scale = XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f), void* pContext = nullptr);
	virtual ~CHeightMapGridMesh();

	XMFLOAT3 GetScale() { return(m_xmf3Scale); }
	int GetWidth() { return(m_nWidth); }
	int GetLength() { return(m_nLength); }

	//격자의 좌표가 (x, z)일 때 교점(정점)의 높이를 반환하는 함수이다.
	virtual float OnGetHeight(int x, int z, void* pContext);
	//격자의 좌표가 (x, z)일 때 교점(정점)의 색상을 반환하는 함수이다.
	virtual XMFLOAT4 OnGetColor(int x, int z, void* pContext);

protected:
	//격자의 크기(가로: x-방향, 세로: z-방향)이다.
	int	m_nWidth;
	int	m_nLength;

	/*격자의 스케일(가로: x-방향, 세로: z-방향, 높이: y-방향) 벡터이다. 실제 격자 메쉬의 각 정점의 x-좌표, y-좌표,
	z-좌표는 스케일 벡터의 x-좌표, y-좌표, z-좌표로 곱한 값을 갖는다. 즉, 실제 격자의 x-축 방향의 간격은 1이 아니
	라 스케일 벡터의 x-좌표가 된다. 이렇게 하면 작은 격자(적은 정점)를 사용하더라도 큰 크기의 격자(지형)를 생성할
	수 있다.*/
	XMFLOAT3 m_xmf3Scale;
};
