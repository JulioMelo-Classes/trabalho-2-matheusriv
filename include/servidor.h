#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <iostream>
#include <algorithm>
#include <vector>

#include "canaltexto.h"

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
		Servidor(int usuarioDonoId, const std::string nome);

		/* Construtor padrão*/
		Servidor();

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
		* @brief Retorna o vetor de mensagens do canal de texto especificado.
		* @param nomeCanal Nome do canal de texto em que ser quer acessar as mensagens.
		* @return O vetor de mensagens do canal de texto 'nomeCanal'.
		*/
		std::vector<Mensagem> getMensagens(const std::string nomeCanal);

		/*
     	* @brief Altera a descrição do servidor.
     	* @param descricao Nova descrição do servidor.
     	*/
		void setDescricao(std::string descricao);

		/*
     	* @brief Altera o código de convite do servidor.
     	* @param codigoConvite Novo código de convite do servidor.
     	*/
		void setConvite(std::string codigoConvite);

		/*
		* @brief Adiciona o ID de um novo participante à lista de IDs do servidor.
		* @param id Inteiro id a ser adicionado.
		*/
		void adicionaParticipante(int id);

		/*
		* @brief Remove o ID de um participante da lista de IDs do servidor.
		* @param id Inteiro id a ser removido.
		*/
		void removeParticipante(int id);

		/*
		* @brief Adiciona um canal de texto na lista de canais de texto do servidor.
		* @param nome Nome do canal de texto a ser adicionado.
		* @param novoCanalTexto Canal de texto a ser adicionado.
		*/
		void adicionaCanalTexto(CanalTexto novoCanalTexto);

		/*
		* @brief Adiciona uma nova mensagem no canal de texto especificado.
		* @param nomeCanal Nome do canal de texto em que ser quer adicionar uma mensagem.
		* @param mensagem classe Mensagem que ser quer adicionar ao canal de texto.
		*/
		void sendMensagem(std::string nomeCanal, Mensagem mensagem);
};

#endif
