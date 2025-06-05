#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define N 1024

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    unsigned char data[N];
    int ss = socket(PF_INET, SOCK_STREAM, 0);
    if(ss == -1){
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(ss, (struct sockaddr *)&addr, sizeof(addr));

    listen(ss, 10);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int s = accept(ss, (struct sockaddr *)&client_addr, &len);
    if(s == -1){
        perror("accept");
        exit(1);
    }

    FILE *fp;
    char *cmdline = "rec -t raw -b 16 -c 1 -e s -r 44100 -";
    if ((fp=popen(cmdline, "r")) == NULL) {
        perror ("popen failed");
        exit(1);
    }
    //fprintf(fp,"");

    while(1){

        int n = fread(data, 1, N, fp);
        if(n == -1){
            perror("read");
            exit(1);
        }
        if(send(s, data, n, 0) == -1){
            perror("send");
        }
        if(n == 0){
            break;
        }
        
    }
    close(s);
    close(ss);
    pclose(fp);

}