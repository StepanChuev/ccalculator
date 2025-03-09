#ifndef IO_H
#define IO_H

#include <stdio.h>
#define FILEIN_FLAG "-i"
#define FILEOUT_FLAG "-o"
#define BASE_FLAG "-b"

void fprintBin(FILE *file, unsigned long int num);
char *getExpressionFromStdin(size_t maxLen);
char *getExpressionFromFile(FILE *file, char sep);
char *getValueByFlag(const char *flag, int argc, char *argv[]);
FILE *getIOFile(const char *flag, const char *mode, int argc, char *argv[]);

#endif
