# D3D Engine by PatchByte

I was bored so i tried to make a d3d "engine" to get the specific functions to hook

___

## How to initialize!
```c++
#include <engine.hpp>
#include <iostream>
#include <Windows.hpp>

int main()
{
    /* new class */
    engine::D3DEngine* d3dengine = new engine::D3DEngine();
    /* check for aviable d3d modules */
    d3dengine->initialize();

    return 0;
}
```
___
## How to get a D3D9 Function (Example: EndScene)
So first of you need the specific function index it starts at 0! For EndScene it would be 42! And then you can get the function pointer!
```c++
int main()
{
    /* new class */
    engine::D3DEngine* d3dengine = new engine::D3DEngine();
    /* check for aviable d3d modules */
    d3dengine->initialize();

    /*check if d3d9 is aviable!*/
    if(d3dengine->IsD3D9Present())
    {
        auto result = d3dengine->GetD3D9DeviceFunc(42);

        if(result.failed)
        {
            /*failed code here*/
            result.errorCode;
        }
        else
        {
            PVOID endScenePointer = result.func;
            /*and now you could hook it with minhook or something*/
            /*MH_CreateHook(endScenePointer, &YourDetour, &TheOriginal);*/
        }
    }
    else
    {
        std::cout << "Error D3D9 (module) missing!" << std::endl;
    }

    return 0;
}
```
___
## How to get a D3D10 Function
```c++
int main()
{
    /* new class */
    engine::D3DEngine* d3dengine = new engine::D3DEngine();
    /* check for aviable d3d modules */
    d3dengine->initialize();

    /*check if d3d9 is aviable!*/
    if(d3dengine->IsD3D10Present())
    {
        auto result = d3dengine->GetD3D10SwapchainFunction(8);

        if(result.failed)
        {
            /*failed code here*/
            result.errorCode;
        }
        else
        {
            PVOID presentPointer = result.func;
            /*and now you could hook it with minhook or something*/
            /*MH_CreateHook(presentPointer, &YourDetour, &TheOriginal);*/
        }
        /*
        There is also:
        d3dengine->GetD3D10DeviceFunction(funcIndex);
        */
    }
    else
    {
        std::cout << "Error D3D10 (module) missing!" << std::endl;
    }

    return 0;
}
```
___
## How to get a D3D11 Function
```c++
int main()
{
    /* new class */
    engine::D3DEngine* d3dengine = new engine::D3DEngine();
    /* check for aviable d3d modules */
    d3dengine->initialize();

    /*check if d3d9 is aviable!*/
    if(d3dengine->IsD3D11Present())
    {
        auto result = d3dengine->GetD3D11SwapchainFunction(8);

        if(result.failed)
        {
            /*failed code here*/
            result.errorCode;
        }
        else
        {
            PVOID presentPointer = result.func;
            /*and now you could hook it with minhook or something*/
            /*MH_CreateHook(presentPointer, &YourDetour, &TheOriginal);*/
        }
        /*
        There is also:
        d3dengine->GetD3D11DeviceFunction(funcIndex);
        d3dengine->GetD3D11ContextFunction(funcIndex);
        */
    }
    else
    {
        std::cout << "Error D3D11 (module) missing!" << std::endl;
    }

    return 0;
}
```