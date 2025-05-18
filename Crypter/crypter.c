#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool XORFile(const char *input_file_path, const char *output_file_path, const char *key)
{
    /* Open input and output files */
    FILE *input_file = fopen(input_file_path, "rb");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Could not open the input file"); 
        return false;
    }

    FILE *output_file = fopen(output_file_path, "wb");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Could not open the input file"); 
        return false;
    }

    /* Seek to the end of the file to determine its size */
    fseek(input_file, 0, SEEK_END);
    const long input_file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    /* Allocate memory for the file contents (+1 for null terminator if needed) */
    char *input_buffer = malloc(input_file_size);
    if (!input_buffer) {
        fprintf(stderr, "Error: Unable to allocate memory for the input file"); 
        goto XORFILE_CLOSE;
    }

    /* Read the file into the buffer */
    size_t read_size = fread(input_buffer, 1, input_file_size, input_file);
    if (read_size != input_file_size) {
        fprintf(stderr, "Error: Failed to read complete file"); 
        free(input_buffer);
        goto XORFILE_CLOSE;
    }

    /* Apply XOR to each byte in input file */
    for (int i = 0; i < strlen(input_buffer); ++i) {
        input_buffer[i] = input_buffer[i] ^ key[i % strlen(key)];
    }

    /* Write results to output file */
    size_t written = fwrite(input_buffer, 1, input_file_size, output_file);
    if (written != input_file_size) {
        fprintf(stderr, "Error: Failed to write complete buffer");
        goto XORFILE_CLOSE;
    }
    
    /* Successfully completed XOR operation */
    return true;

    /* Unsuccessful attempt at XOR -- close files and return false */
XORFILE_CLOSE:
    fclose(input_file);
    fclose(output_file);
    return false;
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        printf("Usage: %s [exe_file] [output_file] [key]\n", argv[0]);
        return 1;
    }

    const char *input_file_path  = argv[1];
    const char *output_file_path = argv[2];
    const char *key              = argv[3];

    /* Encrypt the file */
    if (!XORFile(input_file_path, output_file_path, key)) {
        return 1;
    }

    printf("Process complete. Compile the stub and combine it with the encrypted file.\n");

    return 0;
}