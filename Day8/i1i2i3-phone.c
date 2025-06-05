#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define N 4096

void server(char *port){
    char data[N];
    int ss = socket(PF_INET, SOCK_STREAM, 0);
    if(ss == -1){
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
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
    fprintf(fp,"");

    while(1){
        int is_recv = recv(s, data, N, 0);
        if (is_recv == -1) {
            perror("read");
            exit(1);
        }
        if (is_recv == 0) {
            break;
        }
        fwrite(data, 1, is_recv, stdout);
        fflush(stdout);

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

void client(char *server_ip, char *port){
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if(s == -1){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    if(inet_aton(server_ip, &addr.sin_addr) == 0){
        printf("Invalid IP address\n");
        exit(1);
    }
    addr.sin_port = htons(atoi(port));
    if(connect(s, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        perror("connect");
        exit(1);
    }

    FILE *fp;
    char *cmdline = "rec -t raw -b 16 -c 1 -e s -r 44100 -";
    if ((fp=popen(cmdline, "r")) == NULL) {
        perror ("popen failed");
        exit(1);
    }

    char data[N];

    while (1) {
        int n = fread(data, 1, N, fp);
        if(n == -1){
            perror("fread");
            break;
        }
        if(n == 0){
            break; // EOF
        }
        if(send(s, data, n, 0) == -1){
            perror("send");
            break;
        }

        int is_recv = recv(s, data, N, 0);
        if (is_recv == -1) {
            perror("recv");
            break;
        }
        if (is_recv == 0) {
            break; // Connection closed
        }
        fwrite(data, 1, is_recv, stdout);
        fflush(stdout);
    }
    close(s);
    pclose(fp);
}

int main(int argc, char *argv[]){
    if(argc == 2){
        server(argv[1]);
    }else if(argc == 3){
        client(argv[1], argv[2]);
    }else{
        printf("Usage: %s <server_ip> <port>\nor\n", argv[0]);
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    return 0;
}