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
	char building;
	char gold;
	char energy;
	char owner;
	char natural_gold;
	char natural_energy;
	unsigned short natural_cost;
} Cell;

#endif
