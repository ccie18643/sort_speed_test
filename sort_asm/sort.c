#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

typedef char byte;

extern u_int64_t sort_bubble(byte*, u_int64_t);
extern u_int64_t sort_selection(byte*, u_int64_t);
extern u_int64_t sort_insertion(byte*, u_int64_t);

int main(int argc, char *argv[])
{

    if(argc < 2) {
        printf("Please specify algorithm [bubble|selection|insertion]\n");
        return -1;
    }

    if(argc < 3) {
        printf("Please specify sample file]\n");
        return -2;
    }

    struct stat st;
    stat(argv[2], &st);
    int sample_len = st.st_size;
    int fd = open(argv[2], O_RDONLY);
    u_int8_t* sample = malloc(sample_len);
    int _ = read(fd, sample, sample_len);
    close(fd);

    u_int64_t comp_count;
    clock_t start = clock();

    if(!strcmp("bubble", argv[1])) {
        comp_count = sort_bubble(sample, sample_len);
    }
    else if(!strcmp("selection", argv[1])) {
        comp_count = sort_selection(sample, sample_len);
    }
    else if(!strcmp("insertion", argv[1])) {
        comp_count = sort_insertion(sample, sample_len);
    }
    else {
        printf("Please specify algorithm [bubble|selection|insertion]\n");
        return -3;
    }

    double run_time = (((double) (clock() - start)) / CLOCKS_PER_SEC) * 1000;

    if(argc == 4 && !strcmp("result", argv[3])) {
        printf("[");
        for(int i = 0; i < sample_len - 1; i++) {
            printf("%d, ", sample[i]);
        }
        printf("%d]\n", sample[sample_len - 1]);
    }

    printf("language='assembly', algorithm='%s', run_time=%lfms, comp_count=%ld\n", argv[1], run_time, comp_count);

    free(sample);

    return 0;
}
