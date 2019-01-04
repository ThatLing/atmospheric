// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "BYOND.h"

extern "C" __declspec(dllexport) char* pass_me_the_joint(int dong, char* who_knows)
{
	static char buf[10];
	*buf = 0;
	return buf;
}

void test_run()
{
	BYOND::Variables vars;
	vars.GetFunctionPointers();
	vars.GenerateStringTable();
	BYOND::Variables::ByondList* lst = vars.getListPointer(2);
	BYOND::Variables::ListElement* elems = lst->elements;
	elems++;
	MessageBoxA(NULL, std::to_string((float)elems->value).c_str(), "value of list element", NULL);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		DWORD dwThreadId;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&test_run, NULL, NULL, &dwThreadId);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

