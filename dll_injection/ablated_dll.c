#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dReason_for_call, LPVOID lpReserved)
{
    switch (dReason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
