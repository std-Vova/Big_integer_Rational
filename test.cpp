#include "pch.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <time.h>

#include "gtest/gtest.h"

//#include "big_integer.h"
#include "../big_integer.h"




TEST(correctness, from_int)
{
    
    std::vector<int> values = { 0, 999'999'999, 1'000'000'000, 1'000'010'090, 2'000'000'000, 2'000'010'090,
                              -1, -999'999'999,  -1'000'000'000, -1'000'010'090, -2'000'000'000, -2'000'010'090
    };

    for (auto val : values)
    {
        EXPECT_EQ(std::to_string(val), big_integer(val).to_string());
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int64_t> dist(std::numeric_limits<int64_t>::min());

    
    for (size_t i = 0; i < 5; ++i)
    {
        int val = dist(gen);
        EXPECT_EQ(std::to_string(val), big_integer(val).to_string());
    }
    
}

TEST(correctness, from_double) {

    std::vector<double> vec = { 123.123, -123.123, 0.0, 123.123e+15, 123.123e-15, 0.123e-15,
        1.123e+15, -0.123e-15, -0.123e+15 };

    for (auto value : vec) {
        long long item = value;
        big_integer big = value;
        EXPECT_EQ(item, big);
    }
}

TEST(correctness, two_plus_two) {
    EXPECT_EQ(big_integer(4), big_integer(2) + big_integer(2));
    EXPECT_EQ(4, big_integer(2) + 2); // implicit conversion from int must work
    EXPECT_EQ(4, 2 + big_integer(2));
}


TEST(correctness, default_ctor) {
    big_integer a;
    big_integer b = 0;
    EXPECT_EQ(0, a);
    EXPECT_EQ(b, a);
}



TEST(correctness, ctor_limits) {
    big_integer a = std::numeric_limits<int>::min();
    big_integer b = std::numeric_limits<int>::max();
    EXPECT_EQ(-1, a + b);
}

TEST(correctness, copy_ctor) {
    big_integer a = 3;
    big_integer b = a;

    EXPECT_EQ(b, a);
    EXPECT_EQ(3, b);
}

TEST(correctness, copy_ctor_real_copy) {
    big_integer a = 3;
    big_integer b = a;
    a = 5;

    EXPECT_EQ(3, b);
}

TEST(correctness, copy_ctor_real_copy2) {
    big_integer a = 3;
    big_integer b = a;
    b = 5;

    EXPECT_EQ(3, a);
}


TEST(correctness, ctor_invalid_string) {
    EXPECT_THROW(big_integer("abc"), std::invalid_argument);
    EXPECT_THROW(big_integer("123x"), std::invalid_argument);
    EXPECT_THROW(big_integer(""), std::invalid_argument);
    EXPECT_THROW(big_integer("-"), std::invalid_argument);
    EXPECT_THROW(big_integer("-x"), std::invalid_argument);
    EXPECT_THROW(big_integer("123-456"), std::invalid_argument);
    EXPECT_THROW(big_integer("--5"), std::invalid_argument);
    EXPECT_THROW(big_integer("++5"), std::invalid_argument);
}

TEST(correctness, assignment_operator) {
    big_integer a = 4;
    big_integer b = 7;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, self_assignment) {
    big_integer a = 5;
    a = a;

    EXPECT_TRUE(a == 5);
}

TEST(correctness, assignment_return_value) {
    big_integer a = 4;
    big_integer b = 7;
    (a = b) = a;

    EXPECT_TRUE(a == 7);
    EXPECT_TRUE(b == 7);
}

TEST(correctness, comparisons) {
    big_integer a = 100;
    big_integer b = 100;
    big_integer c = 200;
    big_integer d = -1;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(d != 0);
}

TEST(correctness, compare_zero_and_minus_zero) {
    big_integer a;
    big_integer b = -a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, add) {
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_TRUE(a + b == 25);

    a += b;
    EXPECT_TRUE(a == 25);
}

TEST(correctness, add_signed) {
    big_integer a = 5;
    big_integer b = -20;
    EXPECT_TRUE(a + b == -15);

    a += b;
    EXPECT_TRUE(a == -15);
}

TEST(correctness, add_return_value) {
    big_integer a = 5;
    big_integer b = 1;

    (a += b) += b;
    EXPECT_EQ(7, a);
}

TEST(correctness, sub) {
    big_integer a = 20;
    big_integer b = 5;

    EXPECT_TRUE(a - b == 15);

    a -= b;
    EXPECT_TRUE(a == 15);
}

TEST(correctness, sub_signed) {
    big_integer a = 5;
    big_integer b = 20;

    EXPECT_TRUE(a - b == -15);

    a -= b;
    EXPECT_TRUE(a == -15);

    a -= -100;
    EXPECT_TRUE(a == 85);
}

TEST(correctness, sub_return_value) {
    big_integer a = 5;
    big_integer b = 1;

    (a -= b) -= b;
    EXPECT_EQ(3, a);
}

TEST(correctness, mul) {
    big_integer a = 5;
    big_integer b = 20;
    EXPECT_TRUE(a * b == 100);

    a *= b;
    EXPECT_TRUE(a == 100);
}

TEST(correctness, mul_signed) {
    big_integer a = -5;
    big_integer b = 20;

    EXPECT_TRUE(a * b == -100);

    a *= b;
    EXPECT_TRUE(a == -100);
}

TEST(correctness, mul_return_value) {
    big_integer a = 5;
    big_integer b = 2;

    (a *= b) *= b;
    EXPECT_EQ(20, a);
}

TEST(correctness, div_) {
    big_integer a = 20;
    big_integer b = 5;
    big_integer c = 20;
    EXPECT_EQ(0, b / c);
    EXPECT_TRUE(a / b == 4);
    EXPECT_TRUE(a % b == 0);

    a /= b;
    EXPECT_TRUE(a == 4);

    c %= b;
    EXPECT_TRUE(c == 0);
}

TEST(correctness, div_int_min) {
    big_integer a = std::numeric_limits<int>::min();
    EXPECT_TRUE((a / a) == (a / std::numeric_limits<int>::min()));
}


TEST(correctness, div_int_min_2) {
    big_integer a = std::numeric_limits<int>::min();
    big_integer b = -1;
    big_integer c = a / b;
    EXPECT_TRUE(c == (a / -1));
    EXPECT_TRUE((c - std::numeric_limits<int>::max()) == 1);
}

TEST(correctness, div_signed) {
    big_integer a = -20;
    big_integer b = 5;

    EXPECT_TRUE(a / b == -4);
    EXPECT_TRUE(a % b == 0);
}

TEST(correctness, div_rounding) {
    big_integer a = 23;
    big_integer b = 5;

    EXPECT_TRUE(a / b == 4);
    EXPECT_TRUE(a % b == 3);
}

TEST(correctness, div_rounding_negative) {
    big_integer a = 23;
    big_integer b = -5;
    big_integer c = -23;
    big_integer d = 5;

    EXPECT_TRUE(a / b == -4);
    EXPECT_TRUE(c / d == -4);
    EXPECT_TRUE(a % b == 3);
    EXPECT_TRUE(c % d == -3);
}

TEST(correctness, div_return_value) {
    big_integer a = 100;
    big_integer b = 2;

    (a /= b) /= b;
    EXPECT_EQ(25, a);
}

TEST(correctness, unary_plus) {
    big_integer a = 123;
    big_integer b = +a;

    EXPECT_TRUE(a == b);

    // this code should not compile:
    // &+a;
}

TEST(correctness, negation) {
    big_integer a = 666;
    big_integer b = -a;

    EXPECT_TRUE(b == -666);
}

TEST(correctness, negation_int_min) {
    big_integer a = std::numeric_limits<int>::min();
    big_integer b = -a;

    EXPECT_EQ(b - 1, std::numeric_limits<int>::max());
}

TEST(correctness, increment) {
    big_integer a = 42;
    big_integer pre = ++a;
    big_integer post = a++;

    EXPECT_EQ(43, pre);
    EXPECT_EQ(43, post);
}

TEST(correctness, decrement) {
    big_integer a = 42;
    big_integer pre = --a;
    big_integer post = a--;

    EXPECT_EQ(41, pre);
    EXPECT_EQ(41, post);
}

TEST(correctness, add_long) {
    big_integer a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("10000000000000000000000000000000000000000000000000000100000000"
        "000000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(correctness, add_long_signed) {
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("10000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000");

    EXPECT_EQ(0, a + b);
}

TEST(correctness, add_long_signed2) {
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("-9999999999999999999999999999999999999999999999999999000000000"
        "00000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(correctness, add_long_pow2) {
    big_integer a("18446744073709551616");
    big_integer b("-18446744073709551616");
    big_integer c("36893488147419103232");

    EXPECT_EQ(c, a + a);
    EXPECT_EQ(a, b + c);
    EXPECT_EQ(a, c + b);
}

TEST(correctness, sub_long) {
    big_integer a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("99999999999999999999999999999999999999999999999999999000000000"
        "00000000000000000000000000000");

    EXPECT_EQ(c, a - b);
}

TEST(correctness, sub_long_pow2) {
    big_integer a("36893488147419103232");
    big_integer b("36893488147419103231");

    EXPECT_EQ(1, a - b);
}

TEST(correctness, mul_long) {
    big_integer a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000"
        "00000000000000000000000000000000000000");

    EXPECT_EQ(c, a * b);
}

TEST(correctness, mul_long_signed) {
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("-1000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000"
        "00000000000000000000000000000000000000");

    EXPECT_EQ(c, a * b);
}

TEST(correctness, mul_long_signed2) {
    big_integer a("-100000000000000000000000000");
    big_integer c("100000000000000000000000000"
        "00000000000000000000000000");

    EXPECT_EQ(c, a * a);
}

TEST(correctness, mul_long_pow2) {
    big_integer a("18446744073709551616");
    big_integer b("340282366920938463463374607431768211456");
    big_integer c("11579208923731619542357098500868790785326998466564056403945758"
        "4007913129639936");

    EXPECT_EQ(b, a * a);
    EXPECT_EQ(c, b * b);
}

TEST(correctness, div_0_long) {
    big_integer a;
    big_integer b("100000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(a, a / b);
}

TEST(correctness, div_long) {
    big_integer a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a / b);
}

TEST(correctness, div_long_signed) {
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000");
    big_integer b("100000000000000000000000000000000000000");
    big_integer c("-100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a / b);
}

TEST(correctness, div_long_signed2) {
    big_integer a("-1000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000");
    big_integer b("-100000000000000000000000000000000000000");
    big_integer c("100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a / b);
}

TEST(correctness, negation_long) {
    big_integer a("10000000000000000000000000000000000000000000000000000");
    big_integer c("-10000000000000000000000000000000000000000000000000000");


    EXPECT_EQ(a, -c);
    EXPECT_EQ((-a).to_string(), "-10000000000000000000000000000000000000000000000000000");
}

TEST(correctness, negation_long2) {
    big_integer a("10000000000000000000000000000000000000000000000000000");
    big_integer c("-10000000000000000000000000000000000000000000000000000");
    
    EXPECT_EQ(-a, c);
}

TEST(correctness, negation_long3) {
    big_integer a("10000000000000000000000000000000000000000000000000000");
    big_integer c("-10000000000000000000000000000000000000000000000000000");

    EXPECT_EQ((- (-(-c))).to_string(), "10000000000000000000000000000000000000000000000000000");
}



TEST(correctness, string_conv) {
    EXPECT_EQ("100", big_integer("100").to_string());
    EXPECT_EQ("100", big_integer("0100").to_string());
    EXPECT_EQ("0", big_integer("0").to_string());
    EXPECT_EQ("0", big_integer("-0").to_string());
    EXPECT_EQ("-1000000000000000", big_integer("-1000000000000000").to_string());

    big_integer lim = std::numeric_limits<int32_t>::max();
    EXPECT_EQ("2147483647", lim.to_string());
    lim++;
    EXPECT_EQ("2147483648", lim.to_string());
    lim = std::numeric_limits<int32_t>::min();
    EXPECT_EQ("-2147483648", lim.to_string());
    lim--;
    EXPECT_EQ("-2147483649", lim.to_string());
}

namespace
{
    template <typename T>
    void test_converting_ctor(T value) {
        using std::to_string;
        big_integer bi = value;
        big_integer a = 400000000000LL;
        EXPECT_EQ(to_string(value), bi.to_string());
    }
} // namespace

TEST(correctness, converting_ctor) {
    using std::numeric_limits;
    
    test_converting_ctor(numeric_limits<short>::min());
    test_converting_ctor(numeric_limits<short>::max());
    test_converting_ctor(numeric_limits<unsigned short>::min());
    test_converting_ctor(numeric_limits<unsigned short>::max());
    
    test_converting_ctor(numeric_limits<int>::min());
    test_converting_ctor(numeric_limits<int>::max());
    test_converting_ctor(numeric_limits<unsigned>::min());
    test_converting_ctor(numeric_limits<unsigned>::max());
 
    test_converting_ctor(numeric_limits<long>::min());
    test_converting_ctor(numeric_limits<long>::max());
    test_converting_ctor(numeric_limits<unsigned long>::min());
    test_converting_ctor(numeric_limits<unsigned long>::max());

    
    test_converting_ctor(numeric_limits<long long>::min());
    test_converting_ctor(numeric_limits<long long>::max());
    test_converting_ctor(numeric_limits<unsigned long long>::min());
    test_converting_ctor(numeric_limits<unsigned long long>::max());
    
}


 
TEST(correctness, converting_ctor2) {
    big_integer a(1);
    big_integer b(1U);
    big_integer c(1L);
    big_integer d(1UL);
    big_integer e(1LL);
    big_integer f(1ULL);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a == d);
    EXPECT_TRUE(a == e);
    EXPECT_TRUE(a == f);
}

TEST(correctness, converting_ctor3) {
    big_integer a(-1);
    big_integer b(-1L);
    big_integer c(-1LL);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
}

TEST(correctness, ctor_long_long) {
    auto num = static_cast<long long>(-1U) << 32;
    big_integer bignum(num);
    EXPECT_EQ(bignum.to_string(), std::to_string(num));
}

TEST(correctness, operator_div_ost) {
        srand(time(0));
        int e;
        big_integer big;
        for (int i = 0; i < 1000; ++i)
        {
            long long z = -1505 + rand() % ((650 + 1) + 1507);
            big = z;
            e = -63218 + rand() % ((78931 + 1) + 15784);
            if (e == 0)
                continue;
            EXPECT_EQ(z % e, big % e);
        }
}

TEST(correctness, operator_div) {
    srand(time(0));
    int e;
    big_integer big;
    for (int i = 0; i < 1000; ++i)
    {
        long long z = -10000 + rand() % ((10000 + 1) + 10000);
        big = z;
        e = -100 + rand() % ((100 + 1) + 100);
        if (e == 0)
            continue;
        EXPECT_EQ(z / e, big / e);
    }
}
 
//                                      RATIONAL 

double random2(double max, double min) {
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

TEST(correctness, from_double_rational)
{

    std::vector<double> values = { 0.999, 999'999'999.999, 1'000'000'000.999, 1'000'010'090.999, 2'000'000'000.999, 2'000'010'090.999,
                              -1.900, -999'999'999.999,  -1'000'000'000.999, -1'000'010'090.999, -2'000'000'000.999, -2'000'010'090.999
    };

    for (auto val : values)
    {
        std::string temp = std::to_string(val);
        while (temp.back() == '0')
            temp.pop_back();
        std::string rat = rational(val).to_string();

        EXPECT_EQ(temp, rat);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int64_t> dist(std::numeric_limits<int64_t>::min());


    for (size_t i = 0; i < 5; ++i)
    {
        int val = dist(gen);
        EXPECT_EQ(std::to_string(val), rational(val).to_string());
    }

}

TEST(correctness, ctor_from_double2_rational) {
    std::vector<double> values = { 0, 3.090'909'090'909'094, 1'000'000'000'000'0.1, -0.123, 123.123'123,
        123'123'123'123.131'23, 1.231'233e+10, -124e+10, 0.126'123'456'789'789e+40, -0.123e-40, 1'000'000'000.999,
        1.999'999'999'999'999, 1999'999'999'999'999.0, 5.7, 1.7 };

    for (auto val : values)
    {
        rational rat = val;
        EXPECT_EQ(val, rat);
    }
}

TEST(correctness, ctor_form_double3_rational) {
    for (int i = 0; i < 500; ++i) {
        double d = random2(-123.33,123.44);
        rational rat = d;

        EXPECT_EQ(rat, d);
    }
}

TEST(correctness, two_plus_two_double_rational) {
    EXPECT_EQ(rational(4.4), rational(2.2) + rational(2.2));
    EXPECT_EQ(4.4, rational(2.2) + 2.2); // implicit conversion from double must work
    EXPECT_EQ(4.4, 2.2 + rational(2.2));
}

TEST(correctness, default_ctor_rational) {
    rational a;
    rational b = 0;
    EXPECT_EQ(0, a);
    EXPECT_EQ(b, a);
}

TEST(correctness, ctor_limits_rational) {
    rational a = std::numeric_limits<double>::max();
    rational b = -a;
    EXPECT_EQ(0, a + b);
}

TEST(correctness, copy_ctor_rational) {
    rational a = 3.3;
    rational b = a;

    EXPECT_EQ(b, a);
    EXPECT_EQ(3.3, b);
}

TEST(correctness, copy_ctor_real_copy_rational) {
    rational a = 3.3;
    rational b = a;
    a = 5.5;

    EXPECT_EQ(3.3, b);
}

TEST(correctness, copy_ctor_real_copy2_rational) {
    rational a = 3.3;
    rational b = a;
    b = 5.5;

    EXPECT_EQ(3.3, a);
}

TEST(correctness, ctor_invalid_string_rational) {
    EXPECT_THROW(rational("abc"), std::invalid_argument);
    EXPECT_THROW(rational("123x"), std::invalid_argument);
    EXPECT_THROW(rational(""), std::invalid_argument);
    EXPECT_THROW(rational("-"), std::invalid_argument);
    EXPECT_THROW(rational("-x"), std::invalid_argument);
    EXPECT_THROW(rational("123-456"), std::invalid_argument);
    EXPECT_THROW(rational("--5"), std::invalid_argument);
    EXPECT_THROW(rational("++5"), std::invalid_argument);
}

TEST(correctness, assignment_operator_rational) {
    rational a = 4;
    rational b = 7;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, self_assignment_rational) {
    rational a = 5;
    a = a;

    EXPECT_TRUE(a == 5);
}

TEST(correctness, assignment_return_value_rational) {
    rational a = 4;
    rational b = 7;
    (a = b) = a;
  
    EXPECT_TRUE(a == 7);
    EXPECT_TRUE(b == 7);
}

TEST(correctness, comparisons_rational) {
    rational a = 100.111;
    rational b = 100.111;
    rational c = 200.222;
    rational d = -1.1;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(d != 0);
}

TEST(correctness, comparison_rational) {
    srand((unsigned int)time(0));

    for (int i = 0; i < 5; ++i) {
        double temp = random2(-158.3, 157.4);
        double temp2 = random2(-158.3, 157.4);
         
        rational rat = temp2;
        EXPECT_TRUE((temp2 < temp) == (rat < temp));
        EXPECT_TRUE((temp2 <= temp) == (rat <= temp));
        EXPECT_TRUE((temp2 > temp) == (rat > temp));
        EXPECT_TRUE((temp2 >= temp) == (rat >= temp));
        EXPECT_TRUE((temp2 == temp) == (rat == temp));
        EXPECT_TRUE((temp2 != temp) == (rat != temp));
        EXPECT_TRUE((temp2 <=> temp) == (rat <=> temp));
    }
}

TEST(correctness, operator_equal_rational) {
        srand((unsigned int)time(0));
        for (int i = 0; i < 2; ++i) {
            double temp = random2(-158.345, 157.44);
            double temp2 = temp;
            rational rat = temp;

            EXPECT_TRUE((temp == temp2), (temp == rat));
        }
}

TEST(correctness, operator_double_equal_rational) {
    srand((unsigned int)time(0));
    double temp = 1234.1234567;
    rational r = temp;
    double temp2 = static_cast<double>(r);

    EXPECT_DOUBLE_EQ(temp, temp2);
}

TEST(correctness, operator_less_or_equal_rational) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 2; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = temp;
        rational rat = temp;

        EXPECT_TRUE((temp <= temp2), (temp <= rat));
    }
}

TEST(correctness, operator_double_less_or_equal_rational) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 2; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);
        rational rat = temp2;
        double temp3 = static_cast<double>(rat);

        EXPECT_EQ((temp <= temp2), (temp <= temp3));
    }
}

TEST(correctness, operator_greater_or_equal_rational) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 2; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = temp;
        rational rat = temp;

        EXPECT_TRUE((temp >= temp2), (temp >= rat));
    }
}

TEST(correctness, operator_double_greater_or_equal_rational) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 5; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);
        rational rat = temp2;
        double temp3 = static_cast<double>(rat);

        EXPECT_EQ((temp >= temp2), (temp >= temp3));
    }
}

TEST(correctness, operator_not_equal_rational) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 5; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = temp;
        rational rat = temp;

        EXPECT_FALSE((temp != temp2), (temp != rat));
    }
}

TEST(correctness, operator_double_not_equal_rational) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 5; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);
        rational rat = temp2;
        double temp3 = static_cast<double>(rat);

        EXPECT_EQ((temp != temp2), (temp != temp3));
    }
}


TEST(correctness, compare_zero_and_minus_zero_rational) {
    rational a;
    rational b = -a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, add_rational) {
    rational a = 5.5;
    rational b = 20.6;

    EXPECT_EQ(a + b, 26.1);

    a += b;
    EXPECT_EQ(a, 26.1);
}

TEST(correctness, add_signed_rational) {
    rational a = 5.7;
    rational b = -20.6;
    EXPECT_EQ(a + b, -14.9);
}

TEST(correctness, add_return_value_rational) {
    rational a = 5.2;
    rational b = 1.2;

    (a += b) += b;
    EXPECT_EQ(7.6, a);
}


TEST(correctness, sub_rational) {
    rational a = 20.5;
    rational b = 5.7;

    EXPECT_EQ(a - b, 14.8);

    a -= b;
    EXPECT_EQ(a, 14.8);
}

TEST(correctness, sub_signed_rational) {
    rational a = 5.6;
    rational b = 20.3;

    EXPECT_EQ(a - b, -14.7);

    a -= b;
    EXPECT_EQ(a, -14.7);

    a -= -100;
    EXPECT_EQ(a, 85.3);
}

double round_(double d, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        d *= 10;
    }
    double temp = round(d);
    for (size_t i = 0; i < count; ++i) {
        temp /= 10;
    }
    return temp;
}

 
TEST(correctness, rational_adding) {
    rational a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000.55");
    rational b("100000000000000000000000000000000000000");
    rational c("10000000000000000000000000000000000000000000000000000100000000"
        "000000000000000000000000000000.55");

    EXPECT_EQ(c, a + b);
}

TEST(correctness, rational_adding_long_signed) {
    rational a("-1000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000.55");
    rational b("100000000000000000000000000000000000000.55");
    rational c("-9999999999999999999999999999999999999999999999999999000000000"
        "00000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(correctness, rational_sub) {
    rational a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000.55");
    rational b("100000000000000000000000000000000000000");
    rational c("99999999999999999999999999999999999999999999999999999000000000"
        "00000000000000000000000000000.55");

    EXPECT_EQ(c, a - b);
}

TEST(correctness, rational_sub_long_signed) {
    rational a("-10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000.55");
    rational b("-100000000000000000000000000000000000000");
    rational c("-99999999999999999999999999999999999999999999999999999000000000"
        "00000000000000000000000000000.55");

    EXPECT_EQ(c, a - b);
}

TEST(correctness, rational_mul) {
    rational a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000.55");
    rational b("100000000000000000000000000000000000000.55");
    rational c("10000000000000000000000000000000000000055000000000000000000000"
        "000000000000000000000000000000"
        "55000000000000000000000000000000000000.3025");

    EXPECT_EQ(c, a * b);
}

TEST(correctness, rational_mul_signed) {
    rational a("-10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000.55");
    rational b("100000000000000000000000000000000000000.55");
    rational c("-10000000000000000000000000000000000000055000000000000000000000"
        "000000000000000000000000000000"
        "55000000000000000000000000000000000000.3025");

    EXPECT_EQ(c, a * b);
}

TEST(correctness, rational_dived_long) {
    rational a("10000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000");
    rational b("100000000000000000000000000000000000000");
    rational c("100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a / b);
}

TEST(correctness, rational_dived_long_signed) {
    rational a("-1000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000.555");
    rational b("100000000000000000000000000000000000000");
    rational c("-10000000000000000000000000000000000000000000000000000.000000000000000000000000000000000000555");

    EXPECT_EQ(c, a / b);
}

TEST(correctness, rational_adding_random) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 10; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);
        
        double temp_ad = temp + temp2;

        rational r = temp;
        rational r2 = temp2;

        rational r_ad = temp + temp2;

        EXPECT_EQ(temp_ad, r_ad);
    }
}

TEST(correctness, rationla_subscript_random) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 10; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);

        double temp_ad = temp - temp2;

        rational r = temp;
        rational r2 = temp2;

        rational r_ad = temp - temp2;

        EXPECT_EQ(temp_ad, r_ad);
    }
}

TEST(correctness, rational_mul_random) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 10; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);

        double temp_ad = temp * temp2;

        rational r = temp;
        rational r2 = temp2;

        rational r_ad = temp * temp2;

        EXPECT_EQ(temp_ad, r_ad);
    }
}

TEST(correctness, rational_devide_random) {
    srand((unsigned int)time(0));
    for (int i = 0; i < 10; ++i) {
        double temp = random2(-158.345, 157.44);
        double temp2 = random2(-158.345, 157.44);

        double temp_ad = temp / temp2;

        rational r = temp;
        rational r2 = temp2;

        rational r_ad = temp / temp2;

        EXPECT_EQ(temp_ad, r_ad);
    }
}





