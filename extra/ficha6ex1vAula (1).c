#include<stdio.h>
#include<string.h>
#include"ficha6ex1vAula.h"

int procuraAluno(Turma t , int numero){
    for( int i =0;i< t->tam; i++ ){
        if(t->al[i].numero == numero){
            return i;
        }            
    }
    return -1;
}

float calculaNotaMetodoA(MetodoA a){
    int menorNota = 100, sumNotas = 0;
    for(int i = 0; i< 6; i++){
        if(a.mt[i] < menorNota ) menorNota = a.mt[i];
        sumNotas += a.mt[i];
    }

    sumNotas -= menorNota;  

    if(a.exame > 0) return ((sumNotas/5) *0.40 + a.exame * 0.60)/5.0;

    return ((sumNotas/5) *0.40 + a.teste * 0.60)/5.0;
}

float calculaNotaMetodoB(MetodoB b){
    if(b.exame > 0) return b.exame/5.0;
    return b.teste/5.0;
}

float calculaNota(Aluno a){
    if(a.metodo == 'A'){
        return calculaNotaMetodoA(a.av.mA);
    } else{
        return calculaNotaMetodoB(a.av.mB);
    }
}

int calculaQtAlunosAprovados(Turma t){
    int contador = 0;
    for (int i = 0; i < t->tam;i++){
        if( calculaNota(t->al[i]) >= 10) contador++;
    }
    return contador ++;
}


int acrescentaAluno(Aluno a, Turma t ){
    
    if(procuraAluno(t, a.numero) != -1) return 1;

    if(t->tam == 100) return 2;

    //adicionar aluno
    strcpy(t->al[t->tam].nome,a.nome);
    t->al[t->tam].numero = a.numero;
    t->al[t->tam].metodo = a.metodo;
    t->al[t->tam].av = a.av;
    return 0;    
}