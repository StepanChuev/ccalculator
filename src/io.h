#ifndef IO_H
#define IO_H

#include <stdio.h>
#define FILEIN_FLAG "--filein"
#define FILEOUT_FLAG "--fileout"
#define BASE_FLAG "--base"

void fprintBin(FILE *file, unsigned long int num);
char *getExpressionFromStdin(size_t maxLen);
char *getExpressionFromFile(FILE *file, char sep);
char *getValueByFlag(const char *flag, int argc, char *argv[]);
FILE *getIOFile(const char *flag, const char *mode, int argc, char *argv[]);

#endif