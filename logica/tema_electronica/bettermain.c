/*
 *
 * Autor: Jardan Andrei
 * Grupa: 214
 *
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int N = 128;

typedef struct {
	int digits[N];
	int base;
} Number;

int is_digit(char c){
	return c >= '0' && c <= '9';
}

int is_digit_anybase(char c){
	c = toupper(c);
	return c >= '0' && c <= '9' || c >= 'A' && c <= 'Z';
}

int char_to_digit(char c){
	c = toupper(c);
	if(c >= '0' && c <= '9'){
		return c-'0';
	}else if(c >= 'A' && c <= 'Z'){
		return c-'A' + 10;
	}else{
		assert(0);
		return 0;
	}
}

char digit_to_char(int a){
	if(a >= 0 && a <= 9){
		return a    + '0';
	}else if(a >= 10 && a <= 36){
		return a-10 + 'A';
	}else{
		assert(0);
		return 0;
	}
}

void number_print(Number *a){
	int not_zero = 0;
	for(int i = N-1; i >= 0; --i){
		not_zero |= a->digits[i] != 0;
		if(not_zero){
			printf("%c", digit_to_char(a->digits[i]));
		}
	}
	if(!not_zero)printf("0");
	printf("(%d)", a->base);
}

Number number_new(char *s, int base){
	Number num;
	num.base = base;
	int len = strlen(s);
	for(int i = 0; i < N; ++i){
		num.digits[i] = 0;
		if(i < len)num.digits[i] = char_to_digit(s[len-1-i]);
		assert(num.digits[i] < base);
	}
	return num;
}

Number number_new_zero(int base){
	return number_new("", base);
}

Number number_from_digit(int digit, int base){
	assert(digit < base);
	Number num = number_new_zero(base);
	num.digits[0] = digit;
	return num;
}

int number_is_digit(Number *num){
	for(int i = 1; i < N; ++i){
		if(num->digits[i] != 0)return 0;
	}
	return 1;
}

int number_to_digit(Number *num){
	assert(number_is_digit(num));
	return num->digits[0];
}

int number_is_zero(Number *num){
	for(int i = 0; i < N; ++i){
		if(num->digits[i] != 0)return 0;
	}
	return 1;
}

enum { NUMBER_LT, NUMBER_EQ, NUMBER_GT };

int number_cmp(Number *lhs, Number *rhs){
	assert(lhs->base == rhs->base);
	for(int i = N-1; i >= 0; --i){
		if(lhs->digits[i] < rhs->digits[i])return NUMBER_LT;
		if(lhs->digits[i] > rhs->digits[i])return NUMBER_GT;
	}
	return NUMBER_EQ;
}

// void test_number_cmp(){
// 	Number a = number_new("123", 10);
// 	Number b = number_new("123", 10);
	
// 	assert(number_cmp(&a, &b) == NUMBER_EQ);
// }

Number number_div_digit(Number *lhs, int rhs, int *r){
	assert(rhs < lhs->base);
	Number out = number_new_zero(lhs->base);
	*r = 0;
	for(int i = N-1; i >= 0; --i){
		int v = (*r)*out.base + lhs->digits[i];
		out.digits[i] = v / rhs;
		*r = v % rhs;
	}
	return out;
}

Number number_mul_digit(Number *lhs, int rhs){
	assert(rhs < lhs->base);
	Number out = number_new_zero(lhs->base);
	int t = 0;
	for(int i = 0; i < N; ++i){
		int v = lhs->digits[i]*rhs + t;
		t = v / out.base;
		out.digits[i] = v % lhs->base;
	}
	return out;
}

Number number_add(Number *lhs, Number *rhs){
	assert(lhs->base == rhs->base);
	Number out = number_new_zero(lhs->base);
	
	int t = 0;
	for(int i = 0; i < N; ++i){
		int v = lhs->digits[i] + rhs->digits[i] + t;
		out.digits[i] = v % out.base;
		t = v / out.base;
	}
	
	return out;
}

Number number_sub(Number *lhs, Number *rhs){
	int cmp = number_cmp(lhs, rhs);
	assert(cmp == NUMBER_GT || cmp == NUMBER_EQ);
	assert(lhs->base == rhs->base);
	Number out = number_new_zero(lhs->base);
	
	int t = 0;
	for(int i = 0; i < N; ++i){
		int v = lhs->digits[i] - rhs->digits[i] + t;
		t = 0;
		if(v < 0){
			v += out.base;
			t = -1;
		}
		out.digits[i] = v;
	}
	
	return out;
}

Number convert_divison(Number in, int base){
	assert(in.base >= base);
	int digits[N];
	int digitslen = 0;
	while(!number_is_zero(&in)){
		int r;
		in = number_div_digit(&in, base, &r);
		
		digits[digitslen++] = r;
	}
	
	Number out = number_new_zero(base);
	for(int i = 0; i < digitslen; ++i){
		out.digits[i] = digits[i];
	}
	
	return out;
}

Number convert_substitution(Number in, int base){
	assert(in.base <= base);
	Number out = number_new_zero(base);
	int not_zero = 0;
	for(int i = N-1; i >= 0; --i){
		not_zero |= in.digits[i] != 0;
		if(not_zero){
			out = number_mul_digit(&out, in.base);
			Number digit = number_from_digit(in.digits[i], base);
			out = number_add(&out, &digit);
		}
	}
	return out;
}

Number convert_smart(Number in, int base){
	if(in.base < base){
		return convert_substitution(in, base);
	}else if(in.base > base){
		return convert_divison(in, base);
	}else{
		return in;
	}
}

Number convert_intermediate(Number in, int base){
	Number intermediate = convert_smart(in, 10);
	Number out = convert_smart(intermediate, base);
	return out;
}

Number convert_rapid(Number in, int base){
	int p;
	switch(in.base){
		case 2: p = 1; break;
		case 4: p = 2; break;
		case 8: p = 3; break;
		case 16: p = 4; break;
		default: assert(0); break;
	}
	int q;
	switch(base){
		case 2: q = 1; break;
		case 4: q = 2; break;
		case 8: q = 3; break;
		case 16: q = 4; break;
		default: assert(0); break;
	}
	Number out = number_new_zero(base);
	for(int i = 0; i < N; ++i){
		out.digits[i/q] |= ((in.digits[i/p] >> (i%p)) & 1) << (i%q);
	}
	return out;
}

void error(char *s){
	printf("Eroare: %s\n\n", s);
}

void obs(char *s){
	printf("Observatie: %s\n", s);
}

int in_string(char *s, int *i){
	return (*i == 0) || (s[*i] != '\0') || (s[(*i)-1] != 0);
}

int parse_number(char *s, int *i, Number *number){
	enum { PARSING_NUMBER, PARSING_BASE };

	char num[128];
	int numlen = 0;
	
	char base[16];
	int baselen = 0;
	
	int state = PARSING_NUMBER;
	
	for(; in_string(s, i); ++(*i)){
		switch(state){
			case PARSING_NUMBER: {
				if(is_digit_anybase(s[*i])){
					num[numlen++] = s[*i];
				}else if(s[*i] == '('){
					if(numlen == 0){
						error("numarul nu poate fi nul");
						return 0;
					}
					state = PARSING_BASE;
				}else{
					error("se astepta o cifra in orice baza sau '('");
					return 0;
				}
			} break;
			case PARSING_BASE: {
				if(is_digit(s[*i])){
					base[baselen++] = s[*i];
				}else if(s[*i] == ')'){
					if(baselen == 0){
						error("baza nu poate fi nula");
						return 0;
					}
					goto after_loop;
				}else{
					error("se astepta o cifra in baza 10 sau ')'");
					return 0;
				}
			} break;
		}
	}
after_loop:
	
	(*i)++;
	num[numlen] = base[baselen] = '\0';
	
	int baseint = atoi(base);
	if(baseint < 2) {
		error("baza nu poate fi mai mica decat 2");
		return 0;
	}
	*number = number_new(num, baseint);
	
	return 1;
}

int parse_question(char *s, int *i, int *dest_base, int *intermediate){
	char base[16];
	int baselen = 0;
	
	if(s[(*i)++] != '='){
		error("se astepta '='");
		return 0;
	}
	if(intermediate){
		*intermediate = 0;
		if(s[*i] == '1'){
			(*i)++;
			if(s[(*i)++] != '0'){
				error("conversia cu baza intermediara functioneaza doar in baza 10");
				return 0;
			}
			*intermediate = 1;
		}
	}
	if(s[(*i)++] != '?'){
		error("se astepta '?'");
		return 0;
	}
	
	if(s[(*i)++] != '('){
		error("se astepta '('");
		return 0;
	}
	for(; in_string(s, i); ++(*i)){
		if(is_digit(s[*i])){
			base[baselen++] = s[*i];
		}else if(s[*i] == ')'){
			break;
		}else{
			error("se astepta o cifra in baza 10 sau ')'");
			return 0;
		}
	}
	base[baselen] = '\0';
	
	int baseint = atoi(base);
	if(baseint < 2) {
		error("baza nu poate fi mai mica decat 2");
		return 0;
	}
	*dest_base = baseint;
	
	return 1;
}

int parse_and_answer(char *s){
	int i = 0;
	
	Number out, rout;
	int print_rout = 0;
	
	Number a;
	if(!parse_number(s, &i, &a))return 0;
	if(s[i] == '='){
		int dest_base, intermediate;
		if(!parse_question(s, &i, &dest_base, &intermediate))return 0;
		
		int p = 0;
		switch(a.base){
			case 2:case 4:case 8:case 16:p = 1;break;
		}
		
		int q = 0;
		switch(dest_base){
			case 2:case 4:case 8:case 16:q = 1;break;
		}
		
		if(a.base == dest_base){
			obs("Numarul nu a fost convertit, pentru ca este deja in baza destinatie");
			out = a;
		}else if(intermediate){
			obs("A fost utilizata conversia prin baza intermediara 10");
			out = convert_intermediate(a, dest_base);
		}else if(p && q){
			obs("A fost utilizata conversia rapida");
			out = convert_rapid(a, dest_base);
		}else if(a.base > dest_base){
			obs("A fost utilizata conversia prin impartiri");
			out = convert_divison(a, dest_base);
		}else if(a.base < dest_base){
			obs("A fost utilizata conversia prin substitutie");
			out = convert_substitution(a, dest_base);
		}
	}else if(strchr("+-*/", s[i])){
		char op = s[i++];
		
		Number b;
		if(!parse_number(s, &i, &b))return 0;
	
		int dest_base;
		if(!parse_question(s, &i, &dest_base, NULL))return 0;
		
		switch(op){
			case '+':{
				a = convert_smart(a, dest_base);
				b = convert_smart(b, dest_base);
				out = number_add(&a, &b);
			} break;
			case '-':{
				a = convert_smart(a, dest_base);
				b = convert_smart(b, dest_base);
				out = number_sub(&a, &b);
			} break;
			case '*':{
				if(!number_is_digit(&b)){
					error("Al doilea operand trebuie sa fie cifra in cazul inmultirii");
					return 0;
				}
				a = convert_smart(a, b.base);
				out = number_mul_digit(&a, number_to_digit(&b));
				out = convert_smart(out, dest_base);
			} break;
			case '/':{
				print_rout = 1;
				if(!number_is_digit(&b)){
					error("Al doilea operand trebuie sa fie cifra in cazul impartirii");
					return 0;
				}
				int r;
				a = convert_smart(a, b.base);
				out = number_div_digit(&a, number_to_digit(&b), &r);
				out = convert_smart(out, dest_base);
				rout = number_from_digit(r, dest_base);
			} break;
		}
	}else{
		error("se astepta '=', '+', '-', '*', sau '/'");
		return 0;
	}
	
	printf("rezultat = ");
	number_print(&out);
	if(print_rout){
		printf(" rest ");
		number_print(&rout);
	}
	printf("\n");
	printf("\n");
	
	return 1;
}

void help_message(){
	printf("Introduceti \"help\" pentru a afisa acest mesaj\n");
	printf("Introduceti \"exit\" pentru a inchide programul\n");
	printf("\n");
	
	printf("Pentru a converti dintr-o baza in alta, introduceti numarul, urmat\n");
	printf("de baza sursa intre paranteze, urmat de =?, urmat de baza destinatie\n");
	printf("intre paranteze.\n");
	printf("Exemple: F00(16)=?(5)\n");
	printf("         12(3)=?(9)\n");
	printf("         101010(2)=?(10)\n");
	printf("\n");
	
	printf("Observatie: daca doriti sa se foloseasca conversia prin baza intermediara 10,\n");
	printf("in loc de =? introduceti =10?. Baza intermediara 10 este unica baza intermediara\n");
	printf("acceptata.\n");
	printf("Exemple: 4278(12)=10?(4)\n");
	printf("         ABCD(16)=10?(7)\n");
	printf("\n");
	
	printf("Pentru a efectua un calcul intre doua numere, introduceti primul\n");
	printf("numar, impreuna cu baza in care se afla intre paranteze, urmat de\n");
	printf("operatia dorita (una dintre + - * /), urmata de al doilea numar, tot\n");
	printf("cu baza intre paranteze, urmat de =? si baza destinatie intre paranteze.\n");
	printf("Exemple: 12(3)+FEEF(16)=?(7)\n");
	printf("         777(10)-31(4)=?(2)\n");
	printf("         808(9)*A(14)=?(11)\n");
	printf("         45210(6)/3(5)=?(16)\n");
	printf("\n");
	
	printf("Observatie: inmultirea si impartirea se pot face doar cu o cifra.\n");
	printf("\n");
}

int main(){
	// 1 calculator
	// 2 conversie impartiri
	// 3 conversie substitutie
	// 4 conversie baza intermediara
	// 5 conversie rapida
	
	// char s[] = "63(7)+BEEF(16)=?(2)";
	// char s[] = "63(7)=10?(2)";
	
	// TODO: verifica ca cifrele sa nu fie mai mari decat baza
	
	printf("--- Calculator ---\n");
	printf("Autor: Jardan Andrei\n");
	printf("Grupa: 214\n");
	printf("\n");
	
	help_message();
	
	int is_running = 1;
	
	while(is_running){
		printf("# ");
		char s[512];
		
		fgets(s, sizeof(s), stdin);
		s[strlen(s)-1] = '\0';
		
		if(s[0] == '\0')continue;
		
		if(strcmp(s, "exit") == 0){
			is_running = 0;
		}else if(strcmp(s, "help") == 0){
			help_message();
		}else{
			parse_and_answer(s);
		}
	}
	
	return 0;
}