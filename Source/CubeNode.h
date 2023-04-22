#pragma once

#include "DirectXFramework.h"
#include "SceneNode.h"

#define ShaderFileName		L"shader.hlsl"
#define VertexShaderName	"VS"
#define PixelShaderName		"PS"


class CubeNode: public SceneNode
{

public:

	CubeNode(wstring name, Vector4 colour) : SceneNode(name) { _name = name; _colour = colour; }; 
	~CubeNode(void) {}; 

	bool Initialise();
	void Render(); 
	void Shutdown();

	void BuildGeometryBuffers();
	void BuildShaders();
	void BuildVertexLayout();
	void BuildConstantBuffer();
	void BuildRasteriserState();

private:
	ComPtr<ID3D11Device> _device =	DirectXFramework::GetDXFramework()->GetDevice();
	ComPtr<ID3D11DeviceContext> _deviceContext = DirectXFramework::GetDXFramework()->GetDeviceContext();


	D3D11_VIEWPORT					_screenViewport{ 0 };

	ComPtr<ID3D11Buffer>			_vertexBuffer;
	ComPtr<ID3D11Buffer>			_indexBuffer;

	ComPtr<ID3DBlob>				_vertexShaderByteCode = nullptr;
	ComPtr<ID3DBlob>				_pixelShaderByteCode = nullptr;
	ComPtr<ID3D11VertexShader>		_vertexShader;
	ComPtr<ID3D11PixelShader>		_pixelShader;
	ComPtr<ID3D11InputLayout>		_layout;
	ComPtr<ID3D11Buffer>			_constantBuffer;

	ComPtr<ID3D11RasterizerState>   _rasteriserState;

	Vector3							_eyePosition;
	Vector3							_focalPointPosition;
	Vector3							_upVector;

	// The default constructor for the Matrix class initialises the matrix to the Identity matrix.  
	// This is sufficient for _worldTransformation for this example.  The other two are set in the
	// Render method.

	Matrix							_worldTransformation;
	Matrix							_viewTransformation;
	Matrix							_projectionTransformation;
};

