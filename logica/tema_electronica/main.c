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
	printf("\n");
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
	Number num = number_new_zero(base);
	num.digits[0] = digit;
	return num;
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

void number_div_digit(Number *lhs, int rhs, int *r){
	assert(rhs < lhs->base);
	*r = 0;
	for(int i = N-1; i >= 0; --i){
		int v = (*r)*lhs->base + lhs->digits[i];
		lhs->digits[i] = v / rhs;
		*r = v % rhs;
	}
}

void number_mul_digit(Number *lhs, int rhs){
	assert(rhs < lhs->base);
	int t = 0;
	for(int i = 0; i < N; ++i){
		int v = lhs->digits[i]*rhs + t;
		t = v / lhs->base;
		lhs->digits[i] = v % lhs->base;
	}
}

void number_add(Number *lhs, Number *rhs){
	assert(lhs->base == rhs->base);
	int base = lhs->base;
	
	int t = 0;
	for(int i = 0; i < N; ++i){
		int v = lhs->digits[i] + rhs->digits[i] + t;
		lhs->digits[i] = v % base;
		t = v / base;
	}
}

void number_sub(Number *lhs, Number *rhs){
	int cmp = number_cmp(lhs, rhs);
	assert(cmp == NUMBER_GT || cmp == NUMBER_EQ);
	assert(lhs->base == rhs->base);
	int base = lhs->base;
	
	int t = 0;
	for(int i = 0; i < N; ++i){
		int v = lhs->digits[i] - rhs->digits[i] + t;
		t = 0;
		if(v < 0){
			v += base;
			t = -1;
		}
		lhs->digits[i] = v;
	}
}

Number convert_divison(Number in, int base){
	assert(in.base >= base);
	int digits[N];
	int digitslen = 0;
	while(!number_is_zero(&in)){
		int r;
		number_div_digit(&in, base, &r);
		
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
			number_mul_digit(&out, in.base);
			Number digit = number_from_digit(in.digits[i], base);
			number_add(&out, &digit);
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

enum { PARSING_NUMBER, PARSING_BASE };

void parse_number(char *s, int *i, Number *number){
	char num[128];
	int numlen = 0;
	
	char base[16];
	int baselen = 0;
	
	int state = PARSING_NUMBER;
	
	for(; s[*i] != ')' && s[*i] != '\0'; ++(*i)){
		switch(state){
			case PARSING_NUMBER: {
				if(is_digit_anybase(s[*i])){
					num[numlen++] = s[*i];
				}else if(s[*i] == '('){
					state = PARSING_BASE;
				}else ; // this is bad
				break;
			}
			case PARSING_BASE: {
				if(is_digit(s[*i])){
					base[baselen++] = s[*i];
				}else ; // this is bad
				break;
			}
		}
	}
	(*i)++;
	num[numlen] = base[baselen] = '\0';
	*number = number_new(num, atoi(base));
}

void parse_question(char *s, int *i, int *out_base, int *intermediate){
	char base[16];
	int baselen = 0;
	
	if(s[(*i)++] != '=') {} // this is bad
	if(intermediate){
		*intermediate = 0;
		if(s[*i] == '1'){
			(*i)++;
			if(s[(*i)++] != '0') {}
			*intermediate = 1;
		}
	}
	if(s[(*i)++] != '?') {} // this is bad
	
	if(s[(*i)++] != '(') {} // this is bad
	for(; s[*i] != ')' && s[*i] != '\0'; ++(*i)){
		if(is_digit(s[*i])){
			base[baselen++] = s[*i];
		}else ; // this is bad
	}
	base[baselen] = '\0';
	*out_base = atoi(base);
}

void obs(char *s){
	printf("Observatie: %s\n", s);
}

int main(){
	// 1 calculator
	// 2 conversie impartiri
	// 3 conversie substitutie
	// 4 conversie baza intermediara
	// 5 conversie rapida
	
	// char s[] = "63(7)+BEEF(16)=?(2)";
	char s[] = "63(7)=10?(2)";
	int i = 0;
	
	Number out;
	
	Number a;
	parse_number(s, &i, &a);
	if(s[i] == '='){
		int out_base, intermediate;
		parse_question(s, &i, &out_base, &intermediate);
		
		int p = 0;
		switch(a.base){
			case 2:case 4:case 8:case 16:
			p = 1;
			break;
		}
		
		int q = 0;
		switch(out_base){
			case 2:case 4:case 8:case 16:
			p = 1;
			break;
		}
		
		if(a.base == out_base){
			obs("Numarul nu a fost convertit, pentru ca este deja in baza destinatie");
			out = a;
		}else if(intermediate){
			obs("A fost utilizata conversia prin baza intermediara 10");
			out = convert_intermediate(a, out_base);
		}else if(p && q){
			obs("A fost utilizata conversia rapida");
			out = convert_rapid(a, out_base);
		}else if(a.base > out_base){
			obs("A fost utilizata conversia prin impartiri");
			out = convert_divison(a, out_base);
		}else if(a.base < out_base){
			obs("A fost utilizata conversia prin substitutie");
			out = convert_substitution(a, out_base);
		}
	}else{
		char op = s[i++];
		
		Number b;
		parse_number(s, &i, &b);
	
		int out_base;
		parse_question(s, &i, &out_base, NULL);
		
		out = convert_smart(a, out_base);
		switch(op){
			case '+':{
				Number cb = convert_smart(b, out_base);
				number_add(&out, &cb);
				break;
			}
			case '-':{
				Number cb = convert_smart(b, out_base);
				number_sub(&out, &cb);
				break;
			}
			case '*':{
				
				break;
			}
			case '/':{
				
				break;
			}
		}
	}
	
	number_print(&out);
	
	return 0;
}