#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 6

typedef int t_veiculo;
typedef struct
{
	int inicio;
	int posicao;
	t_veiculo carro[MAXIMO];
} t_fileiras;

t_fileiras total_fileiras[MAXIMO];

int buscar_carro(t_fileiras *f, t_veiculo v);
int encontrar_carro(t_veiculo v, int *fileira, int *lugar);
int exibir_vagas();
int push(t_fileiras *f, t_veiculo v);
int fileira_cheia(t_fileiras *f);
int fileira_vazia(t_fileiras *f);

void inicio_pilha();
void exibir_fileiras(t_fileiras *f);
void push_carro(t_veiculo v);
void pop_carro(t_veiculo v);
void mostrar_estacionamento();

int main()
{
	int op = 0, fileira, lugar, status, placa;
	t_veiculo v = 0;
	inicio_pilha();
	system("cls");
	while (op != 5)
	{
		printf("Estacionamento oficina mecanica UNAERP\n\n");
		printf("------------------MENU------------------\n\n");
		printf("1- Estacionar veiculo no estacionamento\n");
		printf("2- Procurar veiculo na estacionamento\n");
		printf("3- Retirar veiculo do estacionamento\n");
		printf("4- Mostrar vagas do estacionamento\n");
		printf("5- Sair do sistema\n\n");
		printf("Digite a opcao que deseja: ");
		scanf("%i", &op);
		switch (op)
		{
		case 1:
			system("cls");
			printf("Insira a placa do veiculo:");
			scanf("%i", &placa);
			v = placa;
			push_carro(v);
			break;

		case 2:
			system("cls");
			printf("Numero da placa do veiculo: \n");
			scanf("%i", &placa);
			v = placa;

			status = encontrar_carro(v, &fileira, &lugar);
			if (status == 0)
				printf("Veiculo encontrado na fileira: %i e posicao: %i\n", fileira + 1, lugar + 1);
			else
				printf("Nao existe nenhum veiculo com essa placa\n");
			break;

		case 3:
			system("cls");
			printf("Placa do veiculo: ");
			scanf("%i", &placa);
			v = placa;
			pop_carro(v);
			break;

		case 4:
			system("cls");
			mostrar_estacionamento();
			printf("Observe as vagas vazias, para poder estacionar o proximo veiculo\n\n");
			break;

		case 5:
			exit(0);
			break;
		default:
			printf("Opcao invalida, tente novamente!!!\n");
		}
	}

	return (0);
}

void inicio_pilha()
{
	for (int i = 0; i < MAXIMO; i++)
	{
		t_fileiras f;
		f.inicio = -1;
		f.posicao = i;

		for (int k = 0; k < MAXIMO; k++)
		{
			t_veiculo v = 0;
			f.carro[k] = v;
		}
		total_fileiras[i] = f;
	}
}
int buscar_carro(t_fileiras *f, t_veiculo v)
{
	for (int i = 0; i < MAXIMO; i++)
	{
		if (f->carro[i] == v)
			return i;
	}

	return (-1);
}
int calcular_vagas()
{
	int atual = 0, vagas = 0;

	for (int i = 0; i < MAXIMO; i++)
	{
		t_fileiras f = total_fileiras[i];

		if (f.inicio != -1)
			atual += (f.inicio + 1);
	}
	vagas = 36 - atual;
	return (vagas);
}

void push_carro(t_veiculo v)
{
	int vagas, fileira = -1, lugar = -1, status = 0;
	vagas = calcular_vagas();

	if (vagas <= 0 && vagas > MAXIMO)
	{
		printf("\nNo momento o estacionamento esta cheio, aguardo um veiculo sair\n\n");
		return;
	}
	if ((status = encontrar_carro(v, &fileira, &lugar)) == 0)
	{
		printf("\nNao foi possivel cadastrar a placa desse veiculo, tente novamente!!\n");
		return;
	}

	for (int i = 0; i < MAXIMO; i++)
	{
		if (push(&total_fileiras[i], v) != -1)
			return;
	}
}
int encontrar_carro(t_veiculo v, int *fileira, int *lugar)
{
	int vagas = calcular_vagas();
	if (vagas == 36)
	{
		return (-1);
	}

	for (int i = 0; i < MAXIMO; i++)
	{
		t_fileiras f = total_fileiras[i];

		if ((*lugar = buscar_carro(&f, v)) != -1)
		{
			*fileira = i;
			return (0);
		}
	}

	return (-1);
}
void mostrar_estacionamento()
{
	int vagas;
	vagas = calcular_vagas();
	for (int i = 0; i < MAXIMO; i++)
	{
		t_fileiras f = total_fileiras[i];
		exibir_fileiras(&f);
	}
	printf("Vagas disponiveis: %i\n", vagas);
}
void pop_carro(t_veiculo v)
{
	int vagas;
	int pos = 0, status = 0, fileira = -1, lugar = -1, contador = 0;
	t_veiculo placas_fileiras[MAXIMO];
	t_fileiras *f;
	vagas = calcular_vagas();

	if (vagas == 36)
	{
		printf("\nNenhum veiculo cadastrado no estacionamento atualmente\n");
		return;
	}

	if (status = encontrar_carro(v, &fileira, &lugar))
	{
		printf("Placa: %i nao encontrada no sistema\n", v);
		return;
	}

	f = &total_fileiras[fileira];

	for (int i = 0; i < MAXIMO; i++)
	{
		if (i != lugar)
		{
			placas_fileiras[contador] = f->carro[i];
			contador += 1;
		}
	}

	for (int i = 0; i < MAXIMO; i++)
		f->carro[i] = placas_fileiras[i];
	f->inicio--;

	printf("Veiculo da placa %i removido do estacionamento\n", v);
}
int fileira_cheia(t_fileiras *f)
{
	return f->inicio == (MAXIMO - 1);
}
int fileira_vazia(t_fileiras *f)
{
	return f->inicio == -1;
}

int push(t_fileiras *f, t_veiculo v)
{
	if (fileira_cheia(f) != 0)
	{

		return (-1);
	}
	printf("Veiculo com a placa: %i foi estacionado na fileira de numero %i\n\n", v, f->posicao + 1);
	f->carro[++f->inicio] = v;
	return (0);
}

void exibir_fileiras(t_fileiras *f)
{
	int count = 0;
	printf("Fileira %i do estacionamento: ", f->posicao + 1);
	//mostra todos os 6 carros de uma fileira
	for (int i = 0; i < MAXIMO; i++)
	{

		printf("%i | ", f->carro[i]);
	}
	printf("\n");
}
