//1.18.0.2
#include "pch.h"

void mod_init();
void mod_exit();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
 		mod_init();
		break;
	case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		mod_exit();
        break;
    }
    return TRUE;
}

