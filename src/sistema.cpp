#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
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
  
  if(search_it_servidores(nome) != servidores.end()){
    return "== Servidor com o nome '" + nome + "' já existe! ==";
  }

  Servidor novoServidor(id, nome);
  servidores.push_back(novoServidor);
  //servidores[(int)servidores.size()-1].adicionaParticipante(id);

  return "== Servidor '" + nome + "' criado ==";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar descrição de um servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não encontrado! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id){
    it_server->setDescricao(descricao);
    return "== Descrição do servidor '" + nome + "' modificada ==";
  }

  return "== Você não pode alterar a descrição de um servidor que não foi criado por você! ==";

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar código de convite! ==";
  
  auto it_server = search_it_servidores(nome);

  if(it_server == servidores.end())
    return "Servidor '" + nome + "' não encontrado!";

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
  
  string lista_servidores;

  lista_servidores = "## Lista de Servidores ##\n";
  for(int i=0; i<servidores.size(); i++) {
    lista_servidores += "   " + servidores[i].getNome();

    if(servidores[i].getCodigoConvite().empty()) {
      lista_servidores += " | Servidor Aberto\n";
    }
    else {
      lista_servidores += " | Servidor Fechado\n";
    }
  }
  lista_servidores += "## Fim da lista de servidores ##";

  return lista_servidores;

}

string Sistema::list_servers_desc(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados ==";

  string lista_servidores;

  lista_servidores = "## Lista de Descrição dos Servidores ##\n";
  for(int i=0; i<servidores.size(); i++) {
    lista_servidores += "   " + servidores[i].getNome();

    if(servidores[i].getDescricao().empty()){
      lista_servidores += " | Servidor sem descrição\n";
    }
    else{
      lista_servidores += " | '" + servidores[i].getDescricao() + "'\n";
    }
  }
  lista_servidores += "## Fim da lista de servidores ##";

  return lista_servidores;
}

string Sistema::remove_server(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para remover um servidor! ==";
  
  auto it_server = search_it_servidores(nome);

  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id) {
    // se nome do servidor e id do dono do servidor forem iguais aos parametros
    // apagar servidor e atualizar usuariosLogados que estejam visualizando o servidor
    for(auto it_usuariosLogados = usuariosLogados.begin(); 
    it_usuariosLogados != usuariosLogados.end(); it_usuariosLogados++){ 
        if(it_usuariosLogados->second.first == nome){ 
          it_usuariosLogados->second.first.clear();
          it_usuariosLogados->second.second.clear(); 
        }
    }
    servidores.erase(it_server);
  }
  
  return "== Você não é o dono do servidor '" + nome + "' ==";

}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para entrar num servidor! ==";
  
  auto it_server = search_it_servidores(nome);

  if(it_server == servidores.end()) 
    return "== Servidor '" + nome + "' não existe! ==";

  if(it_server->getUsuarioDonoId() == id ||
  it_server->getCodigoConvite().empty() || 
  it_server->getCodigoConvite() == codigo) {
    it_server->adicionaParticipante(id);
    search_it_usuariosLogados(id)->second.first = nome;
    return "== Entrou no servidor '" + nome + "' com sucesso ==";
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
  
  auto it_server = search_it_servidores(nome);

  it_server->removeParticipante(id);
  it_user->second.first.clear();
  it_user->second.second.clear();
  
  return "== Saindo do servidor '" + nome + "' ==";

}

string Sistema::list_participants(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de participantes de um servidor! ==";
  
  auto it_user = search_it_usuariosLogados(id);

  if(it_user->first == id && it_user->second.first != ""){
    // usuario está visualizando um servidor

    vector<int> vetorParticipantesIds;

    for(int i=0; i<servidores.size(); i++) {
      if(servidores[i].getNome() == it_user->second.first) { 
        vetorParticipantesIds = servidores[i].getParticipantesIds();
        break;
      }
    }

    string listaParticipantes;

    listaParticipantes = "## Lista de Participantes '" + it_user->second.first + "' ##\n";
    for(int i=0; i<usuarios.size(); i++) {
      for(int j=0; j<vetorParticipantesIds.size(); j++) {
        if(usuarios[i].getId() == vetorParticipantesIds[j])
          listaParticipantes += "   " + usuarios[i].getNome() + "\n";
      }
    }
    listaParticipantes +=  "## Fim da lista de participantes ##";

    return listaParticipantes;

  }

  // usuario não está visualizando um servidor
  return "== Não há servidor conectado! ==";

}

string Sistema::list_channels(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de canais de um servidor! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  vector<CanalTexto> vetorCanaisTexto = search_it_servidores(nomeServidor)->getCanaisTexto();

  if(vetorCanaisTexto.empty()) 
    return "== Nenhum canal de texto em '" + nomeServidor + "' foi encontrado! ==";

  string canais;
  canais += "# Canais de texto '" + nomeServidor + "' #\n";
  for(int i=0; i<vetorCanaisTexto.size(); i++) {
    canais += "  " + vetorCanaisTexto[i].getNome() + "\n";
  }
  canais += "# Fim canais de texto #";

  return canais;

}

string Sistema::create_channel(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para criar um canal num servidor! ==";
  
  if(nome.empty()) 
    return "== Não é possível criar um canal sem nome! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";
  
  auto it_server = search_it_servidores(nomeServidor);

  CanalTexto NovoCanalTexto(nome);
  it_server->adicionaCanalTexto(NovoCanalTexto);

  return "== Canal de texto '" + nome + "' em '" + nomeServidor + "' criado ==";

}


string Sistema::enter_channel(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado parar entrar num canal! ==";
  
  if(nome.empty()) 
    return "== Não é possível entrar em um canal sem nome! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  vector<CanalTexto> vetorCanaisTexto = search_it_servidores(nomeServidor)->getCanaisTexto();

  if(vetorCanaisTexto.empty()) 
    return "== Nenhum canal de texto em '" + nomeServidor + "' foi encontrado! ==";
  
  for(int i=0; i<vetorCanaisTexto.size(); i++){
    if(vetorCanaisTexto[i].getNome() == nome){
      // parametro canal de usuarioLogados recebe nome do canal
      search_it_usuariosLogados(id)->second.second = nome;
      return "== Entrou no canal '" + nome + "' em '" + nomeServidor + "' ==";
    }
  }

  return "== Canal '" + nome + "' não existe! ==";

}

string Sistema::leave_channel(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para sair de um canal! ==";
  
  string nomeServidor = search_it_usuariosLogados(id)->second.first;

  string nomeCanalConectado = search_it_usuariosLogados(id)->second.second;

  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";
  
  if(nomeCanalConectado.empty())
    return "== Você não está num canal! ==";

  vector<CanalTexto> vetorCanaisTexto = search_it_servidores(nomeServidor)->getCanaisTexto();

  if(vetorCanaisTexto.empty()) 
    return "== Nenhum canal de texto em '" + nomeServidor + "' foi encontrado! ==";
  
  for(int i=0; i<vetorCanaisTexto.size(); i++){
    if(vetorCanaisTexto[i].getNome() == nomeCanalConectado){
      search_it_usuariosLogados(id)->second.second.clear();
      return "== Saindo do canal '" + nomeCanalConectado + "' ==";
    }
  }

  return "== Canal não existe! ==";

}

string Sistema::send_message(int id, const string mensagem) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mandar uma mensagem! ==";

  if(mensagem.empty()) 
    return "== Não é possível enviar uma mensagem vazia! ==";
  
  string nomeServidor = search_it_usuariosLogados(id)->second.first;

  string nomeCanal = search_it_usuariosLogados(id)->second.second;

  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";
  
  if(nomeCanal.empty())
    return "== Você não está num canal! ==";


  auto it_server = search_it_servidores(nomeServidor);

  char dataHora[64];
  time_t now = time(nullptr);

  strftime(dataHora, sizeof(dataHora), "%d/%m/%Y - %R", localtime(&now));

  Mensagem novaMensagem(dataHora, mensagem, id);

  it_server->enviaMensagem(nomeCanal, novaMensagem);

  return "== Mensagem enviada ==";

}

string Sistema::list_messages(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de mensagens! ==";
  
  string nomeServidor = search_it_usuariosLogados(id)->second.first;

  string nomeCanal = search_it_usuariosLogados(id)->second.second;

  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";
  
  if(nomeCanal.empty())
    return "== Você não está num canal! ==";

  
  auto it_server = search_it_servidores(nomeServidor);

  vector<Mensagem> vetorMensagens = it_server->getMensagens(nomeCanal);
  
  if(vetorMensagens.empty()) 
    return "== Sem mensagens para exibir ==";

  string string_mensagens;

  string_mensagens = "== Mensagens '" + nomeCanal + "' ==" + "\n";

  for(auto it_mensagem=vetorMensagens.begin(); it_mensagem!=vetorMensagens.end(); it_mensagem++){ 
    string nomeUsuario = usuarios[it_mensagem->getEnviadaPor()].getNome();
    string_mensagens += nomeUsuario + " <" + it_mensagem->getDataHora() + ">: " + it_mensagem->getConteudo() + "\n";
  }

  string_mensagens += "== Fim das Mensagens ==";

  return string_mensagens;

}

string Sistema::list_online_users(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado! ==";
  
  vector<int> vetorIdsOnline;
  string listaUsuariosOnline;

  for(auto it = usuariosLogados.begin(); it != usuariosLogados.end(); it++){
    vetorIdsOnline.push_back(it->first);
  }

  listaUsuariosOnline = "## Usuários online no Concordo ##\n";
  for(int i=0; i<usuarios.size(); i++) {
      for(int j=0; j<vetorIdsOnline.size(); j++) {
        if(usuarios[i].getId() == vetorIdsOnline[j])
          listaUsuariosOnline += "   " + usuarios[i].getNome() + "\n";
      }
    }
  listaUsuariosOnline +=  "## Fim da lista de usuários ##";

  return listaUsuariosOnline;

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

std::vector<Servidor>::iterator Sistema::search_it_servidores(string nomeServidor){
  auto it_server = servidores.begin();
  for(; it_server != servidores.end(); it_server++) {
    if(it_server->getNome() == nomeServidor) {
      return it_server;
    }
  }

  return servidores.end();

}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
