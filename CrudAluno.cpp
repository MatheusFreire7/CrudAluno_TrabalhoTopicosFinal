#include "CrudAluno.h"
#include <iostream>
#include <fstream>
#include <cstring>    // PARA USAR strcpy() e strcmp()
#include <string.h>
using namespace std;
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
    ofstream arq("aluno.dat", ios::binary | ios::app);
    Aluno aluno;
    if (!arq)
    {
        std::cout << "Arquivo não pode ser aberto";
    }
    else
    {
        char ch;
        cout << "Voce quer digitar mais registros aperte s para sim: ";
        std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
        while (ch == 's')
        {
            cout << "\n Digite o Ra : ";
            cin >> aluno.ra;
            cout << "\n Digite o Nome : ";
            cin >> aluno.nome;
            cout << "\n Digite a idade : ";
            cin >> aluno.idade;
            arq.write((char*)&aluno, sizeof(aluno));
            cout << "Voce quer digitar mais registros aperte s para sim: ";
            std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
        }
        arq.close();
    }
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
    fstream iof("aluno.dat", ios::binary | ios::in | ios::out);
    iof.seekg(0);
    Aluno aluno;
    bool achou = false;
    if (!iof)
    {
        cout << "Arquivo não foi possível ser aberto";
    }
    else
    {
        int ra;
        int flag = 1;
        cout << "Digite o Ra do Aluno para altera-lo:";
        cin >> ra;
        cout << "Ra \tNome\tIdade\t\n";
        while (iof.read((char*)&aluno, sizeof(aluno)) && achou == false)
        {
            if (aluno.ra == ra)
            {
                cout << "Registro encontrado: \n";
                cout << aluno.ra << "\t";
                cout << aluno.nome << "\t";
                cout << aluno.idade << endl;
                cout << "\n";
                achou = true;
                cout << "Digite o novo aluno para alterar: \n";
                cout << "Ra: "; cin >> aluno.ra;
                cout << "Nome: "; cin >> aluno.nome;
                cout << "Idade: "; cin >> aluno.idade;
                iof.seekp(sizeof(aluno),ios::cur);
                //iof.seekg(sizeof(aluno), ios::cur);
                iof.write((char*)&aluno, sizeof(aluno));
            }
        }
        if (achou == false)
            cout << "Registro não encontrado: \n";
        iof.close();
    }
}

void buscaAluno() //Busca o aluno pelo seu Ra, retornrá 0 se não encontrar o aluno
{
    bool achou = false;
    Aluno aluno;
    ifstream ifs("aluno.dat", ios::binary);
    if (!ifs)
    {
        cout << "Arquivo não foi possível ser aberto";
    }
    else
    {
        int ra;
        int flag = 1;
        cout << "Digite o Ra para bucar o Aluno: ";
        cin >> ra;
        while (ifs.read((char*)&aluno, sizeof(aluno)))
        {
            if (aluno.ra == ra)
            {
                cout << "Registro encontrado: \n";
                cout << aluno.ra << "\t";
                cout << aluno.nome << "\t";
                cout << aluno.idade << endl;
                cout << "\n";
                achou = true;
            }
        }
        if(achou == false)
            cout << "Registro não encontrado: \n";
        ifs.close();
    }

}

void lerAquivoAlunos()
{
    ifstream arq("aluno.dat", ios::binary | ios::app);
    Aluno aluno;
    if (!arq)
    {
        std::cout << "Arquivo não pode ser aberto";
    }
    else
    {
        arq.read((char*)&aluno, sizeof(aluno));
        cout << "Ra :\t" << aluno.ra << endl;
        cout << "Nome :\t" << aluno.nome << endl;
        cout << "Idade :\t" << aluno.idade << endl;
        cout << "\n";
        arq.close();
    }
}

void gravarArquivoAlunos()
{
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
    Aluno aluno;

	ifstream ifs("aluno.dat", ios::binary);
	if (!ifs)
	{
		cout << "Arquivo não foi possível ser aberto";
	}
	else
	{
        cout << "Registros de alunos lidos: \n";
		cout << "Ra \tNome\tIdade\t\n";
		while (ifs.read((char*)&aluno, sizeof(aluno)))
		{
			cout << aluno.ra << "\t";
			cout << aluno.nome << "\t";
			cout << aluno.idade << endl;
		}
        cout << "\n";
		ifs.close();
	}
    

    short opcao;// ARMAZENA A OPCAO DO MENU

    do {
        opcao = menu(); // menu() RETORNA UMA OPCAO TRATADA VALIDA
        switch (opcao) {
        case 1: incluirAluno();break;
        case 2: excluirAluno(); break;
        case 3: buscaAluno(); break;
        case 4: quantidadeAlunosCadastrados();break;
        case 5: alterarAluno(); break;
        }
    } while (opcao);

    return 0;
}
