#pragma once
#include "common.hpp"
#define SOME_RANDOM_CLASS_NAME L"iloved3d"
#define SOME_RANDOM_TITLE L"idontlikeit"

#define USE_D3D9 true
#define USE_D3D10 true
#define USE_D3D11 true

#if USE_D3D9 true

#include <d3d9.h>

#endif

#if USE_D3D10 true

#include <d3d10_1.h>

#endif

#if USE_D3D11 true

#include <d3d11.h>

#endif
/*
	Error Codes:
	101 ->  failed to create window

	901 -> Direct3DCreate9 Function not found!
	902 -> Direct 9 Sdk couldnt initialize!
	903 -> Couldnt create the device!

	1001 -> D3D10CreateDeviceAndSwapChain Function not found!
	1002 -> Failed to create the Device and the Swapchain!

	1101 -> D3D11CreateDeviceAndSwapChain Function not found!
	1102 -> Failed to create the Device and the Swapchain!

*/

namespace engine
{


	struct D3D9Result
	{
		bool failed = false;
		int errorCode = 0;
	};

	struct D3D9GetFunctionResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID func = 0;
	};

	struct D3D10Result
	{
		bool failed = false;
		int errorCode = 0;
	};

	struct D3D10GetSwapchainFunctionResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID func = 0;
	};

	struct D3D10GetDeviceFunctionResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID func = 0;
	};

	struct D3D11Result
	{
		bool failed = 0;
		int errorCode = 0;
	};

	struct D3D11GetSwapchainFunctionResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID func = 0;
	};

	struct D3D11GetDeviceFunctionResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID func = 0;
	};

	struct D3D11GetContextFunctionResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID func = 0;
	};

	class D3DEngine
	{
	private:
		std::map<int, bool> presentD3DVersions;
		HWND myWindow = 0;
	public:
		D3DEngine() = default;
		~D3DEngine() = default;

		void initialize()
		{
			this->checkD3DVersions();
			myWindow = this->CreateMyWindow();
		}
	private:
		static LRESULT dummyWndProc(HWND w, UINT a, WPARAM b, LPARAM c)
		{
			return DefWindowProc(w, a, b, c);
		};

		HWND CreateMyWindow()
		{
			const wchar_t CLASS_NAME[] = SOME_RANDOM_CLASS_NAME;

			WNDCLASS wc = { };

			wc.lpfnWndProc = dummyWndProc;
			wc.hInstance = GetModuleHandleA(0);
			wc.lpszClassName = CLASS_NAME;

			RegisterClass(&wc);

			HWND hwnd = CreateWindowEx(
				0,
				CLASS_NAME,
				SOME_RANDOM_TITLE,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL,
				NULL, 
				GetModuleHandleA(0),
				NULL
			);

			return hwnd;
		}
	public:
		void checkD3DVersions()
		{

			bool is9Present = GetModuleHandleA("d3d9.dll") == 0 ? false : true;
			bool is10present = GetModuleHandleA("d3d10.dll") == 0 ? false : true;
			bool is11present = GetModuleHandleA("d3d11.dll") == 0 ? false : true;

			this->presentD3DVersions[9] = is9Present;
			this->presentD3DVersions[10] = is10present;
			this->presentD3DVersions[11] = is11present;

		}
#if USE_D3D9 true
		bool IsD3D9Present()
		{
			return this->presentD3DVersions[9];
		}
	private:
		D3D9Result GetD3d9DeviceTable(void** device_table, int device_size)
		{
			D3D9Result result{};

			using createSdkDef = PVOID(*)(UINT sdkVer);

			HMODULE lib = GetModuleHandleA("d3d9.dll");
			decltype(&Direct3DCreate9) _Direct3DCreate9 = (decltype(&Direct3DCreate9))GetProcAddress(lib, "Direct3DCreate9");

			if (!_Direct3DCreate9)
			{
				result.failed = true;
				result.errorCode = 901;

				return result;
			}

			IDirect3D9* sdk = _Direct3DCreate9(32);

			if (!this->myWindow)
			{
				result.failed = true;
				result.errorCode = 101;

				return result;
			}

			if (!sdk)
			{
				result.failed = true;
				result.errorCode = 902;

				return result;
			}

			D3DPRESENT_PARAMETERS params;
			ZeroMemory(&params, sizeof(params));

			params.Windowed = true;
			params.SwapEffect = D3DSWAPEFFECT_DISCARD;
			params.BackBufferFormat = D3DFMT_UNKNOWN;
			params.EnableAutoDepthStencil = true;
			params.AutoDepthStencilFormat = D3DFMT_D16;
			params.PresentationInterval = 1L;

			IDirect3DDevice9* theDevice = 0;
			auto x = sdk->CreateDevice(0, D3DDEVTYPE_HAL, this->myWindow, 0x40L, &params, &theDevice);

			if (FAILED(x))
			{
				result.failed = true;
				result.errorCode = 903;

				return result;
			}

			memcpy(device_table, *((void***)(theDevice)), device_size);


			result.failed = false;
			result.errorCode = 0;

			theDevice->Release();
			sdk->Release();

			return result;

		}
	public:
		D3D9GetFunctionResult GetD3D9DeviceFunc(int index)
		{
			void* tableFunctions[118] = {};

			auto firstResult = this->GetD3d9DeviceTable(tableFunctions, sizeof(tableFunctions));

			return { firstResult.failed, firstResult.errorCode, tableFunctions[index] };
		}
#endif

#if USE_D3D10
		bool IsD3D10Present()
		{
			return this->presentD3DVersions[10];
		}
	private:

		D3D10Result GetD3D10SwapchainAndDevice(void** swapchain, void** device, int swapchain_size, int device_size)
		{
			D3D10Result result{};

			HMODULE d3d9Mod = GetModuleHandleA("d3d10.dll");


			if (!d3d9Mod)
			{
				result.failed = true;
				result.errorCode = 1001;
				return result;
			}

			decltype(&D3D10CreateDeviceAndSwapChain) _D3D10CreateDeviceAndSwapChain = (decltype(&D3D10CreateDeviceAndSwapChain))(GetProcAddress(d3d9Mod, "D3D10CreateDeviceAndSwapChain"));

			if (!_D3D10CreateDeviceAndSwapChain)
			{
				result.failed = true;
				result.errorCode = 1001;
				return result;
			}

			DXGI_SWAP_CHAIN_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.BufferCount = 2;
			desc.BufferDesc.Width = 0;
			desc.BufferDesc.Height = 0;
			desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.BufferDesc.RefreshRate.Numerator = 60;
			desc.BufferDesc.RefreshRate.Denominator = 1;
			desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			desc.BufferUsage = 0x00000020UL;
			desc.OutputWindow = myWindow;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Windowed = true;
			desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			IDXGISwapChain* endSwapchain = 0;
			ID3D10Device* endDevice = 0;

			if (FAILED(_D3D10CreateDeviceAndSwapChain(0, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &desc, &endSwapchain, &endDevice)))
			{
				result.failed = true;
				result.errorCode = 1002;
				return result;
			}

			if (swapchain != 0)
			{
				memcpy(swapchain, *((void***)endSwapchain), swapchain_size);
			}
			if (device != 0)
			{
				memcpy(device, *((void***)endDevice), device_size);
			}
			

			endDevice->Release();
			endSwapchain->Release();

			return result;
		}
	public:
		D3D10GetSwapchainFunctionResult GetD3D10SwapchainFunction(int index)
		{
			D3D10GetSwapchainFunctionResult result{ };

			void* swapchainTable[18] = {};

			auto beforeResult = GetD3D10SwapchainAndDevice(swapchainTable, 0, sizeof(swapchainTable), 0);

			result.failed = beforeResult.failed;
			result.errorCode = beforeResult.errorCode;
			result.func = swapchainTable[index];


			return result;
		}

		D3D10GetDeviceFunctionResult GetD3D10DeviceFunction(int index)
		{
			D3D10GetDeviceFunctionResult result{ };

			void* deviceTable[97] = {};

			auto beforeResult = GetD3D10SwapchainAndDevice(deviceTable, 0, sizeof(deviceTable), 0);

			result.failed = beforeResult.failed;
			result.errorCode = beforeResult.errorCode;
			result.func = deviceTable[index];


			return result;
		}
		
#endif

#if USE_D3D11 true
	public:
		bool IsD3D11Present()
		{
			return this->presentD3DVersions[11];
		}
	private:
		D3D11Result GetD3D11SwapchainAndDevice(void** swapchain, void** device,void* context, int swapchain_size, int device_size, int context_size)
		{
			D3D11Result result;

			HMODULE d3d11 = GetModuleHandleA("d3d11.dll");
			
			if (!d3d11)
			{
				result.failed = true;
				result.errorCode = 1101;
				
				return result;
			}

			decltype(&D3D11CreateDeviceAndSwapChain) _D3D11CreateDeviceAndSwapChain = (decltype(&D3D11CreateDeviceAndSwapChain))(GetProcAddress(d3d11,"D3D11CreateDeviceAndSwapChain"));

			if (!_D3D11CreateDeviceAndSwapChain)
			{
				result.failed = true;
				result.errorCode = 1101;

				return result;
			}

			DXGI_SWAP_CHAIN_DESC desc;
			ZeroMemory(&desc, sizeof(desc));

			desc.BufferCount = 2;
			desc.BufferDesc.Width = 0;
			desc.BufferDesc.Height = 0;
			desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.BufferDesc.RefreshRate.Numerator = 60;
			desc.BufferDesc.RefreshRate.Denominator = 1;
			desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			desc.BufferUsage = 0x20L;
			desc.OutputWindow = myWindow;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Windowed = TRUE;
			desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			D3D_FEATURE_LEVEL featureLevel;
			const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

			IDXGISwapChain *endSwapchain = 0;
			ID3D11Device* endDevice = 0;
			ID3D11DeviceContext* endContext = 0;

			if (FAILED(_D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, featureLevelArray, 2, D3D11_SDK_VERSION, &desc, &endSwapchain, &endDevice, &featureLevel, &endContext)))
			{

				result.failed = true;
				result.errorCode = 1102;

				return result;
			}

			if (context != 0)
			{

				memcpy(context, *(void***)(endContext), context_size);

			}

			if (device != 0)
			{
				memcpy(device, *(void***)(endDevice), device_size);
			}

			if (swapchain != 0)
			{
				memcpy(swapchain, *(void***)(endSwapchain), swapchain_size);
			}

			result.failed = false;
			result.errorCode = 0;

			endContext->Release();
			endDevice->Release();
			endSwapchain->Release();

			return result;
		}
	public:
		D3D11GetSwapchainFunctionResult GetD3D11SwapchainFunction(int index)
		{
			D3D11GetSwapchainFunctionResult result{ };

			void* swapchainTable[18] = {};

			auto beforeResult = GetD3D11SwapchainAndDevice(swapchainTable, 0, 0, sizeof(swapchainTable), 0, 0);

			result.failed = beforeResult.failed;
			result.errorCode = beforeResult.errorCode;
			result.func = swapchainTable[index];


			return result;
		}

		D3D11GetDeviceFunctionResult GetD3D11DeviceFunction(int index)
		{
			D3D11GetDeviceFunctionResult result{ };

			void* deviceTable[43] = {};

			auto beforeResult = GetD3D11SwapchainAndDevice(0, deviceTable, 0, 0, sizeof(deviceTable), 0);

			result.failed = beforeResult.failed;
			result.errorCode = beforeResult.errorCode;
			result.func = deviceTable[index];


			return result;
		}

		D3D11GetContextFunctionResult GetD3D11ContextFunction(int index)
		{
			D3D11GetContextFunctionResult result{ };

			void* contextTable[115] = {};

			auto beforeResult = GetD3D11SwapchainAndDevice(0, 0, contextTable, 0, 0, sizeof(contextTable));

			result.failed = beforeResult.failed;
			result.errorCode = beforeResult.errorCode;
			result.func = contextTable[index];


			return result;
		}


#endif
	};
	

}