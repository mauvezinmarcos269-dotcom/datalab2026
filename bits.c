/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x) {
        return !y;
    }

    if (!y) {
        return 0;
    }

    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result;
    int shift;

    result = (v > 0xFFFF) << 4;
    v >>= result;

    shift = (v > 0xFF) << 3;
    result |= shift;
    v >>= shift;

    shift = (v > 0xF) << 2;
    result |= shift;
    v >>= shift;

    shift = (v > 0x3) << 1;
    result |= shift;
    v >>= shift;

    shift = v > 0x1;
    result |= shift;

    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n_shift;
    int m_shift;
    int n_byte;
    int m_byte;
    int diff;

    n_shift = n << 3;
    m_shift = m << 3;

    n_byte = (x >> n_shift) & 0xFF;
    m_byte = (x >> m_shift) & 0xFF;

    diff = n_byte ^ m_byte;

    return x ^ (diff << n_shift) ^ (diff << m_shift);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result;
    int count;

    result = 0;
    count = 32;

    while (count) {
        result = (result << 1) | (v & 1);
        v >>= 1;
        count--;
    }

    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int shift;
    int zero_mask;
    int mask;

    shift = (n + ~0) & 31;
    zero_mask = ~((!n) + ~0);
    mask = (0x7FFFFFFF >> shift) | zero_mask;

    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int all_ones;
    int count;
    int step;

    all_ones = ~0;

    step = !((x >> 16) ^ all_ones) << 4;
    count = step;

    step = !((x >> (24 + ~count + 1)) ^ all_ones) << 3;
    count |= step;

    step = !((x >> (28 + ~count + 1)) ^ all_ones) << 2;
    count |= step;

    step = !((x >> (30 + ~count + 1)) ^ all_ones) << 1;
    count |= step;

    step = !((x >> (31 + ~count + 1)) ^ all_ones);
    count |= step;

    return count + !(x ^ all_ones);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign;
    unsigned abs_x;
    unsigned temp;
    unsigned result;
    unsigned extra;
    unsigned half;
    int shift;
    int r;

    if (!x) {
        return 0;
    }

    sign = x & 0x80000000;
    abs_x = x;

    if (sign) {
        abs_x = -abs_x;
    }

    temp = abs_x;
    shift = 0;

    while (temp >>= 1) {
        shift++;
    }

    if (shift < 24) {
        return sign |
               (((shift + 126) << 23) +
                (abs_x << (23 - shift)));
    }

    r = shift - 23;

    result = ((shift + 126) << 23) + (abs_x >> r);

    extra = abs_x & ((1u << r) - 1);
    half = 1u << (r - 1);

    if (extra > half) {
        result++;
    } else if (extra == half) {
        if (result & 1) {
            result++;
        }
    }

    return sign | result;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign;
    unsigned exp;
    unsigned frac;

    sign = uf & 0x80000000;
    exp = uf & 0x7F800000;
    frac = uf & 0x007FFFFF;

    if (exp == 0x7F800000) {
        return uf;
    }

    if (!exp) {
        frac <<= 1;

        if (frac & 0x00800000) {
            exp = 0x00800000;
            frac &= 0x007FFFFF;
        }

        return sign | exp | frac;
    }

    exp += 0x00800000;

    if (exp == 0x7F800000) {
        frac = 0;
    }

    return sign | exp | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign;
    unsigned exp;
    unsigned val;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7FF;

    if (exp < 1023) {
        return 0;
    }

    if (exp > 1054) {
        return 0x80000000u;
    }

    val = 0x80000000u |
          ((uf2 & 0xFFFFF) << 11) |
          (uf1 >> 21);

    val >>= 1054 - exp;

    if (sign) {
        if (val > 0x80000000u) {
            return 0x80000000u;
        }
        return -val;
    }

    if (val > 0x7FFFFFFF) {
        return 0x80000000u;
    }

    return val;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }

    if (x < -126) {
        return 1 << (x + 149);
    }

    if (x <= 127) {
        return (x + 127) << 23;
    }

    return 0x7F800000;
}
