#pragma once

#include <D3D11.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dxgi.lib")

#include "Common.h"
#include "Win32.h"

namespace Device
{
	class DirectX
	{
	private:
		ID3D11Device				*_device;
		IDXGISwapChain				*_swapChain;
		ID3D11DeviceContext			*_immediateContext;

		ID3D11Texture2D				*_depthStencil;
		ID3D11DepthStencilView		*_depthStencilView;
		ID3D11ShaderResourceView	*_depthStencilSRV;

		ID3D11RenderTargetView		*_renderTargetView;

		D3D_FEATURE_LEVEL			_featureLevel;
		D3D_DRIVER_TYPE				_driverType;

		ID3D11RasterizerState		*_disableCulling;
		ID3D11BlendState			*_opaqueBlend;
		ID3D11BlendState			*_alphaToCoverageBlend;

		ID3D11DepthStencilState		*_depthLessEqual;
		ID3D11DepthStencilState		*_depthEqualAndDisableDepthWrite;

	public:
		DirectX();
		~DirectX(void);

	private:
		bool CreateRenderTargetView();
		bool CreateDepthStencilRenderTarget(const Math::Size<int>& winSize, IDXGISwapChain* swapChain);
		bool CreateDeviceAndSwapChain(const Win32* win, const DXGI_SAMPLE_DESC* multiSampler = nullptr);
		bool CreateViewport(const Math::Size<int>& winSize);
		bool CreateSwapChain(const Win32* win);
	
		void CheckAbleMultiSampler(std::vector<DXGI_SAMPLE_DESC>& outDescs, DXGI_FORMAT format);		

	public:
		bool InitDevice(const Win32* win);
		unsigned int CalcFormatSize(DXGI_FORMAT format) const;

	public:
		GET_ACCESSOR(Device, ID3D11Device*, _device);
		GET_ACCESSOR(SwapChain, IDXGISwapChain*, _swapChain);
		GET_ACCESSOR(Context, ID3D11DeviceContext*, _immediateContext);
		//GET_ACCESSOR(Adapter, IDXGIAdapter*, _adapter);

		GET_ACCESSOR(DetpthStencilTexture, ID3D11Texture2D*, _depthStencil);
		GET_ACCESSOR(DepthStencilView, ID3D11DepthStencilView*, _depthStencilView);

		GET_ACCESSOR(RenderTarget, ID3D11RenderTargetView*, _renderTargetView);
	};
}