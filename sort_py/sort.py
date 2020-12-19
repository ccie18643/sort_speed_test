#!/usr/bin/env python3

import sys
import time
import random


def sort_bubble(sample):
    """ Bubble sort - slower version """

    swapped = True
    comp_count = 0 
    sample_len = len(sample)

    while swapped:
        swapped = False
        i = 0
        while i < sample_len - 1:
            comp_count += 1
            if sample[i + 1] < sample[i]:
                sample[i], sample[i + 1] = sample[i + 1], sample[i]
                swapped = True
            i += 1
    return comp_count


def sort_bubble(sample):
    """ Bubble sort - faster version """
    
    comp_count = 0
    sample_len = len(sample)
    swapped = True

    j = -1
    while swapped:
        swapped = False
        j += 1
        for i in range(1, sample_len - j):
            comp_count += 1
            if sample[i - 1] > sample[i]:
                sample[i - 1], sample[i] = sample[i], sample[i - 1]
                swapped = True

    return comp_count


def sort_selection(sample):
    """ Selection sort - slower version """

    updated = True
    comp_count = 0 
    sample_len = len(sample)

    sorted_len = 0
    while sorted_len < sample_len:
        i = sorted_len
        while i < sample_len:
            if sample[i] < sample[sorted_len]:
                sample[i], sample[sorted_len] = sample[sorted_len], sample[i]
            i += 1
            comp_count += 1
        sorted_len += 1
    return comp_count


def sort_selection(sample):        
    """ Selection sort - faster version """

    comp_count = 0

    for i in range(len(sample)):
        minimum = i
        
        for j in range(i + 1, len(sample)):
            comp_count += 1
            if sample[j] < sample[minimum]:
                minimum = j

        sample[minimum], sample[i] = sample[i], sample[minimum]
            
    return comp_count


def sort_insertion(sample):
    """ Insertion sort - modified (left to right seek) """

    comp_count = 0
    sample_len = len(sample)

    for j in range(sample_len):
        for i in range(j, sample_len):
            comp_count += 1
            if sample[i] < sample[j]:
                sample.insert(j, sample.pop(i))
        
    return comp_count


def _sort_insertion(sample):
    """ Insertion sort - classic (right to left seek) """

    comp_count = 0
    sample_len = len(sample)

    for j in range(sample_len):
        for i in range(sample_len - 1, j, -1):
            comp_count += 1
            if sample[i] < sample[j]:
                sample.insert(j, sample.pop(i))

    return comp_count


def main(argv):
    if len(argv) < 2:
        print("Please specify algorithm [bubble|selection]")
        return -1
    algorithm = argv[1]

    if len(argv) < 3:
        print("Please specify sample file")
        return -2
    with open(argv[2], "rb") as _:
        sample = list(_.read())

    start = time.time()

    if algorithm == "bubble":
        comp_count = sort_bubble(sample)
    elif algorithm == "selection":
        comp_count = sort_selection(sample)
    elif algorithm == "insertion":
        comp_count = sort_insertion(sample)
    else:
        "Please specify algorithm [bubble|selection]"
        return -3

    run_time = (time.time() - start) * 1000

    if len(argv) == 4 and argv[3] == "result":
        print(sample)

    print(f"language='python', {algorithm=}, {run_time=}ms, {comp_count=}")

if __name__ == "__main__":
    sys.exit(main(sys.argv))

