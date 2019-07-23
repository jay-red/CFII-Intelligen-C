#ifndef USER_H
#define USER_H

typedef struct {
	unsigned short gold_mine;
	unsigned short energy_well;
	char home;
} BuildingNum;

typedef struct {
	char uid;
	char alive;
	char tech_level;
	char tax_level;
	unsigned short cell_number;
	unsigned short gold_source;
	unsigned short energy_source;
	unsigned short tax_amount;
	unsigned int energy;
	unsigned int gold;
	CString username;
	BuildingNum building_number;
} User;

#endif
