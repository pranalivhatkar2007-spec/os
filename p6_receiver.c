
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

int main()
{
    char msg[100];
    int fd, n, i, words=0, lines=0, in=0;

    mkfifo("f1", 0666);
    mkfifo("f2", 0666);

    fd = open("f1", O_RDONLY);
    n = read(fd, msg, 99);
    close(fd);

    if(n <= 0) return 1;

    msg[n] = '\0';

    for(i=0; i<n; i++)
    {
        if(msg[i] == '\n')
            lines++;

        if(isspace((unsigned char)msg[i]))
            in=0;
        else if(!in)
        {
            words++;
            in=1;
        }
    }

    if(msg[n-1] != '\n')
        lines++;

    FILE *fp = fopen("result.txt", "w");

    fprintf(fp, "Characters = %d\n", n);
    fprintf(fp, "Words = %d\n", words);
    fprintf(fp, "Lines = %d\n", lines);

    fclose(fp);

    fp = fopen("result.txt", "r");
    fd = open("f2", O_WRONLY);

    while((n=fread(msg, 1, 99, fp)) > 0)
        write(fd, msg, n);

    fclose(fp);
    close(fd);

    return 0;
}
gcc p6_sender.c -o sender
gcc p6_receiver.c -o receiver
./receiver
./sender