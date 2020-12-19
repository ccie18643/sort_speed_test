#!/usr/bin/env python3

import sys
import random


def main():
    array = []

    for _ in range(100000):
        array.append(random.randint(0, 255))

    with open("sample.bin", "wb") as f:
        f.write(b"".join([bytes([_]) for _ in array]))


if __name__ == "__main__":
    sys.exit(main())

