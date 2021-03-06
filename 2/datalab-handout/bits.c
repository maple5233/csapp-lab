/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
 int bitXor(int x, int y) {
  return ~( ~(~x & y) & ~(x & ~y));//参考离散数学等价转换
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
 int tmin(void) {
  return 1<<31;//32位机器最小的整数当然是0x80000000
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
	//Tmax:有符号整型最大值 Umax:无符号整型最大值
	//Tmax的特别之处在于 Tmax+1+Tmax会是-1(也就是Umax) 这是因为补码表示的负数比正数多一个的原因
	//我们可以用这个验证x是不是Tmax
	//但是世界上还有一个数满足x+1+x等于-1 那就是-1本身 于是除了满足x+1+x等于-1之外 我们还要保证x不是-1 才能保证x是Tmax

    /* 验证x是不是(-1) */
    int xPlusOne = x+1;//验证是不是-1的一种方式
    int y = !(xPlusOne);//y 表示 x+1 的非
    // 把xPlusOne进行逻辑非运算  如果是1 说明xPlusOne是0  那么x为0xFFFFFFFF
    // 如果是0 那么x不为0xFFFFFFFF
    
    /* 验证(x+1)+x是不是(-1) */
    x = x+xPlusOne;//x表示 2x+1
    x = ~x;//验证是不是-1的另外一种方式
    //把它按位取反 如果是0 那么(x+1)+x就是0xFFFFFFFF(-1) 如果是1 那么就不是0xFFFFFFFF(-1)
    
    //当且仅当 x+1+x为0xFFFFFFFF且x不是0xFFFFFFFF 参数x是0x7FFFFFFF
    //也就是x==0 y==0
    
    // x = x|y;
    // x = !x;//y不成立 && x也不成立 这里才是1 其实就是用|和!实现了&
    
    x=(!x)&(!y);
    return x;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
 int allOddBits(int x) {
	//因为我们没法直接和0xAAAAAAAA比较（常量只能在0-0xff之间）
	//所以我们对x的奇数位置上的信息用与运算进行规整 (因为与运算只有两个操作数都是1的情况才为1 所以可以方便的检查是不是两个都是1)
	//直到规整到能与0xAA(0-0xff之的后八位奇数位全为1偶数位全为0的数)比较 (即后面八位包含了全部的奇数位置的信息)
	//然后我们提取x后八位里所有奇数位置上的数的信息 得到的x与0xAA比较即可
	//把十六进制每8位(两个字母)看成1个部分 分为A B C D四个部分
	//很显然我们只需要计算A&B&C&D&(0xAA) 再与0xAA比较
	//下面是全过程
	int y = x >> 16;//折半提取左十六位 把左十六位变成f或者0  (y提取了A B的信息 变为 ? ? A B）
	x = x & y;  //x的后两个字节是 对原来x的前后两半部分进行与运算的结果 (折半规整)(将A B 与 C D规整 x变为 A B A&C B&D)
	y = x >> 8;//提取A&C 这一步把A&C 放在了y的最后两个字节的位置上 即y变成 ? ? ? A&C 而x为A B A&C B&D
	x = x & y;  //这一步前面二十四位的变化我们不考虑 后面八位就是A&B&C&D 即x为 ? ? ? A&B&C&D
	x = (x & 0xAA);//提取后八位所有奇数位置 后八位偶数位置全部变成0 其他位全1 x为 FF FF FF A&B&C&D&(0xAA)
	return  !(x ^ 0xAA); //比较x是否和0xAA即(24个1后面跟着)10101010相等

	//（其实我们可以换一种思路 用0不断的+A再<<4构造出一个变量 值为0xAAAAAAAA 这样也就能直接和x比较了）
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
 int negate(int x) {
	//求相反数即取反+1
	return ~x + 1;//当然这里有个漏洞 就是0x80000000(Tmin)的相反数是不能这么算的 因为0x80000000(Tmin)的相反数无法用int型表示 Tmin取反加1后还是它自己
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to 
'9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
 int isAsciiDigit(int x) {
	int _zero = ~(0x30) + 1;//-'0'
	int X_sub_zero=x+_zero;//x-'0'
	int _x = ~x + 1;//-x
	int nine_sub_X=(0x39)+_x;//'9'-x
	int a = X_sub_zero >> 31;//x-'0'的符号位;
	int b = nine_sub_X >> 31;//'9'-x的符号位;
	//要求两个符号位都为0;
	return !(a | b);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
 int conditional(int x, int y, int z) {
	//!!x  			 在x不为0时 为1，  x为0时 为0;
	//~!!x 			 在x不为0时 为-2， x为0时 为-1;
	//从而a=~!!x + 1 在x不为0时 为-1， x为0时 为0;
	//而 !x，~!x，~!x + 1和上面3个正好相反;
	//从而：
	int a = ~!!x + 1;//x假 -> 0 		x真 -> -1
	int b = ~!x + 1;// x假 -> -1 	x真 -> 0
	// 0=0x00000000 -1=0xffffffff
	// &运算的特性是 有0则0 那么对于任意的t有t&0=0 t&(-1)=x
	// a b肯定1个是0 1个是-1  
	// 这样 a&y b&z肯定1个不变（在接下来的|运算中保留） 一个是0（在接下来的|运算中消失）
	return (a & y) | (b & z);
	
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
// int isLessOrEqual(int x, int y) {
// 	/** 考虑x==y的情况 **/
// 	int isEqual = !(x^y);//如果为1则x==y;
// 	/** 考虑x<y且x不为0x80000000的情况 **/
// 	int _x = ~x + 1;//-x 除了0x80000000都可以这么算
// 	int y_sub_x = y + _x;//y-x
// 	int sub_result_sign = y_sub_x >> 31;//y-x的符号位;如果为0则y>x;
// 	/** 考虑x为0x80000000且y不是的情况 **/
// 	/** 当x正y负的时候  或者x负y正的时候 y+_x可能溢出 所以 要考虑溢出的情况**/
// 	int x_sign = x >> 31;
// 	int y_sign = y >> 31;
// 	int diff = x_sign&(!y_sign);//仅在x负y正的时候取1;
// 	int _diff = (!x_sign)&y_sign;//仅在x正y负的时候取1;
// 	return (isEqual | (!sub_result_sign) | diff)&(!_diff);
// 	//上述方法太麻烦了。。。先放这里 以后思考如何优化。。
// }
//以下是优化版本：
 int isLessOrEqual(int x, int y) {
   int x_sign = x >> 31;
   int y_sign = y >> 31;
	/** 如果符号位不相同 那么当且仅当x负y正的时候 x<y 返回1 **/
	int diff = x_sign&(!y_sign);//仅在x负y正的时候取1;
	/** 如果符号位相同 那么可以通过(x+(~y))>>31的值来判断小于等于 **/
	int signSame = !(x_sign^y_sign);//保证符号位相同;
	int comp = !(!((x + ~y) >> 31));//双重!强制转为0或1; 这里是用x+~y而不是x+(~y+1)是因为这是x<=y而不是x<y
	int same = signSame&comp;
	return diff | same;
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
	//在c里面 当且仅当x为0 !x才为1;
	int _x = (~x + 1);//只要x不是0 x和_x就有一个是负数;
	int x_x = x | _x;//这样x|_x就一定是个负数;
	int y = x_x>>31;//这样y就肯定是-1(0xFFFFFFFF);
	return y+1;
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
    //对于正数而言是不断右移直到结果为0 右移的次数 再+1 其实就是⌊log2(x)⌋+2;
    //观察发现 对于负数而言是不断右移直到结果为-1 右移的次数 再+1;对负数按位取反后 结果和对应的正数的位数一样是⌊log2(x)⌋+2;
    //补码总是这样 对称轴在0和-1之间(因为补码能表示的负数比正数多一个 不像反码 对称轴是+0和-0之间) 处于对称轴两边的数 是按位取反关系;                   
    int ans = 1;//先把最后的1加上;
    int bin;
    int shift;//记录左移次数;
    x ^= (x >> 31);//对于正数x而言 符号位是0 异或操作不改变x的值 对于负数x 符号位是1 相当于按位取反得到~x;
    //经过上述处理 x无论是不是负数 都变成了对应的正数 可以用⌊log2(x)⌋+2(⌊⌋是下取整的意思)来计算需要的位数;
    //以下用折半策略法计算⌊log2(x)⌋+1;也就是正数的二进制补码去掉前面所有的0之后的长度;
    //(采用一次一次右移验证右移后结果是不是0的方法固然可以 但是毕竟太繁琐（总共要考虑16次...在不能写循环的情况下代码量巨大） 所以我们可以进行折半策略尝试;)

    bin = !(!(x >> 16));//bin标志了x长度折半之后是不是0;这是第一次折半尝试判断;
    shift = bin << 4;//如果折半结果不是0 则这是第一次折半的长度;如果折半后是0 说明折太多了 shift为0 我们后面的动作取消 等待下次折半尝试判断;
    ans += shift;//既然折半后还不是0我们就理所应当地把折半长度16加上;
    x >>= shift;//如果折半后不为0 则对x进行折半 如果为0 我们就啥也不做 等待下次折半判断;

    bin = !(!(x >> 8));//bin标志了x长度折半之后是不是0;这是第二次折半尝试判断;
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

    bin = !(!x);//这是最后一次折半判断;
    shift = bin;
    ans += shift;
    return ans;
}
//float
/*
* float_twice - Return bit-level equivalent(等值) of expression 2*f for
*   floating point argument(参数) f.
*   Both the argument and result are passed as unsigned int' s, but
*   they are to be interpreted(解释) as the bit-level representation of
*   single-precision(单精度) floating point values.
*   When argument is NaN, return argument
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 30
*   Rating: 4
*/
unsigned float_twice(unsigned uf) {//用32位的unsigned来表示浮点数 左起第1位是符号位 第2-9位是阶码 剩下是尾数;
	//要将浮点数加倍 只需要将其阶码+1;但要考虑IEEE754标准对于浮点数的规定;
	int tool_for_exponent = 0x7F800000;//提取阶码用 这个数2-9位是1 其他位为0; 同时也是浮点数的最大阶码;
	unsigned exponent = uf & tool_for_exponent;//提取阶码部分;
	unsigned sign = uf & 0x80000000;//提取符号位;
	if (exponent)//如果阶码E不为0 
	//IEEE754标准：阶码E应在1-254之间 E(阶码)和M(尾数)都为0表示±0 E为255且M为0则表示±∞ E为255且M不为0则为NaN E为0而M非0为非规格化数;
	{
		if (exponent != 0x7F800000) //排除E=255即NaN和±∞的情况;
		{
			uf = uf + 0x00800000;//阶码+1;
			if (exponent == 0x7F000000) //如果加完1阶码变为11111110(254) 下次再+1就会上溢变成±∞ 所以这里尾数要置为0 否则下次阶码+1会变成NaN;
				uf = (uf & 0xFF800000);//符号位和阶码不变 尾数置为0(达到上溢边界);
		}
		//如果if不成立即E=255 则浮点数为±∞或NaN 直接返回不做处理;
	}
	else//E=0 M为0的话应返回0 正0是全0 负0是符号位1其他全0 M不为0则是非规格化数 本应在价码处+1 现在处理为尾数加倍
	    uf = (uf << 1) | sign;//左移一位(尾数加倍) 符号位强制置为原来的符号位;
	return uf;
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
	//把一个int型的转化为unsigned表示的float;
	unsigned result;
	int sign = 0; //符号位;
	int tmp;//尾数乘以2的tmp次方
	int _frac = 0x007FFFFF;//尾数部分全为1;阶码和符号位为0;此为只保留尾数部分的掩码;
	int flag;//尾数超过23位的部分是否进位的标志;
	int frac=0;//尾数部分;
	int exponent = 0;//阶码设置为0;
	if (x >> 31)//考虑Tmin的情况;
	{
		exponent = 31 + 127;//阶码为158(0x9e);
		sign = 0x80000000;
	}
	if (x << 1) //x不是0也不是Tmin;
	{ 
		/** 预处理 **/
		if (x < 0)
		{
			sign = 0x80000000;
			x = -x;//转化为正数以便规格化;符号位已经被保存了;
		}	
		
		/** 计算阶码 **/
		tmp = 30;//作为32位整型不应该超过30;
		while (!((x >> tmp) & 1))
			tmp--;
		exponent = tmp + 127;//加上偏移量;
		
		/** 计算尾数并使其归位 **/
		x = x << (31 - tmp);//把x左边的零全部移到右边;
		//即把尾数都移到了无符号数的最左边 对于那些尾数相同的数 （如100 200 400）; 
		//这里得到的x是相同的 而且左起第一位都是1 （如都是0xc80000000）;
		frac = _frac & (x >> 8);//尾数归位 x>>8把尾数的第一位放在阶码的最后一位（这一位会被省略）上;
		//这样和取尾数掩码_frac做且运算时 会省略最前面的1 截取尾数第一位之后的部分;
		x = x & 0x000000FF;//只保留后八位;尾数长达25-32位时,这个值将是尾数的最后几位;IEEE754标准的尾数只有23位最长;
		//因此超过了23位的部分要截取下来 判断是否要进位;
		flag = x > 128 || ((x == 128) && (frac & 1));//如果上面的x不是0这里才有意义;
		//附加位即x的左起第1-2位;
		//若x>128 也就是附加位为11 入;
		//若x<128 即附加位为01 舍;
		//若x==128 即附加位为10 应强迫为偶数 看尾数的第23位是不是1 是1就进位 使得结果为偶数 是0 本来就是偶数 就舍去; 
		frac += flag;
		if (frac >> 23) {
			frac &= _frac;
			exponent += 1;
		}//考虑由进位导致的阶码增加 和尾数变化;
	}
	result = sign;//符号位赋值; 如果有强迫症可改为 result = result | sign;
	result = result | (exponent << 23);//阶码赋值;
	result = result | frac;//尾数赋值;
	return result;
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
	int exponent = (uf >> 23) & 0x000000FF;//取得阶码;
	int _exponent = exponent - 127;//还原阶码;
	int _frac = 0x007FFFFF;//尾数掩码;
	int frac = uf & _frac;//取得尾数;

	if (!exponent)//E为0且M为0表示正负0;
		return 0;
	if (_exponent < 0)//下溢出;
		return 0;
	if (_exponent > 30)//上溢出;整型最多2的31次方减去1,所以这里最多30;
		return 0x80000000u;
	frac = frac | 0x00800000;//还原尾数最前面的1;
	//现在frac刚好处于尾数的23次方的位置上（相当于阶码为23的情况）;
	//应按照 实际阶码 将尾数部分整体向左（阶码大于23）或向右移动（阶码小于23）;移动长度为数轴上_exponent和23的距离;
	if (_exponent >= 23)
		frac = frac << (_exponent - 23);
	else
		frac = frac >> (23 - _exponent);

	if ((uf >> 31) & 1)//负数;
		return ~frac + 1;

	return frac;
}
