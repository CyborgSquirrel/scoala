#ifndef valid_h_INCLUDED
#define valid_h_INCLUDED

#include "./domain.h"

int validate_data(struct Data *data) {
	const static int zile_in_lune[12] =
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (data->luna < 1 || data->luna > 12) return 0;
	
	int zile_in_luna = zile_in_lune[data->luna-1];
	if (data->luna == 2) {
		int bisect = data->an % 4 == 0
			&& (data->an % 100 != 0 || data->an % 400 == 0);
		zile_in_luna += bisect;
	}
	
	if (data->zi < 1 || data->zi > zile_in_luna) return 0;
	
	return 1;
}

int validate_suma(float suma) {
	return suma >= 0;
}

#endif // valid_h_INCLUDED

