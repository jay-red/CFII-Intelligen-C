#include <stdlib.h>
#include <stdio.h>

#include "container/arraylist.h"
#include "container/heap.h"
#include "container/jstring.h"
#include "enigma/enigma.h"

typedef struct {
	ArrayList adjacent;
	Heap targets;
	Enigma* game;
	Cell* home;
	unsigned int lastTurn;
	unsigned char playing;
} Oxymora;

unsigned char cost_compare( void* ptr1, void* ptr2 );
void initialize_oxymora( Oxymora* oxymora );
void Start( Oxymora* oxymora );
void Analyze( Oxymora* oxymora );
void GameLoop( Oxymora* oxymora );

unsigned char cost_compare( void* ptr1, void* ptr2 ) {
	Cell* c1 = ( Cell* ) ptr1;
	Cell* c2 = ( Cell* ) ptr2;
	return c1->attack_cost < c2->attack_cost;
}

void initialize_oxymora( Oxymora* oxymora, CString const room ) {
	oxymora->game = ( Enigma* ) malloc( sizeof( Enigma ) );
	initialize_enigma( oxymora->game, room );
	initialize_list( &( oxymora->adjacent ) );
	initialize_heap( &( oxymora->targets ), cost_compare );
}

void Start( Oxymora* oxymora, CString const name, CString const pass ) {
	if( JoinGame( oxymora->game, name, pass ) ) {
		oxymora->lastTurn = 0;
		oxymora->playing = 1;
		while( oxymora->playing ) {
			GameLoop( oxymora );
		}
	}
}

void Analyze( Oxymora* oxymora ) {
	unsigned int x = 0, y = 0;
	Cell* cell, *up, *down, *left, *right;
	unsigned char attackable;
	for( ; y < 30; ++y ) {
		for( x = 0; x < 30; ++x ) {
			cell = GetCell( oxymora->game, x, y );
			if( cell->owner == oxymora->game->me->uid ) {
				if( cell->building / 3 == HOME_ID ) {
					printf( "Home: %d,", cell->x );
					printf( "%d\n", cell->y );
				}
			} else {
				attackable = 0;
				up = GetCell( oxymora->game, x, y - 1 );
				right = GetCell( oxymora->game, x + 1, y );
				down = GetCell( oxymora->game, x, y + 1 );
				left = GetCell( oxymora->game, x - 1, y );
				if( up && up->owner == oxymora->game->me->uid ) attackable = 1;
				if( right && right->owner == oxymora->game->me->uid ) attackable = 1;
				if( down && down->owner == oxymora->game->me->uid ) attackable = 1;
				if( left && left->owner == oxymora->game->me->uid ) attackable = 1;
				if( attackable ) {
					push_heap( &( oxymora->targets ), cell );
				}
			}
		}
	}
}

void GameLoop( Oxymora* oxymora ) {
	Enigma* game = oxymora->game;
	Refresh( game );
	if( game->turn == oxymora->lastTurn ) return;
	BeginTurn( game );
	Analyze( oxymora );
	printf( "%d\n", game->turn );
	oxymora->lastTurn = game->turn;
	void* ptr = top_heap( &( oxymora->targets ) );
	Cell* target;
	while( ptr ) {
		target = ( Cell* ) ptr;
		Attack( game, target->x, target->y, target->attack_cost );
		pop_heap( &( oxymora->targets ) );
		ptr = top_heap( &( oxymora->targets ) );
	}
	EndTurn( game );
}

int main() {
	Oxymora oxymora;
	initialize_oxymora( &oxymora, "public" );
	Start( &oxymora, "Oxymora", "CuteButDeadly" );
	return 0;
}
