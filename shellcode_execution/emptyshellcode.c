#include <windows.h>
int main() {
    unsigned char shellcode[]="\x90";



    void *exec = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcode, sizeof(shellcode));
    ((void(*)())exec)(); // Execute shellcode
    return 0;

}
