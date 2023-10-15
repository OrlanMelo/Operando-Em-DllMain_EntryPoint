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
        MessageBox(0, L"Sucesso na operação de injeção..\n", L"Teste", MB_OK | MB_ICONINFORMATION);
        break;

    case DLL_THREAD_ATTACH:
        MessageBox(0, L"Sucesso na operação de injeção..\n", L"Teste", MB_OK | MB_ICONINFORMATION);
        break;

    case DLL_THREAD_DETACH:

        //Finalize todos os identificadores e memórias pendentes quando não for mais necessário.

        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break;
        }

        //Finalize todos os identificadores e memórias pendentes.

        break;
    }
    return TRUE;//Sucesso na operação..
}