#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define N 100

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "使用方法: %s 入力ファイル 出力ファイル\n", argv[0]);
        exit(1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    unsigned char read_data[N];
    int current_bit = 0;
    char buf[32];  // 出力用バッファ

    while (1) {
        int is_read = read(fd1, read_data, N);
        if (is_read == -1) {
            perror("read");
            exit(1);
        }
        if (is_read == 0) {
            break;
        }

        for (int i = 0; i < is_read; i++) {
            int len = snprintf(buf, sizeof(buf), "%d %d\n", current_bit, read_data[i]);
            if (write(fd2, buf, len) != len) {
                perror("write");
                exit(1);
            }
            current_bit++;
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}