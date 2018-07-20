.name "The Rock"
.comment "I will kick your ass!"

name:	sti r1,%:live,%1

live:	live %1

		ldi %:live,%1,r15

load:	ld %16777216,r2 #  saves 01 00 00 00 to r2
		# ld %260308992,r3 # saves 0f 84 00 00 to r3
		ld %191365632,r4
		ld %38411,r5
		ld %1745813504,r6
		ld %9440104,r7
		ld %67108864,r8
		ld %2366334981,r9
		ld %138,r10
		ld %191366656,r11

write:
		sti   r2,%0,%150 #  write 01 00 00 00 on +153 bytes
		sti   r15,%0,%144 # 	write name of bot from r1 on +154 bytes
		# sti   r3,%0,%141 #  write command 0f and dir 84 from r3
		sti   r4,%0,%141 # copys comands to copy!
		sti   r5,%0,%138 
		sti	  r6,%0,%135
		sti	  r7,%0,%132
		sti   r8,%0,%129
		sti   r9,%0,%126
		sti   r10,%0,%123
		sti	  r11,%0,%120

		# sti   r2,%0,%290 #
		# sti   r1,%0,%291 #
		# sti   r3,%0,%295 #
		# sti   r2,%0,%430 #
		# sti   r1,%0,%431 #
		# sti   r3,%0,%435 #
		# sti   r2,%0,%570 #
		# sti   r1,%0,%571 #
		# sti   r3,%0,%575 #
		# sti   r2,%0,%710
		# sti   r1,%0,%711
		# sti   r3,%0,%715 #

		# # ld %:write, 
