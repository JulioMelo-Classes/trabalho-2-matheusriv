#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <vector>

class Usuario{
  private:
    int id;            //<! ID do usuário
    std::string nome;  //<! Nome do usuário 
    std::string email; //<! Endereço de email do usuário 
    std::string senha; //<! Senha do login  
    std::vector<std::string> servidores_usuario; //<! Um vetor contendo os servidores em que o usuário está

  public:
    /* Construtor */
    Usuario(int id, std::string nome, std::string email, std::string senha);

    /* Construtor padrão */
    Usuario();

    /*
     * @brief Altera o ID do usuário.
     * @param id ID novo.
     */
    void setId(int id);

    /*
     * @brief Altera o nome do usuário.
     * @param nome Novo nome.
     */
    void setNome(std::string nome);

    /*
     * @brief Altera o email do usuario.
     * @param email Novo email.
     */
    void setEmail(std::string email);

    /*
     * @brief Altera a senha do usuário.
     * @param senha Nova senha.
     */
    void setSenha(std::string senha);

    /*
     * @brief Retorna o ID do usuário.
     * @return Inteiro do ID do usuário.
     */
    int getId();

    /*
     * @brief Retorna o Nome do usuário.
     * @return String com o nome do usuário.
     */
    std::string getNome();

    /*
     * @brief Retorna o Email do usuário.
     * @return String com o email do usuário.
     */
    std::string getEmail();

    /*
     * @brief Retorna a senha do usuário.
     * @return String com a senha do usuário.
     */
    std::string getSenha();

    /*
     * @brief Retorna os servidores do usuário.
     * @return Vetor com os servidores do usuário.
     */
    std::vector<std::string> getServidores_usuario();

    /*
     * @brief Adiciona o nome de um novo servidor à lista de servidores em que o usuário está.
     * @param nome_servidor Nome do novo servidor a ser adicionado.
     */
    void adicionaServidor(std::string nome_servidor);



};

#endif
