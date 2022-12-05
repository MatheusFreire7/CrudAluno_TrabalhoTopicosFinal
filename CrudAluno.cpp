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
    cout << "Quantidade de Alunos: ";
    cout << quantosAlunos;
    cout << "\n\n";
}

bool buscaAlunoRa(int ra) //Busca o aluno pelo seu Ra, retornrá 0 se não encontrar o aluno
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

void incluirAluno()
{
    ofstream arq("aluno.dat", ios::binary | ios::app);
    Aluno aluno;
    char ra[10]; //Char usados para verificar se são inteiros o ra e a idade digitados
    char idade[4];
    if (!arq)
    {
        std::cout << "Arquivo não pode ser aberto";
    }
    else
    {
        cout << "\n Digite o Ra : ";
        cin >> ra;
        int tamanhoRa = strlen(ra);
        if (isdigit(ra[1]) && tamanhoRa>= 5)
        {
            aluno.ra = (int)ra;
            if (buscaAlunoRa(aluno.ra) == false)
            {
                cout << "\n Digite o Nome : ";
                cin >> aluno.nome;
                cout << "\n Digite a idade : ";
                cin >>  idade;
                if (isdigit(idade[1]))
                {
                    aluno.idade = (int)idade;
                    arq.write((char*)&aluno, sizeof(aluno));
                    quantosAlunos++;
                }
                else
                    cout << "Digite uma idade valida\n\n";
              
            }
            else
            {
                cout << "Aluno já existe\n\n";
            }
        }
        else
            cout << "Digite um ra valido\n";
        

        char ch;
        cout << "Voce quer incluir mais registros aperte s para sim: ";
        std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
        while (ch == 's')
        {
            cout << "\n Digite o Ra : ";
            cin >> ra;
            int tamanhoRa = strlen(ra);
            if (isdigit(ra[1]) && tamanhoRa >= 5)
            {
                aluno.ra = (int)ra;
                if (buscaAlunoRa(aluno.ra) == false)
                {
                    cout << "\n Digite o Nome : ";
                    cin >> aluno.nome;
                    cout << "\n Digite a idade : ";
                    cin >> idade;
                    if (isdigit(idade[1]))
                    {
                        aluno.idade = (int)idade;
                        arq.write((char*)&aluno, sizeof(aluno));
                        quantosAlunos++;
                        cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                        std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                    }
                    else
                    {
                        cout << "Digite uma idade valida\n\n";
                        cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                        std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                    }
                }
                else
                {
                    cout << "Aluno já existe \n\n";
                    cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                    std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
                }
            }
            else
            {
                cout << "Digite um ra valido\n";
                cout << "Voce quer incluir mais registros aperte "s" para sim: ";
                std::cin >> ch;  // LEITURA DA OPÇÃO DESEJADA
            }
        }
        arq.close();
    }
}

void excluirAluno()
{
    ifstream ifs("aluno.dat", ios::binary | ios::in);
    ofstream ofs("temp.dat", ios::binary | ios::out);
    Aluno aluno;
    bool excluiu = false;
    if (!ifs || !ofs)
    {
        cout << "Arquivo não foi possível ser aberto";
    }
    else
    {
        int ra;
 
        cout << "Digite o Ra para excluir o Aluno: ";
        cin >> ra;
        if (buscaAlunoRa(ra) == true)
        {
            while (ifs.read((char*)&aluno, sizeof(aluno)))
            {
                if (aluno.ra != ra)
                {
                    ofs.write((char*)&aluno, sizeof(aluno));
                }
                if (aluno.ra == ra)
                {
                    cout << "Excluimos com sucesso o Aluno \n\n";
                    excluiu = true;
                }
            }

            if(excluiu == false)
                cout << "Não conseguimos excluir o Aluno\n\n";
        }
        else
        {
            cout << "Aluno digitado não está cadastrado \n\n";
        }

       
        ifs.close();
        ofs.close();
        remove("aluno.dat");
        rename("temp.dat", "aluno.dat");
        quantosAlunos--;
    }

}

void alterarAluno()
{
    ifstream ifs("aluno.dat", ios::binary | ios::in);
    ofstream ofs("temp.dat", ios::binary | ios::out);
    Aluno aluno;
    bool ehPossivelAlterar = false;
    if (!ifs || !ofs)
    {
        cout << "Arquivo não foi possível ser aberto";
    }
    else
    {
        int ra;

        cout << "Digite o Ra do Aluno que quer alterar: ";
        cin >> ra;
        if (buscaAlunoRa(ra) == true)
        {
            ehPossivelAlterar = true;
            while (ifs.read((char*)&aluno, sizeof(aluno)))
            {
                if (aluno.ra != ra)
                {
                    ofs.write((char*)&aluno, sizeof(aluno));
                }
            }
        }
        else
            cout << "Aluno digitado não está cadastrado";
        
        ifs.close();
        ofs.close();
        remove("aluno.dat");
        rename("temp.dat", "aluno.dat");
    }

    ofstream arq("aluno.dat", ios::binary | ios::app);
    if (!arq)
    {
        std::cout << "Arquivo não pode ser aberto";
    }
    if(ehPossivelAlterar == true)
    {
        cout << "Digite o novo aluno para alterar: \n";
        cout << "\n Digite o Ra : ";
        cin >> aluno.ra;
        cout << "\n Digite o Nome : ";
        cin >> aluno.nome;
        cout << "\n Digite a idade : ";
        cin >> aluno.idade;
        arq.write((char*)&aluno, sizeof(aluno));
        quantosAlunos++;
    }
    arq.close();
}

void exibirAlunos()
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
        //cout << "Ra \tNome\tIdade\t\n";
        while (ifs.read((char*)&aluno, sizeof(aluno)))
        {
            cout << aluno.ra << "\t";
            cout << aluno.nome << "\t";
            cout << aluno.idade << endl;
            quantosAlunos++;
        }
        cout << "\n";
        ifs.close();
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
        cout << "Digite o Ra para buscar o Aluno: ";
        cin >> ra;
        while (ifs.read((char*)&aluno, sizeof(aluno)))
        {
            if (aluno.ra == ra)
            {
                cout << "Aluno encontrado: \n";
                cout << aluno.ra << "\t";
                cout << aluno.nome << "\t";
                cout << aluno.idade << endl;
                cout << "\n";
                achou = true;
            }
        }
        if (achou == false)
        {
            cout << "Aluno não encontrado: \n\n";
        }
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
        cout << "\n\n";
        arq.close();
    }
}

short menu(void)  // MENU PRINCIPAL COM TODAS AS OPÇÕES
{    
    short opcao;// ARMAZENA A OPCAO DO MENU
    do {
       cout << " Menu Crud\n\n\n";
       cout << " [1] - Cadastrar Aluno.\n\n";
       cout << " [2] - Excluir Aluno.\n\n";
       cout << " [3] - Pesquisar Aluno por Ra.\n\n";
       cout << " [4] - Exibir quantidade de Alunos Cadastrados.\n\n";
       cout << " [5] - Alterar Aluno.\n\n";
       cout << " [6] - Exibir Alunos.\n\n";
       cout << " [0] - Sair.\n\n";
       cout << " Entre a opcao desejada: ";
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
		cout << "Arquivo não foi possível ser aberto\n\n";
	}
	else
	{
        cout << "Registros de alunos lidos: \n";
		//cout << "Ra \tNome\tIdade\t\n";
		while (ifs.read((char*)&aluno, sizeof(aluno)))
		{
			cout << aluno.ra << "\t";
			cout << aluno.nome << "\t";
			cout << aluno.idade << endl;
            quantosAlunos++;
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
        case 6: exibirAlunos();break;
        }
    } while (opcao);

    return 0;
}
