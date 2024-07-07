#pragma once
#ifndef UI_H_
#define UI_H_
#include "service.h"
#include "stdio.h"
#include "stdlib.h"
typedef struct {
	Service* srv;

}UI;
UI* create_ui(Service *srv);
void destroy_ui(UI* user_interface);
void run(UI* user_interface);
void menu();
#endif 
