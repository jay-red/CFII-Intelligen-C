#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../container/jstring.h"

JString initializeJStr( CString const str ) {
	unsigned int len = 0;
	for( ; str[ len ] != '\0'; ++len );
	unsigned int** buffer = ( unsigned int** ) malloc( sizeof( void** ) );
	*buffer = ( unsigned int* ) malloc( ( sizeof( unsigned int ) * 2 ) + ( ( len + 1 ) * sizeof( char ) ) );
	**buffer = len;
	*( *buffer + 1 ) = len;
	memcpy( *buffer + 2, str, **buffer + 1 );
	return ( JString ) buffer;
}

void terminateJStr( JString jstr ) {
	free( *jstr );
	*jstr = NULL;
	free( jstr );
}

void setJStr( JString jstr, CString const str ) {
	unsigned int len = 0;
	for( ; str[ len ] != '\0'; ++len );
	if( len > **( ( unsigned int** ) jstr ) ) {
		free( *( ( unsigned int** ) jstr ) );
		*( ( unsigned int** ) jstr ) = ( unsigned int* ) malloc( ( sizeof( unsigned int ) * 2 ) + ( ( len + 1 ) * sizeof( char ) ) );
		**( ( unsigned int** ) jstr ) = len;
	}
	*( *( ( unsigned int** ) jstr ) + 1 ) = len;
	memcpy( *( ( unsigned int** ) jstr ) + 2, str, len + 1 );
}

unsigned int lenJStr( JString jstr ) {
	return *( *( ( unsigned int** ) jstr ) + 1 );
}

CString toString_JStr( JString jstr ) {
	return ( CString )( *( ( unsigned int** ) jstr ) + 2 );
}
