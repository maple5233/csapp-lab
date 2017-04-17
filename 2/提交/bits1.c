/* 
 * CS:APP Data Lab 
 * 
 * <wanglun 1400012938@pku.edu.cn>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  /*use the character of arithmetic shift to implement the task*/
  return (x << 31) >> 31;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*try to make 2 masks to inplememt the task*/
  int faultmask = (!x << 31) >> 31;
  int realmask = ~faultmask;
  return (y & realmask) | (z & faultmask);
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  /*generate a special mask 0x55555555 to judge*/ 
  int mask = 0x55 | (0x55 << 8);
  mask |= mask << 16;
  return !((x & mask) ^ mask);
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    /*x==0||y==1*/
    return !x | y;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  /*first, use a mask to replace the byte with 0, then use | to replace the byte with c*/
  int shiftbit = n << 3;
  return x & ~(0xFF << shiftbit) | c << shiftbit;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*nothing to explain*/
  return 1 << 31;
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) { 
  /*nothing to explain||=-=*/
  return ~0;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /* if x >= 0 && y < 0, return 1;
    if x - y > 0, return 1;
    specially judge x == y; */
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int sub;
  int sign_sub;
  sub = y + ~x;
  ++sub;
  sign_sub = sub >> 31;
  return (!sign_x & sign_y) | ((sign_sub & 1) & !(sign_x & !sign_y));
}
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
  /*Firsly, judge if the second hex bit is 3;
    Then, judge if the last hex bit < A;*/
  int a = 0x9 + ~(x & 0xf);
  ++a;
  return !((x ^ (0x3 << 4)) & (~0xF)) & !(a >> 31);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
w
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
  /*First, if x is negative, change it to ~x;
    Find the most significant 1;
    Put all the lower bit to 1;
    Count the number of 1*/
  /*int m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);
  int m3 = 0x0F | (0x0F << 8);
  m3 = m3 | (m3 << 16);
  int m4 = 0xFF | (0xFF << 16);
  int m5 = 0xFF | (0xFF << 8);*/
  /*int sign_x = x>>31;
  int s;
  int mask;
  x = (x ^ sign_x);
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;
  mask = (0x11 | (0x11 << 8) | (0x11 << 16) | (0x11 << 24));
  s = x & mask;
  s = s + ((x >> 1) & mask);
  s = s + ((x >> 2) & mask);
  s = s + ((x >> 3) & mask);
  s = s + (s >> 16);
  mask = 0x0f | (0x0f << 8);
  s = (s & mask) + ((s >> 4) & mask);
  return ((s + (s >> 8)) & 0x3f) + 1;*/
  /*x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m3) + ((x >> 4) & m3);
  x = (x & m4) + ((x >> 8) & m4);
  x = (x & m5) + ((x >> 16) & m5);*/
  // return x + 1;
  int ans = 1;
  int b;
  int shift;
  x ^= (x >> 31);
  b = !(!(x >> 16));
  shift = b << 4;
  ans += shift;
  x >>= shift;
  b = !(!(x >> 8));
  shift = b << 3;
  ans += shift;
  x >>= shift;
  b = !(!(x >> 4));
  shift = b << 2;
  ans += shift;
  x >>= shift;
  b = !(!(x >> 2));
  shift = b << 1;
  ans += shift;
  x >>= shift;
  b = !(!(x >> 1));
  shift = b;
  ans += shift;
  x >>= shift;
  b = !(!x);
  shift = b;
  ans += shift;
  return ans;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  /*Almost the same as last question*/
  int a;
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;
  a = ((x >> 1) & ~(1 << 31));
  ++a;
  return ~((!x << 31) >> 31) & a;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    /*the judgement of overflow*/
    int x2 = x << 1;
    int x3 = x2 + x;
    int sign_x = x >> 31;
    int sign_x2 = x2 >> 31;
    int sign_x3 = x3 >> 31;
    int over_flow = (sign_x ^ sign_x2) | (sign_x ^ sign_x3);
    int pos_flow = over_flow & ~sign_x; 
    int neg_flow = over_flow & sign_x;
    int not_flow = ~(pos_flow | neg_flow);
    int TMax = ~0 + (1 << 31);
    int TMin = 1<<31;
    return (pos_flow & TMax) | (neg_flow & TMin) | (not_flow & x3);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  /*the judge of overflow*/
  int ans;
  int sign_x;
  int sign_y;
  int sign_ans;
  ans = x + ~y;
  ++ans;
  sign_x = x >> 31;
  sign_y = y >> 31;
  sign_ans = ans >> 31; 
  return !((sign_x ^ sign_y) & (sign_x ^ sign_ans));
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 /*judge if NaN*/
 unsigned exp = (uf >> 23) & 0xFFu;
 unsigned frac = uf & 0x7FFFFFu;
 if(frac && exp == 0xffu) return uf;
 return 0x80000000 ^ uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  /*Follow the rules of IEEE, a little bit annoying*/
  unsigned shiftLeft = 0;
  unsigned afterShift, tmp, flag;
  unsigned absX = x;
  unsigned sign = 0;
  if (!x) return 0;
  if (x < 0)  
  {  
    sign = 0x80000000;  
    absX = -x;
  }
  afterShift = absX;
  while (1)
  {
    tmp = afterShift;
    afterShift <<= 1;
    ++shiftLeft;
    if (tmp & 0x80000000) break;
  }
  if ((afterShift & 0x01ff) > 0x0100) flag = 1;  
  else if ((afterShift & 0x03ff) == 0x0300) flag = 1;  
  else flag = 0;    
  return sign + (afterShift >> 9) + ((159 - shiftLeft) << 23) + flag;  
}
