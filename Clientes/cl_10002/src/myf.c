/**
 *       @file  myf.c
 *      @brief  Contém as funções para a execução do ciclo infinito
 *
 * 
 *
 *     @author  Bruno Ramos, B.Ramos@ua.pt
 *
 *   @internal
 *     Created  20-Mar-2018
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2018, Bruno Ramos
 *
 * =====================================================================================
 */

#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "myf.h"

/**
 * @brief Ciclo infinito a cada ciclo ele introduz um valor na base de dados e a cada cinco ciclos ele atualiza as tabelas
 * @param void
 * @return void
 */
void START_CYCLE(void)
{
	do
	{
		QUERY_INSERT_INTO_TABLE();
		//intervalo entre valores obtidos, actualmente 1s
		//usleep(200000);
		//Variável alterada na callback ctrl+c
	} while (keep_goingG);
}

/**
 * @brief Regista os valores dos sensores na base de dados
 * @param void
 * @return void
 */
void QUERY_INSERT_INTO_TABLE(void)
{
	static int i = 0;

	int seg, miliseg, molde1, molde2, molde3, molde4, molde5, molde6;
	char query[1000];
	struct timeval t1;

	float valor1, valor2, valor3, valor4, valor5, valor6, valor7, valor8, valor9, valor10, valor11, valor12, valor13, valor14, valor15, valor16, valor17, valor18, valor19, valor20, valor21, valor22, valor23, valor24, valor25, valor26, valor27, valor28, valor29, valor30, O, A, t, G;

	//Cálculo do valor em função de horas, minutos, segundos e micro segundos
	time_t timep = time(NULL);
	struct tm *tm = localtime(&timep);
	gettimeofday(&t1, NULL);

	seg = tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;
	miliseg = t1.tv_usec / pow(10, floor(log10(abs(t1.tv_usec))) - 1); /*pow(10, floor(log10(abs(t1.tv_usec))) - 1) para retirar os dois digitos mais altos dos micro segundos porque não me lembrei que 1ms = 1000us
	https://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c*/

	//Identificação do molde
	molde1 = 9004;
	//dados da onda
	O = 500;
	A = 10.5;
	t = 240; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor1 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor2 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor3 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor4 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor5 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//Identificação do molde
	molde2 = 9005;
	//dados da onda
	O = 500;
	A = 10;
	t = 240; //Em segundos
	G = 5;
	//Expressão seno em função do tempo
	valor6 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor7 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor8 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI / 2;
	//Expressão seno em função do tempo
	valor9 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI / 2;
	//Expressão seno em função do tempo
	valor10 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//Identificação do molde
	molde3 = 9006;
	//dados da onda
	O = 500;
	A = 10;
	t = 240; //Em segundos
	G = PI / 2;
	//Expressão seno em função do tempo
	valor11 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor12 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor13 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor14 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor15 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//Identificação do molde
	molde4 = 9010;
	//dados da onda
	O = 500;
	A = 10.5;
	t = 240; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor16 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor17 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor18 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor19 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor20 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//Identificação do molde
	molde5 = 9011;
	//dados da onda
	O = 500;
	A = 10;
	t = 240; //Em segundos
	G = 5;
	//Expressão seno em função do tempo
	valor21 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor22 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = 0;
	//Expressão seno em função do tempo
	valor23 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI / 2;
	//Expressão seno em função do tempo
	valor24 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI / 2;
	//Expressão seno em função do tempo
	valor25 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//Identificação do molde
	molde6 = 9012;
	//dados da onda
	O = 500;
	A = 10;
	t = 240; //Em segundos
	G = PI / 2;
	//Expressão seno em função do tempo
	valor26 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor27 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor28 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor29 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);

	//dados da onda
	O = 1500;
	A = 1500;
	t = 60; //Em segundos
	G = PI;
	//Expressão seno em função do tempo
	valor30 = O + A * sin(2 * PI * (1 / t) * (seg + miliseg * 0.01) + G);
	//Inserir na tabela 'variável' os valores (Data atual, Hora atual,'valor')
	sprintf(query, "INSERT IGNORE registos VALUES(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f),(%d,%d,NOW(),%d,%.02f)", molde1, 1, miliseg, valor1, molde1, 2, miliseg, valor2, molde1, 3, miliseg, valor3, molde1, 4, miliseg, valor4, molde1, 5, miliseg, valor5, molde2, 1, miliseg, valor6, molde2, 2, miliseg, valor7, molde2, 3, miliseg, valor8, molde2, 4, miliseg, valor9, molde2, 5, miliseg, valor10, molde3, 1, miliseg, valor11, molde3, 2, miliseg, valor12, molde3, 3, miliseg, valor13, molde3, 4, miliseg, valor14, molde3, 5, miliseg, valor15, molde4, 1, miliseg, valor16, molde4, 2, miliseg, valor17, molde4, 3, miliseg, valor18, molde4, 4, miliseg, valor19, molde4, 5, miliseg, valor20, molde5, 1, miliseg, valor21, molde5, 2, miliseg, valor22, molde5, 3, miliseg, valor23, molde5, 4, miliseg, valor24, molde5, 5, miliseg, valor25, molde6, 1, miliseg, valor26, molde6, 2, miliseg, valor27, molde6, 3, miliseg, valor28, molde6, 4, miliseg, valor29, molde6, 5, miliseg, valor30);
	printf("%s\n", query);

	if (mysql_real_query(connG, query, (unsigned long)strlen(query)))
	{
		i++;
		fprintf(stderr, "Error %d: %s [%d]\n", i, mysql_error(connG), mysql_errno(connG));
		//exit(1);
	}
}

/**
 * @brief  Callback para ctrl+c, desliga ciclo infinito
 */
void InterceptCTRL_C(int a)
{
	keep_goingG = 0;
}