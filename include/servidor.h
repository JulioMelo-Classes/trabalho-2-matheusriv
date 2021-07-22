#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <algorithm>
#include <vector>

#include "canaltexto.h"
#include "usuario.h"

class Servidor{
	private:
		int usuarioDonoId;     //<! Id do usuário dono do Servidor.
		std::string nome; 	   //<! Nome do servidor.
		std::string descricao; //<! Descrição do servidor.
		std::string codigoConvite; //<! Código de convite do servidor. 
		std::vector<CanalTexto> canaisTexto; //<! Um vetor contendo todos os canais de texto deste servidor.
		std::vector<int> participantesIDs; //<! Um vetor contendo os ids de todos os participantes deste servidor.

	public:
		/* Construtor */
		Servidor(int UsuarioDonoId, std::string nome);

		/* Getters */
		int getUsuarioDonoId();
		std::string getNome();
		std::string getDescricao();
		std::string getCodigoConvite();
		std::vector<CanalTexto> getCanaisTexto();
		std::vector<int> getParticipantesIds();

		/*
		* @brief Adiciona o ID de um novo participante à lista de IDs do servidor
		* @param id id do tipo inteiro a ser adicionado
		*/
		void adicionaParticipante(int id);
};

#endif
