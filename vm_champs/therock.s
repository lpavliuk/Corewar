.name "The Rock"
.comment "I will kick your ass!"

# MAX 682 Mb

name:
		sti r1,%:zero0,%1
		sti r1,%:forkin,%1
		sti r1,%:forkin1,%1
		sti r1,%:forkin2,%1
		sti r1,%0,%8

		live %1

# load:
		# ldi %:live,%1,r15
		# ld %16777216,r7 #  saves 01 00 00 00 to r2
		# ld %150,r3
		# ld %145,r4
		# ld %140,r6
		# ld %6,r5
		# ld %589944,r10
		ld %0,r11
		# ld %393216,r12
		# ld %917504,r13
		ld   %11,r2
		ld   %12,r5
		ld   %4,r3
		ld   %5,r6

		fork  %:forkin

zero0: 	live %1
		st   r11, 299
		st   r11, 298
		st   r11, 297
		st   r11, 296
		st   r11, 295
		st   r11, 294
		st   r11, 293
		st   r11, 292
		st   r11, 291
		st   r11, 290
		st   r11, 289
		st   r11, 288
		st   r11, 287
		st   r11, 286
		st   r11, 285
		st   r11, 284
		st   r11, 283
		st   r11, 282
		st   r11, 281
		st   r11, 280
		st   r11, 279
		st   r11, 278
		st   r11, 277
		st   r11, 276
		st   r11, 275
		st   r11, 274
		st   r11, 273
		st   r11, 272
		st   r11, 271
		st   r11, 270
		st   r11, 269
		st   r11, 268
		st   r11, 267
		st   r11, 266
		st   r11, 265
		st   r11, 264
		st   r11, 263
		st   r11, 262
		st   r11, 261
		st   r11, 260
		st   r11, 259
		st   r11, 258
		st   r11, 257
		st   r11, 256
		st   r11, 255
		st   r11, 254
		st   r11, 253
		st   r11, 252
		st   r11, 251
		st   r11, 250

        
        add  r8,r8,r8
		zjmp  %:zero0

forkin:	live %1
		fork  %:forkin

forkin1:
		live %1
		fork  %:zero0

forkin2:
        live %1
		fork  %:zero0

        zjmp  %:name

		# fork  %:zero1
		# fork  %:zero2

# zero1:  sti   r15,%0,%8
# 		live %1
# 		sti   r11,%2048,r12
# 		add   r12,r13,r12

# 		and   r1,%0,r14
# 		zjmp  %:zero1

# zero2:  sti   r15,%0,%8 
# 		live %1
# 		sti   r11,%3072,r12
# 		add   r12,r13,r12

# 		and   r1,%0,r14
# 		zjmp  %:zero2

# write:
# 		sti   r2,%0,r3 #  write 01 00 00 00
# 		sti   r15,%0,r4 # 	write name of bot from r15
# 		sti   r10,%0,r6

# 		add   r3,r5,r3
# 		add   r4,r5,r4
# 		add   r6,r5,r6

# 		and   r1,%0,r14
# 		zjmp  %:write


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
