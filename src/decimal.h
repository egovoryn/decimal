#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    D_NORMAL_VALUE = 0,
    D_INFINITY = 1,
    D_NEGATIVE_INFINITY = 2,
    D_NAN = 3,
} value_type_t;

typedef struct {
    unsigned int bits[4];
    value_type_t value_type;
} d_decimal;

#define MASK_FIRST_BIT 0x80000000         // маска, указывающая на первый бит из 32
#define MASK_FIRST_BIT_MANTISSA 0x400000  // маска, указывающая на первый бит мантиссы
#define MASK_EXP_SCALE 0x00ff0000         // маска, указывающая на N в scale
#define MASK_CARRY_UNIT 0x100000000       // неявная единица между мантиссой и старшим разрядом
#define MAX_LEN 29u                       // значимые биты (u - unsigned)

#define DECIMAL_NULL {{0, 0, 0, 0}, D_NORMAL_VALUE};          // 0
#define DECIMAL_ONE {{1, 0, 0, 0}, D_NORMAL_VALUE};           // 1
#define DECIMAL_HALF {{5, 0, 0, 0x0010000}, D_NORMAL_VALUE};  // 0.5

// Арифметические операторы
d_decimal d_add(d_decimal dec1, d_decimal dec2);  // сложение
d_decimal d_sub(d_decimal dec1, d_decimal dec2);  // вычитание
d_decimal d_mul(d_decimal dec1, d_decimal dec2);  // умножение
d_decimal d_div(d_decimal dec1, d_decimal dec2);  // деление
d_decimal d_mod(d_decimal dec1, d_decimal dec2);  // остаток от деления (mod)

// Операторы сравнения
int d_is_less(d_decimal dec1, d_decimal dec2);              // меньше (<)
int d_is_less_or_equal(d_decimal dec1, d_decimal dec2);     // меньше или равно (<=)
int d_is_greater(d_decimal dec1, d_decimal dec2);           // больше (>)
int d_is_greater_or_equal(d_decimal dec1, d_decimal dec2);  // больше или равно (>=)
int d_is_equal(d_decimal dec1, d_decimal dec2);             // равно (==)
int d_is_not_equal(d_decimal dec1, d_decimal dec2);         // не равно (!=)

// Преобразователи
int d_from_int_to_decimal(int src, d_decimal *dst);      // из int
int d_from_float_to_decimal(float src, d_decimal *dst);  // из float
int d_from_decimal_to_int(d_decimal src, int *dst);      // в int
int d_from_decimal_to_float(d_decimal src, float *dst);  // в float

// Другие рекомендованные функции
d_decimal d_floor(d_decimal dec);
// округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности
d_decimal d_round(d_decimal dec);
// округляет Decimal до ближайшего целого числа
d_decimal d_truncate(d_decimal dec);
// возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются
d_decimal d_negate(d_decimal dec);
// возвращает результат умножения указанного Decimal на -1

// Другие наши функции
int d_shift_left(d_decimal *dec, unsigned int value);
int d_shift_right(d_decimal *dec, unsigned int value);
int d_normalize(d_decimal *dec1, d_decimal *dec2);
int shiftBit(d_decimal *dst, int position);
d_decimal d_move_right(d_decimal src, int shift);
d_decimal d_move_left(d_decimal src, int shift);

int getBit(d_decimal d, int i);                            // возвращает 1, если бит установлен (дека)
int getBitNumber(unsigned int number, int position);         // возвращает 1, если бит установлен (число)
void setBit(d_decimal *d, int i);                          // устанавливает бит по указанному индексу
void setOtherBit(d_decimal *dst, int i, int value);        // обнуляет или устанавливает бит
int getSign(d_decimal *d);                                 // возвращает 1, если число имеет знак минус
void setSign(d_decimal *d);                                // устанавливает числу знак минус
void clearSign(d_decimal *d);                              // очищает знак числа
int getScale(d_decimal *d);                                // возвращает коэффицент масштабирования
int setScale(d_decimal *d, int scale);                     // устанавливает коэффицент масштабирования
int getBinExp(float src);                                    // считает эскпоненту в числе с плавающей точкой
int FindFirstNonZeroBit(d_decimal *d);                     // находит самый старший разряд
void d_swap(d_decimal *dec1, d_decimal *dec2);         // меняет деки местами
void d_decimal_set_default(d_decimal *dec);              // обнуление деки
unsigned int float_bits(float src);                          // перевод float в битовый формат
void rewriteDecimal(d_decimal *dst, d_decimal *dectmp);  //  перезапись decimal

// Распечать Decimal
void decimal_print(d_decimal d);
void bits_print(unsigned value);
char *dec_to_string(d_decimal d);

// Проверки
value_type_t d_typeCheck(d_decimal dec1, d_decimal dec2, int type);  // проверить тип деки
void checkFloat(float src, d_decimal *decimal);                          // проверка числа
int checkMul(d_decimal dec1, d_decimal dec2, d_decimal *res);        // проверки для умножения
void check_div(d_decimal *dividend, d_decimal *divisor,                // проверки для деления
               d_decimal *quotient, d_decimal *mod);

// Деление
void div_mod(d_decimal *mod, d_decimal *divisor,  //  деление остатка от деления
             d_decimal *quotient);
void div_int(d_decimal *dividend, d_decimal *divisor,  // целочислeнное деление decimal
             d_decimal *quotient, d_decimal *mod);

#endif  // SRC_DECIMAL_H_
