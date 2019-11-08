#ifndef CELL_H
#define CELL_H

#define EMPTY_ID 0
#define HOME_ID 1
#define GOLD_ID 2
#define ENERGY_ID 3
#define FORT_ID 4

typedef struct {
	unsigned short attack_cost;
	unsigned short force_field;
	unsigned char building;
	signed char gold;
	signed char energy;
	unsigned char owner;
	unsigned char natural_gold;
	unsigned char natural_energy;
	unsigned char x;
	unsigned char y;
	unsigned short natural_cost;
} Cell;

#endif
