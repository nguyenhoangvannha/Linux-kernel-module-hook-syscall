#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEVICE_NODE "/dev/random_chardrv"

int main(void)
{

    int file, random;

    file = open(DEVICE_NODE, O_RDONLY);

    if (file < 0)
    {
        printf("Cannot open file device\n");
        return 1;
    }

    if (read(file, &random, sizeof(random)) < 0)
    {
        printf("Cannot read from file device\n");
        return 1;
    }
    printf("Random number: %d\nRead from %s\n", random, DEVICE_NODE);

    return 0;
}
