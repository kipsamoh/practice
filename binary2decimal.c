#include <stdio.h>

unsigned int binary2decimal(const char *b) 
{
    if (b == NULL) 
    {
        return 0; // Return 0 if the string is NULL
    }

    int decimal = 0;

    for (int i = 0; b[i] != '\0'; i++)
    {
        if (b[i] == '0')
        {
            decimal = decimal * 2; // Shift left by 1 position (multiply by 2)
        } 
        else if (b[i] == '1') 
        {
            decimal = decimal * 2 + 1; // Shift left by 1 position and add 1
        } 
        else 
        {
            return 0; // Return 0 if a character in the string is not '0' or '1'
        }
    }

    return decimal;
}

int main() {
    const char *binary_num = "1101";
    unsigned int result = binary2decimal(binary_num);
    printf("The binary number %s is equivalent to decimal: %u\n", binary_num, result);
    return 0;
}
