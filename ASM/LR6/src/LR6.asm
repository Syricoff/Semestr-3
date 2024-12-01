title Арифметические выражения
model large, C
CODESEG ; начало сегмента кода
;======== ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ==========
Extrn C X:word
Extrn C a:word
;локальные перменные - константы
b dw -333
c dw 1000
d dw -10
;==============================
Public C prim
prim proc far
mov ax, 2
Imul a
mov bx, dx
mov cx, ax
mov ax, b
Imul c
add ax, cx
adc dx, bx
mov cx, d
sub cx, a
Idiv cx
mov X, ax
ret
prim endp
end