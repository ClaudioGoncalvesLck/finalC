#include "Header.h"

/*Procedimento para abrir ficheiro binario*/
void abrirFicheiro(char * nome)
{
	/*Abrir o ficheiro em modo leitura e escrita*/
	fp = fopen(nome, "r+b");
	if (fp == NULL)
	{
		/*Criar um ficheiro e abrir em modo escrita e leitura*/
		fp = fopen(nome, "w+b");
		if (fp == NULL)
		{
			printf("Impossivel criar ficheiro %s.\n",nome);
			exit(1);
		}
	}
	/*if (fp != NULL)
	{
		printf("Abertura do ficheiro \"%s\" com sucesso!\n",nome);
	}*/
}
/*Procedimento para abrir um ficheiro tendo outro aberto*/
void abrirFicheiroTmp(char* nome)
{
	/*Abrir o ficheiro em modo leitura e escrita*/
	fp_tmp = fopen(nome, "r+b");
	if (fp_tmp == NULL)
	{
		/*Criar um ficheiro e abrir em modo escrita e leitura*/
		fp_tmp = fopen(nome, "w+b");
		if (fp_tmp == NULL)
		{
			printf("Impossivel criar ficheiro %s.\n", nome);
			exit(1);
		}
	}
	/*if (fp_tmp != NULL)
	{
		printf("Abertura do ficheiro \"%s\" com sucesso!\n", nome);
	}*/
}

/*-----------------------------COLABORADOR-------------------------------*/
/*Proccedimento que agrega as funcoes para inserir um colaborador*/
void inserirColaborador()
{
	Colaborador c;
	lerColaborador(&c);
	registarColaborador(c);
}
/*Procedimento que le os dados relativos a um colaborador*/
void lerColaborador(Colaborador *c)
{
	printf("Codigo: ");
	scanf("%d", &c->codigo);
	fseek(stdin, 0, SEEK_END);
	printf("Nome: ");
	fgets(c->nome, MAX_NOME, stdin);
	c->apagado = ' ';
	fseek(stdin, 0, SEEK_END);
}
/*Procedimento que grava a informação de colaborador num ficheiero*/
void registarColaborador(Colaborador c)
{
	abrirFicheiro(F_Colaboradores);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&c, sizeof(c), 1, fp) != 1) 
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	fclose(fp);
}
/*Procedimento para editar o registo de um colaborador*/
void alterarColaborador()
{
	Colaborador c;
	long int numReg;

	listarColaboradores();
	printf("Numero do registo a alterar: ");
	scanf("%ld", &numReg);
	fseek(stdin, 0, SEEK_END);

	abrirFicheiro(F_Colaboradores);
	if (fseek(fp, (numReg - 1) * sizeof(Colaborador), SEEK_SET) != 0)
	{
		printf("Registo inexistente!\n");
		return;
	}
	if (fread(&c, sizeof(Colaborador), 1, fp) != 1)
	{
		printf("Problemas na leitura!\n");
		return;
	}
	if (c.apagado == '*')
	{
		printf("Este registo foi apagado, não pode ser alterado.\n");
	}
	printf("Dados atuais\n");
	apresentarColaborador(c);
	printf("Novos dados\n");
	lerColaborador(&c);
	//recuar um registo no ficheiro
	fseek(fp, -(long) sizeof(Colaborador), SEEK_CUR);
	//reescrever o registo
	fwrite(&c, sizeof(Colaborador), 1, fp);
	fclose(fp);
}
/*Procedimento que apaga um colaborador*/
void apagarColaborador()
{
	Auditoria a;
	Colaborador c;
	long int nReg;
	int aux = 0, codigo;
	char resp;
	

	abrirFicheiro(F_Colaboradores);
	printf("Numero do registo: ");
	scanf("%ld", &nReg);
	printf("Codigo do trabalhador: ");
	scanf("%d", &codigo);
	fseek(stdin, 0, SEEK_END);
	if (fseek(fp, (nReg - 1) * sizeof(Colaborador), SEEK_SET) != 0)
	{
		printf("Registo inexistente!\n");
		return;
	}
	if (fread(&c, sizeof(Colaborador), 1, fp) != 1)
	{
		printf("Problemas na leitura!\n");
		return;
	}
	if (c.apagado == '*')
	{
		printf("Registo ja estava apagado.\n");
		return;
	}
	printf("\nDados atuais\n");
	apresentarColaborador(c);
	printf("\nApagar Registo (s/n)?: ");
	resp = getchar();
	fseek(stdin, 0, SEEK_END);
	if (resp == 'n')
	{
		return;
	}
	abrirFicheiroTmp(F_Auditorias);
	while (1)
	{
		if (fread(&a, sizeof(a), 1, fp_tmp) != 1)
		{
			break;
		}
		if (a.colaborador.codigo == codigo)
		{
			printf("Impossivel apagar registo!\n");
			printf("<ENTER> para continuar.\n");
			getchar();
			fseek(stdin, 0, SEEK_END);
			aux = 1;
			break;
		}
	}
	if (aux == 0)
	{
		c.apagado = '*';
		printf("Registo apagado.\n");
		printf("<ENTER> para continuar.\n");
		getchar();
		fseek(stdin, 0, SEEK_END);
	}
	fclose(fp_tmp);

	fseek(fp, -(long) sizeof(Colaborador), SEEK_CUR);
	fwrite(&c, sizeof(Colaborador), 1, fp);
	fflush(fp);
	fclose(fp);
}
/*Procedimento que lista os colaboradores*/
void listarColaboradores()
{
	long int cont = 0;
	Colaborador c;

	abrirFicheiro(F_Colaboradores);
	rewind(fp);
	/*Ciclo para listar todos os colaboradores exceto os que tiverem a flag ativa de apagados*/
	while (1)
	{
		/*Condicao de paragem*/
		if (fread(&c, sizeof(c), 1, fp) != 1)
		{
			break;
		}
		/*Condicao para saltar registos apagados*/
		if (c.apagado == '*')
		{
			cont++;
			continue;
		}
		printf("Registo %d", ++cont);
		apresentarColaborador(c);
	}
	fclose(fp);
}
/*Procedimento que mostra no ecra os dados de um colaborador*/
void apresentarColaborador(Colaborador c)
{
	printf("\tCodigo: %2d\tNome: %s", c.codigo, c.nome);
}



/*----------------------------VULNERABLIDADE-------------------------------*/


/*Procedimento para inserir uma vulnerabilidade*/
void inserirVulnerabilidade()
{
	Vulnerabilidade v;
	lerVulnerabilidade(&v);
	registarVulnerabilidade(v);
}
/*Procedimento que le os dados referentes a uma vulnerabilidade*/
void lerVulnerabilidade(Vulnerabilidade* v)
{
	char opcao = 's';
	int i = 0;
	v->qddVulnI = 0;
	v->codAuditoria = -1;
	printf("Codigo: ");
	scanf("%d", &v->codigo);
	fseek(stdin, 0, SEEK_END);
	printf("Descricao: ");
	fgets(v->descricao, MAX_NOME, stdin);
	fseek(stdin, 0, SEEK_END);
	printf("Impacto(0-baixo, 1-moderado, 2-elevado): ");
	scanf("%u", &v->impacto);
	fseek(stdin, 0, SEEK_END);
	printf("Resolvido (0-Nao, 1-Sim):");
	scanf("%u", &v->resolvido);
	fseek(stdin, 0, SEEK_END);
	v->apagado = ' ';
	printf("Insere o(s) equipamento(s)\n");

	while (opcao == 's' && i < MAX_EQUIPAMENTOS)
	{
		printf("Codigo do equipamento %d: ", i + 1);
		scanf("%d", &v->equipamentos[i].codigo);
		fseek(stdin, 0, SEEK_END);
		printf("Insere tipo do equipmanto %d: ", i + 1);
		fgets(v->equipamentos[i].tipo, MAX_EQUIP, stdin);
		fseek(stdin, 0, SEEK_END);
		printf("Insere marca do equipmanto %d: ", i + 1);
		fgets(v->equipamentos[i].marca, MAX_EQUIP, stdin);
		fseek(stdin, 0, SEEK_END);
		printf("Insere modelo do equipmanto %d: ", i + 1);
		fseek(stdin, 0, SEEK_END);
		fgets(v->equipamentos[i].modelo, MAX_EQUIP, stdin);
		fseek(stdin, 0, SEEK_END);
		printf("Insere data de aquisicao do equipmanto %d\n", i + 1);
		printf("Dia: ");
		scanf("%d", &v->equipamentos[i].dataAquisicao.dia);
		fseek(stdin, 0, SEEK_END);
		printf("Mes: ");
		scanf("%d", &v->equipamentos[i].dataAquisicao.mes);
		fseek(stdin, 0, SEEK_END);
		printf("Ano: ");
		scanf("%d", &v->equipamentos[i].dataAquisicao.ano);
		fseek(stdin, 0, SEEK_END);

		printf("Inserir vulnerabilidade em mais equipamentos ? (s / n)");
		scanf("%c", &opcao);
		i++;
		v->qddVulnI++;
	}
}
/*Procedimento que guarda a informação de uma vulnerabilidade num ficheiro*/
void registarVulnerabilidade(Vulnerabilidade v)
{
	abrirFicheiro(F_Vulnerabilidades);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&v, sizeof(v), 1, fp) != 1)
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	fclose(fp);
}


/*Procedimento para alterar uma vulnerabilidade*/
void alterarVulnerabilidade()
{
	Vulnerabilidade v;
	long int numReg;

	listarVulnerabilidadeSimples();
	printf("Numero do registo a alterar: ");
	scanf("%ld", &numReg);
	fseek(stdin, 0, SEEK_END);

	abrirFicheiro(F_Vulnerabilidades);
	if (fseek(fp, (numReg - 1) * sizeof(v), SEEK_SET) != 0)
	{
		printf("Registo inexistente!\n");
		return;
	}
	if (fread(&v, sizeof(v), 1, fp) != 1)
	{
		printf("Problemas na leitura!\n");
		return;
	}
	if (v.apagado == '*')
	{
		printf("Este registo foi apagado, não pode ser alterado.\n");
	}
	printf("Dados atuais\n");
	apresentarVulnerabilidade(v);
	printf("Novos dados\n");
	lerVulnerabilidade(&v);
	//recuar um registo no ficheiro
	fseek(fp, -(long) sizeof(v), SEEK_CUR);
	//reescrever o registo
	fwrite(&v, sizeof(v), 1, fp);
	fclose(fp);
}
/*Procedimento que lista as vulnerabilidades*/
void listarVulnerabilidadeSimples()
{
	long int cont = 0;
	Vulnerabilidade v;

	abrirFicheiro(F_Vulnerabilidades);
	rewind(fp);
	/*Ciclo para listar todos as vulnerabilidades exceto os que tiverem a flag ativa de apagados*/
	while (1)
	{
		if (fread(&v, sizeof(v), 1, fp) != 1)
		{
			break;
		}
		if (v.apagado == '*')
		{
			cont++;
			continue;
		}
		printf("Registo %d\n", ++cont);
		apresentarVulnerabilidade(v);
	}
	fclose(fp);
}
/*Procedimento que mostra no ecra os dados referentes a uma vulnerabilidade*/
void apresentarVulnerabilidade(Vulnerabilidade v)
{
	printf("Codigo: %d\tDescricao: %sImpacto: %u\tResolvido: %u\n", v.codigo, v.descricao, v.impacto, v.resolvido);
	/*ciclo para mostrar todos os equipamentos com a vulnerabilidade selecionada*/
	for (int i = 0; i < v.qddVulnI; i++)
	{
		printf("Codigo do equipamento: %d\n",v.equipamentos[i].codigo);
	}
}
/*Procedimento que adiciona vulnerabilidades numa auditoria*/
void adicionarVuln(Auditoria* a)
{
	int i, j;
	char opcao = 's';

	i = a->qddVulnI;
	printf("Novos dados\n");
	while (opcao == 's' && i < MAX_VULNERABILIDADES)
	{
		j = 0;
		printf("Codigo: ");
		scanf("%d", &a->Vulnerabilidades[i].codigo);
		fseek(stdin, 0, SEEK_END);
		printf("Descricao: ");
		fgets(a->Vulnerabilidades[i].descricao, MAX_NOME, stdin);
		fseek(stdin, 0, SEEK_END);
		printf("Impacto (0-baixo, 1-moderado, 2-elevado): ");
		scanf("%u", &a->Vulnerabilidades[i].impacto);
		fseek(stdin, 0, SEEK_END);
		printf("Resolvido (0-nao, 1-sim):");
		scanf("%u", &a->Vulnerabilidades[i].resolvido);
		fseek(stdin, 0, SEEK_END);
		a->Vulnerabilidades[i].apagado = ' ';

		printf("Insere o(s) equipamento(s)\n");
		while (opcao == 's' && j < MAX_EQUIPAMENTOS)
		{
			a->qddVulnI++;
			a->qddEquiI++;
			printf("Codigo do equipamento %d: ", j + 1);
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].codigo);
			fseek(stdin, 0, SEEK_END);
			printf("Insere tipo do equipmanto %d: ", j + 1);
			fgets(a->Vulnerabilidades[i].equipamentos[j].tipo, MAX_EQUIP, stdin);
			fseek(stdin, 0, SEEK_END);
			printf("Insere marca do equipmanto %d: ", j + 1);
			fgets(a->Vulnerabilidades[i].equipamentos[j].marca, MAX_EQUIP, stdin);
			fseek(stdin, 0, SEEK_END);
			printf("Insere modelo do equipmanto %d: ", j + 1);
			fseek(stdin, 0, SEEK_END);
			fgets(a->Vulnerabilidades[i].equipamentos[j].modelo, MAX_EQUIP, stdin);
			fseek(stdin, 0, SEEK_END);
			printf("Insere data de aquisicao do equipmanto %d\n", j + 1);
			printf("Dia: ");
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.dia);
			fseek(stdin, 0, SEEK_END);
			printf("Mes: ");
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.mes);
			fseek(stdin, 0, SEEK_END);
			printf("Ano: ");
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.ano);
			fseek(stdin, 0, SEEK_END);

			printf("Inserir vulnerabilidade em mais equipamentos ? (s / n)");
			scanf("%c", &opcao);
			fseek(stdin, 0, SEEK_END);
			a->Vulnerabilidades[i].equipamentos[j].apagado = ' ';
			j++;
		}
		printf("Inserir mais vulnerabilidades (s / n)");
		scanf("%c", &opcao);
		fseek(stdin, 0, SEEK_END);
		i++;
	}
	a->qddVulnR = a->qddVulnI;
	a->qddEquiR = a->qddEquiI;
}
/*Procedimento que remove vulnerabilidades numa auditoria*/
void removerVuln(Auditoria* a)
{
	int nReg, nEqui;
	char resp;

	printf("Numero do registo: ");
	scanf("%d", &nReg);
	printf("Numero do equipamento: ");
	scanf("%d", &nEqui);

	if (a->Vulnerabilidades[nReg - 1].equipamentos[nEqui - 1].apagado == '*')
	{
		printf("Registo ja estava apagado.\n");
		return;
	}
	else
	{
		a->Vulnerabilidades[nReg - 1].equipamentos[nEqui - 1].apagado = '*';
		a->qddVulnR--;
		a->qddEquiR--;
	}
}
/*Procedimento que agrupa as vulnerabilidades de uma auditoria pelo nivel de impacto*/
void listarVulnerabilidades()
{
	int cod, aux = 0, i1 = 0, i2 = 0, i3 = 0;
	int* ptrB; 
	int* ptrM;
	int* ptrE;
	Vulnerabilidade v;
	VulnImpacto vi;
	Auditoria a;
	
	ptrB = (int*)malloc(5 * sizeof(int));
	ptrM = (int*)malloc(5 * sizeof(int));
	ptrE = (int*)malloc(5 * sizeof(int));

	abrirFicheiro(F_Auditorias);
	rewind(fp);
	printf("Codigo das auditorias\n");
	/*Apresenta o codigo das auditorias*/
	while (1)
	{
		if (fread(&a, sizeof(a), 1, fp) != 1)
		{
			break;
		}
		apresentarCodAuditoria(a);
	}
	fclose(fp);
	abrirFicheiro(F_Vulnerabilidades);
	rewind(fp);
	abrirFicheiroTmp(F_VulnImpacto);
	
	printf("Selecionar codigo: ");
	scanf("%d", &cod);
	fseek(stdin, 0, SEEK_END);

	printf("Vulnerabilidades da auditoria com codigo %d\n", cod);
	/*Ciclo que percorre o ficheiro todo*/
	while (1)
	{
		if (fread(&v, sizeof(v), 1, fp) != 1)
		{
			break;
		}
		if (v.apagado == '*')
		{
			continue;
		}
		/*Condição para encontrar o match dos codigos da auditoria*/
		if (v.codAuditoria == cod)
		{
			vi.codAud = cod;
			if (v.impacto == 0)
			{
				/*Ciclo que preenchem o array com os dados agrupads pelo impacto*/
				for (int i = 0 ; i < v.qddVulnI; i++)
				{
					if (v.apagado == ' ')
					{
						ptrB[i1] = v.equipamentos[i].codigo;
						i1++;
					}
				}
			}
			if (v.impacto == 1)
			{	
				/*Ciclo que preenchem o array com os dados agrupads pelo impacto*/
				for (int i = 0; i < v.qddVulnI; i++)
				{
					if (v.apagado == ' ')
					{
						ptrM[i2] = v.equipamentos[i].codigo;
						i2++;
					}
				}
			}
			if (v.impacto == 2)
			{
				/*Ciclo que preenchem o array com os dados agrupads pelo impacto*/
				for (int i = 0; i < v.qddVulnI; i++)
				{
					if (v.apagado == ' ')
					{
						ptrE[i3] = v.equipamentos[i].codigo;
						i3++;
					}
				}
			}
		}
	}
	/*ciclo que mostra no ecra os dados agrupados e grava-os no ficheiro permanentemente*/
	printf("Impacto baixo: \n");
	for (int i = 0; i < i1; i++)
	{
		fseek(fp_tmp, 0, SEEK_END);
		if (fwrite(&vi, sizeof(vi), 1, fp_tmp) != 1)
		{
			printf("Erro na escrita do ficheiro.\n");
		}
		printf("\tcodigo do equipamento: %d\n", ptrB[i]);
	}
	/*ciclo que mostra no ecra os dados agrupados e grava-os no ficheiro permanentemente*/
	printf("Impacto medio: \n");
	for (int i = 0; i < i2; i++)
	{	
		fseek(fp_tmp, 0, SEEK_END);
		if (fwrite(&vi, sizeof(vi), 1, fp_tmp) != 1)
		{
			printf("Erro na escrita do ficheiro.\n");
		}
		printf("\tcodigo do equipamento: %d\n", ptrM[i]);
	}
	/*ciclo que mostra no ecra os dados agrupados e grava-os no ficheiro permanentemente*/
	printf("Impacto alto: \n");
	for (int i = 0; i < i3; i++)
	{
		fseek(fp_tmp, 0, SEEK_END);
		if (fwrite(&vi, sizeof(vi), 1, fp_tmp) != 1)
		{
			printf("Erro na escrita do ficheiro.\n");
		}
		printf("\tcodigo do equipamento: %d\n", ptrE[i]);
	}
	fclose(fp_tmp);
	fclose(fp);
	printf("<ENTER> para continuar");
	getchar();
	fseek(stdin, 0, SEEK_END);
}

/*Procedimento para apresentar o codigo das auditorias*/
void apresentarCodAuditoria(Auditoria a)
{
	printf("Codigo: %d\n", a.codigo);
}

/*Procedimento que apresenta as vulenerabilidades num equipamento*/
void listarVulnPorEquipamento()
{
	Auditoria a;
	VulnEquipamento v;
	int codEqui;

	printf("Insere codigo do equipamento: ");
	scanf("%d", &codEqui);
	fseek(stdin, 0, SEEK_END);

	abrirFicheiro(F_Auditorias);
	rewind(fp);

	while (1)
	{
		/*Condicao de paragem*/
		if (fread(&a, sizeof(a), 1, fp) != 1)
		{
			break;
		}
		/*ciclo para percorrer todas as posiçoes do array de vulnerabilidades*/
		for (int i = 0; i < MAX_VULNERABILIDADES; i++)
		{
			if (a.Vulnerabilidades[i].apagado == '*')
			{
				continue;
			}
			/*ciclo para percorrer todas as posiçoes do array de equipamentos, para cada posicao no array de vulnerabilidades*/
			for (int j = 0; j < MAX_EQUIPAMENTOS; j++)
			{
				if (a.Vulnerabilidades[i].equipamentos[j].codigo == codEqui)
				{
					printf("Data da detecao da vulnerabilidade: %d/%d/%d\n", a.data.dia, a.data.mes, a.data.ano);
					if (a.Vulnerabilidades[i].resolvido == 1)
					{
						printf("Resolvido.\n");
					}
					else
					{
						printf("Por resolver.\n");
					}
					v.data.dia = a.data.dia;
					v.data.mes = a.data.mes;
					v.data.ano = a.data.ano;
					v.resolvido = a.Vulnerabilidades[i].resolvido;
				}
			}
		}
	}
	fclose(fp);
	abrirFicheiro(F_Equipamentos);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&v, sizeof(v), 1, fp) != 1)
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	fclose(fp);	
	printf("<ENTER> para continuar");
	getchar();
	fseek(stdin, 0, SEEK_END);
}



/*--------------------------AUDITORIA----------------------------------------*/


/*Procedimento para adicionar auditoria*/
void inserirAuditoria()
{
	Auditoria a;
	lerAuditoria(&a);
	registarAuditoria(a);
}
/*Procedimento que le os dados referentes a uma auditoria*/
void lerAuditoria(Auditoria * a)
{
	Colaborador c;
	Vulnerabilidade v;
	Equipamento e;
	char opcao = 's', inseriu = 'n';
	int i = 0, j = 0;
	a->qddVulnI = 0;
	a->qddEquiI = 0;

	printf("Codigo: ");
	scanf("%d", &a->codigo);
	fseek(stdin, 0, SEEK_END);
	printf("Duracao: ");
	scanf("%d", &a->duracao);

	printf("Inserir dados referentes ao Colaborador\n");
	printf("Codigo: ");
	scanf("%d", &a->colaborador.codigo);
	fseek(stdin, 0, SEEK_END);
	printf("Nome: ");
	fgets(a->colaborador.nome, MAX_NOME, stdin);
	a->colaborador.apagado = ' ';
	fseek(stdin, 0, SEEK_END);

	/*Copia dos dados de um colaborador para outra estrutura para guardar num ficheiro referente aos colaboradores*/
	c.codigo = a->colaborador.codigo;
	strcpy(c.nome, a->colaborador.nome);
	c.apagado = ' ';
	abrirFicheiro(F_Colaboradores);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&c, sizeof(c), 1, fp) != 1)
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	fclose(fp);

	printf("Inserir data\n");
	printf("Dia: ");
	scanf("%d", &a->data.dia);
	fseek(stdin, 0, SEEK_END);
	printf("Mes: ");
	scanf("%d", &a->data.mes);
	fseek(stdin, 0, SEEK_END);
	printf("Ano: ");
	scanf("%d", &a->data.ano);
	fseek(stdin, 0, SEEK_END);
	
	printf("Inserir vulnerabilidades (s / n)");
	scanf("%c", &opcao);
	fseek(stdin, 0, SEEK_END);

	/*ciclo para inserir vulnerabilidades*/
	while (opcao == 's' && i < MAX_VULNERABILIDADES)
	{
		if (inseriu == 'n')
		{
			a->qddVulnI = 0;
			a->qddEquiI = 0;
		}

		j = 0;
		a->Vulnerabilidades[i].codAuditoria = a->codigo;
		printf("Codigo: ");
		scanf("%d", &a->Vulnerabilidades[i].codigo);
		fseek(stdin, 0, SEEK_END);
		printf("Descricao: ");
		fgets(a->Vulnerabilidades[i].descricao, MAX_NOME, stdin);
		fseek(stdin, 0, SEEK_END);
		printf("Impacto (0-baixo, 1-moderado, 2-elevado): ");
		scanf("%u", &a->Vulnerabilidades[i].impacto);
		fseek(stdin, 0, SEEK_END);
		printf("Resolvido (0-nao, 1-sim):");
		scanf("%u", &a->Vulnerabilidades[i].resolvido);
		fseek(stdin, 0, SEEK_END);
		a->Vulnerabilidades[i].apagado = ' ';
		/*Copia dos dados de uma auditoria para outra estrutura para guardar num ficheiro referente a auditorias*/
		v.codAuditoria = a->codigo;
		v.codigo = a->Vulnerabilidades[i].codigo;
		strcpy(v.descricao, a->Vulnerabilidades[i].descricao);
		v.impacto = a->Vulnerabilidades[i].impacto;
		v.resolvido = a->Vulnerabilidades[i].resolvido;
		v.apagado = ' ';

		printf("Insere o(s) equipamento(s)\n");
		/*Ciclo para inserir os equipamentos referentes a uma vulnerabilidade*/
		while (opcao == 's' && j < MAX_EQUIPAMENTOS)
		{
			printf("Codigo do equipamento %d: ", j + 1);
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].codigo);
			fseek(stdin, 0, SEEK_END);
			printf("Insere tipo do equipmanto %d: ", j + 1);
			fgets(a->Vulnerabilidades[i].equipamentos[j].tipo, MAX_EQUIP, stdin);
			fseek(stdin, 0, SEEK_END);
			printf("Insere marca do equipmanto %d: ", j + 1);
			fgets(a->Vulnerabilidades[i].equipamentos[j].marca, MAX_EQUIP, stdin);
			fseek(stdin, 0, SEEK_END);
			printf("Insere modelo do equipmanto %d: ", j + 1);
			fseek(stdin, 0, SEEK_END);
			fgets(a->Vulnerabilidades[i].equipamentos[j].modelo, MAX_EQUIP, stdin);
			fseek(stdin, 0, SEEK_END);
			printf("Insere data de aquisicao do equipmanto %d\n", j + 1);
			printf("Dia: ");
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.dia);
			fseek(stdin, 0, SEEK_END);
			printf("Mes: ");
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.mes);
			fseek(stdin, 0, SEEK_END);
			printf("Ano: ");
			scanf("%d", &a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.ano);
			fseek(stdin, 0, SEEK_END);
			/*Copia dos dados de uma vulnerabilidade para outra estrutura para guardar num ficheiro referente a vulnerabilidades*/
			v.equipamentos[j].codigo = a->Vulnerabilidades[i].equipamentos[j].codigo;
			strcpy(v.equipamentos[j].tipo, a->Vulnerabilidades[i].equipamentos[j].tipo);
			strcpy(v.equipamentos[j].marca, a->Vulnerabilidades[i].equipamentos[j].marca);
			strcpy(v.equipamentos[j].modelo, a->Vulnerabilidades[i].equipamentos[j].modelo);
			v.equipamentos[j].dataAquisicao.dia = a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.dia;
			v.equipamentos[j].dataAquisicao.mes = a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.mes;
			v.equipamentos[j].dataAquisicao.ano = a->Vulnerabilidades[i].equipamentos[j].dataAquisicao.ano;

			printf("Inserir vulnerabilidade em mais equipamentos ? (s / n)");
			scanf("%c", &opcao);
			fseek(stdin, 0, SEEK_END);
			a->Vulnerabilidades[i].equipamentos[j].apagado = ' ';
			a->qddVulnI++;
			a->qddEquiI++;
			j++;
			inseriu = 's';
		}
		v.qddVulnI = a->qddVulnI;

		abrirFicheiro(F_Vulnerabilidades);
		fseek(fp, 0, SEEK_END);
		if (fwrite(&v, sizeof(v), 1, fp) != 1)
		{
			printf("Erro na escrita do ficheiro.\n");
		}
		fclose(fp);

		printf("Inserir mais vulnerabilidades (s / n)");
		scanf("%c", &opcao);
		i++;
	}
	/*Variaveis que guardam a informacao das vulnerabilidades inseridas e as reais (reais = inseridas - apagadas)*/
	a->qddVulnR = a->qddVulnI;
	a->qddEquiR = a->qddEquiI;
	fseek(stdin, 0, SEEK_END);
}
/*Procedimento que guarda os dados de uma auditoria num ficheiro*/
void registarAuditoria(Auditoria a)
{
	abrirFicheiro(F_Auditorias);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&a, sizeof(a), 1, fp) != 1)
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	fclose(fp);
}
/*Procedimento para alterar uma auditoria*/
void alterarAuditoria()
{
	Auditoria a;
	long int numReg;
	char ch;

	listarAuditoria();

	abrirFicheiro(F_Auditorias);
	printf("Numero do registo a alterar: ");
	scanf("%ld", &numReg);
	fseek(stdin, 0, SEEK_END);
	if (fseek(fp, (numReg - 1) * sizeof(Auditoria), SEEK_SET) != 0)
	{
		printf("Registo inexistente!\n");
		return;
	}
	if (fread(&a, sizeof(Auditoria), 1, fp) != 1)
	{
		printf("Problemas na leitura!\n");
		return;
	}
	printf("Dados atuais\n");
	apresentarVulnAuditoria(a);
	printf("Alterar vulnerabilidades (0 - Remover, 1 - Adicionar)\n");
	scanf("%c", &ch);
	fseek(stdin, 0, SEEK_END);
	if (ch == '1')
	{
		adicionarVuln(&a);
		apresentarVulnAuditoria(a);
	}
	else if (ch == '0')
	{
		removerVuln(&a);
		apresentarVulnAuditoria(a);
	}

	fseek(fp, -(long) sizeof(Auditoria), SEEK_CUR);
	//reescrever o registo
	fwrite(&a, sizeof(Auditoria), 1, fp);
	fclose(fp);
}
/*Procedimento que mostra os dados presentes numa auditoria*/
void apresentarVulnAuditoria(Auditoria a)
{
	if (a.qddVulnI == 0)
	{
		printf("Esta auditoria nao tem vulnerabilidades associadas.\n");
	}
	for (int i = 0; i < a.qddVulnI; i++)
	{
		if (a.Vulnerabilidades[i].apagado == ' ')
		{
			printf("\nRegisto %d\nCodigo: %d", i + 1, a.Vulnerabilidades[i].codigo);
			printf("\nDescricao: %s", a.Vulnerabilidades[i].descricao);
			printf("Impacto (0 - baixo, 1 - moderado, 2 - elevado): %u\n", a.Vulnerabilidades[i].impacto);
			printf("Resolvido (0 - nao, 1 - sim): %u\n", a.Vulnerabilidades[i].resolvido);

			for (int j = 0; j < a.qddEquiI; j++)
			{
				if (a.Vulnerabilidades[i].equipamentos[j].apagado == ' ')
				{
					printf("Vulnerabilidade no equipamento %d\n\tCodigo: %d\n", j + 1, a.Vulnerabilidades[i].equipamentos[j].codigo);
					printf("\tTipo: %s\tMarca: %s\tModelo: %s", a.Vulnerabilidades[i].equipamentos[j].tipo,
						a.Vulnerabilidades[i].equipamentos[j].marca,
						a.Vulnerabilidades[i].equipamentos[j].modelo);
					printf("\tData de aquisicao: %d/%d/%d\n", a.Vulnerabilidades[i].equipamentos[j].dataAquisicao.dia,
						a.Vulnerabilidades[i].equipamentos[j].dataAquisicao.mes,
						a.Vulnerabilidades[i].equipamentos[j].dataAquisicao.ano);
				}
				if (a.Vulnerabilidades[i].equipamentos[j].apagado == '*')
				{
					continue;
				}
			}
		}
	}
}
/*Procedimento que apresenta as auditorias guardas no ficheiro referente as auditorias*/
void listarAuditoria()
{
	int cont = 0;
	Auditoria a;

	abrirFicheiro(F_Auditorias);
	rewind(fp);
	while (1)
	{
		if (fread(&a, sizeof(a), 1, fp) != 1)
		{
			break;
		}
		printf("Registo %d\t", ++cont);
		apresentarAuditoria(a);
	}
	fclose(fp);
}
/*Procedimento que apresenta na consola dados resumidos referentes a uma auditoria*/
void apresentarAuditoria(Auditoria a)
{
	printf("Codigo - %d\tdata - %d/%d/%d\n", a.codigo, a.data.dia, a.data.mes, a.data.ano);
	printf("Quantidade de vulnerabilidades - %d\n", a.qddVulnR);
}

/*Procedimento para ordenar as auditorias pelo quantidade de vulnerablidades*/
void ordenaAuditorias()
{
	int* ptr;
	int  n, aux = 0, maior;
	Auditoria a;

	n = contaAuditorias();

	abrirFicheiro(F_Auditorias);
	rewind(fp);

	ptr = (int*)malloc(n * sizeof(int));

	if (ptr == NULL)
	{
		printf("Memoria nao foi alocada.\n");
		exit(0);
	}
	else
	{
		/*Ciclo que le todas as auditorias e guarda a informaçao do numero de vulnerabilidades num array*/
		while (1)
		{
			if (fread(&a, sizeof(a), 1, fp) != 1)
			{
				break;
			}
			ptr[aux] = a.qddVulnR;
			aux++;
		}
	}
	abrirFicheiroTmp(F_AuditoriasOrdenadas);

	maior = -1;
	/*ciclo que percorre o todo array e guarda o valor da primeira ocorrencia do maior numero */
	for (int i = 0; i < n; i++)
	{
		if (ptr[i] > maior)
		{
			maior = ptr[i];
		}
	}
	/*Ciclo executado ate todas as aditorias serem inseridas*/
	while (aux > 0)
	{
		/*ciclo que insere as auditorias com maior numero de vulnerabilidades*/
		for (int i = 0; i < n; i++)
		{
			if (maior == ptr[i])
			{
				if (fseek(fp, i * sizeof(a), SEEK_SET) != 0)
				{
					printf("Registo inexistente!\n");
					return;
				}
				if (fread(&a, sizeof(a), 1, fp) != 1)
				{
					printf("Problemas na leitura!\n");
					return;
				}
				fwrite(&a, sizeof(a), 1, fp_tmp);
				aux--;
			}
		}
		maior--;
	}
	fclose(fp_tmp);
	fclose(fp);
	listarAuditoriaOrdenadas();
}
/*Procedimento para apresentar auditorias*/
void listarAuditoriaOrdenadas()
{
	int cont = 0;
	Auditoria a;

	abrirFicheiro(F_AuditoriasOrdenadas);
	rewind(fp);
	while (1)
	{
		if (fread(&a, sizeof(a), 1, fp) != 1)
		{
			break;
		}
		printf("Registo %d\t", ++cont);
		apresentarAuditoria(a);
	}
	fclose(fp);
	fseek(stdin, 0, SEEK_END);
	printf("<ENTER> para continuar.");
	getchar();
	fseek(stdin, 0, SEEK_END);
}


/*Procedimento que apresenta os colaboradores*/
void selecionarColaborador() 
{
	int num;

	listarColaboradores();
	printf("Inserir codigo do colaborador: ");
	scanf("%d", &num);
	fseek(stdin, 0, SEEK_END);
	listarAuditoriaColaborador(num);
}
/*Procedimento que grava num ficheiro todas as ocorrencias de um colaborador*/
void listarAuditoriaColaborador(int n)
{
	int cont = 0;
	Auditoria a;

	abrirFicheiro(F_Auditorias);
	rewind(fp);
	while (1)
	{
		/*Condicao de paragem*/
		if (fread(&a, sizeof(a), 1, fp) != 1)
		{
			break;
		}
		if (a.colaborador.codigo == n)
		{
			apresentarAuditoriaColaborador(a);
		}
	}
	fclose(fp);
	printf("<Enter> para continuar.\n");
	getchar();
	fseek(stdin, 0, SEEK_END);
}
/*Procedimento para apresentar dados de auditorias referente a um colaborador*/
void apresentarAuditoriaColaborador(Auditoria a)
{
	printf("Codigo: %d\n",a.codigo);
	printf("Data: %d/%d/%d\n", a.data.dia, a.data.mes, a.data.ano);
	printf("Numero de vulnerabilidades: %d\n", a.qddVulnR);
}

/*Procedimento que conta todas as auditorias registadas num ficheiro*/
int contaAuditorias()
{
	int cont = 0;
	Auditoria a;

	abrirFicheiro(F_Auditorias);
	rewind(fp);
	while (fread(&a, sizeof(a), 1, fp) == 1)
	{
		cont++;
	}
	fclose(fp);
	return cont;
}
/*Procedimento que apresenta a auditoria com maior e menor numero de vulnerabilidades*/
void maiorMenorVulnerabilidades()
{
	Auditoria a;
	Auditoria maior;
	Auditoria menor;

	int aux = 0, vulnDetetadas = 0, qtddAuditorias = 0;

	abrirFicheiro(F_Auditorias);
	rewind(fp);

	while (fread(&a, sizeof(a), 1, fp) == 1)
	{
		if (aux == 0)
		{
			maior = a;
			menor = a;
			aux++;
		}
		else
		{
			if (maior.qddVulnR <= a.qddVulnR)
			{
				maior = a;
			}
			if (menor.qddVulnR >= a.qddVulnR)
			{
				menor = a;
			}
		}
	}
	fclose(fp);
	abrirFicheiro(F_MaisVulnerabilidades);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&maior, sizeof(a), 1, fp) != 1)
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	printf("Auditoria com mais vulnerabilidades.\n");
	apresentarAuditoria(maior);
	fclose(fp);
	abrirFicheiro(F_MenosVulnerabilidades);
	fseek(fp, 0, SEEK_END);
	if (fwrite(&menor, sizeof(a), 1, fp) != 1)
	{
		printf("Erro na escrita do ficheiro.\n");
	}
	printf("Auditoria com menos vulnerabilidades.\n");
	apresentarAuditoria(menor);
	fclose(fp);

}
/*Funcao que calcula a media de vulnerabilidades*/
float mediaVulnerabilidades()
{
	Auditoria a;
	int vulnDetetadas = 0, qtddAuditorias = 0;
	float media;
	abrirFicheiro(F_Auditorias);
	rewind(fp);

	while (fread(&a, sizeof(a), 1, fp) == 1)
	{
		vulnDetetadas = vulnDetetadas + a.qddVulnR;
		qtddAuditorias++;
	}
	fclose(fp);
	if (qtddAuditorias == 0)
	{
		printf("Impossivel calcular media de vulnerabilidades.\n");
		return;
	}
	return media = (float) vulnDetetadas / qtddAuditorias;
}

/*Procedimento que apresenta um dashboard*/
void dashboard()
{
	printf("Numero de auditorias realizadas: %d\n", contaAuditorias());
	maiorMenorVulnerabilidades();
	printf("Media de vulnerablidades: %f\n\n",mediaVulnerabilidades());
}
/*Procedimento para apresentar um menu*/
void menu()
{
	system("cls");
	dashboard();
	printf("Opcao\tDescricao\n");
	printf("1\tInserir Dados\n2\tEditar Dados\n3\tAdicionar e remover vulnerabilidades numa auditoria\n4\tRemover colaboradores\n5\tListar Dados\n0\tSair\n");
	printf("Seleciona opcao: ");
}
/*Procedimento para apresentar um sub-menu*/
void inserirDados() 
{
	int opcao;
	do
	{
		system("cls");
		dashboard();
		printf("Opcao\tDescricao\n");
		printf("1\tInserir Colaboradores\n2\tInserir vulnerabilidades\n3\tCriar auditorias\n0\tRetroceder\n");
		printf("Seleciona opcao: ");
		scanf("%d", &opcao);

		switch (opcao)
		{
			/*Opcao para Inserir Colaborador*/
			case 1:
				inserirColaborador();
				break;
			/*Opcao para Inserir vulnerabilidade*/
			case 2:
				inserirVulnerabilidade();
				break;
			/*Opcao para criar auditoria*/
			case 3:
				inserirAuditoria();
				break;
			default:
				if (opcao != 0)
				{
					printf("Opcao invalida!\n");
					break;
				}
		}
	} while (opcao != 0);
}
/*Procedimento para apresentar um sub-menu*/
void editarDados()
{
	int opcao;
	do
	{
		system("cls");
		dashboard();
		printf("Opcao\tDescricao\n");
		printf("1\tEditar Colaboradores\n2\tEditar vulnerabilidades\n0\tRetroceder\n");
		printf("Seleciona opcao: ");
		scanf("%d", &opcao);

		switch (opcao)
		{
			/*Opcao para Editar Colaborador*/
		case 1:
			alterarColaborador();
			break;
			/*Opcao para Editar vulnerabilidade*/
		case 2:
			alterarVulnerabilidade();
			break;
		default:
			if (opcao != 0)
			{
				printf("Opcao invalida!\n");
				break;
			}
		}
	} while (opcao != 0);
}
/*Procedimento para apresentar um sub-menu*/
void listar()
{
	int opcao;
	do
	{
		system("cls");
		dashboard();
		printf("Opcao\tDescricao\n");
		printf("1\tListar auditorias ordenadas por numero de vulnerabilidades\n2\tListar auditorias efetuadas por colaborador\n");
		printf("3\tListar vulnerabilidades pelo nivel de impacto\n4\tListar vulnerabilidades identificadas num equipamento\n0\tRetroceder\n");
		printf("Seleciona opcao: ");
		scanf("%d", &opcao);

		switch (opcao)
		{
			/*Opcao para Listar auditorias ordenadas por numero de vulnerabilidades*/
		case 1:
			ordenaAuditorias();
			break;
			/*Opcao para Listar auditorias efetuadas por colaborador*/
		case 2:
			selecionarColaborador();
			break;
			/*Opcao para Listar auditorias ordenadas por numero de vulnerabilidades*/
		case 3:
			listarVulnerabilidades();
			break;
			/*Opcao para Listar vulnerabilidades identificadas num equipamento*/
		case 4:
			listarVulnPorEquipamento();
			break;
		default:
			if (opcao != 0)
			{
				printf("Opcao invalida!\n");
				break;
			}
		}
	} while (opcao != 0);
}