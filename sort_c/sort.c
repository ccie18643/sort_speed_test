#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


u_int64_t sort_bubble(u_int8_t* sample, u_int64_t sample_len)
{
    u_int8_t swapped = 1;
    u_int64_t comp_count = 0;

    while(swapped) {
        u_int64_t i = 0;
        swapped = 0;
        while(i < sample_len - 1) {
            if(sample[i + 1] < sample[i]) {
                u_int8_t _ = sample[i];
                sample[i] = sample[i + 1];
                sample[i + 1] = _;
                swapped = 1;
            }
            i++;
            comp_count++;
        }
    }

    return comp_count;
}


u_int64_t sort_selection(u_int8_t* sample, u_int64_t sample_len)
{
    u_int64_t comp_count = 0;
    u_int64_t sorted_len = 0;
    u_int64_t i;

    while(sorted_len < sample_len) {
        i = sorted_len;;
        while(i < sample_len) {
            if(sample[i] < sample[sorted_len]) {
                u_int8_t _ = sample[sorted_len];
                sample[sorted_len] = sample[i];
                sample[i] = _;
            }
            i++;
            comp_count++;
        }
        sorted_len += 1;
    }

    return comp_count;
}


u_int64_t sort_insertion(u_int8_t* sample, u_int64_t sample_len)
{
    u_int64_t comp_count = 0;

    for(int j = 0; j < sample_len; j++) {
        for(int i = j; i < sample_len; i++) {
            comp_count++;
            if(sample[i] < sample[j]) {
                int element = sample[i];
                for(int n = i; n > j; n--) {
                    sample[n] = sample[n - 1];
                }
                sample[j] = element;
            }
        }
    }

    return comp_count;
}


int main(int argc, char *argv[])
{

    if(argc < 2) {
        printf("Please specify algorithm [bubble|selection]\n");
        return -1;
    }

    if(argc < 3) {
        printf("Please specify sample file\n");
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
        printf("Please specify algorithm [bubble|selection]\n");
        return -1;
    }

    double run_time = (((double) (clock() - start)) / CLOCKS_PER_SEC) * 1000;

    if(argc == 4 && !strcmp("result", argv[3])) {
        printf("[");
        for(int i = 0; i < sample_len - 1; i++) {
            printf("%d, ", sample[i]);
        }
        printf("%d]\n", sample[sample_len - 1]);
    }

    printf("language='C', algorithm='%s', run_time=%lfms, comp_count=%ld\n", argv[1], run_time, comp_count);

    free(sample);

    return 0;
}
