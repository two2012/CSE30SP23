//file header
    .arch armv6     //armv6 architecture
    .arm            //arm 32-bit IS
    .fpu vfp        //floating point co-processor
    .syntax unified //modern syntax

//definitions applying to the entire source file
    //.equ EXAMPLE_DEF, 0xff

    //.data         //uncomment if needed

    .text           //start of text segment

    .global fpconvert               //make fpconvert global for linking to
    .type   fpconvert, %function    //define fpconvert to be a function
    .equ 	FP_OFF, 32 	            //fp offset distance from sp (# of saved regs - 1) * 4

fpconvert:	
// function prologue - do not edit this part
    push    {r4-r10, fp, lr}    // save registers to stack
    add     fp, sp, FP_OFF      // set frame pointer to frame base

// you can use any of r0-r10 inclusive
// R0 is the parameter to the function
// the last value of R0 is the value
// returned from the function
// ==========================================================================
// YOUR CODE GOES IN THE SECTION BELOW
// ==========================================================================
//seperate sign bit, exponent and mantissa
    and r4, r0, 0x000007c0      //extract exponent and store in r4
    lsr r4, r4, #6              //shift exponent to the least significant bit
    and r5, r0, 0x0000003f      //extract mantissa and store in r5
    bit r0, r0, 0xfffff7ff      //clear out all bits but sign bit
    lsl r0, r0, #20             //shift sign bit to the most significant bit

//check if exponent is infinity
    cmp r4, 0x000007c0      // if (exponent == "11111")
    bne  .Lnot_infinity     // .
    bl convert_infinity     // call convert_infinity
    b .Lend                 // end if statement for infinity branch

.Lnot_infinity:             // else
    //check if exponent is zero
    cmp r4, #0              // if (exponent == 0)
    beq .Ldenormal          // it a denormalized number
    sub r4, r4 #15          // else it is a normal number so subtract 15 from exponent
    add r4, r4, #127        // add 127 to exponent
    lsl r4, r4, #23         // shift exponent to the position next to sign bit
    lsl r5, r5, #17         // shift mantissa to the position next to exponent
    b .Lend                 // end if statement for normal number branch

.Ldenormal:                 //else    

    mov r8, #0              // i = 0
    mov r7, 0x00000020      //      y = 0x00100000 (store 00100000 in r7)
.Lloop:                     // while (first bit of mantissa != 1 && i < 5)
    cmp r8, #5              //  if (i > 5)
    bgt .Lend               //      end of loop
                            //  else
    mov r6, r5              //      x = mantissa (copy mantissa to r6)
    and r6, r6, r7          //      x = x & y (and x with y)
    cmp r6, #0              //  if (x == 0)
    beq .Lnext              //      jump to lable .Lnext
                            //  else
    b .Lend                 //      end if statement for found leading 1 for mantissa

.Lnext:                     // else
    lsl r5, r5, #1          //      mantissa = mantissa >> 1 (shift x right by 1)
    add r8, r8, #1          //      i = i + 1 (increment i)
    sub r4, r4, #1          //      exponent = exponent - 1 (decrement exponent)
    b .Lloop                //      jump to lable .Lloop


.Lend:
    orr r0, r0, r4          // combine sign bit, exponent and store in r0
    orr r0, r0, r5          // combine sign bit, exponent and mantissa and store in r0

// ==========================================================================
// function epilogue - do not edit
    sub	sp, fp, FP_OFF
    pop     {r4-r10, fp, lr}     // MUST MATCH LIST IN PROLOG'S PUSH
    bx      lr                   // return

// function footer
    .size fpconvert, (. - fpconvert) // set size for function

// ==========================================================================

    .global convert_infinity
    .type   convert_infinity, %function
    .equ    FP_OFF, 32
// make a 32-bit IEEE +Inf or -Inf
convert_infinity:	
// function prologue (do not edit)
    push    {r4-r10, fp, lr}    // save regs
    add     fp, sp, FP_OFF
// you can use any of r0-r10 inclusive
// R0 is the parameter to the function
// the last value of R0 is the value
// returned from the function
// r4-r10 are local to this function
// changes to these values will not be reflected
// in the main function.

// ==========================================================================
// YOUR CODE GOES IN THE SECTION BELOW
// ==========================================================================

    mov r4, 0x000000ff      // exponent = 11111111
    lsl r4, r4, #23         // exponent = exponent << 23 (shift exponent to the position next to sign bit)
    orr r5, r5, #0          // mantissa = 0


// ==========================================================================
// function epilogue (do not edit)
    sub	sp, fp, FP_OFF
    pop     {r4-r10, fp, lr}    // restore regs
    bx      lr                  // return
// function footer
    .size convert_infinity, (. - convert_infinity)

//file footer
    .section .note.GNU-stack,"",%progbits // stack/data non-exec (linker)
.end
