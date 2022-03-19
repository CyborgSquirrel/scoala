#include "./domain.h"
#include <assert.h>

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

void test_validate_data() {
	struct Data data_valid_1 = data_new(11, 12, 2017);
	struct Data data_valid_2 = data_new(29, 2, 2020);
	struct Data data_invalid_1 = data_new(33, 12, 2008);
	struct Data data_invalid_2 = data_new(-2, 7, 2008);
	struct Data data_invalid_3 = data_new(17, 14, 2008);
	struct Data data_invalid_4 = data_new(17, 0, 2019);
	struct Data data_invalid_5 = data_new(29, 2, 2021);
	
	assert(validate_data(&data_valid_1));
	assert(validate_data(&data_valid_2));
	assert(!validate_data(&data_invalid_1));
	assert(!validate_data(&data_invalid_2));
	assert(!validate_data(&data_invalid_3));
	assert(!validate_data(&data_invalid_4));
	assert(!validate_data(&data_invalid_5));
}

void test_validate_suma() {
	assert(validate_suma(3.1415));
	assert(validate_suma(123.321));
	assert(validate_suma(0));
	assert(!validate_suma(-777.777));
}

void test_validate() {
	test_validate_data();
	test_validate_suma();
}
