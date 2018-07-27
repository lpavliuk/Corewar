.name "The Rock"
.comment "I will kick your ass!"

# MAX 682 Mb



name:
		# sti r1,%:zero0,%1
		sti r1,%:jump,%1
		# sti r1,%:zero,%1
		sti r1,%:forkin,%1
		sti r1,%:for,%1
		sti r1,%:f,%1
		sti r1,%:jump2,%1
		sti r1,%:start,%1
		sti r1,%:zero0,%1
		sti r1,%:forkin2,%1
		sti r1,%:for2,%1
		sti r1,%:f2,%1
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
		fork %:zero0
start:	
		live %1
		fork %:name
<<<<<<< HEAD

		and r8,%0,r8
		zjmp %:f

zero0: 	live %1
		st   r11, 399
		st   r11, 398
		st   r11, 397
		st   r11, 396
		st   r11, 395
		st   r11, 394
		st   r11, 393
		st   r11, 392
		st   r11, 391
		st   r11, 390
		st   r11, 389
		st   r11, 388
		st   r11, 387
		st   r11, 386
		st   r11, 385
		st   r11, 384
		st   r11, 383
		st   r11, 382
		st   r11, 381
		st   r11, 380
		st   r11, 379
		st   r11, 378
		st   r11, 377
		st   r11, 376
		st   r11, 375
		st   r11, 374
		st   r11, 373
		st   r11, 372
		st   r11, 371
		st   r11, 370
		st   r11, 369
		st   r11, 368
		st   r11, 367
		st   r11, 366
		st   r11, 365
		st   r11, 364
		st   r11, 363
		st   r11, 362
		# st   r11, 261
		# st   r11, 260
		# st   r11, 259
		# st   r11, 258
		# st   r11, 257
		# st   r11, 256
		# st   r11, 255
		# st   r11, 254
		# st   r11, 253
        
        add  r8,r8,r8
		zjmp  %:zero0
=======
>>>>>>> 80b85525ff9bbdc6aea7c129dab026fb4de145d4
#########  1  #############

f:	
		live %1
		fork %:forkin

for:
		live %1
		sti r1,%:write,%1
		sti r1,%:write1,%1
		fork %:write1

write:		
		live %1
		ld   %159, r14	
		ldi  %0, %:jump, r15

		and r8,%0,r8
		zjmp %:jump

write1: 
		live %1
		ld   %163, r14	
		ldi  %4, %:jump, r15

		and r8,%0,r8
		zjmp %:jump

forkin:
		live %1
		sti r1,%:write2,%1
		sti r1,%:write3,%1
		fork %:write3

write2: 
		live %1
		ld   %167, r14	
		ldi  %8, %:jump, r15
		
		and r8,%0,r8
		zjmp %:jump

write3: 
		live %1
		ld   %171, r14	
		ldi  %12, %:jump, r15
		
		and r8,%0,r8
		zjmp %:jump

jump:
		live %1				# 5
		sti  r15,%0,r14			# 6
		zjmp %153

# # ######### 2 ################

f2:
		live %1
		fork %:forkin2

for2:
		live %1
		sti r1,%:write2,%1
		sti r1,%:write21,%1
		fork %:write21

write2:		
		live %1
		ld   %-191, r14	
		ldi  %0, %:jump2, r15

		and r8,%0,r8
		zjmp %:jump2

write21: 
		live %1
		ld   %-187, r14	
		ldi  %4, %:jump2, r15

		and r8,%0,r8
		zjmp %:jump2

forkin2:
		live %1
		sti r1,%:write22,%1
		sti r1,%:write23,%1
		fork %:write23

write22: 
		live %1
		ld   %-183, r14	
		ldi  %8, %:jump2, r15
		
		and r8,%0,r8
		zjmp %:jump2

write23: 
		live %1
		ld   %-179, r14	
		ldi  %12, %:jump2, r15
		
		and r8,%0,r8
		zjmp %:jump2

jump2:
		live %1				# 5
		sti  r15,%0,r14			# 6
		zjmp %-200

# zero: 
#         live %1
# 		fork  %:zero0
<<<<<<< HEAD

# 		zjmp %:zero


=======

# 		zjmp %:zero

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
		# st   r11, 261
		# st   r11, 260
		# st   r11, 259
		# st   r11, 258
		# st   r11, 257
		# st   r11, 256
		# st   r11, 255
		# st   r11, 254
		# st   r11, 253
        
        add  r8,r8,r8
		zjmp  %:zero0
>>>>>>> 80b85525ff9bbdc6aea7c129dab026fb4de145d4


        # fork  %:forkin
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
        
# 		zjmp  %:zero0
# forkin:	
#         live %1

# forkin1: 
#         live %1
# 		fork  %:zero0


# cpy:  
#         live %1
#         ld %184549376,r10
#         ld %



