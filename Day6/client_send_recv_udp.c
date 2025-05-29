#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

#define N 1024

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }
    int s = socket(PF_INET, SOCK_DGRAM, 0);
    if(s == -1){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    if(inet_aton(argv[1], &addr.sin_addr) == 0){
        printf("Invalid IP address\n");
        exit(1);
    }
    addr.sin_port = htons(atoi(argv[2]));


    socklen_t addr_len = sizeof(addr);

    
    while (1) {
        char data_send[N];
        int n = read(0, data_send, N);
        if(n == -1){
            perror("recvfrom");
            exit(1);
        }
        if(n==0){
            shutdown(s, SHUT_WR);
            break;
        }
        if(sendto(s, data_send, n, 0, (struct sockaddr *)&addr, addr_len) == -1){
            perror("sendto");
            exit(1);
        }
    }

    char data[N];

    while (1) {
        int is_recv = recvfrom(s, data, N, 0, (struct sockaddr *)&addr, &addr_len);
        if (is_recv == -1) {
            perror("recvfrom");
            exit(1);
        }
        if (is_recv == 0) {
            break;
        }
        for (int i = 0; i < is_recv; i++) {
            printf("%c",data[i]);
        }
    }
    close(s);
    return 0;
}