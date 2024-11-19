#ifndef IO_H
#define IO_H

#include <stdio.h>
#define FILEIN_ARG "--filein"
#define FILEOUT_ARG "--fileout"

char *getExpressionFromStdin(size_t maxLen);
char *getExpressionFromFile(FILE *file, char sep);
char *getFilePathByFlag(const char *flag, int argc, char *argv[]);
FILE *getIOFile(const char *flag, const char *mode, int argc, char *argv[]);

#endif