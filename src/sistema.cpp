#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

bool Sistema::search_usuariosLogados(int id){
  //verificar se usuario esta no std::map<int, std::pair<std::string, std::string>> usuariosLogados;
  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                            [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                if(entrada.first == id) 
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

std::map<int, std::pair<std::string, std::string>>::iterator Sistema::search_it_usuariosLogados(int id){
  auto it = usuariosLogados.begin();
  for(; it != usuariosLogados.end(); it++){
    if(it->first == id)
      break;
  }

  return it;

}

void Sistema::apagar_servidor_usuariosLogados(string nome){
  for(auto it_users=usuariosLogados.begin(); it_users!=usuariosLogados.end(); it_users++){ 
    auto it_aux = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                                [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                    if(entrada.second.first == nome) 
                                        return true; 
                                    else 
                                        return false;
                                });

    if(it_aux != usuariosLogados.end()) {
      it_aux->second.first.clear();
      it_aux->second.second.clear();
    }
  }
}

string Sistema::create_user(const string email, const string senha, const string nome) {
  for(int i=0; i<usuarios.size(); i++) { 
    if(usuarios[i].getEmail() == email) {
      return "== Usuário '" + email + "' já existe! ==";
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
  if(search_usuariosLogados(id) == false)  
    return "== Usuário precisa estar logado para desconectar! ==";

  usuariosLogados.erase(search_it_usuariosLogados(id));
  return "== Desconectando usuário " + usuarios[id].getEmail() + " ==";

}

string Sistema::create_server(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para criar servidor! ==";

  for(int i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) 
      return "== Servidor com o nome '" + nome + "' já existe! ==";
  }

  Servidor novoServidor(id, nome);
  servidores.push_back(novoServidor);
  //servidores[(int)servidores.size()-1].adicionaParticipante(id);
  return "== Servidor criado ==";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar descrição de um servidor! ==";

  for(int i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome && servidores[i].getUsuarioDonoId() == id) {
      servidores[i].setDescricao(descricao);
      return "== Descrição do servidor '" + nome + "' modificada ==";
    }
    else if(servidores[i].getNome() == nome && servidores[i].getUsuarioDonoId() != id) {
      return "== Você não pode alterar a descrição de um servidor que não foi criado por você! ==";
    }
  }

  return "Servidor '" + nome + "' não encontrado!";

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar código de convite de um servidor! ==";

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
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados ==";

  cout << "== Lista de Servidores ==" << endl;
  for(int i=0; i<servidores.size(); i++) {
    cout << "  " << servidores[i].getNome();

    if(servidores[i].getCodigoConvite().empty()) {
      cout << " | Servidor Aberto" << endl;
    }
    else {
      cout << " | Servidor Fechado" << endl;
    }
  }

  return "";

}

string Sistema::remove_server(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para remover um servidor! ==";

  for(auto it = servidores.begin(); it != servidores.end(); it++) {
    if(it->getNome() == nome && it->getUsuarioDonoId() == id) {
      // apagar servidor e atualizar usuariosLogados que estejam visualizando o servidor
      apagar_servidor_usuariosLogados(nome);
      servidores.erase(it);
      return "== Servidor '" + nome + "' removido ==";
    }
    else if(it->getNome() == nome && it->getUsuarioDonoId() != id) {
      return "== Você não é o dono do servidor '" + nome + "' ==";
    }
  }

  return "== Servidor '" + nome + "' não existe! ==";

}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para entrar num servidor! ==";

  bool ServidorAchado = false;
  int i;
  for(i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) {
      ServidorAchado = true;
      break;
    };
  }

  if(!ServidorAchado) return "== Servidor '" + nome + "' não existe! ==";

  if(servidores[i].getUsuarioDonoId() == id) {
    servidores[i].adicionaParticipante(id);
    search_it_usuariosLogados(id)->second.first = nome;
    return "== Entrou no servidor com sucesso ==";
  } 
  else if(servidores[i].getCodigoConvite().empty() || 
          servidores[i].getCodigoConvite() == codigo) {
    servidores[i].adicionaParticipante(id);
    search_it_usuariosLogados(id)->second.first = nome;
    return "== Entrou no servidor com sucesso ==";
  } 
  else if( !(servidores[i].getCodigoConvite().empty()) && codigo.empty() ) {
    return "== Servidor requer código de convite! ==";
  } 
  
  return "== Código de convite incorreto! ==";

}

string Sistema::leave_server(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para sair de um servidor! ==";
  
  auto it = search_it_usuariosLogados(id);
  if(it->second.first.empty())
    return "== Você não está em qualquer servidor! ==";
  
  for(int i=0; i<servidores.size(); i++) {
    if(servidores[i].getNome() == nome) {
      servidores[i].removeParticipante(id);
      // atualizar usuariosLogados se usuario estiver visualizando o servidor
      it->second.first.clear();
      it->second.second.clear();
      break;
    };
  }
  
  return "== Saindo do servidor '" + nome + "' ==";

}

string Sistema::list_participants(int id) {
  if(search_usuariosLogados(id)==false) 
    return "== Usuário precisa estar logado acessar lista de participantes de um servidor! ==";
  
  auto it = search_it_usuariosLogados(id);

  if(it->first == id && it->second.first != ""){
    // usuario está visualizando um servidor
    cout << "== Lista de Participantes '" + it->second.first + "' ==" << endl;

    vector<int> listaParticipantesIds;

    for(int i=0; i<servidores.size(); i++) {
      if(servidores[i].getNome() == it->second.first) { 
        listaParticipantesIds = servidores[i].getParticipantesIds();
        break;
      }
    }

    string listaParticipantes;
    
    for(int i=0; i<usuarios.size(); i++) {
      for(int j=0; j<listaParticipantesIds.size(); j++) {
        if(usuarios[i].getId() == listaParticipantesIds[j])
          listaParticipantes += "  " + usuarios[i].getNome() + "\n";
      }
    }

    return listaParticipantes;

  }

  // usuario não está visualizando um servidor
  return "== Não há servidor conectado ==";

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
