#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#include "usuario.h"
#include "canaltexto.h"

class Servidor{
    private:
        int usuarioDonoId; //<! Id do usuário dono do Servidor.
        std::string nome; //<! Nome do servidor.
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
        * @brief Altera a descrição do servidor.
        * @param descricao String com nova descrição do servidor.
        */
        void setDescricao(std::string descricao);

        /*
        * @brief Altera o código de convite do servidor.
        * @param codigoConvite String com novo código de convite do servidor.
        */
        void setCodigoConvite(std::string codigoConvite);

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
        * @brief Adiciona um canal de texto se não existir um canal com o mesmo nome do novo canal.
        * @param novoCanalTexto Canal de texto a ser adicionado.
        * @return String com uma mensagem de sucesso ou de erro.
        */
        std::string adicionaCanalTexto(CanalTexto novoCanalTexto);

        /*
        * @brief Adiciona um canal de texto ao servidor.
        * @param novoCanalTexto Canal de texto a ser adicionado.
        */
        void adicionaCanalTexto_(CanalTexto novoCanalTexto);

        /*
        * @brief Lista os canais de texto do servidor.
        */
        void list_channels();

        /*
        * @brief Lista os participantes presentes no servidor.
        * @param usuarios vetor com todos os usuários cadastrados.
        */
        void list_participants(std::vector<Usuario> &usuarios);

        /*
        * @brief Verifica as condições válidas para entrar ou sair de um canal de texto do servidor.
        * @param nomeCanal String com nome do canal de texto.
        * @return Uma string de erro em caso de falha ou uma string vazia se as condições são válidas.
        */
        std::string enter_leave_channel(std::string nomeCanal);

        /*
        * @brief Salva os ids participantes do servidor num arquivo.
        * @param ofs ofstream do arquivo.
        */
        void salvarIdsOfstream(std::ofstream &ofs);

        /*
        * @brief Salva os dados dos canais de texto do servidor num arquivo.
        * @param ofs ofstream do arquivo.
        */
        void salvarCanaisOfstream(std::ofstream &ofs);

        /*
        * @brief Procura um canal de texto especificado.
        * @param nomeCanal Nome do canal de texto que se procurar.
        * @return Iterator do canal de texto ou iterator canaisTexto.end() se o canal não for encontrado.
        */
        std::vector<CanalTexto>::iterator search_it_canalTexto(std::string nomeCanal);

};

#endif