# CCALCULATOR
CCALCULATOR is fast console calculator written on C. 

### Install
 1. Download archive from release and unzip it.
 2. Do ```make``` in a root of ccalculator.

### Usage
#### Synopsis
```
./ccalculator [-i|-o *file*] [-o|-i *file*] [-b *base*]
```

#### Options
```
-i FILE - input FILE (default - stdin)
-o FILE - output FILE (default - stdout)
-b BASE - set base of result (b - binary; o - octal; x - hexadecimal) (default - decimal)
```

If you don't use option, ccalculator will use default value.

Examples:

```./ccalculator``` - Use standart i/o

```./ccalculator -i input.txt -o output.txt``` - Use i/o files

```./ccalculator -i input.txt``` - Use input file and stdout


#### Expression
- Operators -> "+", "-", "*", "/"
- Constants -> *pi*, *e*, *sqrt_2*
- Functions -> *sqrt* - squre root, *cbrt* - cube root, *pow* - power
- Numbers   -> Every number of double. You can use binary (0b), octal (0o), decimal and hexadecimal (0x) numbers.  

When you started ccalculator, you can enter the expression and you must observe mathematics rules.

> [!CAUTION]
> When you enter the incorrect expression, behaviour of ccalculator is undefined.

### Plans
 1. User errors
 2. Precision
 3. Special symbol for previous expression's answer
 4. Additional options for disable *normalize*, errors etc.
