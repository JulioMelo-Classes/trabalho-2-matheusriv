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

		/*
		* @brief Retorna o Id do dono do servidor.
		* @return Inteiro Id com o dono do servidor.
		*/
		int getUsuarioDonoId();

		/*
		* @brief Retorna o nome do servidor.
		* @return String com o nome do servidor.
		*/
		std::string getNome();

		/*
		* @brief Retorna a descrição do servidor.
		* @return String com a descrição do servidor.
		*/
		std::string getDescricao();

		/*
		* @brief Retorna o código de convite do servidor.
		* @return String com a descrição do servidor.
		*/
		std::string getCodigoConvite();

		/*
		* @brief Retorna os canais de texto do servidor.
		* @return Vetor com os canais de texto do servidor.
		*/
		std::vector<CanalTexto> getCanaisTexto();

		/*
		* @brief Retorna os participantes do servidor.
		* @return Vetor com os participantes do servidor.
		*/
		std::vector<int> getParticipantesIds();

		/*
		* @brief Adiciona o ID de um novo participante à lista de IDs do servidor
		* @param id Inteiro id a ser adicionado
		*/
		void adicionaParticipante(int id);
};

#endif
