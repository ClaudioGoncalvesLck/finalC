typedef struct metodoA{
    int mt[6];
    int teste;
    int exame;
} MetodoA;

typedef struct metodoB{
    int teste;
    int exame;
}MetodoB;

typedef union avaliacao{
    MetodoA mA;
    MetodoB mB;
}Avaliacao;

typedef struct aluno{
    int numero;
    char nome[100];
    char metodo;

    Avaliacao av;
}Aluno;

struct turma
{
    Aluno al[100];
    int tam;
};

typedef struct turma* Turma;

int procuraAluno(Turma t , int numero);

float calculaNota(Aluno a);

int calculaQtAlunosAprovados(Turma t);

int acrescentaAluno(Aluno a, Turma t );