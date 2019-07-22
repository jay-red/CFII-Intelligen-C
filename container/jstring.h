#ifndef JSTRING_H
#define JSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void** JString;
typedef char const* CString;

JString initializeJStr( CString const str );

void terminateJStr( JString jstr );

void setJStr( JString jstr, CString const str );

unsigned int lenJStr( JString jstr );

void catJStr( JString jstr, CString const str );

void appendJStr( JString jstr, char const chr );

char equalJStr( JString jstr, CString const str );

CString toString_JStr( JString jstr );

#endif
