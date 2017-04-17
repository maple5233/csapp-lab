//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	return ~(x&y)&~(~x&~y);
	
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
	return !((x + x + 2) | !(~x));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	int mask = (0xAA << 8) + 0xAA;
	mask = (mask << 16) + mask;
	return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return ~x + 1;;
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
	int y, z;

	//If y = -1, then 0x30 <= x is FALSE
	//If y =  0, then 0x30 <= x is TRUE
	y = x + (~0x2f);
	y = y >> 31;

	//If z = -1, then x <= 0x39 is FALSE
	//If z =  0, then x <= 0x39 is TRUE
	z = 58 + ~x;
	z = z >> 31;

	return !(y | z);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int mask1, mask2, val1, val2;

	mask1 = !!x;
	mask2 = ~mask1 + 1;
	val1 = mask2 & y;
	val2 = ~mask2 & z;

	return val1 + val2;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int signx = x >> 31;
	int signy = y >> 31;
	int signSame = ((x + (~y)) >> 31)&(!(signx^signy));
	int signDiffer = signx&(!signy);
	return signDiffer | signSame;
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
	return ((~(~x + 1)&(~x)) >> 31) & 1;
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

	int sign = (x >> 31) & 1;
	int signChain = ~sign + 1;
	int placeHolder = 0; /*throwaway variable for various operations*/
	int c = 2; /*counter to increment to count the bits*/
	int copy = x; /*to be used for checking if power of 2*/
	int copy2 = x; /*to be used for checking zero*/
	int tminCheck = x ^ (1 << 31);
	tminCheck = !tminCheck;
	tminCheck = ~tminCheck + 1; /*all ones if x was tmin*/

	x = (x & ~signChain) | ((~x + 1) & signChain);/*now a positive value*/
	x = x + ~0;
	x = (x | x >> 1);
	x = (x | x >> 2);
	x = (x | x >> 4);
	x = (x | x >> 8);
	x = (x | x >> 16);
	x = (x + 1); /*x is rounded up to the next power of 2*/

	/*the following chunks of code follow an algorithm that
	does five different checks, incrementing the counter
	for each check so that the result is the bit position
	of the rounded up value of x*/
	placeHolder = !(x & (0xFF | 0xFF << 8));
	placeHolder = ~placeHolder + 1;
	c += (placeHolder & 16);

	placeHolder = !(x & (0xFF | 0xFF << 16));
	placeHolder = ~placeHolder + 1;
	c += (placeHolder & 8);

	placeHolder = 0x0F | 0x0F << 8;
	placeHolder = placeHolder | placeHolder << 16;
	placeHolder = !(x & placeHolder);
	placeHolder = ~placeHolder + 1;
	c += (placeHolder & 4);

	placeHolder = 0x33 | 0x33 << 8;
	placeHolder = placeHolder | placeHolder << 16;
	placeHolder = !(x & placeHolder);
	placeHolder = ~placeHolder + 1;
	c += (placeHolder & 2);

	placeHolder = 0x55 | 0x55 << 8;
	placeHolder = placeHolder | placeHolder << 16;
	placeHolder = !(x & placeHolder);
	placeHolder = ~placeHolder + 1;
	c += (placeHolder & 1);

	/*determines if x is 0. if so, you want to return 1.*/
	copy2 = !copy2;
	copy2 = ~copy2 + 1;

	c += ~((tminCheck)& 1);

	/*add one to the count if x is a power of 2*/
	copy = copy & (copy + ~0);
	c += !copy;
	return (c & ~copy2) | (copy2 & 1);
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned f = uf;
	/* Computer 2*f. If f is a NaN, then return f. */
	if ((f & 0x7F800000) == 0){
		//shift one bit to left  
		f = ((f & 0x007FFFFF) << 1) | (0x80000000 & f);
	}
	else if ((f & 0x7F800000) != 0x7F800000){
		/* Float has a special exponent. */
		/* Increment exponent, effectively multiplying by 2. */
		f = f + 0x00800000;
	}
	return f;
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
	unsigned shiftLeft = 0;
	unsigned afterShift, tmp, flag;
	unsigned absX = x;
	unsigned sign = 0;
	//special case  
	if (x == 0) return 0;
	//if x < 0, sign = 1000...,abs_x = -x  
	if (x<0)
	{
		sign = 0x80000000;
		absX = -x;
	}
	afterShift = absX;
	//count shift_left and after_shift  
	while (1)
	{
		tmp = afterShift;
		afterShift <<= 1;
		shiftLeft++;
		if (tmp & 0x80000000) break;
	}
	if ((afterShift & 0x01ff)>0x0100)
		flag = 1;
	else if ((afterShift & 0x03ff) == 0x0300)
		flag = 1;
	else
		flag = 0;

	return sign + (afterShift >> 9) + ((159 - shiftLeft) << 23) + flag;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
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
int float_f2i(unsigned uf) {
	int exponent = (uf >> 23) & 0xff;
	int exp = exponent - 127;
	int frac = uf & 0x7fffff;

	if (exponent == 0x7F800000)
		return 0x80000000u;
	if (!exponent)
		return 0;
	if (exp < 0)
		return 0;
	if (exp > 30)
		return 0x80000000u;

	frac = frac | 0x800000;
	if (exp >= 23)
		frac = frac << (exp - 23);
	else
		frac = frac >> (23 - exp);

	if ((uf >> 31) & 1)
		return ~frac + 1;

	return frac;
}

