.model small
.stack 100h
.data
    B_TAB  db 1Ah,2Bh,3Ch,4Dh,5Eh,6Fh,7Ah,8Bh
    W_TAB  dw 1A2Bh,3C4Dh,5E6Fh,7A8Bh
    B_TAB1 db 0Ah,8 dup(1)
    W_TAB1 dw 8 dup(1)
    W_TAB2 dw 11h,12h,13h,14h,15h,16h,17h,18h

.code
    start:
          mov ax, @data
          mov ds, ax

    ; Непосредственная адресация
          mov al, -3                        ; Расширение знака
          mov ax, 3                         ; Переместить значение 3 в регистр ax
          mov B_TAB, -3                     ; Переместить значение -3 в массив B_TAB
          mov W_TAB, -3                     ; Переместить значение -3 в массив W_TAB
          mov ax, 2A1Bh                     ; Переместить значение 2A1Bh в регистр ax

    ; Регистровая адресация
          mov bl, al                        ; Переместить значение регистра al в регистр bl
          mov bh, al                        ; Переместить значение регистра al в регистр bh
          sub ax, bx                        ; Переместить разность регистров ax и bx в регистр ax
          sub ax, ax                        ; Переместить разность регистров ax и ax в регистр ax

    ; Прямая адресация
          mov ax, W_TAB                     ; Переместить в ax 1-ый элемент W_TAB
          mov ax, W_TAB + 3                 ; Переместить в регистр ax
          mov ax, W_TAB + 5                 ; Переместить в регистр ax
          mov al, byte ptr W_TAB + 6        ; Переместить в регистр al
          mov al, B_TAB                     ; Переместить в al 1-ый элемент B_TAB
          mov al, B_TAB + 2                 ; Переместить в регистр al
          mov ax, word ptr B_TAB            ; Переместить в регистр ax
          mov es:W_TAB2 + 4, ax             ; В W_TAB2 ax

    ; Косвенная адресация
          mov bx, offset B_TAB              ; Переместить в bx адрес 1-ого элемента B_TAB
          mov si, offset B_TAB + 1          ; Переместить в si адрес 2-ого элемента B_TAB
          mov di, offset B_TAB + 2          ; Переместить в di адрес 3-ого элемента B_TAB
          mov dl, [bx]                      ; Переместить в dl 1-ый элемент B_TAB
          mov dl, [si]                      ; Переместить в dl 2-ый элемент B_TAB
          mov dl, [di]                      ; Переместить в dl 3-ый элемент B_TAB
          mov ax, [di]                      ; Переместить в ax 3-ий элемент B_TAB
          mov bp, bx                        ; Переместить значение регистра bx в bp
          mov al, [bp]                      ; Переместить в al 1-ый элемент B_TAB
          mov al, ds:[bp]                   ; Переместить в al 1-ый элемент B_TAB
          mov al, es:[bx]                   ; Переместить в dl 1-ый элемент B_TAB
          mov ax, cs:[bx]                   ; Переместить в dl 1-ый элемент B_TAB

    ; Базовая адресация
          mov ax, [bx] + 2                  ;
          mov ax, [bx] + 4                  ;
          mov ax, [bx + 2]                  ;
          mov ax, [4 + bx]                  ;
          mov ax, 2 + [bx]                  ;
          mov ax, 4 + [bx]                  ;
          mov al, [bx] + 2                  ;
          mov bp, bx                        ;
          mov ax, [bp + 2]                  ;
          mov ax, ds:[bp] + 2               ;
          mov ax, ss:[bx + 2]               ;

    ; Индексная адресация
          mov si, 2                         ; Загрузка индекса
          mov ah, B_TAB[si]                 ; Переместить в ah 2-ой элемент B_TAB
          mov al, [B_TAB + si]              ; Переместить в al 2-ой элемент B_TAB
          mov bh, [si + B_TAB]              ; Переместить в bh 2-ой элемент B_TAB
          mov bl, [si] + B_TAB              ; Переместить в bl 2-ой элемент B_TAB
          mov bx, es:W_TAB2[si]             ;
          mov di, 4                         ; Загрузка индекса
          mov bl, byte ptr es:W_TAB2[di]    ;
          mov bl, B_TAB[si]                 ; Переместить в bl 2-ой элемент B_TAB

    ; Базовая индексная адресация
          mov bx, offset B_TAB              ; Загрузка базы
          mov al, 3[bx][si]                 ;
          mov ah, [bx + 3][si]              ;
          mov al, [bx][si + 2]              ;
          mov ah, [bx + si + 2]             ;
          mov bp, bx                        ;
          mov ah, 3[bp][si]                 ;
          mov ax, ds:3[bp][si]              ;
          mov ax, word ptr ds:2[bp][si]     ;

          mov ax, 4c00h
          int 21h
end start
