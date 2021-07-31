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
  for(int i=0; i<usuarios.size(); i++) { 
    if(usuarios[i].getEmail() == email) {
      return "== Usuário " + email + " já existe! ==";
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
          return "== Usuário " + email + " já encontra-se logado! ==";
        } 
        else { 
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
  
  if(nome.empty())
    return "== Você não pode criar um servidor sem nome! ==";
  
  if(search_it_servidores(nome) != servidores.end()) {
    return "== Servidor com o nome '" + nome + "' já existe! ==";
  }

  Servidor novoServidor(id, nome);
  servidores.push_back(novoServidor);

  return "== Servidor '" + nome + "' criado ==";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar descrição de um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não encontrado! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id) {
    it_server->setDescricao(descricao);
    return "== Descrição do servidor '" + nome + "' modificada ==";
  }

  return "== Você não pode alterar a descrição de um servidor que não foi criado por você! ==";

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar código de convite! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);

  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não encontrado! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id) {
      if(codigo == "") {
        it_server->setConvite(codigo);
        return "== Código de convite do servidor '" + nome + "' removido ==";
      }
      else {
        it_server->setConvite(codigo);
        return "== Código de convite do servidor '" + nome + "' modificado ==";
      }
  }
  
  return "== Você não pode alterar o código de convite de um servidor que não foi criado por você! ==";

}

string Sistema::list_servers(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados ==";

  cout << "## Lista de Servidores ##" << endl;
  for(int i=0; i<servidores.size(); i++) {
    cout << "   " + servidores[i].getNome();

    if(servidores[i].getCodigoConvite().empty()) {
      cout << " [Servidor Aberto]" << endl;
    }
    else {
      cout << " [Servidor Fechado]" << endl;;
    }
  }

  return "";

}

string Sistema::list_servers_desc(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados ==";

  cout << "## Lista de Descrição dos Servidores ##" << endl;
  for(int i=0; i<servidores.size(); i++) {
    cout << "   " + servidores[i].getNome();

    if(servidores[i].getDescricao().empty()) {
      cout << " | Servidor sem descrição" << endl;
    }
    else {
      cout << " | " + servidores[i].getDescricao() << endl;
    }
  }

  return "";

}

string Sistema::remove_server(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para remover um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor para remover! ==";
  
  auto it_server = search_it_servidores(nome);

  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id) {
    for(auto it_usuariosLogados = usuariosLogados.begin(); 
    it_usuariosLogados != usuariosLogados.end(); it_usuariosLogados++) { 
        // atualizar usuariosLogados que estejam visualizando o servidor e apagar servidor
        if(it_usuariosLogados->second.first == nome) { 
          // second.first Campo do nome do servidor
          it_usuariosLogados->second.first.clear();
          // second.second Campo do nome do canal de texto
          it_usuariosLogados->second.second.clear(); 
        }
    }
    servidores.erase(it_server);

    return "== Servidor '" + nome + "' removido ==";
  }
  
  return "== Você não é o dono do servidor '" + nome + "' ==";

}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para entrar num servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);

  if(it_server == servidores.end()) 
    return "== Servidor '" + nome + "' não existe! ==";

  auto it_user = search_it_usuariosLogados(id);

  if(it_user->second.first != "") {
    return "== Saia do servidor conectado atualmente! ==";
  }

  if(it_server->getUsuarioDonoId() == id ||
    it_server->getCodigoConvite().empty() || 
    it_server->getCodigoConvite() == codigo) {
      it_server->adicionaParticipante(id);
      it_user->second.first = nome;
      return "== " + usuarios[id].getNome() + " entrou no servidor '" + nome + "' com sucesso ==";
  } 
  else if( !(it_server->getCodigoConvite().empty()) && codigo.empty() ) {
    return "== Servidor requer código de convite! ==";
  } 
  
  return "== Código de convite incorreto! ==";

}

string Sistema::leave_server(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para sair de um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor para sair! ==";
  
  auto it_user = search_it_usuariosLogados(id);

  if(it_user->second.first.empty())
    return "== Você não está em qualquer servidor! ==";

  search_it_servidores(nome)->removeParticipante(id);

  it_user->second.first.clear();
  it_user->second.second.clear();
  
  return "== Saindo do servidor '" + nome + "' ==";

}

string Sistema::list_participants(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de participantes de um servidor! ==";
  
  auto it_user = search_it_usuariosLogados(id);

  if(it_user->first == id && it_user->second.first != "") {
    // usuario está visualizando um servidor
    search_it_servidores(it_user->second.first)->list_participants(usuarios);

    return "";
  }

  return "== Não há servidor conectado! ==";

}

string Sistema::list_channels(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de canais de um servidor! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";
  
  search_it_servidores(nomeServidor)->list_channels();

  return "";

}

string Sistema::create_channel(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para criar um canal num servidor! ==";
  
  if(nome.empty()) 
    return "== Não é possível criar um canal sem nome! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  CanalTexto NovoCanalTexto(nome);
  search_it_servidores(nomeServidor)->adicionaCanalTexto(NovoCanalTexto);

  return "== Canal de texto '" + nome + "' em '" + nomeServidor + "' criado ==";

}


string Sistema::enter_channel(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado parar entrar num canal! ==";
  
  if(nome.empty()) 
    return "== Não é possível entrar em um canal sem nome! ==";
  
  auto it_user = search_it_usuariosLogados(id);

  string nomeServidor = it_user->second.first;
  
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  if(it_user->second.second == nome)
    return "== Usuário já está no canal! ==";

  if(it_user->second.second != "") {
    return "== Saia do canal de texto conectado atualmente! ==";
  }
  
  string string_erro = search_it_servidores(nomeServidor)->enter_leave_channel(nome);
  if(string_erro != "")
    return string_erro;

  it_user->second.second = nome;

  return "== " + usuarios[id].getNome() + " entrou no canal '" + nome + "' ==";

}

string Sistema::leave_channel(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para sair de um canal! ==";
  
  auto it_user = search_it_usuariosLogados(id);
  
  string nomeServidor = it_user->second.first;

  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  string nomeCanal = it_user->second.second;
  
  if(nomeCanal.empty())
    return "== Você não está num canal! ==";

  auto it_server = search_it_servidores(nomeServidor);

  string string_erro = it_server->enter_leave_channel(nomeCanal);
  if(string_erro != "") 
    return string_erro;

  it_user->second.second.clear();
  
  return "== Saindo do canal '" + nomeCanal + "' ==";

}

string Sistema::send_message(int id, const string mensagem) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mandar uma mensagem! ==";

  if(mensagem.empty()) 
    return "== Não é possível enviar uma mensagem vazia! ==";
  
  auto it_user = search_it_usuariosLogados(id);
  
  string nomeServidor = it_user->second.first;

  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  string nomeCanal = it_user->second.second;
  
  if(nomeCanal.empty())
    return "== Você não está num canal! ==";

  auto it_canaltexto = search_it_servidores(nomeServidor)->search_it_canalTexto(nomeCanal);

  it_canaltexto->addMensagem(mensagem, id);

  return "";

}

string Sistema::list_messages(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de mensagens! ==";
  
  string nomeServidor = search_it_usuariosLogados(id)->second.first;

  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  string nomeCanal = search_it_usuariosLogados(id)->second.second;
  
  if(nomeCanal.empty())
    return "== Você não está num canal! ==";
  
  auto it_canaltexto = search_it_servidores(nomeServidor)->search_it_canalTexto(nomeCanal);

  it_canaltexto->list_messages(usuarios);

  return "";

}

string Sistema::list_online_users(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de usuários online! ==";
  
  vector<int> vetorIDsOnline;
  
  string listaUsuariosOnline;

  for(auto it = usuariosLogados.begin(); it != usuariosLogados.end(); it++) {
    vetorIDsOnline.push_back(it->first);
  }

  listaUsuariosOnline = "## Usuários online no Concordo ##\n";
  for(int i=0; i<usuarios.size(); i++) {
      for(int j=0; j<vetorIDsOnline.size(); j++) {
        if(usuarios[i].getId() == vetorIDsOnline[j])
          listaUsuariosOnline += "   " + usuarios[i].getNome() + "\n";
      }
  }

  return listaUsuariosOnline;

}

bool Sistema::search_usuariosLogados(int id) {
  //verificar se usuario esta no std::map<int, std::pair<std::string, std::string>> usuariosLogados;
  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                            [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                if(entrada.first == id) 
                                    return true; 
                                else 
                                    return false;
                                });
                                
  if(it != usuariosLogados.end()) { 
    //usuario logado 
    return true;
  }

  //usuario não logado 
  return false;
  
}

std::map<int, std::pair<std::string, std::string>>::iterator Sistema::search_it_usuariosLogados(int id) {
  auto it = usuariosLogados.begin();
  for(; it != usuariosLogados.end(); it++) {
    if(it->first == id)
      break;
  }

  return it;

}

std::vector<Servidor>::iterator Sistema::search_it_servidores(string nomeServidor) {
  auto it_server = servidores.begin();
  for(; it_server != servidores.end(); it_server++) {
    if(it_server->getNome() == nomeServidor) {
      return it_server;
    }
  }

  return servidores.end();

}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
