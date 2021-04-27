// Test.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <Windows.h>
#include <engine.hpp>
#include <d3d11.h>

int main()
{
	/*load*/
	LoadLibraryA("d3d9.dll");
	LoadLibraryA("d3d10.dll");

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
			std::cout << "End Scene -> " << result.func << std::endl;
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
			std::cout << "Present -> " << result.func << std::endl;
		}

		
	}

	while (true);
}
