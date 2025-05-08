#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    //if (argc != 3) {
    //    printf("Usage: %s <downsample_rate> <input_file> \n", argv[0]);
    //    exit(1);
    //}

    int downsample_rate = atoi(argv[1]);
    //int fd1 = open(argv[2], O_RDONLY);
    
    //if (fd1 == -1) {
    //    perror("open");
    //    exit(1);
    //}

    short read_data;
    int current_bit = 0;
    char buf[200];  // 出力用バッファ

    while (1) {
        int is_read = read(0, &read_data, sizeof(short));
        if (is_read == -1) {
            perror("read");
            exit(1);
        }
        if (is_read == 0) {
            break;
        }
        if (current_bit % downsample_rate == 0) {
            if (write(1, &read_data, sizeof(read_data)) != sizeof(read_data)) {
                perror("write");
                exit(1);
            }
        }
        current_bit++;
    }

    //close(fd1);
    return 0;
}