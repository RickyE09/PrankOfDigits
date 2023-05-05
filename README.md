# Prank of Digits

## Problem ID: prankofdigits

Shoshana just told you that 12 + 30 = 90. After thinking about it for a while you realized that she is playing a prank
on you by changing the meaning of the symbols 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , and 9.
While usually, they appear in this order, with 0 standing for “zero”, 1 for “one”, etc., if we use 2371904856 as the
meaning of the symbols (by that we mean that 2 means “zero”, 3 means “one”, 7 means “two”, 1 means “three”, 9
means “four”, 0 means “five”, 4 means “six”, 8 means “seven”, 5 means “eight”, and 6 means “nine”), then Shoshana’s
message (12 + 30 = 90) means “thirty plus fifteen equals forty-five”, which is true.
You’ve decided to write a program to help you decide what Shoshana means. Because of the nature of the prank, it
is considered valid to have any numbers of leading zeros in any of the numbers the might appear. The inputs guarantee
there is at least one solution.

## Input

The input will contain a single line with an expression of the form A+B=C, where A, B, and C are numbers with up to
9 digits each.

## Output

The output should be formed by a single line containing the ten symbols in order of their meaning (starting with the
symbol that means “zero” and ending with the symbol that means “nine”) to make Shoshana’s expression valid. If
there are several possibilities output any of them.

```
Sample Input 1 Sample Output 1
12+30=90 2371904856
```
```
Sample Input 2 Sample Output 2
123+654=777 0123456789
```

