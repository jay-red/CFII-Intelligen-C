#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../container/jstring.h"

JString initializeJStr( char const* const str ) {
	unsigned int len = 0;
	for( ; str[ len ] != '\0'; ++len );
	unsigned int** buffer = ( unsigned int** ) malloc( sizeof( void** ) );
	*buffer = ( unsigned int* ) malloc( sizeof( unsigned int ) + ( ( len + 1 ) * sizeof( char ) ) );
	**buffer = len;
	memcpy( *buffer + 1, str, **buffer + 1 );
	return ( JString ) buffer;
}

void terminateJStr( JString jstr ) {
	free( *jstr );
	*jstr = NULL;
	free( jstr );
}

void setJStr( JString jstr, char const* const str ) {
	unsigned int len = 0;
	for( ; str[ len ] != '\0'; ++len );
	*( ( unsigned int** ) jstr ) = ( unsigned int* ) malloc( sizeof( unsigned int ) + ( ( len + 1 ) * sizeof( char ) ) );
	**( (unsigned int** ) jstr ) = len;
	memcpy( *( ( unsigned int** ) jstr ) + 1, str, len + 1 );
}

unsigned int lenJStr( JString jstr ) {
	return **( ( unsigned int** ) jstr );
}

char* toString_JStr( JString jstr ) {
	return ( char* )( *( ( unsigned int** ) jstr ) + 1 );
}
