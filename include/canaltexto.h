#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <vector>

#include "mensagem.h"

class CanalTexto{
	private:
		std::string nome; //<! O nome do canal, conforme o comando create-channel
		std::vector<Mensagem> mensagens; //<! Um vector com mensagens que foram enviadas neste canal
	
	public:
		/* Construtor */
		CanalTexto(std::string nome);

		/*
		* @brief Retorna o nome do canal texto.
		* @return String com o nome do canal texto.
		*/
		std::string getCanalTextoNome();
};

#endif
