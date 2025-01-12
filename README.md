# CCALCULATOR
CCALCULATOR is fast console full expression calculator written on C. 

### Why ccalculator?
 1. I think that for a lot of programms CLI better than GUI, because programms that use CLI is more portable and more functional...
 2. ccalculator take good input/output (i/o), you can use files or standart i/o and you can combine them.
 3. You can work with full expressions ```pow(-5, 2) - 4 * -3 * 2```.

### Install
 1. Download archive from release and unpack it.
 2. Do ```make``` in a root of ccalculator.

### Usage
#### Synopsis
```
./ccalculator [option file] [[option file]]
```

#### Options
```
--filein FILE - input FILE (default - stdin)
--fileout FILE - output FILE (default - stdout)
```

If you don't use option, ccalculator will use default value.

Examples:

```./ccalculator``` - Use standart i/o

```./ccalculator --filein input.txt --fileout output.txt``` - Use i/o files

```./ccalculator --filein input.txt``` - Use input file and stdout


#### Expression
- Operators -> "+", "-", "*", "/"
- Constants -> *pi*, *e*, *sqrt_2*
- Functions -> *sqrt* - squre root, *cbrt* - cube root, *pow* - power
- Numbers   -> Every number of double

When you started ccalculator, you can enter the expression and you must observe mathematics rules.

> [!CAUTION]
> When you enter the incorrect expression, behaviour of ccalculator is undefined.

### Plans
 1. User errors
 2. Safety working with memory or custom *exit*
 3. Scientific notation and precision
 4. Special symbol for previous expression's answer
 5. Additional options for disable *normalize*, errors etc.