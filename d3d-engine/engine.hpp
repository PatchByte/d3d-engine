#pragma once
#include "common.hpp"
#define SOME_RANDOM_CLASS_NAME L"iloved3d"
#define SOME_RANDOM_TITLE L"idontlikeit"

#define USE_D3D9 true
#define USE_D3D10 true

#if USE_D3D9 true

#include <d3d9.h>

#endif

#if USE_D3D10 true

#include <d3d10_1.h>

#endif
/*
	Error Codes:
	101 ->  failed to create window

	901 -> Direct3DCreate9 Function not found!
	902 -> Direct 9 Sdk couldnt initialize!
	903 -> Couldnt create the device!

	1001 -> D3D10CreateDeviceAndSwapChain Function not found!

*/

namespace engine
{


	struct D3D9Result
	{
		bool failed = false;
		int errorCode = 0;
	};

	struct D3D9EndSceneResult
	{
		bool failed = false;
		int errorCode = 0;
		PVOID endSceneFunc = 0;
	};

	struct D3D10Result
	{
		bool failed = false;
		int errorCode = 0;
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

			this->presentD3DVersions[9] = is9Present;
			this->presentD3DVersions[10] = is10present;

		}
#if USE_D3D9 true
		bool IsD3D9Present()
		{
			return this->presentD3DVersions[9];
		}

		D3D9Result GetD3d9DeviceTable(int VTableSize, void** ToCopyIn)
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
			
			/*newest version 32*/

			IDirect3D9* sdk = _Direct3DCreate9(D3D_SDK_VERSION);

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
			params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

			IDirect3DDevice9* theDevice = 0;
			auto x = sdk->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->myWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &theDevice);

			if (FAILED(x))
			{
				result.failed = true;
				result.errorCode = 903;

				return result;
			}

			memcpy(ToCopyIn, *reinterpret_cast<void***>(theDevice), VTableSize);


			result.failed = false;
			result.errorCode = 0;

			theDevice->Release();
			sdk->Release();

			return result;

		}
		D3D9EndSceneResult GetD3D9EndScene()
		{
			void* tableFunctions[119] = {};
			auto firstResult = this->GetD3d9DeviceTable(sizeof(tableFunctions), tableFunctions);

			return { firstResult.failed, firstResult.errorCode, tableFunctions[42] };
		}
#endif

#if USE_D3D10
		bool IsD3D10Present()
		{
			return this->presentD3DVersions[10];
		}
#endif
	};
	

}