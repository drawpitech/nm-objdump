;;
;; EPITECH PROJECT, 2024
;; nm/objdump
;; File description:
;; a
;;

BITS 64

section .data
    src db "Hello, World!", 0

section .text
global memcpy
memcpy:
  push rdx
.loop:
  ; while *src == '\0'
  cmp rdx, 0
  je .end
  dec rdx

  ; copy rdi[rdx] in byte sized register
  ; and copy it in rsi[rdx]
  mov al, [rsi + rdx]
  mov byte [rdi + rdx], al
  jmp .loop
.end:
  pop rdx
  mov rax, rdi
  ret
