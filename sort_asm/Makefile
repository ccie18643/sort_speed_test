all:
	nasm -felf64 sort_bubble.asm && \
	nasm -felf64 sort_selection.asm && \
	nasm -felf64 sort_insertion.asm && \
	gcc -O3 -std=c99 sort_*.o sort.c -o sort
