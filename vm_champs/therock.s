.name "The Rock"
.comment "I will kick your ass!"

# MAX 682 Mb

zero1: 	live %1
		st   r11, -90
		st   r11, -99
		st   r11, -108
		st   r11, -117
		st   r11, -126
		st   r11, -135
		st   r11, -144
		st   r11, -153
		st   r11, -162
		st   r11, -171
		st   r11, -180
		st   r11, -189
		st   r11, -198
		st   r11, -207
		st   r11, -216
		st   r11, -225
		st   r11, -234
		st   r11, -243
		st   r11, -252
		st   r11, -261
		st   r11, -270
		st   r11, -279
		st   r11, -288
		st   r11, -297
		st   r11, -306
		st   r11, -315
		st   r11, -324
		st   r11, -333
		st   r11, -342
		st   r11, -351
		st   r11, -360
		st   r11, -369
		st   r11, -378
		st   r11, -387
		st   r11, -396
		st   r11, -405
		st   r11, -414
		st   r11, -423
		st   r11, -432
		st   r11, -441
		st   r11, -450
		st   r11, -459
		st   r11, -468
		st   r11, -477
		st   r11, -486
		st   r11, -495
		st   r11, -504
		st   r11, -513

		add  r8,r8,r8
		zjmp  %:zero1

name:
		# sti r1,%:zero0,%1
		sti r1,%:jump,%1
		sti r1,%:zero,%1
		sti r1,%:forkin,%1
		sti r1,%:for,%1
		sti r1,%:f,%1
		sti r1,%:l2,%1
		# sti r1,%:jump2,%1
		sti r1,%:start,%1
		sti r1,%:zero0,%1
		# sti r1,%:forkin2,%1
		# sti r1,%:for2,%1
		# sti r1,%:f2,%1
		sti r1,%0,%8

	    live %1
# load: 
		st r1,r15
		ld %16777216,r7 #  saves 01 00 00 00 to r2
		st r0,r3
		st r1,r4
		st r1,r6
		st r1,r5
		st r1,r10
		ld %0,r11
		st r1,r12
		st r1,r13
		st r1,r2
		lfork %1250

zero:
		live %1
		fork %:zero0

l2:
		live %1
		lfork %2250

# start:	
# 		live %1
# 		fork %:name
		
# 		and r8,%0,r8
# 		zjmp %:f

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

# #########  1  #############

# f:	
# 		live %1
# 		fork %:forkin

# for:
# 		live %1
# 		sti r1,%:write,%1
# 		sti r1,%:write1,%1
# 		fork %:write1

# write:		
# 		live %1
# 		ld   %159, r14	
# 		ldi  %0, %:jump, r15

# 		and r8,%0,r8
# 		zjmp %:jump

# write1: 
# 		live %1
# 		ld   %163, r14	
# 		ldi  %4, %:jump, r15

# 		and r8,%0,r8
# 		zjmp %:jump

# forkin:
# 		live %1
# 		sti r1,%:write2,%1
# 		sti r1,%:write3,%1
# 		fork %:write3

# write2: 
# 		live %1
# 		ld   %167, r14	
# 		ldi  %8, %:jump, r15
		
# 		and r8,%0,r8
# 		zjmp %:jump

# write3: 
# 		live %1
# 		ld   %171, r14	
# 		ldi  %12, %:jump, r15
		
# 		and r8,%0,r8
# 		zjmp %:jump

# jump:
# 		live %1				# 5
# 		sti  r15,%0,r14			# 6
# 		zjmp %153

# # # ######### 2 ################

# f2:
# 		live %1
# 		fork %:forkin2

# for2:
# 		live %1
# 		sti r1,%:write2,%1
# 		sti r1,%:write21,%1
# 		fork %:write21

# write2:		
# 		live %1
# 		ld   %-191, r14	
# 		ldi  %0, %:jump2, r15

# 		and r8,%0,r8
# 		zjmp %:jump2

# write21: 
# 		live %1
# 		ld   %-187, r14	
# 		ldi  %4, %:jump2, r15

# 		and r8,%0,r8
# 		zjmp %:jump2

# forkin2:
# 		live %1
# 		sti r1,%:write22,%1
# 		sti r1,%:write23,%1
# 		fork %:write23

# write22: 
# 		live %1
# 		ld   %-183, r14	
# 		ldi  %8, %:jump2, r15
		
# 		and r8,%0,r8
# 		zjmp %:jump2

# write23: 
# 		live %1
# 		ld   %-179, r14	
# 		ldi  %12, %:jump2, r15
		
# 		and r8,%0,r8
# 		zjmp %:jump2

# jump2:
# 		live %1				# 5
# 		sti  r15,%0,r14			# 6
# 		zjmp %-200

# zero: 
#         live %1
# 		fork  %:zero0

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



