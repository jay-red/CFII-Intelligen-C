#ifndef JSTRING_H
#define JSTRING_H

typedef void** JString;

JString initializeJStr( char const* const str );

void terminateJStr( JString jstr );

void setJStr( JString jstr, char const* const str );

unsigned int lenJStr( JString jstr );

char charAtJStr( JString jstr, unsigned int index );

char const* const toString_JStr( JString jstr );

#endif
