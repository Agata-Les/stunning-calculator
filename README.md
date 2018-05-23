# Simple calculator for arithmetical expressions

## Error codes:

1 - Empty string

2 - Brackets do not match

3 - Invalid syntax

4 - Too many plus/minus operators

## Grammar:

* binary-operator = '+' | '-' | '*' | '/' | '(' | ')'

* unary-operator = '+' | '-'

* digit = '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'

* number = ^[unary-operator] {digit} | binary-operator [unary-operator] {digit}
