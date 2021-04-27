#include <iostream>
#include <Windows.h>
#include <engine.hpp>
#include <d3d11.h>

int main()
{
	/*load*/
	LoadLibraryA("d3d9.dll");
	LoadLibraryA("d3d10.dll");
	LoadLibraryA("d3d11.dll");

	/*intialize it*/

	engine::D3DEngine* d3dengine = new engine::D3DEngine();
	d3dengine->initialize();


	/*test it*/
	
	if (d3dengine->IsD3D9Present())
	{
		
		std::cout << "Getting D3D9!" << std::endl;
		auto result = d3dengine->GetD3D9DeviceFunc(42);

		if (result.failed)
		{
			std::cout << "Error Code -> " << result.errorCode << std::endl;
			
		}
		else
		{
			std::cout << "End Scene [ YOU NEED TO HOOK ] -> " << result.func << std::endl;
		}
	}
	
	if (d3dengine->IsD3D10Present())
	{
		std::cout << "Getting D3D10!" << std::endl;

		
		auto result = d3dengine->GetD3D10SwapchainFunction(8);

		if (result.failed)
		{
			std::cout << "Error Code -> " << result.errorCode << std::endl;
		}
		else
		{
			std::cout << "Present [ YOU NEED TO HOOK ] -> " << result.func << std::endl;
		}

		auto result_2 = d3dengine->GetD3D10DeviceFunction(0);

		if (result_2.failed)
		{
			std::cout << "Error Code -> " << result.errorCode << std::endl;
		}
		else
		{
			std::cout << "The first func of the Device Class -> " << result_2.func << std::endl;
		}

		
	}

	if (d3dengine->IsD3D11Present())
	{
		std::cout << "Getting D3D11!" << std::endl;


		auto result = d3dengine->GetD3D11SwapchainFunction(8);

		if (result.failed)
		{
			std::cout << "Error Code -> " << result.errorCode << std::endl;
		}
		else
		{
			std::cout << "Present [ YOU NEED TO HOOK ] -> " << result.func << std::endl;
		}

		auto result_2 = d3dengine->GetD3D11DeviceFunction(0);

		if (result_2.failed)
		{
			std::cout << "Error Code -> " << result.errorCode << std::endl;
		}
		else
		{
			std::cout << "The first func of the Device Class -> " << result_2.func << std::endl;
		}

		auto result_3 = d3dengine->GetD3D11ContextFunction(0);

		if (result_3.failed)
		{
			std::cout << "Error Code -> " << result_3.errorCode << std::endl;
		}
		else
		{
			std::cout << "The first func of the Context Class -> " << result_3.func << std::endl;

		}
	}

	IDXGISwapChain;

	while (true);

}
