.model small
.stack 100h
.data 
    X dw 80
.code 
start:
M: inc X
	cmp X, 80
	jle M
	dec X
end start
