#include "Renderer.h"
#include "../Dev/Log.h"
#include <wrl\client.h>


bool Renderer::createDevice(RenderWindow& window, bool vsyncEnabled) {

	HRESULT result;

	// Swap chain desc
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1; // One back buffer, (and one front buffer)
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	
	swapChainDesc.BufferDesc.Width = window.getWidth(); // window width
	swapChainDesc.BufferDesc.Height = window.getHeight(); // window hight
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.OutputWindow = window.GetHWND(); //hwnd
	swapChainDesc.SampleDesc.Count = 1; // Number of samples for AA
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// Set feature level of DirectX 11
	D3D_FEATURE_LEVEL featureLevel;
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the swap chain, device and device context
	result = D3D11CreateDeviceAndSwapChain(
		nullptr,  //IDXGI Adapter
		D3D_DRIVER_TYPE_HARDWARE,  
		nullptr,  //FOR SOFTWARE DRIVER TYPE
		0, //FLAGS FOR RUNTIME LAYERS
		nullptr,//&featureLevel,  //FEATURE LEVELS ARRAY
		0,//1, //# OF FEATURE LEVELS IN ARRAY
		D3D11_SDK_VERSION, 
		&swapChainDesc, //SWAPCHAIN DESCRIPTION
		&this->_swapChain,  //SWAPCHAIN ADDRESS
		&this->_device, //DEVICE ADDRESS
		nullptr, //SUPPORTED FEATURE LEVEL
		&this->_deviceContext //DEVICE CONTEXT ADDRESS
	);

	// Check for errors
	if (FAILED(result)) {
		Log::error("Failed to create device and swapchain");
		return false;
	}

	return true;
}

bool Renderer::createRenderTarget() {
	HRESULT hr;
	// Get back buffer from swap chain
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = this->_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr))	{
		Log::error("GetBuffer failed");
		return false;
	}

	hr = this->_device->CreateRenderTargetView(	backBuffer.Get(), nullptr, &this->_renderTargetView );

	if (FAILED(hr)) {
		Log::error("Failed to create render target view");
		return false;
	}

	// Get desc before releasing
	backBuffer->GetDesc(&_backBufferDesc);

	return true;
}

bool Renderer::createDepthStencilBuffers(RenderWindow& window)
{
	HRESULT result;

	// Create a description of the depth and stencil buffers
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc = { 0 };
	depthStencilBufferDesc.Width = window.getWidth();
	depthStencilBufferDesc.Height = window.getHeight();
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.MiscFlags = 0;



	// Create a texture for the depth and stencil buffers using the filled out
	// description
	result = _device->CreateTexture2D(&depthStencilBufferDesc, NULL, &this->_depthStencilBuffer);

	if (FAILED(result))	{
		Log::error("Could not create depth/stencil texture.");
		return false;
	}

	// Create a description of the depth and stencil states
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // Write on/off
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xFF; // Portion for reading
	depthStencilDesc.StencilWriteMask = 0xFF; // Portion for writing

	// Stencil operations if pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//depthStencilDesc.DepthFunc == D3D11_COMPARISON_LESS_EQUAL;
	//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	// Create a depth stencil state
	result = _device->CreateDepthStencilState(&depthStencilDesc, &this->_depthStencilState);

	if (FAILED(result))	{
		Log::error("Could not create depth stencil state.");
		return false;
	}

	// Set the depth stencil state
	_deviceContext->OMSetDepthStencilState(this->_depthStencilState, 1);

	// Set up the depth stencil views desc
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;


	// Create the depth stencil view
	result = _device->CreateDepthStencilView(this->_depthStencilBuffer, &depthStencilViewDesc, &this->_depthStencilView);

	if (FAILED(result))	{
		Log::error("Failed creating depth stencil view.");
		return false;
	}

	// Bind the render target view and depth stencil view to the 
	// output merger pipeline
	this->_deviceContext->OMSetRenderTargets(1, &this->_renderTargetView, _depthStencilView);

	// Setup the raster description which will determine how and what
	// polygons will be drawn
	this->_rasterDesc.AntialiasedLineEnable = false;
	this->_rasterDesc.CullMode = D3D11_CULL_BACK; //D3D11_CULL_NONE;
	this->_rasterDesc.DepthBias = 0;
	this->_rasterDesc.DepthBiasClamp = 0.0f;
	this->_rasterDesc.DepthClipEnable = true;
	this->_rasterDesc.FillMode = D3D11_FILL_SOLID;
	this->_rasterDesc.FrontCounterClockwise = false;
	this->_rasterDesc.MultisampleEnable = false;
	this->_rasterDesc.ScissorEnable = false;
	this->_rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out
	result = _device->CreateRasterizerState(&_rasterDesc, &this->_rasterState);

	if (FAILED(result))	{
		Log::error("Could not create rasterizer state.");
		return false;
	}

	// Set rasteriser state
	_deviceContext->RSSetState(this->_rasterState);

	// Set viewport
	CD3D11_VIEWPORT viewport = CD3D11_VIEWPORT(	0.0f, 0.0f,	(float)_backBufferDesc.Width, (float)_backBufferDesc.Height	);

	this->_deviceContext->RSSetViewports(1, &viewport);

	return true;
}

Renderer::Renderer(RenderWindow& window): _swapChain(nullptr), _device(nullptr), _deviceContext(nullptr), _renderTargetView(nullptr), _camera(nullptr) {
	this->_projectionMatrix = XMMatrixIdentity();
	this->_viewMatrix = XMMatrixIdentity();

	this->createDevice(window, vsyncEnabled);
	this->createRenderTarget();
	this->createDepthStencilBuffers(window);
}

Renderer::~Renderer() {
	// Set to windowed mode or the swap chain will throw an exception
	if (this->_swapChain) {
		this->_swapChain->SetFullscreenState(false, NULL);
	}

	S_RELEASE(this->_rasterState);
	S_RELEASE(this->_depthStencilView);
	S_RELEASE(this->_depthStencilState);
	S_RELEASE(this->_depthStencilBuffer);
	S_RELEASE(this->_renderTargetView);
	S_RELEASE(this->_deviceContext);
	S_RELEASE(this->_device);
	S_RELEASE(this->_swapChain);
}


void Renderer::beginFrame() {
	// Update view matrix
	if (this->_camera != nullptr) {
		this->_viewMatrix = this->_camera->getViewMatrix();
	}
}

void Renderer::endFrame() {
	// Swap buffers
	this->_swapChain->Present(vsyncEnabled, 0);
}

void Renderer::clear() {

	float backgroundColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	this->_deviceContext->ClearRenderTargetView(this->_renderTargetView, backgroundColor);
	this->_deviceContext->ClearDepthStencilView(this->_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//this->_swapChain->Present(0, NULL);
}

ID3D11Device* Renderer::getDevice() const {
	return this->_device;
}

ID3D11DeviceContext* Renderer::getDeviceContext() const {
	return this->_deviceContext;
}

void Renderer::setCamera(Camera& cam) {
	this->_camera = &cam;
	this->_projectionMatrix = this->_camera->getProjectionMatrix();
	this->_viewMatrix = this->_camera->getViewMatrix();
}

XMMATRIX Renderer::getProjectionMatrix() {
	return this->_projectionMatrix;
}

XMMATRIX Renderer::getViewMatrix() {
	return this->_viewMatrix;
}

XMFLOAT3 Renderer::getCameraPosition() const {
	return this->_camera->getPosition();
}
