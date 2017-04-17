int bitXor(int x, int y) {
	return ~(~(~x & y) & ~(x & ~y));
}

int tmin(void) {
	return 1 << 31;
}

int isTmax(int x) {

	int xPlusOne = x + 1;
	int y = !(xPlusOne);
	x = x + xPlusOne;
	x = ~x;
	x = (!x)&(!y);
	return x;
}
int allOddBits(int x) {
	int y = x >> 16;
	x = x & y;  
	y = x >> 8;
	x = x & y; 
	x = (x & 0xAA);
	return  !(x ^ 0xAA); 
}
int negate(int x) {
	return ~x + 1;
}
int isAsciiDigit(int x) {
	int _zero = ~(0x30) + 1;
	int X_sub_zero = x + _zero;
	int _x = ~x + 1;
	int nine_sub_X = (0x39) + _x;
	int a = X_sub_zero >> 31;
	int b = nine_sub_X >> 31;
	return !(a | b);
}
int conditional(int x, int y, int z) {
	int a = ~!!x + 1;
	int b = ~!x + 1;
	return (a & y) | (b & z);
}
int isLessOrEqual(int x, int y) {
	int x_sign = x >> 31;
	int y_sign = y >> 31;
	int diff = x_sign&(!y_sign);
	int signSame = !(x_sign^y_sign);
	int comp = !(!((x + ~y) >> 31));
	int same = signSame&comp;
	return diff | same;
}
int logicalNeg(int x) {
	int _x = (~x + 1);
	int x_x = x | _x;
	int y = x_x >> 31;
	return y + 1;
}
int howManyBits(int x) {               
	int ans = 1;
	int bin;
	int shift;
	x ^= (x >> 31);
	bin = !(!(x >> 16));
	shift = bin << 4;
	ans += shift;
	x >>= shift;
	bin = !(!(x >> 8));
	shift = bin << 3;
	ans += shift;
	x >>= shift;
	bin = !(!(x >> 4));
	shift = bin << 2;
	ans += shift;
	x >>= shift;
	bin = !(!(x >> 2));
	shift = bin << 1;
	ans += shift;
	x >>= shift;
	bin = !(!(x >> 1));
	shift = bin;
	ans += shift;
	x >>= shift;
	bin = !(!x);
	shift = bin;
	ans += shift;
	return ans;
}
unsigned float_twice(unsigned uf) {
	int tool_for_exponent = 0x7F800000;
	unsigned exponent = uf & tool_for_exponent;
	unsigned sign = uf & 0x80000000;
	if (exponent)
	{
		if (exponent != 0x7F800000) 
		{
			uf = uf + 0x00800000;
			if (exponent == 0x7F000000) 
				uf = (uf & 0xFF800000);
		}
	}
	else
		uf = (uf << 1) | sign;
	return uf;
}
unsigned float_i2f(int x) {
	unsigned result;
	int sign = 0; 
	int tmp;
	int _frac = 0x007FFFFF;
	int flag;
	int frac = 0;
	int exponent = 0;
	if (x >> 31)
	{
		exponent = 31 + 127;
		sign = 0x80000000;
	}
	if (x << 1)
	{
		if (x < 0)
		{
			sign = 0x80000000;
			x = -x;
		}
		tmp = 30;
		while (!((x >> tmp) & 1))
			tmp--;
		exponent = tmp + 127;
		x = x << (31 - tmp);
		frac = _frac & (x >> 8);
		x = x & 0x000000FF;
		flag = x > 128 || ((x == 128) && (frac & 1));
		frac += flag;
		if (frac >> 23) {
			frac &= _frac;
			exponent += 1;
		}
	}
	result = sign;
	result = result | (exponent << 23);
	result = result | frac;
	return result;
}
int float_f2i(unsigned uf) {
	int exponent = (uf >> 23) & 0x000000FF;
	int _exponent = exponent - 127;
	int _frac = 0x007FFFFF;
	int frac = uf & _frac;

	if (!exponent)
		return 0;
	if (_exponent < 0)
		return 0;
	if (_exponent > 30)
		return 0x80000000u;
	frac = frac | 0x00800000;
	if (_exponent >= 23)
		frac = frac << (_exponent - 23);
	else
		frac = frac >> (23 - _exponent);
	if ((uf >> 31) & 1)
		return ~frac + 1;
	return frac;
}