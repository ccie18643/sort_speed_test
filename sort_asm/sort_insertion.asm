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
; r8  - j
; r9  - i, n
; 

                global  sort_insertion
                section .text

sort_insertion:
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
                cmp dl, [rdi + r9]
                jbe no_insert

                push r9
                mov dl, [rdi + r9]

move_32_bytes:
                mov r10, r9
                sub r10, r8
                cmp r10, 32
                jb move_16_bytes
                mov rcx, [rdi + r9 - 8]
                mov [rdi + r9 - 7], rcx
                mov rcx, [rdi + r9 - 16]
                mov [rdi + r9 - 15], rcx
                mov rcx, [rdi + r9 - 24]
                mov [rdi + r9 - 23], rcx
                mov rcx, [rdi + r9 - 32]
                mov [rdi + r9 - 31], rcx
                sub r9, 32
                jmp move_32_bytes

move_16_bytes:
                mov r10, r9
                sub r10, r8
                cmp r10, 16
                jb move_8_bytes
                mov rcx, [rdi + r9 - 8]
                mov [rdi + r9 - 7], rcx
                mov rcx, [rdi + r9 - 16]
                mov [rdi + r9 - 15], rcx
                sub r9, 16
                jmp move_16_bytes

move_8_bytes:
                mov r10, r9
                sub r10, r8
                cmp r10, 8
                jb move_4_bytes
                mov rcx, [rdi + r9 - 8]
                mov [rdi + r9 - 7], rcx
                sub r9, 8
                jmp move_8_bytes

move_4_bytes:
                mov r10, r9
                sub r10, r8
                cmp r10, 4
                jb move_2_bytes
                mov ecx, [rdi + r9 - 4]
                mov [rdi + r9 - 3], ecx
                sub r9, 4
                jmp move_4_bytes

move_2_bytes:
                mov r10, r9
                sub r10, r8
                cmp r10, 2
                jb move_1_byte
                mov cx, [rdi + r9 - 2]
                mov [rdi + r9 - 1], cx
                sub r9, 2
                jmp move_2_bytes

move_1_byte:
                cmp r8, r9
                je move_end
                mov cl, [rdi + r9 - 1]
                mov [rdi + r9], cl
                dec r9
                jmp move_1_byte

move_end:
                mov [rdi + r8], dl
                pop r9
                
no_insert:
                inc rax
                inc r9
                cmp r9, rsi
                jb loop_2
                inc r8
                jmp loop_1
                
finished:
                ret
