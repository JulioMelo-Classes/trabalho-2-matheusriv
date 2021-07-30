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

  public:
    /* Construtor */
    Usuario(int id, const std::string nome, const std::string email, const std::string senha);

    /* Construtor padrão */
    Usuario();

    /*
     * @brief Altera o ID do usuário
     * @param id ID novo
     */
    void setId(int id);

    /*
     * @brief Altera o nome do usuário
     * @param nome Novo nome
     */
    void setNome(const std::string nome);

    /*
     * @brief Altera o email do usuario
     * @param email Novo email
     */
    void setEmail(const std::string email);

    /*
     * @brief Altera a senha do usuário
     * @param senha Nova senha
     */
    void setSenha(const std::string senha);

    /*
     * @brief Retorna o ID do usuário
     * @return Inteiro do ID do usuário
     */
    int getId();

    /*
     * @brief Retorna o Nome do usuário
     * @return String com o nome do usuário
     */
    std::string getNome();

    /*
     * @brief Retorna o Email do usuário
     * @return String com o email do usuário
     */
    std::string getEmail();

    /*
     * @brief Retorna a senha do usuário
     * @return String com a senha do usuário
     */
    std::string getSenha();

};

#endif
