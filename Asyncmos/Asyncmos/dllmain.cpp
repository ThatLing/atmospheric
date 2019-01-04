// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "BYOND.h"
#define FATAL(x) MessageBoxA(NULL, x, "Fatal Error", NULL); exit(-1);

void test_run()
{
	BYOND::Variables vars;
	if(!vars.GetFunctionPointers())
	{
		FATAL("Failed to get all function pointers!")
	}
	vars.GenerateStringTable();
	BYOND::List* lst = vars.GetListFromId(2);
	for(DWORD i = 0; i < lst->Length(); i++)
	{
		BYOND::Object* elem = lst->At(i);
		if(elem->Type() == BYOND::VariableType::Number)
		{
			MessageBoxA(NULL, std::to_string(elem->AsNumber()).c_str(), "value of number element", NULL);
		}
		else if(elem->Type() == BYOND::VariableType::String)
		{
			MessageBoxA(NULL, elem->AsString(vars).c_str(), "value of string element", NULL);
		}
	}
	lst->Append(BYOND::VariableType::Number, (float)13);
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

