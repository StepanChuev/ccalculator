# ccalculator
ccalculator is console full expression calculator
=======
# CCALCULATOR
ccalculator is console full expression calculator written on C.

### Building from source
You must use mingw to build project if you are windows user, but you need use ccalculator through start ccalculator.exe or in cmd.

```
  git clone https://github.com/StepanChuev/ccalculator.git
  cd ccalculator
  mkdir obj
  make 
```

### Usage
- Operators -> "+", "-", "*", "/"
- Constants -> *pi*, *e*
- Numbers   -> Every number of double

When you started ccalculator, you can enter the expression and you must observe next rules:
 1. Every binary operator must have number/constant on left and right, for exemple: ```-2 * -(3 + 4)```
 2. Don't enter empty expression
 3. Write constants as numbers ```2 * pi * 12.5```
