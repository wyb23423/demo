#include <stdio.h>
#include <windows.h>

int main()
{
    printf("Celsius2Fahr\n");
    for (float celsius = 0; celsius <= 300; celsius += 20)
    {
        printf("%3.0f %6.1f\n", celsius, celsius * 9.0 / 5.0 - 32.0);
    }

    system("pause");
    return 0;
}