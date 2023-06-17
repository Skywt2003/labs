/* 
 * CS:APP Data Lab 
 * 
 * WuTian 202108060109
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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int n2 = n + n;
  int n4 = n2 + n2;
  int n8 = n4 + n4;
  return (x >> n8) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int sub1 = ~0;
  int keeper = ~(1 << 31);
  int result = (x >> n) & (keeper >> (n + sub1));
  int notn = !n;
  int flag = notn + sub1;
 return ((~flag) & x) | (flag & result);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int ret = x;
  int mask = 0;
  // 0x55555555
  mask = 0x55 + (0x55 << 8);
  mask = mask + (mask << 16);
  ret = (ret & mask) + ((ret>>1) & mask);
  // 0x33333333
  mask = 0x33 + (0x33 << 8);
  mask = mask + (mask << 16);
  ret = (ret & mask) + ((ret>>2) & mask);
  // 0x0f0f0f0f
  mask = 0x0f + (0x0f << 8) + (0x0f << 16) + (0x0f << 24);
  ret = (ret & mask) + ((ret>>4) & mask);
  // 0x00ff00ff
  mask = 0xff + (0xff << 16);
  ret = (ret & mask) + ((ret>>8) & mask);
  // 0x0000ffff
  mask = 0xff + (0xff << 8);
  ret = (ret & mask) + ((ret>>16) & mask);
  return ret;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int ret = ~x;
  ret = ret & (ret >> 16);
  ret = ret & (ret >> 8);
  ret = ret & (ret >> 4);
  ret = ret & (ret >> 2);
  ret = ret & (ret >> 1);
  return ret&1;
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
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int sub1 = ~0;
  int get_sign = 1<<31;
  int sign = (x & get_sign) >> 31;
  int not_sign = !sign;
  int power = 1 << (n + sub1);
  int sub_power = (~power) + 1;
  int result1 = !(((x + power) & get_sign) >> 31);
  int result2 = ((x + sub_power) & get_sign) >> 31;
  return (sign & result1) | (not_sign & result2);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    // Round to zero is the difficult part
    int sub1 = ~0;
    int super2sub1 = (1<<n) + sub1;
    int notn = !n;
    int flag = notn + sub1;
    int result = (x + ((x >> 31) & super2sub1)) >> n;
    return ((~flag) & x) | (flag & result);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x) + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int sub1 = ~0;
  int notx = !x;
  int flag = notx + sub1;
  int result = !(x >> 31);
  return flag & result;
  // return ((~flag) & 0) | (flag & result);
  // the first part isn't necessary
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int xxory = (x >> 31) ^ (y >> 31);
  int subx = (~x) + 1;
  int ysubx = y + subx;
  int result_1 = (x >> 31) & 1;
  int result_2 = !(ysubx >> 31);
  return (xxory & result_1) | ((~xxory) & result_2);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  // idea: 1xxxx -> 11111 -> count
  int sum = 0;
  int bit = 0;
  int len = 30;
  bit = bit | ((x>>len)&1); sum = sum + bit;
  
  return 2;
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
  unsigned change_sign = 1 << 31;
  unsigned get_exp = 0xFF << 23;
  unsigned get_frac = (~get_exp) ^ change_sign;
  if ((uf & get_exp) == get_exp && (uf & get_frac) != 0) return uf;
  return uf ^ change_sign;
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
  int bias = 127;
  unsigned tminf = 0xcf000000;
  int fix_x, sign, count, temp, i, j;
  unsigned ret;
  if (x == (1<<31)) return tminf;
  if (x == 0) return 0;
  fix_x = x;
  sign = 0;
  if (fix_x < 0) fix_x = -fix_x, sign=1;
  //printf("fix_x=%x\n",fix_x);
  count = 0;
  temp = fix_x;
  while (temp) count++, temp>>=1;
  //printf("count=%d\n",count);

  ret = sign << 31;
  ret = ret + ((count - 1 + bias) << 23);
  //printf("now ret=%x\n",ret);

  i = count-2, j = 22;
  while (i>=0 && j>=0){
    ret = ret + (((fix_x & (1 << i)) >> i) << j);
    i--; j--;
  }
  if (count-1 > 23 && (fix_x & (1 << (count-25))) && (fix_x & (1 << (count-24)))){ // may need carry
    i = 0;
    while (i <= 22){
      ret = ret ^ (1 << i);
      if (ret & (1 << i)) return ret;
      i--;
    }
    ret = ret - ((count - 1 + bias) << 23);
    ret = ret + ((count + bias) << 23);
  }
  return ret;
}
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
  unsigned neg_inf = 0xff800000;
  unsigned pos_inf = 0x7f800000;
  unsigned get_exp = 0x7f800000;
  unsigned get_frac = 0x007fffff;
  unsigned exp = (uf & get_exp) >> 23;
  unsigned frac = uf & get_frac;
  unsigned ret = uf;
  if (exp == 0xff) return uf;
  if (exp == 0){ // denomolized
    if (frac & (1<<23)){ // de -> no
      ret = ret | (1 << 23);
      return ret;
    } else {
      ret = ret - frac;
      frac = frac << 1;
      ret = ret + frac;
      return ret;
    }
  } else { // nomolized
    ret = ret - (exp << 23);
    exp++;
    if (exp > 0xff) { // no -> inf
      if (uf & (1<<31)) return neg_inf;
      else return pos_inf;
    }
    ret = ret + (exp << 23);
    return ret;
  }
  return 2;
}
