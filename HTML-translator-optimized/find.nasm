global Find
section .text

extern CastTo__m256i

; rdi - pointer to table
; rsi - pointer to value

Find: ;save rpb, rbx
    push rbp
    mov  rbp, rsp
    push rbx
    and  rsp, 0xffffffffffffffe0
    sub  rsp, 0xa0
    push r9
    push r11
    push r12

    mov  rbx, [rdi + 0x10] ; rbx - pointer to hash function
    mov  r10, rdi          ; saving table pointer
    
    push rsi
    mov r9, rdi
    mov rdi, rsp
    call rbx               ; calling hash function
    pop rsi

    mov rbx, [r9 + 0x08]   ; table size
    xor rdx, rdx
    div rbx                ; hash %= size

    shl rdx, 3
    mov rbx, rdx
    add rdx, rbx           ; rdx = hash * sizeof(DynamicArray/24/)
    add rdx, rbx

    mov r9, [r10]
    add r9, rdx            ; r9 - table->data + hash % size - pointer to array

    mov rdi, rsi           ; pointer to value
    push r9
    call CastTo__m256i     ; ymm0 - value_
    pop r9
    vmovdqa ymm2, ymm0

    mov rcx, [r9 + 0x08]   ; size of array
    mov r9, [r9]           ; r9 - pointer to the first pair
    
    xor rax, rax

find_for:
    test rcx, rcx
    jz find_for_end

    vmovdqa ymm0, [r9]     ; ymm0 - array->data[i].value
    vmovdqa ymm1, ymm2             ; ymm1 - value_
    vpcmpeqb ymm0, ymm1, ymm0
    vpmovmskb eax, ymm0
    cmp eax, 0xFFFFFFFF
    je words_equal

    add r9, 64
    dec rcx
    jmp find_for

words_equal:
    add r9, 32
    mov rax, [r9]

    pop r12
    pop r11
    pop r9
    mov rbx, [rbp-0x8]
    leave
    ret

find_for_end:
    
    pop r12
    pop r11
    pop r9
    xor rax, rax
    mov rbx, [rbp-0x8]
    leave
    ret
