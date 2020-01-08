#include "Header.h"

int main()
{
	int opcao;

	/*Ciclo para mostrar o menu principal*/
	do
	{
		menu();
		scanf("%d", &opcao);
		switch (opcao)
		{
			case 1:
				inserirDados();
				break;
			case 2:
				editarDados();
				break;
			case 3:
				alterarAuditoria();
			case 4:
				listarColaboradores();
				apagarColaborador();
			case 5:
				listar();
		default:
			if (opcao != 0)
			{
				printf("Opcao invalida!\n");
				break;
			}
			break;
		}
	} while (opcao != 0);
	return 0;
}