#ifndef MENSAGEM_H
#define MENSAGEM_H
#include <iostream>

class Mensagem{
    private:
        std::string dataHora; //<! Um texto representando um timestamp com a data e hora em que a mensagem foi enviada
        int enviadaPor; //<! Id do usuário que enviou a mensagem
        std::string conteudo; //<! Conteúdo da mensagem
    
    public:
        /* Construtor */
        Mensagem(std::string dataHora, std::string conteudo, int enviadaPor);

        /* Construtor padrão */
        Mensagem();

         /*
        * @brief Retorna o conteudo da mensagem
        * @return String com o conteudo da mensagem
        */
        std::string getConteudo();

        /*
        * @brief Retorna a data e hora da mensagem
        * @return String com a data e hora da mensagem
        */
        std::string getDataHora();

        /*
        * @brief Retorna o id do usuário que enviou a mensagem
        * @return inteiro com o id do usuário que enviou a mensagem
        */
        int getEnviadaPor();

        /*
        * @brief Altera a data e hora da mensagem
        * @param dataHora String com nova data e hora da mensagem
        */
        void setDataHora(const std::string dataHora);

        /*
        * @brief Altera o conteudo da mensagem
        * @param conteudo String com o conteudo da mensagem
        */
        void setConteudo(const std::string conteudo);

        /*
        * @brief Altera o id do dono da mensagem
        * @param enviadaPor Novo id do dono da mensagem
        */
        void setEnviadaPor(int enviadaPor);

};

#endif