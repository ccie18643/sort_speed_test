;
; Arguments passed from C 
;
; rdi - pointer to array
; rsi - length of array
;
; Register use
;
; rax - number of comparisions (return value)
; rdx - swap elements
; rcx - swap elements
; r8  - swap indicator
; r9  - index
; 

                global  sort_bubble
                section .text

sort_bubble:
                xor rax, rax
                xor rdx, rdx
                xor rcx, rcx
                dec rsi
                mov r8, 1

loop_1:
                cmp r8, 0
                je finished
                xor r8, r8
                xor r9, r9

loop_2:
                mov dl, [rdi + r9]
                mov cl, [rdi + r9 + 1]
                cmp dl, cl
                jbe no_swap
                mov [rdi + r9], cl
                mov [rdi + r9 + 1], dl
                mov r8, 1
                
no_swap:
                inc rax
                inc r9
                cmp r9, rsi
                jb loop_2
                jmp loop_1
                
finished:
                ret
