#include "my_date.h"
#include <string.h>
#include <stdlib.h>


Date atribuiData(char* date){ // "AAAA-MM-DD"
	char* ano_str = malloc(5);
	char* mes_str = malloc(3);
	char* dia_str = malloc(3);
	int ano, mes, dia;

	strncpy(ano_str, date, 4);
	strncpy(mes_str, date+5, 2);
	strncpy(dia_str, date+8, 2);

	ano = atoi(ano_str);
	mes = atoi(mes_str);
	dia = atoi(dia_str);

	return (createDate(dia, mes, ano));
}

int comparaDatas(Date a, Date b){ // se a primeira for mais pequena que a segunda retorna -1

	// Compara o ano
	if(get_year(a) > get_year(b)) return 1;
	if(get_year(a) < get_year(b)) return -1;

	// Compara o mês - se chegaram aqui é proque o ano é o mesmo
	if(get_month(a) > get_month(b)) return 1;
	if(get_month(a) < get_month(b)) return -1;

	// Compara o dia - se chegaram aqui é porque o ano e o mês são os mesmos
	if(get_day(a) > get_day(b)) return 1;
	if(get_day(a) < get_day(b)) return -1;

	return 0;
}
