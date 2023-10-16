#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"onecore.lib")

using namespace std;

class cFuncoes
{
private:

	HANDLE Identificador;

	HANDLE Snapshot;

public:

	bool Processo(const char* Nome)
	{
		bool bRetorno = false;

		Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (Snapshot == INVALID_HANDLE_VALUE)
		{
			cout << "Identificador inválido para o processo selecionado..\n";
		}
		else
		{
			PROCESSENTRY32 Entrada;
			Entrada.dwSize = sizeof(PROCESSENTRY32);

			Process32First(Snapshot, &Entrada);
			do
			{
				string sNome = Entrada.szExeFile;
				if (sNome == Nome == true)
				{
					Identificador = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE, 0, Entrada.th32ProcessID);
					if (Identificador == NULL)
					{
						cout << "Não foi possível prosseguir com a operação..\n";
					}
					else
					{
						bRetorno = true;
					}
				}

			} while (Process32Next(Snapshot, &Entrada));

			CloseHandle(Snapshot);
		}

		return bRetorno;
	}

	/*
	* Para funcionar, o arquivo .dll ou em outro formato precisa ter um ponto de entrada DllMain.
	*/
	void InjetarArquivo(const char* Arquivo)
	{
		LPVOID Alocar = VirtualAllocEx(Identificador, 0, strlen(Arquivo), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		WriteProcessMemory(Identificador, Alocar, Arquivo, strlen(Arquivo), 0);

		HANDLE Thread = CreateRemoteThread(Identificador, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, Alocar, 0, 0);
		WaitForSingleObject(Thread, INFINITE);

		VirtualFreeEx(Identificador, Alocar, strlen(Arquivo), MEM_RELEASE);
		CloseHandle(Thread);
		CloseHandle(Identificador);
	}

}Funcoes;

int main()
{

	cout << "O assistente está executando operações de memória entre arquivos...\n";

	/*
	* Isto não irá funcionar com processos que possuem proteção anti-injection ou outro mecânismo relacionado.
	* Alguns softwares anti-malwares podem interromper o processo ou detectar arquivo potencialmente indesejado.
	* 
	* Um arquivo .dll que possui ponto de entrada e um Thread na função, irá ser finalizado apenas se o respectivo processo for fechado.
	*/
	if (Funcoes.Processo("ConsoleApplication1.exe") == true)
	{
		Funcoes.InjetarArquivo("Dll1.dll");
	}

	system("pause");
}
