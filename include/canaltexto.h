#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <vector>
#include <ctime>

#include "usuario.h"
#include "mensagem.h"

class CanalTexto{
    private:
        std::string nome; //<! O nome do canal, conforme o comando create-channel
        std::vector<Mensagem> mensagens; //<! Um vector com mensagens que foram enviadas neste canal
	
    public:
        /* Construtor */
        CanalTexto(const std::string nome);

        /*
        * @brief Retorna o nome do canal texto
        * @return String com o nome do canal texto
        */
        std::string getNome();

        /*
        * @brief Altera o nome do canal texto
        * @param novoNome String com novo nome do canal texto
        */
        void setNome(const std::string novoNome);
		
        /*
        * @brief Adiciona uma mensagem no vetor de mensagens do canal de texto
        * @param novaMensagem Nova mensagem a ser adicionado
        */
        void addMensagem(const std::string mensagem, int id);

        /*
        * @brief Lista as mensagens do canal de texto
        * @param usuarios Vetor com todos os usuários cadastrados
        */
        void list_messages(std::vector<Usuario> &usuarios);

};

#endif
