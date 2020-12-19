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
; r8  - sorted_len
; r9  - index
; 

                global  sort_selection
                section .text

sort_selection:
                xor rax, rax
                xor rdx, rdx
                xor rcx, rcx
                xor r8, r8

loop_1:
                cmp r8, rsi
                je finished
                mov r9, r8

loop_2:
                mov dl, [rdi + r8]
                mov cl, [rdi + r9]
                cmp dl, cl
                jbe no_swap
                mov [rdi + r8], cl
                mov [rdi + r9], dl
                
no_swap:
                inc rax
                inc r9
                cmp r9, rsi
                jb loop_2
                inc r8
                jmp loop_1
                
finished:
                ret
