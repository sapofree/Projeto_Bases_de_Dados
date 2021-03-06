/**
 *       @file  myf.c
 *      @brief  Contém as funções para a execução do programa gestor_backups.c, as funções estão ordenadas por ordem de aparecimento no main
 *
 * Contém as estruturas das componentes de gerar e concatenar backups. Estas funções encontram-se nos ficheiros gerar.c e concatenar.c, respetivamente.
 *
 *     @author  Bruno Ramos, B.Ramos@ua.pt
 *
 *   @internal
 *     Created  29-Mar-2018
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2018, Bruno Ramos
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <string.h>
#include "myf.h"

/**
 * @brief Conectar às bases de dados no sistema central
 * @param void
 * @return void
 */
void CONNECT_CENTRAL_SYSTEM_DATABASES(void)
{
	//Dados do sistema central
	static char *host_central = HOST; //ip do sistema central
	static char *user_central = USER;
	static char *pass_central = PASS;
	static char *dbname_central = NULL; //Para não conectar a uma BD específica

	unsigned int port_central = 3306;
	static char *unix_socket_central = NULL;
	unsigned int flag_central = 0;

	//Conectar ao sistema central
	connG_central_system = mysql_init(NULL);
	if (!mysql_real_connect(connG_central_system, host_central, user_central, pass_central, dbname_central, port_central, unix_socket_central, flag_central))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central_system), mysql_errno(connG_central_system));
		exit(1);
	}
	return;
}


/**
 * @brief Componente de gerar backups, gera um backup individual para cada molde se este tiver registos e um backup geral para efeitos de recuperação do sistema
 * @param void
 * @return void
 */
void GERAR_BACKUPS(void)
{
	printf("\n------------------------------------------------\n");
	printf("Inicio da componente de gerar backups\n");

	//Limpar as bds backups e backups_temp para evitar dados residuais
	LIMPAR_BDS();

	//Ler data e hora do sistema para evitar perda de registos
	TIMESTAMP();
	printf("%s\n",datetime_limitG);

	//Copiar registos para a bd backups antes da data e hora lida anteriormente
	COPY_CENTRAL_TO_BACKUPS();

	//Gera um backup individual de cada molde, se este tiver gerado registos
	FILTRAR_E_GERAR_BACKUPS_INDIVIDUAIS();

	//Gera o backup geral para efeitos de recuperação de sistema
	GERAR_BACKUP_GERAL();

	//Limpa a bd central dos registos já armazenados em ficheiros
	LIMPAR_CENTRAL();

	printf("\nFim da componente de gerar backups\n");
	printf("------------------------------------------------\n");
	return;
}

/**
 * @brief Componente de gerar backups, gera um backup individual para cada molde se este tiver registos e um backup geral para efeitos de recuperação do sistema
 * @param void
 * @return void
 */
void CONCATENAR_BACKUPS(void)
{
	printf("\n------------------------------------------------\n");
	printf("Inicio da componente de concatenar backups\n");

	//Verificar se é necessário concatenar moldes
	TESTAR_ATUALIZAR();

	if(atualizarG)
	{
		printf("Sim\n");
		//Limpar as bds backups e backups_temp para evitar dados residuais
		LIMPAR_BDS();

		IDENTIFICAR_E_ARQUIVAR_MOLDES();

		LIMPAR_LISTA_DE_MOLDES_A_CONCATENAR();

		RESET_ATUALIZAR_BACKUPS();
	}else
	{
		printf("Não\n");
	}

	printf("\nFim da componente de concatenar backups\n");
	printf("------------------------------------------------\n");
	return;
}

/**
 * @brief Limpar as bds backups e backups_temp para evitar dados residuais
 * @param void
 * @return void
 */
void LIMPAR_BDS(void)
{
	char query[500];

	//Apaga moldes, sensores e registos da bd backups
	sprintf(query, "DELETE FROM backups.moldes");
	if (mysql_real_query(connG_central_system, query, (unsigned long)strlen(query)))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central_system), mysql_errno(connG_central_system));
	}

	//Apaga clientes da bd backups
	sprintf(query, "DELETE FROM backups.clientes");
	if (mysql_real_query(connG_central_system, query, (unsigned long)strlen(query)))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central_system), mysql_errno(connG_central_system));
	}

	//Apaga moldes, sensores e registos da bd backups_temp
	sprintf(query, "DELETE FROM backups_temp.moldes");
	if (mysql_real_query(connG_central_system, query, (unsigned long)strlen(query)))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central_system), mysql_errno(connG_central_system));
	}

	//Apaga clientes da bd backups_temp
	sprintf(query, "DELETE FROM backups_temp.clientes");
	if (mysql_real_query(connG_central_system, query, (unsigned long)strlen(query)))
	{
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(connG_central_system), mysql_errno(connG_central_system));
	}

	return;
}

/**
 * @brief  Callback para ctrl+c, desliga ciclo infinito
 */
/*void InterceptCTRL_C(int a)
{
	keep_goingG = 0;
	return;
}*/
