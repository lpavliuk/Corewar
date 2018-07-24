.name "The Rock"
.comment "I will kick your ass!"

# MAX 682 Mb

name:   sti r1,%:zero0,%1
		# sti r1,%:zero1,%1
		sti r1,%:forkin,%1
		sti r1,%:forkin1,%1
		sti r1,%:forkin2,%1
		sti r1,%0,%8

	    live %1

# load:
		# ldi %:live,%1,r15
		ld %16777216,r7 #  saves 01 00 00 00 to r2
		# ld %150,r3
		# ld %145,r4
		# ld %140,r6
		# ld %6,r5
		# ld %589944,r10
		ld %0,r11
		# ld %393216,r12
		# ld %917504,r13
		# ld   %11,r2
		# ld   %12,r5
        fork  %:forkin

# zero0: 	live %1
# 		st   r11, -90
# 		st   r11, -99
# 		st   r11, -108
# 		st   r11, -117
# 		st   r11, -126
# 		st   r11, -135
# 		st   r11, -144
# 		st   r11, -153
# 		st   r11, -162
# 		st   r11, -171
# 		st   r11, -180
# 		st   r11, -189
# 		st   r11, -198
# 		st   r11, -207
# 		st   r11, -216
# 		st   r11, -225
# 		st   r11, -234
# 		st   r11, -243
# 		st   r11, -252
# 		st   r11, -261
# 		st   r11, -270
# 		st   r11, -279
# 		st   r11, -288
# 		st   r11, -297
# 		st   r11, -306
# 		st   r11, -315
# 		st   r11, -324
# 		st   r11, -333
# 		st   r11, -342
# 		st   r11, -351
# 		st   r11, -360
# 		st   r11, -369
# 		st   r11, -378
# 		st   r11, -387
# 		st   r11, -396
# 		st   r11, -405
# 		st   r11, -414
# 		st   r11, -423
# 		st   r11, -432
# 		st   r11, -441
# 		st   r11, -450
# 		st   r11, -459
# 		st   r11, -468
# 		st   r11, -477
# 		st   r11, -486
# 		st   r11, -495
# 		st   r11, -504
# 		st   r11, -513
        
#         add  r8,r8,r8
# 		zjmp  %:zero0

forkin:	
        live %1

forkin1: 
        live %1
		fork  %:zero0

forkin2: 
        live %1
		fork  %:forkin1
        zjmp  %:name

# cpy:  
#         live %1
#         ld %184549376,r10
#         ld %

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
        
        add  r8,r8,r8
		zjmp  %:zero0

