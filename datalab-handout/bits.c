/* 
 * CS:APP Data Lab 
 * 
 * tinaaaaa42
 * Update: 2/12/23
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* x^y==0 only if x==y. */
  return ~((~(~x&y))&(~(x&~y)));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* Left shift 0x1 to get 0x80000000. */
  return 0x1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/* Tmax=0x7fffffff, which is exactly the reverse of 0x8000000. */
	int plus1 = x + 1;
	int flag = x ^ (~plus1);
  return !flag & !!plus1; 
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/* whether x==0xAAAAAAAA */
	int low = 0xAA | (0xAA << 8); 
	int allOdd = low | (low << 16);
  return !((allOdd&x)^allOdd);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/* x+(-x)=2^32 */
  return (~x)+0x1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	/* Divided into 2 parts: 0x30 and less than 0xA.
	 * 4-bit numbers larger than 0x9 are either 1x1x or 11xx. */
	int flag3 = (x >> 4) ^ 0x3;
  int maskA = x & 0xA;
	int maskC = x & 0xC;
	int flagA = !(maskA ^ 0xA);
	int flagC = !(maskC ^ 0xC);
  return !(flag3 | flagA | flagC);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/* Use double !! to change x to boolean value.
	 * When x is true, all bits are 1. Else, all are 0. */
	x = !!x;
	x = ~x + 1;
  return (y&x) | (~x&z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/* x<=y only if 
	 * x y have different signs and sign of x is 1
	 * OR x y have the same sign and y-x>=0 */
	int negX = ~x + 1;    // -x
	int ysubx = y + negX; // y-x
	int signOfSub = (ysubx >> 31) & 0x1;
	int highestBit = 0x1 << 31;
	int highestOfX = x & highestBit;
	int highestOfY = y & highestBit;
	int signXor = highestOfX ^ highestOfY;
	signXor = (signXor >> 31) & 0x1;
  return (signXor & (highestOfX >> 31)) | ((!signXor) & (!signOfSub));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/* Only -0 and 0 has the same sign of 0. */
  return ((x|(~x+1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
	/* the answer equals to the index of highest bit of 1 + 1(sign) */
  int sign = x >> 31;
  int b16, b8, b4, b2, b1, b0;
	x = (sign&~x) | (~sign&x);   // change x to start with 0

  b16 = !!(x>>16) << 4;        // whether the higher 16 bits has 1
  x = x >> b16;                // if there is, right shift by 16
  b8 = !!(x>>8) << 3;          // whether the higher 8 bits now has 1
  x = x >> b8;                 // if there is , tight shift by 8
  b4 = !!(x>>4) << 2;          // whether the higher 4 bits now has 1
  x = x >> b4;                 // if there is , tight shift by 4
  b2 = !!(x>>2) << 1;          // whether the higher 2 bits now has 1
  x = x >> b2;                 // if there is , tight shift by 2
  b1 = !!(x>>1);               // whether the higher 1 bits now has 1
  x = x >> b1;                 // if there is , tight shift by 1
	b0 = x;

  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	/* if exp == 2, left shift by 1.
	 * if exp == 255, return uf 
	 * else, decide whether it would be infinate 
	 * */
	unsigned exp = (uf&0x7f800000) >> 23;
  unsigned sign = uf & (0x1 << 31);
	if (exp == 0) {
		return (uf << 1) | sign;
	}
	if (exp == 255) {
		return uf;
	}
	exp++;
	if (exp == 255) {
		return 0x7f800000 | sign;
	}
  return (exp << 23) | (uf & 0x807fffff);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	/* Classified by the value of exponent:
	 * key value: 0, 23, 31
	 * */
	unsigned sign = uf >> 31;
	unsigned exp = (uf&0x7f800000) >> 23;
	unsigned significant = (uf & 0x7fffff) | 0x800000;

	int RealExp = exp - 127;
	int result = 0;

	if (RealExp < 0) {
		return 0;
	}
	if (RealExp > 31) {
		return 0x80000000u;
	}

	if (RealExp > 23) {
		result = significant << (RealExp - 23);
	} else {
		result = significant >> (23 - RealExp);
	}

	if (sign == 1) {
		result = ~result + 1;
	}

  return result;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	/* Denorm float: 2^-149 ~ 2^-126
	 * Norm float: 2^-126 ~ 2^127
	 * */
	int exp;
	unsigned ret;

	if (x < -149) {
		return 0;
	}
	if (x > 127) {
		return 0x7f800000;
	}

	if (x < -126) {   // denorm
		return 0x1 << (x + 149);
	}
	exp = x + 127;
	ret = exp << 23;
  return ret;
}
