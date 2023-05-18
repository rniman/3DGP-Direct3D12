#pragma once

//������ ǥ���ϱ� ���� Ŭ������ �����Ѵ�.
class CVertex
{
public:
	CVertex();
	CVertex(XMFLOAT3 xmf3Position);
	~CVertex();

protected:
	//������ ��ġ �����̴�(��� ������ �ּ��� ��ġ ���͸� ������ �Ѵ�).
	XMFLOAT3 m_xmf3Position;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CDiffusedVertex : public CVertex
{
protected:
	//������ �����̴�.
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