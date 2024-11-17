; var8: x1=92 x2=a1h=161 x3=222 a=39 b=33h=51 c=5 d=6
include macroses.asm
.model small
.stack 100h
.data
	x1         db  92
	x2         db  161
	x3         db  222
	a          db  39
	b          db  51
	c          db  5
	d          db  6
	e          db  ?
	f          db  ?
	sum_result db  0
	sub_result db  0
	mul_result dw  1
	rem_result db  0
	div_result db  0
	mes_res db 'Result: ', '$'
	new_line db 13,10,'$'

.code
calc_value macro  reg
	           mov al, reg
	           sub al, a
	           mov sub_result, al
	           add al, b
	           mov sum_result, al
	           mul c
	           mov mul_result, ax
	           div d
	           inc al
	           mov e, al
	           dec ah
	           mov f, ah
	           add al, ah
			   xor ah, ah
endm
	start:
	      mov        ax, @data
	      mov        ds, ax

	      xor        ax, ax
	      calc_value x1
		  mWriteStr mes_res
		  mWriteAX
		  mWriteStr new_line
	      xor        ax, ax
	      calc_value x2
		  mWriteStr mes_res
		  mWriteAX
		  mWriteStr new_line
	      xor        ax, ax
	      calc_value x3
		  mWriteStr mes_res
		  mWriteAX
		  mWriteStr new_line
		
	      mov        ax, 4C00h
	      int        21h
end start
end
