#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user(const string email, const string senha, const string nome) {
  if(usuarios.size()==0){
    countId++;
    Usuario NovoUsuario(countId, nome, email, senha);
    usuarios.push_back(NovoUsuario);
    return "Usuário Criado";
  }
  
  for(int i=0; i<usuarios.size(); i++){
    if(usuarios[i].getEmail() == email){
      return "Usuário já existe!";
    }
    else{
      countId++;
      Usuario NovoUsuario(countId, nome, email, senha);
      usuarios.push_back(NovoUsuario);
      return "Usuário Criado";
    }
  }

  return "Erro!";

}

bool Sistema::search_user(int Id){
  //verificar se usuario esta no std::map<int, std::pair<std::string, std::string>> usuariosLogados;
  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                            [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                if(entrada.first == Id) 
                                    return true; 
                                else 
                                    return false;
                                });
                                
  if(it != usuariosLogados.end()){ 
    //usuario logado 
    return true;
  }

  //usuario não logado 
  return false;
  
}

string Sistema::login(const string email, const string senha) {
  for(int i=0; i<usuarios.size(); i++){
    if(usuarios[i].getEmail() == email && usuarios[i].getSenha() == senha){
      if( search_user(usuarios[i].getId()) ) { 
        return "Usuário '" + usuarios[i].getEmail() + "' já encontra-se logado!";
      }
      else{ 
        usuariosLogados.insert({usuarios[i].getId(), {"",""}});
        return "Logado como " + email;
      }
    } 
  }

  return "Senha ou Usuário Inválidos!";

}

string Sistema::disconnect(int id) {
  if( !search_user(id) ) { 
    return "Não está conectado";
  }

  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                            [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                if(entrada.first == id) 
                                    return true; 
                                else 
                                    return false;
                                });

  usuariosLogados.erase(it);
  return "Desconectando usuário isaacfranco@imd.ufrn.br";

}

string Sistema::create_server(int id, const string nome) {
  if( !search_user(id) ) { 
    return "Usuário não logado.";
  }

  for(int i = 0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) 
      return "Servidor com esse nome já existe.";
  }

  Servidor novo(id, nome);
  servidores.push_back(novo);
  servidores[(int)servidores.size()-1].adicionaParticipante(id);
  return "Servidor criado";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
