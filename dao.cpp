#include<stdio.h>

class Aluno {

	int	 *ra;
	char *nome[31];
	int	 *idade;


	/*void setRa(int ra) throw()
	{

		if (raToString.length() != 5)
			throw new Exception("Ra invalido");

		this.Ra = Ra;
	}*/

	int getRa() throw() {
		return *ra;
	}

	char getNome() throw()
	{
		return *nome[31];
	}

	int getIdade() throw()
	{
		return *idade;
	}

	void setRa(int *ra) throw() {
		if (ra < 0)
			printf("RA inválido");
		this->ra = ra;
	}

	void setNome(char *nome[31]) throw() {
		if (*nome[0] == ' ')
			printf("Nome inválido");

		for(int i=0;i != 30; i++)
			this->nome[i] = nome[i];
	}

	void setIdade(int* idade) throw() {
		if (ra < 0)
			printf("Idade inválida");
		this->idade = idade;
	}
};