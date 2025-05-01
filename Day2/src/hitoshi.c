#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        perror("open");
        exit(1);
    }
    unsigned char data[6]  = {228, 186, 186, 229, 191, 151};

    for(int i = 0; i < 6; i++){
        int bugger = write(fd, &data[i], 1);
        if (bugger == -1){
            perror("write");
            exit(1);
        }
    }
    close(fd);
    return 0;
}