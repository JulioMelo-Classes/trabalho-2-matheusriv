#ifndef USUARIO_H
#define USUARIO_H

class Usuario{
  private:
    int id; //<! ID do usuário
    string nome; //<! Nome do usuário 
    string email; //<! Endereço de email do usuário 
    string senha; //<! Senha do login  

  public:
    /* Construtor */
    Usuario(int id, string nome, string email, string senha);

    /*
     * @brief Altera o ID do usuário.
     * @param id ID novo.
     */
    void setId(int id);

    /*
     * @brief Altera o nome do usuário.
     * @param nome Novo nome.
     */
    void setNome(string nome);

    /*
     * @brief Altera o email do usuario.
     * @param email Novo email.
     */
    void setEmail(string email);

    /*
     * @brief Altera a senha do usuário.
     * @param senha Nova senha.
     */
    void setSenha(string senha);

    /*
     * @brief Retorna o ID do usuário.
     * @return Inteiro do ID do usuário.
     */
    int getId();

    /*
     * @brief Retorna o Nome do usuário.
     * @return String com a ao nome do usuário.
     */
    string getNome();

    /*
     * @brief Retorna o Email do usuário.
     * @return String com a ao email do usuário.
     */
    string getEmail();

    /*
     * @brief Retorna a senha do usuário.
     * @return String com a senha do usuário.
     */
    string getSenha();

};

#endif
