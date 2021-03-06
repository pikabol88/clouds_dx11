#pragma once

#include "../../pch.h"
#include "Renderer.h"
#include "ConstantBuffer.h"

using namespace DirectX;

class Shader {
private:
	struct MatrixBuffer	{
		XMMATRIX projectionMatrix;	// 64 bytes
		XMMATRIX viewMatrix;		// 64 bytes
		XMMATRIX worldMatrix;		// 64 bytes
	} matrixBufferValues{};

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
	ID3D11DeviceContext* deviceContext;

	ConstantBuffer matrixBuffer;

	bool loadFromFile(
		ID3D11Device* device,
		std::string vertexShaderFilePath,
		std::string pixelShaderFilePath,
		std::vector<D3D11_INPUT_ELEMENT_DESC>& layout
	);

public:
	Shader(
		Renderer& renderer,
		std::string vertexShaderFilePath,
		std::string pixelShaderFilePath
	);
	Shader(
		Renderer& renderer, 
		std::string vertexShaderFilePath, 
		std::string pixelShaderFilePath,
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	);

	virtual ~Shader();

	virtual void update(Renderer& renderer, XMMATRIX currentWorldMatrix);

	virtual void set();
};