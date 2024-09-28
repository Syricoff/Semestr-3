.MODEL small
.STACK 100h
.DATA
;----byte--
i db 11,49 
;--shortint 
is db -49,-11 
db 11,49 
;----word-- 
iw dw 11,49 
dw 2124 
dw 2162 
; ----integer---- 
ii dw -2162 
dw -2124 
dw -49 
dw -11 
dw 11 
dw 49 
dw 2124 
dw 2162 
;----longint---- 
il dd -2162 
dd 2162
end