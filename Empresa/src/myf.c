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

#include <unistd.h>
#include <string.h>
#include "myf.h"

/**
 * @brief Contar o número de clientes para fazer fork n times
 * @param void
 * @return void
 */
int numberOfClients(void)
{
	int n;

	CONNECT_CENTRAL_DATABASE();
	mysql_close(connG_central);
	return n;
}

/**
 * @brief Função para fazer fork n vezes, baseada na solução em: https://stackoverflow.com/questions/1664787/problem-forking-fork-multiple-processes-unix
 * @param void
 * @return void
 */
int forkChildren(int nChildren)
{
	int i;
	int pid;
	for (i = 1; i <= nChildren; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			/* error handling here, if needed */
			exit(1);
			return i = 0;
		}
		if (pid == 0)
		{
			printf("I am client: %d PID: %d\n", i, getpid());
			return i;
		}
	}
	return 0;
}

/**
 * @brief Conectar à base de dados central
 * @param void
 * @return void
 */
void CONNECT_CENTRAL_DATABASE(void)
{
	//Dados da base de dados central
	static char *host_central = "127.0.0.1"; //ip da base de dados
	static char *user_central = "sapofree";
	static char *pass_central = "naopossodizer";
	static char *dbname_central = "central";

	unsigned int port_central = 3306;
	static char *unix_socket_central = NULL;
	unsigned int flag_central = 0;

	//Conectar à base de dados central
	connG_central = mysql_init(NULL);
	if (!mysql_real_connect(connG_central, host_central, user_central, pass_central, dbname_central, port_central, unix_socket_central, flag_central))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central), mysql_errno(connG_central));
		exit(1);
	}
	return;
}

/**
 * @brief Ciclo infinito a cada ciclo ele introduz um valor na base de dados e a cada cinco ciclos ele atualiza as tabelas
 * @param void
 * @return void
 */
void START_CYCLE(void)
{
	do
	{
		MOVE_VALUES();
		//intervalo entre valores obtidos, actualmente 1s
		usleep(1000000);
		//Variável alterada na callback ctrl+c
	} while (keep_goingG);
	return;
}

/**
 * @brief Move valores de uma base de dados para a outra
 * @param void
 * @return void
 */
void MOVE_VALUES(void)
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	unsigned int num_fields, num_rows;
	unsigned int i, j = 1;
	unsigned long *lengths;

	unsigned int central_query_size = 100000;
	char local_query[100], str[100], central_query[central_query_size], datetime_limit[22];

	//Lê todos os valores da base de dados local
	sprintf(local_query, "SELECT * FROM Registos ORDER BY data_hora, milisegundos, numero_sensor, ID_molde");
	if (mysql_real_query(connG_local, local_query, (unsigned long)strlen(local_query)))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_local), mysql_errno(connG_local));
	}

	res = mysql_store_result(connG_local);
	num_fields = mysql_num_fields(res);
	num_rows = mysql_num_rows(res);
	sprintf(central_query, "INSERT IGNORE Registos VALUES");
	while (row = mysql_fetch_row(res))
	{
		sprintf(str, "(");
		strcat(central_query, str);
		lengths = mysql_fetch_lengths(res);
		for (i = 0; i < num_fields; i++)
		{
			sprintf(str, "\"%.*s\"", (int)lengths[i],
					row[i] ? row[i] : "NULL");
			strcat(central_query, str);
			//Guarda o valor do tempo para depois se apagar os valores mais antigos na base de dados local
			if (i == 2)
				sprintf(datetime_limit, "%s", str);
			//Adiciona a "," entre os valores, não adicionando depois do último valor
			if (i < num_fields - 1)
			{
				sprintf(str, ",");
				strcat(central_query, str);
			}
		}
		sprintf(str, ")");
		strcat(central_query, str);

		//Adiciona a "," entre os tuplos, não adicionando depois do último tuplo
		if (j < num_rows && strlen(central_query) <= central_query_size - 100)
		{
			sprintf(str, ",");
			strcat(central_query, str);
		}
		//Se por acaso a query for demasiado grande para o tamanho da string vai divindo e submetendo até chegar ao fim da query
		else
		{
			printf("%s", central_query);
			// //Query para inserir os valores na base de dados central
			if (mysql_real_query(connG_central, central_query, (unsigned long)strlen(central_query)))
			{
				fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central), mysql_errno(connG_central));
			}
			printf("     %d\n", (int)strlen(central_query));
			sprintf(central_query, "INSERT IGNORE Registos VALUES");
		}
		j++;
	}
	mysql_free_result(res);

	//Apaga os valores da base de dados local já movidos para a base de dados central
	sprintf(local_query, "DELETE FROM Registos WHERE data_hora < %s", datetime_limit);
	if (mysql_real_query(connG_local, local_query, (unsigned long)strlen(local_query)))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_local), mysql_errno(connG_local));
	}
	return;
}

/**
 * @brief  Callback para ctrl+c, desliga ciclo infinito
 */
void InterceptCTRL_C(int a)
{
	keep_goingG = 0;
	return;
}
