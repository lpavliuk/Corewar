.name "The Rock"
.comment "I will kick your ass!"

name:	sti r1,%:live,%1

live:	live %1

load:	ld %16777216,r2 #  saves 01 00 00 00 to r2
		ld %260308992, r3 # saves 0f 84 00 00 to r3

		sti   r2,%:load,%153 #  write 01 00 00 00 on +153 bytes
		sti   r1,%:load,%154 # 	write name of bot from r1 on +154 bytes
		sti   r3,%:load,%158 #  write command 0f and dir 84 from r3
		sti   r2,%:load,%290 #
		sti   r1,%:load,%291 #
		sti   r3,%:load,%295 #
		sti   r2,%:load,%430 #
		sti   r1,%:load,%431 #
		sti   r3,%:load,%435 #
		sti   r2,%:load,%570 #
		sti   r1,%:load,%571 #
		sti   r3,%:load,%575 #
		sti   r2,%:load,%710
		sti   r1,%:load,%711
		sti   r3,%:load,%715 #
