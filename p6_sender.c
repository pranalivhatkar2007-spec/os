
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    char msg[100], result[200];
    int fd, n;

    printf("Enter message: ");
    fgets(msg, 100, stdin);

    fd = open("f1", O_WRONLY);
    write(fd, msg, strlen(msg));
    close(fd);

    fd = open("f2", O_RDONLY);

    printf("Result:\n");

    while((n = read(fd, result, 199)) > 0)
    {
        result[n] = '\0';
        printf("%s", result);
    }

    close(fd);
    return 0;
}
