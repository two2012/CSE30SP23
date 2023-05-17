// CES30 assignment template
// 
// cse30sp23id: 
//
// Describe target Hardware to the assembler
.arch   armv6
.cpu    cortex-a53
.syntax unified
/////////////////////////////////////////////////////////

.text                       // start of the text segment
/////////////////////////////////////////////////////////
// function hashFun 
/////////////////////////////////////////////////////////
.type   hashFun, %function  // define as a function
.global hashFun             // export function name
.equ    FP_OFFSET, 28       // (regs - 1) * 4
/////////////////////////////////////////////////////////

// put any .equ for hashFun here - delete this line

/////////////////////////////////////////////////////////

hashFun:
    push    {r4-r9, fp, lr}     // use r4-r9 protected regs
    add     fp, sp, FP_OFFSET   // locate our frame pointer
    // DO NOT EDIT PROLOGUE ABOVE
    // You can use temporary r0-r3 and preserved r4-r9
    // Store return value (results) in r0
    ///////////////////////////////////////////////////////
    
    // YOUR CODE GOES HERE
    // compute hash << 6
    mov r2, r1
    lsl r2,r2, #6

    // compute hash << 16
    mov r3, r1
    lsl r3, r3, #16

    // compute c + (hash << 6) + ( hash << 16)
    add r0, r0, r2
    add r0, r0, r3

    // subtract hash to get the final result
    sub r0, r0, r1 
    
    ///////////////////////////////////////////////////////
    // DO NOT EDIT EPILOGUE BELOW
    sub     sp, fp, FP_OFFSET   // restore sp
    pop     {r4-r9, fp, lr}     // restore saved registers
    bx      lr                  // function return
    .size   hashFun,(.-hashFun)
