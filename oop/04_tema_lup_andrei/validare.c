#include "validare.h"

int validare(Materie* nou)
{
	if (strlen(nou->nume) == 0 || strlen(nou->producator) == 0)
		return -2;
	if (nou->cantitate < 0)
		return -2;
	return 1;
}