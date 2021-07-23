#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

bool Sistema::search_usuariosLogados(int Id){
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

string Sistema::create_user(const string email, const string senha, const string nome) {
  for(int i=0; i<usuarios.size(); i++) { 
    if(usuarios[i].getEmail() == email) {
      return "== Usuário já existe! ==";
    }
  }
  
  countId++;
  Usuario NovoUsuario(countId, nome, email, senha);
  usuarios.push_back(NovoUsuario);
  return "== Usuário Criado ==";

}

string Sistema::login(const string email, const string senha) {
  for(int i=0; i<usuarios.size(); i++) {
    if(usuarios[i].getEmail() == email && usuarios[i].getSenha() == senha) {
      if( search_usuariosLogados(usuarios[i].getId()) ) { 
        return "== Usuário '" + email + "' já encontra-se logado! ==";
      }
      else{ 
        usuariosLogados.insert({usuarios[i].getId(), {"",""}});
        return "== Logado como " + email + " ==";
      }
    } 
  }

  return "== Senha ou Usuário Inválidos! ==";

}

string Sistema::disconnect(int id) {
  if( search_usuariosLogados(id)==false )  
    return "== Usuário precisa estar logado para desconectar! ==";

  auto it = usuariosLogados.begin();
  for(; it != usuariosLogados.end(); it++){
    if(it->first == id)
      break;
  }

  usuariosLogados.erase(it);
  return "== Desconectando usuário isaacfranco@imd.ufrn.br ==";

}

string Sistema::create_server(int id, const string nome) {
  if( search_usuariosLogados(id)==false ) 
    return "== Usuário precisa estar logado para criar servidor! ==";

  for(int i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) 
      return "== Servidor com esse nome já existe. ==";
  }

  Servidor novoServidor(id, nome);
  servidores.push_back(novoServidor);
  //servidores[(int)servidores.size()-1].adicionaParticipante(id);
  //usuarios[id].adicionaServidor(nome);
  return "== Servidor criado ==";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  for(int i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome && servidores[i].getUsuarioDonoId() == id) {
      servidores[i].setDescricao(descricao);
      return "== Descrição do servidor '" + nome + "' modificada ==";
    }
    else if(servidores[i].getNome() == nome && servidores[i].getUsuarioDonoId() != id) {
        return "== Você não pode alterar a descrição de um servidor que não foi criado por você! ==";
    }
  }

return "Servidor '" + nome + "' não existe";

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  for(int i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome && servidores[i].getUsuarioDonoId() == id) {
        if(codigo == "") {
          servidores[i].setConvite(codigo);
          return "== Código de convite do servidor '" + nome + "' removido ==";
        }
        else{
          servidores[i].setConvite(codigo);
          return "== Código de convite do servidor '" + nome + "' modificado ==";
        }
    }
    else if(servidores[i].getNome() == nome && servidores[i].getUsuarioDonoId() != id) {
      return "== Você não pode alterar o código de convite de um servidor que não foi criado por você! ==";
    }
  }

  return "== Servidor '" + nome + "' não encontrado ==";

}

string Sistema::list_servers(int id) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados. ==";

  cout << "== Lista de Servidores ==" << endl;
  for(int i=0; i<servidores.size(); i++) {
    cout << "  " << servidores[i].getNome();

    if(servidores[i].getCodigoConvite() == "") {
      cout << " | Servidor Aberto" << endl;
    }
    else {
      cout << " | Servidor Fechado" << endl;
    }
  }

  return "";

}

string Sistema::remove_server(int id, const string nome) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  for(auto it_serv = servidores.begin(); it_serv != servidores.end(); it_serv++) {
    if(it_serv->getNome() == nome && it_serv->getUsuarioDonoId() == id) {
      // apagar servidor e atualizar usuariosLogados que estejam visualizando o servidor
      for(auto it_users=usuariosLogados.begin(); it_users!=usuariosLogados.end(); it_users++){ 
        auto it_aux = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                              [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                  if(entrada.second.first == nome) 
                                      return true; 
                                  else 
                                      return false;
                                  });
        if(it_aux != usuariosLogados.end()) {
          usuariosLogados.erase(it_aux);
          usuariosLogados.insert({it_aux->first, {"",""}});
        } 
      }
      servidores.erase(it_serv);
      return "== Servidor '" + nome + "' removido ==";
    }
    else if(it_serv->getNome() == nome && it_serv->getUsuarioDonoId() != id) {
      return "== Você não é o dono do servidor '" + nome + "' ==";
    }
  }

  return "== Servidor '" + nome + "' não existe ==";

}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  int i;
  bool ServidorAchado = false;
  for(i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) {
      ServidorAchado = true;
      break;
    };
  }

  if(!ServidorAchado) return "== Servidor '" + nome + "' não existe ==";
  
  auto it = usuariosLogados.begin();
  for(; it != usuariosLogados.end(); it++){
    if(it->first == id)
      break;
  }

  if(servidores[i].getUsuarioDonoId() == id) {
    servidores[i].adicionaParticipante(id);
    usuarios[id].adicionaServidor(nome);
    usuariosLogados.erase(it);
    usuariosLogados.insert({id, {nome,""}});
    return "== Entrou no servidor com sucesso ==";
  } 
  else if(servidores[i].getCodigoConvite().empty() || 
          servidores[i].getCodigoConvite() == codigo) {
    servidores[i].adicionaParticipante(id);
    usuarios[id].adicionaServidor(nome);
    usuariosLogados.erase(it);
    usuariosLogados.insert({id, {nome,""}});
    return "== Entrou no servidor com sucesso ==";
  } 
  else if( !(servidores[i].getCodigoConvite().empty()) && codigo.empty() ) {
    return "== Servidor requer código de convite ==";
  } 
  
  return "== Código de convite incorreto! ==";

}

string Sistema::leave_server(int id, const string nome) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  if(usuarios[id].getServidores_usuario().empty())
    return "== Você não está em qualquer servidor ==";
  
  int i;
  for(i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) {
      break;
    };
  }

  servidores[i].removeParticipante(id);
  
  return "Saindo do servidor '" + nome + "'";

}

string Sistema::list_participants(int id) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado! ==";

  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                            [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                if(entrada.first == id && entrada.second.first != "")
                                    return true; 
                                else 
                                    return false;
                                });
  
  if(it != usuariosLogados.end()) {
    //usuario tem servidor conectado
    cout << "== Lista de Participantes ==" << endl;

    int i;
    for(i=0; i<servidores.size(); i++) {
      if(servidores[i].getNome() == it->second.first) 
        break;
    }

    vector<int> listaIds = servidores[i].getParticipantesIds();
    for(int i=0; i<usuarios.size(); i++) {
      for(int j=0; j<listaIds.size(); j++) {
        if(usuarios[i].getId() == listaIds[j]) 
          listaParticipantes += usuarios[i].getNome() + "\n";
      }
    }
  }

  //usuario não tem servidor conectado
  return "Não há servidor conectado";

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
