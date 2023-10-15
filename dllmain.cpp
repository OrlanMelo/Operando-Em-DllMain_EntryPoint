// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "pch.h"
#include <Windows.h>
#include <WinUser.h>
#pragma comment(lib,"user32.lib")

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(0, L"Sucesso na opera��o de inje��o..\n", L"Teste", MB_OK | MB_ICONINFORMATION);
        break;

    case DLL_THREAD_ATTACH:
        MessageBox(0, L"Sucesso na opera��o de inje��o..\n", L"Teste", MB_OK | MB_ICONINFORMATION);
        break;

    case DLL_THREAD_DETACH:

        //Finalize todos os identificadores e mem�rias pendentes quando n�o for mais necess�rio.

        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break;
        }

        //Finalize todos os identificadores e mem�rias pendentes.

        break;
    }
    return TRUE;//Sucesso na opera��o..
}