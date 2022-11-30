#include "CrudAluno.h"
#include <iostream>   // ENTRADA E SAÍDA PADRÃO
#include <cstring>    // PARA USAR strcpy() e strcmp()
#include <fstream>    // MANIPULAR ARQUIVOS
#include <string.h>
#pragma warning(disable:4996) //Para desabilitar o erro 4996

struct Aluno
{
    int ra;
    char nome[31];
    int idade;
};

int quantosAlunos = 0;

int getQuantosAlunos()
{
    return quantosAlunos;
}

void setQuantosAlunos(int quantidade)
{
    quantosAlunos = quantidade;
}

void quantidadeAlunosCadastrados()
{
    std::cout << getQuantosAlunos() + " \n";
}

void incluirAluno()
{
    int ra;
    char nome[31];
    int idade;
    std::cout << "Digite o Ra do aluno\n";
    std::cin >> ra;                                                   
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    std::cout << "Digite o nome do aluno\n";
    std::cin >> nome;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    std::cout << "Digite a idade do aluno\n";
    std::cin >> idade;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    Aluno aluno;
    aluno = {ra,"nome",idade};
    int posicao = 0;
    FILE* PtrAluno = fopen("Alunos.dat", "ab");
    fflush(stdin);
   
    //posicao = buscaBinariaAluno(aluno.ra);

    if(posicao == 0) // se posição = 0 quer dizer que encontramos o registro de aluno
    {
       //std::cout << "Registro de aluno já registrado";
       printf("Registro de aluno registrado");
    }
    else
    {
       fwrite(&aluno, sizeof(Aluno), 1, PtrAluno); //Incluimos o aluno no arquivo binário de alunos
       quantosAlunos++; //Incremnetamos +1 ao contador de aluno, após a inclusão
    }
    fclose(PtrAluno);
}

void excluirAluno()
{
    int ra;
    char nome[31];
    int idade;
    std::cout << "Digite o Ra do aluno\n";
    std::cin >> ra;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    std::cout << "Digite o nome do aluno\n";
    std::cin >> nome;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    std::cout << "Digite a idade do aluno\n";
    std::cin >> idade;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    Aluno aluno;
    aluno = { ra,"nome",idade };
    int posicao = 0;
    FILE* PtrAluno = fopen("Alunos.dat", "ab");
    fflush(stdin);

    //posicao = buscaBinariaAluno(aluno.ra);

    if (posicao != 0) // se posição = 0 quer dizer que encontramos o registro de aluno
    {
        //std::cout << "Registro de aluno já registrado";
        printf("Cadastre um aluno, para poder excluir");
    }
    else
    {
        printf("Aluno excluido com sucesso");
    }
    fclose(PtrAluno);
}

void alterarAluno()
{
    int ra;
    char nome[31];
    int idade;
    std::cout << "Digite o Ra do aluno\n";
    std::cin >> ra;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    std::cout << "Digite o nome do aluno\n";
    std::cin >> nome;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    std::cout << "Digite a idade do aluno\n";
    std::cin >> idade;
    std::cin.ignore(80, '\n');// LIMPA BUFFER DO TECLADO
    Aluno aluno;
    aluno = { ra,"nome",idade };
    int posicao = 0;
    FILE* PtrAluno = fopen("Alunos.dat", "ab");
    fflush(stdin);
    fread(&aluno, sizeof(Aluno), 1, PtrAluno);

    if (feof(PtrAluno))
    {
        printf("Nenhum registro cadastrado!");
    }
    else
    {
        fflush(stdin);
        //posicao = buscaBinariaAluno(aluno.ra);

        if (posicao != 0)
        {
            printf("Cadastre um aluno primeiro, para poder alterar");
        }
        else
        {
            fseek(PtrAluno, posicao, 0);
            fwrite(&aluno, sizeof(Aluno), 1, PtrAluno);
            printf("Registro atualizado corretamente!");
        }
    }
    fclose(PtrAluno);
}

int buscaBinariaAluno() //Busca o aluno pelo seu Ra, retornrá 0 se não encontrar o aluno
{
    //Aluno aluno;
    //int Inicio = 0, Meio, Fim;
    //fseek(aluno, 0, 2);
    //Fim = ftell(aluno) / sizeof(Aluno) - 1;  // Fim = QtdedeRegistros - 1
    //Meio = Fim / 2;
    //fseek(aluno, Meio * sizeof(Aluno), 0);
    //fread(&RegM, sizeof(Aluno), 1, aluno);
    return 0;

}

void lerAquivoAlunos()
{
    FILE* arq;
    double Vet[100];
    int result;
    int i;
    // Abre um arquivo BINÁRIO para LEITURA
    arq = fopen("Alunos.dat", "rb");
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    result = fread(&Vet[0], sizeof(Aluno), 100, arq);
    printf("Numero de elementos lidos: %d\n", result);

    for (i = 0; i < result; i++)
        printf("%lf\n", Vet[i]);

    fclose(arq);
}

void gravarArquivoAlunos()
{
    FILE* arq;
    int result;
    int i;
    Aluno aluno;

    arq = fopen("Alunos.dat", "wb"); // Cria um arquivo binário para gravação

    if (arq == NULL) // Se não conseguiu criar
    {
        printf("Problemas na CRIACAO do arquivo\n");
        return;
    }
    result = fwrite(&aluno, sizeof(Aluno), 0, arq);

    printf("Numero de elementos gravados: %d", result);
    fclose(arq);
}


short menu(void)  // MENU PRINCIPAL COM TODAS AS OPÇÕES
{    
    short opcao;// ARMAZENA A OPCAO DO MENU
    do {
        std::cout << " Menu Crud\n\n\n";
        std::cout << " [1] - Cadastrar registro.\n\n";
        std::cout << " [2] - Excluir Aluno.\n\n";
        std::cout << " [3] - Pesquisar aluno por Ra.\n\n";
        std::cout << " [4] - Exibir quantidade de alunos Cadastrados.\n\n";
        std::cout << " [5] - Alterar registro.\n\n";
        std::cout << " [0] - Sair.\n\n";
        std::cout << " Entre a opcao desejada: ";
        std::cin >> opcao;  // LEITURA DA OPÇÃO DESEJADA
        std::cin.ignore(80, '\n'); // LIMPA BUFFER DO TECLADO
    } while (opcao < 0 or 5 < opcao); // EVITA OPCÃO INEXISTENTE
    return opcao; // RETORNA O NÚMERO DA OPÇÃO
}

int main()
{
    short opcao;// ARMAZENA A OPCAO DO MENU

    do {
        opcao = menu(); // menu() RETORNA UMA OPCAO TRATADA VALIDA
        switch (opcao) {                                          
        case 1: incluirAluno();break;
        case 2: excluirAluno(); break;
        case 3: buscaBinariaAluno(); break;
        case 4: quantidadeAlunosCadastrados();break;
        case 5: alterarAluno(); break;
        }
    } while (opcao);

    return 0;
}