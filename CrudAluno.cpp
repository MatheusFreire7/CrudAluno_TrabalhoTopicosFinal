#include "CrudAluno.h"
#include <iostream>
#include <fstream>
//#include <sqltypes.h>
//#include <sql.h>
//#include <sqlext.h>
#include <string.h>
#include<stdio.h>
using namespace std;
#pragma warning(disable:4996) //Para desabilitar o erro 4996 de alerta do windowns

struct Aluno
{
    int ra;
    char nome[31];
    int idade;
};

//void showSQLError(unsigned int handleType, const SQLHANDLE& handle) {
//    SQLCHAR SQLState[1024];
//    SQLCHAR message[1024];
//    if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
//        cout << "SQL driver menssagem: " << message << "\nSQL state: " << SQLState << "." << endl;
//}

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
    std::cout << "Quantidade de Alunos: ";
    std::cout << quantosAlunos;
    std::cout << "\n\n";
}

bool buscaAlunoRa(int ra) //Busca o aluno pelo seu Ra, retornrá 0 se não encontrar o aluno
{
    bool achou = false;
    Aluno aluno;

    ifstream ifs("aluno.dat", ios::binary);
    if (!ifs)
    {
        std::cout << "Arquivo não foi possível ser aberto";
    }
    else
    {
        while (ifs.read((char*)&aluno, sizeof(aluno)))
        {
            if (aluno.ra == ra)
            {
                achou = true;
            }
        }
        return achou;
        ifs.close();
    }

}

bool verifcaAtributoIntAluno(int tamanho, char atributo[])
{
    bool ehInt = true;
    for (int i = 0; i < tamanho; ++i) 
    {

        if (!isdigit(atributo[i])) 
        {
            ehInt = false;
        }
    }

    return ehInt;

}

bool verificaNome(int tamanhoNome, char nome[])
{
    bool ehNome = true;
    for (int i = 0; i < tamanhoNome; ++i)
    {
        if (isdigit(nome[i]))
        {
            ehNome = false;
        }
    }
    return ehNome;
}


void incluirAluno()
{
    try
    {
        ofstream arq("aluno.dat", ios::binary | ios::app);
        Aluno aluno;
        char ra[10]; //Char usados para verificar se são inteiros o ra e a idade digitados
        char idade[3];

        if (!arq)
        {
            std::cout << "Arquivo não pode ser aberto";
        }
        else
        {
            std::cout << "\n Digite o Ra : ";
            cin >>ra;
            int tamanhoRa = strlen(ra);
            if (verifcaAtributoIntAluno(tamanhoRa,ra) && tamanhoRa >= 5)
            {
                aluno.ra = std::strtol(ra, nullptr, 10);
                if (buscaAlunoRa(aluno.ra) == false)
                {
                    std::cout << "\n Digite o Nome : ";
                    cin >> aluno.nome;
                    int tamanhoNome = strlen(aluno.nome);
                    if (verificaNome(tamanhoNome, aluno.nome))
                    {
                        std::cout << "\n Digite a idade : ";
                        cin >> idade;
                        int tamanhoIdade = strlen(idade);
                        if (verifcaAtributoIntAluno(tamanhoIdade,idade))
                        {
                            aluno.idade = std::strtol(idade, nullptr, 10);
                            arq.write((char*)&aluno, sizeof(aluno));
                            quantosAlunos++;
                        }
                        else
                            std::cout << "Digite uma idade valida\n\n";
                    }
                    else
                        std::cout << "Digite um nome valido\n\n";
                      
                }
                else
                {
                    std::cout << "Aluno já existe\n\n";
                }
            }
            else
            {
                std::cout << "Digite um ra valido\n";
            }
               
            char ch;
            std::cout << "Voce quer incluir mais registros aperte s para sim: ";
            std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
            while (ch == 's')
            {
                std::cout << "\n Digite o Ra : ";
                cin >> ra;
                int tamanhoRa = strlen(ra);
                if (verifcaAtributoIntAluno(tamanhoRa, ra) && tamanhoRa >= 5)
                {
                    aluno.ra = std::strtol(ra, nullptr, 10);;
                    if (buscaAlunoRa(aluno.ra) == false)
                    {
                        std::cout << "\n Digite o Nome : ";
                        cin >> aluno.nome;
                        int tamanhoNome = strlen(aluno.nome);
                        if (verificaNome(tamanhoNome, aluno.nome))
                        {
                            std::cout << "\n Digite a idade : ";
                            cin >> idade;
                            int tamanhoIdade = strlen(idade);
                            if (verifcaAtributoIntAluno(tamanhoIdade, idade))
                            {
                                aluno.idade = std::strtol(idade, nullptr, 10);;
                                arq.write((char*)&aluno, sizeof(aluno));
                                quantosAlunos++;
                                std::cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                                std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                            }
                            else
                            {
                                std::cout << "Digite uma idade valida\n\n";
                                std::cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                                std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                            }
                        }
                        else
                        {
                            std::cout << "Digite um nome valido\n\n";
                            std::cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                            std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                        }
                    }
                    else
                    {
                        std::cout << "Aluno já existe \n\n";
                        std::cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                        std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                    }
                }
                else
                {
                    std::cout << "Digite um ra valido\n";
                    std::cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                    std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                }
            }
            arq.close();
        }
    }
    catch (exception)
    {
        throw new exception("Erro na inclusão do Aluno\n\n");
    }
   
}

void excluirAluno()
{
    try
    {
        bool fechouArq = false;
        ifstream ifs("aluno.dat", ios::binary | ios::in);
        ofstream ofs("temp.dat", ios::binary | ios::out);
        Aluno aluno;
        bool excluiu = false;

        if (!ifs || !ofs)
        {
            std::cout << "Arquivo não foi possível ser aberto";
        }
        else
        {
            char ra[10];

            std::cout << "Digite o Ra para excluir o Aluno: ";
            cin >> ra;
            int tamanhoRa = strlen(ra);
            if (verifcaAtributoIntAluno(tamanhoRa, ra))
            {
                if (buscaAlunoRa(std::strtol(ra, nullptr, 10)) == true)
                {
                    while (ifs.read((char*)&aluno, sizeof(aluno)))
                    {
                        if (aluno.ra != std::strtol(ra, nullptr, 10))
                        {
                            ofs.write((char*)&aluno, sizeof(aluno));
                        }
                        if (aluno.ra == std::strtol(ra, nullptr, 10))
                        {
                            std::cout << "Excluimos com sucesso o Aluno \n\n";
                            excluiu = true;
                        }
                    }

                    if (excluiu == false)
                    {
                        std::cout << "Não conseguimos excluir o Aluno\n\n";
                    }
                    else
                    {
                        ifs.close();
                        ofs.close();
                        std::remove("aluno.dat");
                        std::rename("temp.dat", "aluno.dat");
                        quantosAlunos--;
                        fechouArq = true;
                    }
                     
                }
                else
                {
                    std::cout << "Aluno digitado não está cadastrado \n\n";
                }
            }
            else
            {
                std::cout << "Digite um Ra valido \n\n";
            }
           
            if (fechouArq == false)
            {
                ifs.close();
                ofs.close();
            }
          
        }
    }
    catch (exception)
    {
        throw new exception("Erro na exclusão do Aluno\n\n");
    }
    

}

void alterarAluno()
{
    try
    {
        bool fechouArq = false;
        ifstream ifs("aluno.dat", ios::binary | ios::in);
        ofstream ofs("temp.dat", ios::binary | ios::out);
        Aluno aluno;
        char ra[10];
        char novoRa[10];
        char novaIdade[3];
        bool ehPossivelAlterar = false;

        if (!ifs || !ofs)
        {
            std::cout << "Arquivo não foi possível ser aberto";
        }
        else
        {
            
            std::cout << "Digite o Ra do Aluno que quer alterar: ";
            cin >> ra;
            int tamanhoRa = strlen(ra);
            if (verifcaAtributoIntAluno(tamanhoRa, ra))
            {
                if (buscaAlunoRa(std::strtol(ra, nullptr, 10)) == true)
                {
                    ehPossivelAlterar = true;
                    while (ifs.read((char*)&aluno, sizeof(aluno)))
                    {
                        if (aluno.ra != std::strtol(ra, nullptr, 10))
                        {
                            ofs.write((char*)&aluno, sizeof(aluno));
                        }
                    }
                }
                else
                    std::cout << "Aluno digitado não está cadastrado\n\n";
            }
            else
                std::cout << "Digite um Ra valido para poder alterar\n\n";


            //ifs.close();
            //ofs.close();
            //std::remove("aluno.dat");
            //std::rename("temp.dat", "aluno.dat");
        }

        //ofstream arq("aluno.dat", ios::binary | ios::app);
      /*  if (!arq)
        {
            std::cout << "Arquivo não pode ser aberto";
        }*/
        if (ehPossivelAlterar == true)
        {
            std::cout << "Digite o novo aluno para alterar: \n\n";
            std::cout << "\n Digite o Ra : ";
            cin >> novoRa;
            int tamanhoNovoRa = strlen(novoRa);
            if (verifcaAtributoIntAluno(tamanhoNovoRa, novoRa))
            {
                aluno.ra = std::strtol(novoRa, nullptr, 10);
                std::cout << "\n Digite o Nome : ";
                cin >> aluno.nome;
                int tamanhoNovoNome = strlen(aluno.nome);
                if (verificaNome(tamanhoNovoNome, aluno.nome))
                {
                    std::cout << "\n Digite a idade : ";
                    cin >> novaIdade;
                    int tamanhoNovaIdade = strlen(novaIdade);
                    if (verifcaAtributoIntAluno(tamanhoNovaIdade, novaIdade))
                    {
                        aluno.idade = std::strtol(novaIdade, nullptr, 10);
                        ofs.write((char*)&aluno, sizeof(aluno));
                        ifs.close();
                        ofs.close();
                        std::remove("aluno.dat");
                        std::rename("temp.dat", "aluno.dat");
                        fechouArq = true;
                        std::cout << "Aluno alterado com sucesso\n\n";
                    }
                    else
                    {
                        std::cout << "Digite uma idade valida\n\n";
                    }

                }
                else
                {
                    std::cout << "Digite um nome valido\n\n";
                }
            }
            else
            {
                std::cout << "Digite um Ra valido\n\n";
            }
        }
        if (fechouArq == false)
        {
            ifs.close();
            ofs.close();
        }
       /* arq.close();*/
    }
    catch (exception)
    {
        throw new exception("Erro na alteração do Aluno");
    }
    
}

void exibirAlunos()
{
    Aluno aluno;

    try
    {
        ifstream ifs("aluno.dat", ios::binary);
        if (!ifs)
        {
            std::cout << "Arquivo não foi possível ser aberto";
        }
        else
        {
            std::cout << "Registros de alunos lidos: \n";
            //cout << "Ra \tNome\tIdade\t\n";
            while (ifs.read((char*)&aluno, sizeof(aluno)))
            {
                std::cout << aluno.ra << "\t";
                std::cout << aluno.nome << "\t";
                std::cout << aluno.idade << endl;
                quantosAlunos++;
            }
            std::cout << "\n";
            ifs.close();
        }
    }
    catch (exception)
    {
        throw new exception("Erro na exibição dos Alunos Cadastrados");
    }
   
}


void buscaAluno() //Busca o aluno pelo seu Ra, retornrá 0 se não encontrar o aluno
{
    bool achou = false;
    Aluno aluno;
    try
    {
        ifstream ifs("aluno.dat", ios::binary);
        if (!ifs)
        {
            std::cout << "Arquivo não foi possível ser aberto";
        }
        else
        {
            int ra;
            std::cout << "Digite o Ra para buscar o Aluno: ";
            cin >> ra;
            while (ifs.read((char*)&aluno, sizeof(aluno)))
            {
                if (aluno.ra == ra)
                {
                    std::cout << "Aluno encontrado: \n";
                    std::cout << aluno.ra << "\t";
                    std::cout << aluno.nome << "\t";
                    std::cout << aluno.idade << endl;
                    std::cout << "\n";
                    achou = true;
                }
            }
            if (achou == false)
            {
                std::cout << "Aluno não encontrado: \n\n";
            }
            ifs.close();
        }
    }
    catch (exception)
    {
        throw new exception("Erro na Busca dos Alunos Cadastrados");
    }
   

}


void lerAquivoAlunos()
{
    try
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
            std::cout << "Ra :\t" << aluno.ra << endl;
            std::cout << "Nome :\t" << aluno.nome << endl;
            std::cout << "Idade :\t" << aluno.idade << endl;
            std::cout << "\n\n";
            arq.close();
        }
    }
    catch (exception)
    {
        throw new exception("Erro na leitura do arquivo binário de Alunos");
    }
    
}

short menu(void)  // MENU PRINCIPAL COM TODAS AS OPÇÕES
{    
    short opcao;// ARMAZENA A OPCAO DO MENU
    do {
        std::cout << " Menu Crud\n\n\n";
        std::cout << " [1] - Cadastrar Aluno.\n\n";
        std::cout << " [2] - Excluir Aluno.\n\n";
        std::cout << " [3] - Pesquisar Aluno por Ra.\n\n";
        std::cout << " [4] - Exibir quantidade de Alunos Cadastrados.\n\n";
        std::cout << " [5] - Alterar Aluno.\n\n";
        std::cout << " [6] - Exibir Alunos.\n\n";
        std::cout << " [0] - Sair.\n\n";
        std::cout << " Entre a opcao desejada: ";
       cin >> opcao;  // LEITURA DA OPÇÃO DESEJADA
       cin.ignore(80, '\n'); // LIMPA BUFFER DO TECLADO
    } while (opcao < 0 or 6 < opcao); // EVITA OPCÃO INEXISTENTE
    return opcao; // RETORNA O NÚMERO DA OPÇÃO
}

int main()
{
    //SQLHANDLE SQLEnvHandle = NULL;
    //SQLHANDLE SQLConnectionHandle = NULL;
    //SQLHANDLE SQLStatementHandle = NULL;
    //SQLRETURN retCode = 0;
    //char SQLQuerry[] = "SELECT * FROM Aluno";

    //do {
    //    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
    //        break;

    //    if(SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,0))
    //        break;

    //    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
    //        break;

    //    if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
    //        break;

    //    SQLCHAR retConString[1024];
    //    //String de Conexão com SQL SERVER
    //    switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=myDB; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) 
    //    {
    //        case SQL_SUCCESS:
    //            break;
    //        case SQL_SUCCESS_WITH_INFO:
    //            break;
    //        case SQL_NO_DATA_FOUND:
    //            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
    //            retCode = 1;
    //            break;
    //        case SQL_INVALID_HANDLE:
    //            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
    //            retCode = 1;
    //            break;
    //        case SQL_ERROR:
    //            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
    //            retCode = 1;
    //            break;

    //        default:
    //            break;
    //    }

    //    if (retCode == -1)
    //        break;

    //    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
    //        break;

    //    if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuerry, SQL_NTS)) 
    //    {
    //        showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
    //        break;
    //    }
    //    else
    //    {
    //        int ra;
    //        char nome[31];
    //        int idade;

    //        while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
    //        {
    //            SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &ra, sizeof(ra), NULL);
    //            SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &nome, size(nome), NULL);
    //            SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &idade, sizeof(idade), NULL);
    //            cout << ra << " " << nome << " " << idade << endl;
    //        }
    //    }
    //       

    //} while (false);



    Aluno aluno;

	ifstream ifs("aluno.dat", ios::binary);
	if (!ifs)
	{
        std::cout << "Arquivo não foi possível ser aberto, pois não foi criado ainda\n\n";
	}
	else
	{
        std::cout << "Registros de alunos lidos: \n";
		//cout << "Ra \tNome\tIdade\t\n";
		while (ifs.read((char*)&aluno, sizeof(aluno)))
		{
            std::cout << aluno.ra << "\t";
            std::cout << aluno.nome << "\t";
            std::cout << aluno.idade << endl;
            quantosAlunos++;
		}
        std::cout << "\n";
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
        case 6: exibirAlunos();break;
        }
    } while (opcao);

    return 0;
}
