.name "The Rock"
.comment "I will kick your ass!"

name:	sti r1,%:live,%1

live:	live %1
		zjmp %:live
load:
		ldi %:live,%1,r15
		ld %16777216,r2 #  saves 01 00 00 00 to r2
		ld %150,r3
		ld %145,r4
		ld %140,r6
		ld %6,r5
		ld %589944,r10
		ld %0,r11
		ld %0,r12
		ld %100,r13

		and   r1,%0,r14
		zjmp  %:forkin

zero0: 	sti   r15,%0,%8
		live %1
		sti   r11,%250,r12
		add   r12,r13,r12

		and   r1,%0,r14
		zjmp  %:zero0

zero1:  sti   r15,%0,%8
		live %1
		sti   r11,%500,r12
		add   r12,r13,r12

		and   r1,%0,r14
		zjmp  %:zero1

zero2:  sti   r15,%0,%8 
		live %1
		sti   r11,%750,r12
		add   r12,r13,r12

		and   r1,%0,r14
		zjmp  %:zero2

write:
		sti   r2,%0,r3 #  write 01 00 00 00
		sti   r15,%0,r4 # 	write name of bot from r15
		sti   r10,%0,r6

		add   r3,r5,r3
		add   r4,r5,r4
		add   r6,r5,r6

		and   r1,%0,r14
		zjmp  %:write

forkin:
		fork  %:forkin
		fork  %:name
		fork  %:zero0
		fork  %:zero1
		fork  %:zero2


		# sti   r3,%0,%141 #  write command 0f and dir 84 from r3
		# sti   r4,%0,%141 # copys comands to copy!
		# sti   r5,%0,%138 
		# sti	  r6,%0,%135
		# sti	  r7,%0,%132
		# sti   r8,%0,%129
		# sti   r9,%0,%126
		# sti   r10,%0,%123
		# sti	  r11,%0,%120

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
