#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    if (argc != 4){
        printf("Usage: %s volume frequency duration\n", argv[0]);
        exit(1);
    }

    double volume = atof(argv[1]);
    double frequency = atof(argv[2]);
    double duration = atof(argv[3]);
    int sample_rate = 44100;

    for(int i = 0; i < duration; i++){
        float amplitude = volume * sin(2 * M_PI * frequency * i / sample_rate);

        short int_amplitude = (short)amplitude;
        int is_write = write(1,&int_amplitude,sizeof(int_amplitude));
        if(is_write == -1){
            printf("write error\n");
            exit(1);
        }
    }
    
    return 0;
}