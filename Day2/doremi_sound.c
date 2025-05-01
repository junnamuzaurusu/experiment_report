#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    if (argc != 3){
        printf("Usage: %s volume[double] times[int]\n", argv[0]);
        exit(1);
    }

    double volume = atof(argv[1]);
    double frequency = 261.63;
    int times = atoi(argv[2]);
    int sample_rate = 44100;
    int one_cycle = sample_rate * 0.3;

    for(int i = 0; i < times; i++){
        
        for(int j = 0; j < one_cycle; j++){
            float amplitude = volume * sin(2 * M_PI * frequency * j / sample_rate);

            short int_amplitude = (short)amplitude;
            int is_write = write(1,&int_amplitude,sizeof(int_amplitude));
            if(is_write == -1){
                printf("write error\n");
                exit(1);
            }
        }
        frequency = frequency * 1.059463;
        if(i % 7 == 0 || i % 7 == 1 || i % 7 == 3 || i % 7 == 4 || i % 7 == 5){
            frequency = frequency * 1.059463;
        }
    }
    
    return 0;
}