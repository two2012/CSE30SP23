    .arch armv7
    .cpu cortex-a53
    .equ 	NUL, 0

    .global asm_doRow
	
	// Set offsets for incoming parameters 5 and 6
	.equ	IARG6, 8				// newlife parameter
	.equ    IARG5, 4				// number of columns parameter	

    // !!! SET FP_OFFSET TO THE NUMBER OF (SAVED REGISTERS -1 * 4)	
    .equ 	FP_OFFSET, 32			// (# of saved regs - 1) * 4

	// Add any local variables used
	.equ 	PARAM1, FP_OFFSET + 4	// offset for dest
	.equ 	PARAM2, PARAM1 + 4		// offset for src
	.equ 	PARAM3, PARAM2 + 4		// offset for curRow
	.equ 	PARAM4, PARAM3 + 4		// offset for nRows

	.equ 	FRMADD, PARAM4 + 4		// Frame size for parameters

	// asm_doRow(belem *dest,   	// r0, pointer to the first cell in the next buffer (index 0, top left)
	//           belem *src,     	// r1, pointer to the first cell in current buffer (index 0, top left)
	//           size_t curRow,  	// r2, row to process
	//           size_t nRows,   	// r3, number of rows in the board
	//           size_t nCols,   	// fp + 4, number of columns in the board
	//	         int *newLife)   	// fp + 8, pointer to a int that represents how many cells have gone from dead to alive in a timestep



asm_doRow:	
	push {r4-r10, fp, lr} 			//Push any preserved registers
	add fp,sp,#FP_OFFSET
	sub sp,sp,#FRMADD
	
	
	// Write body of asm_doRow here
	// store parameters to stack
	str r0, [fp,#-PARAM1]			// store dest to stack
	str r1, [fp,#-PARAM2] 			// store src to stack
	str r2, [fp,#-PARAM3]			// store curRow to stack
	str r3, [fp,#-PARAM4]			// store nRows to stack

	// loop through each cell in the row
	mov r4, #0						// i = 0
.Louter_i_Loop:
	ldr r5, [fp, #IARG5]			// r5 = nCols
	cmp r4, r5						// i < nCols

	bge .Lend_outer_i_loop  		// if i >= nCols, end loop
	mov r6, #0						// alive_neighbors = 0

	// loop through each neighbor of a cell
	mov r7, #-1						// j = -1
.Linner_j_Loop:
	cmp r7, #2						// j < 2
	bge .LendInner_j_Loop			// if j >= 2, end loop

	mov r8, #-1						// k = -1
.Linner_k_loop:
	cmp r8, #2						// k < 2
	bge .LendInner_k_Loop			// if k >= 2, end loop

	cmp r7, #0						// if j == 0
	bne .Linner_k_loop_continue 	// if j != 0, continue
	cmp r8, #0						// if k == 0
	beq .Linner_k_loop_skip 		// if k == 0, skip

.Linner_k_loop_continue:

	// calculate the index of the neighbor
        ldr r2, [fp,#-PARAM3]			// r2 = curRow
	add r2, r2, r7					// r2 = curRow + j	
	add r3, r4, r8					// r3 = i + k
	ldr r0, [fp,#-PARAM4]			// r0 = nRows
	ldr r1, [fp,#IARG5]			    // r1 = nCols
	bl nGetIndex					// r0 = get_index(curRow + j, i + k, nRows, nCols)					

	// load the neighbor from src
	ldr r1,[fp,#-PARAM2]			// r1 = src
	ldrb r2, [r1, r0]				// r2 = src[r0]

	// check if the neighbor is alive
	cmp r2, #0						// if neighbor == 0
	beq .Linner_k_loop_skip			// if neighbor == 0, skip
	add r6,r6,#1					// alive_neighbors++

.Linner_k_loop_skip:
	add r8,r8,#1					// k++
	b .Linner_k_loop				// continue loop
	
.LendInner_k_Loop:
	add r7,r7,#1					// j++
	b .Linner_j_Loop				// continue loop

.LendInner_j_Loop:
	
	//update the cell state in the destination buffer
	ldr r0, [fp,#-PARAM2] 			// r0 = src
	ldr r1, [fp,#-PARAM3]		    // r1 = curRow
	mul r1, r1, r5					// r1 = curRow * nCols
	add r1, r1, r4					// r1 = curRow * nCols + i
	ldrb r3, [r0, r1] 				// r3 = src[curRow * nCols + i]
	cmp r3,#1						// if src[curRow * nCols + i] == 1 
	beq .Lcell_alive				// if src[curRow * nCols + i] == 1, go to Lcell_alive
	b .Lcell_dead					// else the cell is dead
	
.Lcell_alive:
	cmp r6,#2						// if alive_neighbors == 2
	blt .Lcell_turn_dead			// if alive_neighbors < 2, go to Lcell_dead
	cmp r6,#3						// if alive_neighbors == 3
	bgt .Lcell_turn_dead			// if alive_neighbors > 3, go to Lcell_dead
	ldr r0, [fp,#-PARAM1]			// r0 = dest
	mov r2, #1				// r2 = 1
	strb r2, [r0, r1]			// dest[curRow * ncol + i] = 1
	b .Louter_i_imcrement			// else the cell is alive, continue loop

.Lcell_dead:
	cmp r6,#3						// if alive_neighbors == 3
	bne .Lcell_keep_dead			// if alive_neighbors != 3, cell keep dead
	ldr r0, [fp,#-PARAM1]			// r0 = dest
	mov r2,#1						// r2 = 1
	strb r2, [r0, r1]				// dest[curRow * nCols + i] = 1
	ldr r1, [fp, #IARG6]			// r1 = *newLife
	add r1,r1,#1					// *newLife++
	str r1, [fp, #IARG6]			// store *newLife back to stack
	b .Louter_i_imcrement			// continue loop

.Lcell_turn_dead:
	ldr r0, [fp,#-PARAM1]			// r0 = dest
	mov r2, #0						// r2 = 0
	strb r2, [r0, r1]				// dest[curRow * nCols + i] = 0
	b .Louter_i_imcrement			// continue loop

.Lcell_keep_dead:
	ldr r0, [fp,#-PARAM1]			// r0 = dest
	mov r2, #0				// r2 = 0
	strb r2, [r0, r1]			// dest[curRow * ncols + i] = 0	

.Louter_i_imcrement:
        add r4,r4,#1                //i++
	b .Louter_i_Loop

.Lend_outer_i_loop:

	sub sp, fp, #FP_OFFSET
	pop {r4-r10, fp, lr} 			//Pop preserved registers
	bx lr
	
