#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain {

public:
	SwapChain();
	~SwapChain();

	bool present(bool vsync);

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

private:
	friend class DeviceContext;
};

