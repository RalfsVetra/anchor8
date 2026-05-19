;	SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
;
;	SPDX-License-Identifier: MIT
;
	xref	f_main, __stack
	xdef	f_exit, f__stext
;
;	startup routine from reset vector
;
	switch	.text
f__stext:
;
;	initialize stack pointer
;
	ldw	x,#__stack	; stack pointer
	ldw	sp,x		; in place
;
;	execute main() function
;	may be called by a 'jpf' instruction if no return expected
;
	callf	f_main		; execute main
f_exit:
	jra	f_exit		; and stay here
	end
