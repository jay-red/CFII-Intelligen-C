#include "jstring.h"

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

void catJStr( JString jstr, CString const str ) {
	unsigned int len = 0;
	for( ; str[ len ] != '\0'; ++len );
	unsigned int tempLen = lenJStr( jstr );
	if( len + tempLen > **( ( unsigned int** ) jstr ) ) {
		unsigned int* temp = *( ( unsigned int** ) jstr );
		*( ( unsigned int** ) jstr ) = ( unsigned int* ) malloc( ( sizeof( unsigned int ) * 2 ) + ( ( len + tempLen + 1 ) * sizeof( char ) ) );
		**( ( unsigned int** ) jstr ) = len + tempLen;
		memcpy( ( char* )( *( ( unsigned int** ) jstr ) + 2 ), temp + 2, tempLen );
		free( temp );
	}
	*( *( ( unsigned int** ) jstr ) + 1 ) = len + tempLen;
	memcpy( ( char* )( *( ( unsigned int** ) jstr ) + 2 ) + tempLen, str, len + 1 );
}

void appendJStr( JString jstr, char const chr ) {
	int len = lenJStr( jstr );
	if( len + 1 > **( ( unsigned int** ) jstr ) ) {
		unsigned int* temp = *( ( unsigned int** ) jstr );
		*( ( unsigned int** ) jstr ) = ( unsigned int* ) malloc( ( sizeof( unsigned int ) * 2 ) + ( ( len + 2 ) * sizeof( char ) ) );
		**( ( unsigned int** ) jstr ) = len + 1;
		memcpy( ( char* )( *( ( unsigned int** ) jstr ) + 2 ), temp + 2, len );
		free( temp );
	}
	*( *( ( unsigned int** ) jstr ) + 1 ) = len + 1;
	*( ( char* )( *( ( unsigned int** ) jstr ) + 2 ) + len ) = chr;
	*( ( char* )( *( ( unsigned int** ) jstr ) + 2 ) + len + 1 ) = '\0';
}

char equalJStr( JString jstr, CString const str ) {
	return strcmp( toString_JStr( jstr ), str ) == 0;
}

CString toString_JStr( JString jstr ) {
	return ( CString )( *( ( unsigned int** ) jstr ) + 2 );
}
