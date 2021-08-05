#include "sistema.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

void Sistema::salvar_sistema() {
    salvar_usuarios();
    salvar_usuariosLogados();
    salvar_servidores();
}

void Sistema::salvar_usuarios() {
  // Abre o arquivo usuarios.txt para salvar dados dos usuários
  ofstream osfstream_usuarios("../data/usuarios.txt");

  if(osfstream_usuarios) {
    // Imprime a quantidade de usuários cadastrados
    osfstream_usuarios << usuarios.size() << endl;

    // Imprime os dados de cada usuário
    for(auto it_user = usuarios.begin(); it_user != usuarios.end(); it_user++) {
      osfstream_usuarios << it_user->getId() << endl;
      osfstream_usuarios << it_user->getNome() << endl;
      osfstream_usuarios << it_user->getEmail() << endl;
      osfstream_usuarios << it_user->getSenha() << endl;
    }
  }
  else 
    std::cerr << "Erro ao salvar usuários! " << endl;
  
  osfstream_usuarios.close();

}

void Sistema::salvar_usuariosLogados() {
  // Abre o arquivo para salvar dados dos usuários logados
  ofstream ofstream_usuariosLog("../data/usuarioslogados.txt");

  if(ofstream_usuariosLog) {
    // Imprime a quantidade de usuários logados
    ofstream_usuariosLog << usuariosLogados.size() << endl;

    for(auto it = usuariosLogados.begin(); it != usuariosLogados.end(); it++) {
      // Imprime o id do usuário logado
      ofstream_usuariosLog << it->first << endl;
      // Imprime o nome do servidor que o usuário está visualizando
      ofstream_usuariosLog << it->second.first << endl;
      // Imprime o nome do canal de texto que o usuário está visualizando
      ofstream_usuariosLog << it->second.second << endl;
    }
  }
  else 
    std::cerr << "Erro ao salvar usuários logados!" << endl;

  ofstream_usuariosLog.close();

}

void Sistema::salvar_servidores() {
  // Abre o arquivo servidores.txt para salvar dados dos servidores cadastrados
  ofstream ofstream_servidores("../data/servidores.txt");

  if(ofstream_servidores) {
    // Imprime a quantidade de servidores cadastrados
    ofstream_servidores << servidores.size() << endl;

    // Imprime os dados de cada servidor
    for(auto it_server = servidores.begin(); it_server != servidores.end(); it_server++) {
      ofstream_servidores << it_server->getUsuarioDonoId() << endl;
      ofstream_servidores << it_server->getNome() << endl;
      ofstream_servidores << it_server->getDescricao() << endl;
      ofstream_servidores << it_server->getCodigoConvite() << endl;
      it_server->salvarIdsParticipantes(ofstream_servidores);
      it_server->salvarCanais(ofstream_servidores);
    }
  }
  else 
    std::cerr << "Erro ao salvar servidores!" << endl;

  ofstream_servidores.close();

}

void Sistema::carregar_sistema() {
  carregar_usuarios();
  carregar_usuariosLogados();
  carregar_servidores();
}

void Sistema::carregar_usuarios() {
  // Abre o arquivo para obter os dados do usuários
  ifstream ifstream_usuarios("../data/usuarios.txt");

  if(ifstream_usuarios) {
    // Verifica se o arquivo não está vazio
    if(ifstream_usuarios.peek() != ifstream::traits_type::eof()) {
      usuarios.clear();

      string users_qtd, id, nome, email, senha;

      // Lê a quantidade de usuários cadastrados
      getline(ifstream_usuarios, users_qtd);

      // Lê os dados de cada usuário
      for(int user = 0; user<stoi(users_qtd); user++) {
        getline(ifstream_usuarios, id);
        getline(ifstream_usuarios, nome);
        getline(ifstream_usuarios, email);
        getline(ifstream_usuarios, senha);

        // Cria e cadastra o novo usuário no sistema
        Usuario novoUsuario(stoi(id), nome, email, senha);
        usuarios.push_back(novoUsuario);
      }
    }
  } 
  else
    std::cerr << "Erro ao restaurar usuários!" << endl;

}

void Sistema::carregar_usuariosLogados() {
  // Abre o arquivo para obter os dados dos usuários logados
  ifstream ifstream_usuariosLog("../data/usuarioslogados.txt");

  if(ifstream_usuariosLog) {
    // Verifica se o arquivo não está vazio
    if(ifstream_usuariosLog.peek() != std::ifstream::traits_type::eof()) {
      usuariosLogados.clear();

      string users_qtd, id, nomeServidor, nomeCanal;

      // Lê a quantidade de usuários logados
      getline(ifstream_usuariosLog, users_qtd);

      // Lê os dados de cada usuário
      for(int user = 0; user<stoi(users_qtd); user++) {
        getline(ifstream_usuariosLog, id);
        getline(ifstream_usuariosLog, nomeServidor);
        getline(ifstream_usuariosLog, nomeCanal);
        // Insere o usuário logado no sistema
        usuariosLogados.insert({stoi(id), {nomeServidor,nomeCanal}});
      }
    }
  } 
  else 
    std::cerr << "Erro ao restaurar usuários logados!" << endl;

}

void Sistema::carregar_servidores() {
  // Abre o arquivo para obter os dados dos servidores
  ifstream ifstream_servidores("../data/servidores.txt");

  if(ifstream_servidores) {
    // Verifica se o arquivo não está vazio
    if(ifstream_servidores.peek() != ifstream::traits_type::eof()) {
      servidores.clear();

      string server_qtd, server_donoId, server_nome, server_desc;
      string server_cod, server_qtdParticipantes, server_partId;
      string canal_qtd, canal_Id, canal_nome;
      string mensagem_qtd, mensagem_donoId, mensagem_dataHora, mensagem_cont;

      // Lê a quantidade de usuários cadastrados
      getline(ifstream_servidores, server_qtd);

      // Lê os dados de cada servidor
      for(int server = 0; server<stoi(server_qtd); server++) {
        getline(ifstream_servidores, server_donoId);
        getline(ifstream_servidores, server_nome);
        getline(ifstream_servidores, server_desc);
        getline(ifstream_servidores, server_cod);
        
        // Cria e cadastra o novo servidor no sistema
        Servidor novoServidor(stoi(server_donoId), server_nome);
        novoServidor.setDescricao(server_desc);
        novoServidor.setCodigoConvite(server_cod);

        // Lê a quantidade de participantes do servidor
        getline(ifstream_servidores, server_qtdParticipantes);

        // Faz a leitura do Id de todos os participantes e os adiciona ao servidor
        for(int part = 0; part<stoi(server_qtdParticipantes); part++){
          getline(ifstream_servidores, server_partId);
          novoServidor.adicionaParticipante(stoi(server_partId));
        }

        // Lê a quantidade de canais do servidor
        getline(ifstream_servidores, canal_qtd);

        // Lê os dados dos canais e insere no servidor
        for(int canal = 0; canal<stoi(canal_qtd); canal++) {
          getline(ifstream_servidores, canal_nome);

          CanalTexto novoCanal(canal_nome);

          // Lê a quantidade de mensagens do canal
          getline(ifstream_servidores, mensagem_qtd);

          // Faz a leitura dos dados das mensagens do canal
          for(int m = 0; m<stoi(mensagem_qtd); m++) {
            getline(ifstream_servidores, mensagem_dataHora);
            getline(ifstream_servidores, mensagem_donoId);
            getline(ifstream_servidores, mensagem_cont);

            // Cria e adiciona a mensagem ao canal
            Mensagem novaMensagem(mensagem_dataHora, stoi(mensagem_donoId), mensagem_cont);
            novoCanal.addMensagem(novaMensagem);
          }
          // Adiciona o canal de texto ao servidor
          novoServidor.adicionaCanalTexto_(novoCanal);
        }
        // Adiciona o servidor
        servidores.push_back(novoServidor);
      }
    }
  } 
  else
    std::cerr << "Erro ao restaurar usuários!" << endl;

}

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user(const string email, const string senha, const string nome) {
  if(email.empty() || senha.empty() || nome.empty())
    return "Informe todos os dados necessários!";

  carregar_sistema();

  auto it_user = std::find_if(usuarios.begin(), usuarios.end(), 
                                [email](Usuario usuario){
                                  return usuario.getEmail() == email;
                                });

  if(it_user != usuarios.end())
    return "== Usuário " + email + " já existe! ==";
  
  countId++;
  Usuario NovoUsuario(countId, nome, email, senha);
  usuarios.push_back(NovoUsuario);

  salvar_sistema();

  return "== Usuário Criado ==";

}

string Sistema::login(const string email, const string senha) {
  if(email.empty() || senha.empty())
    return "Informe todos os dados necessários!";

  carregar_sistema();

  auto it_user = std::find_if(usuarios.begin(), usuarios.end(), 
                              [email, senha](Usuario usuario) {
                                return usuario.getEmail() == email && 
                                       usuario.getSenha() == senha;
                              });

  if(it_user != usuarios.end()) {
    if( search_usuariosLogados(it_user->getId()) ) { 
      return "== Usuário " + email + " já encontra-se logado! ==";
    } 
    else { 
      usuariosLogados.insert({it_user->getId(), {"",""}});
      salvar_sistema();
      return "== Logado como " + email + " ==";
    }
  }

  return "== Senha ou Usuário Inválidos! ==";

}

string Sistema::disconnect(int id) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false)  
    return "== Usuário precisa estar logado para desconectar! ==";

  usuariosLogados.erase(search_it_usuariosLogados(id));

  salvar_sistema();

  return "== Desconectando usuário " + usuarios[id].getEmail() + " ==";

}

string Sistema::create_server(int id, const string nome) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para criar servidor! ==";
  
  if(nome.empty())
    return "== Você não pode criar um servidor sem nome! ==";
  
  if(search_it_servidores(nome) != servidores.end()) 
    return "== Servidor com o nome '" + nome + "' já existe! ==";

  Servidor novoServidor(id, nome);
  servidores.push_back(novoServidor);

  salvar_sistema();

  return "== Servidor '" + nome + "' criado ==";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar descrição de um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não encontrado! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id) {
    it_server->setDescricao(descricao);
    salvar_sistema();

    return "== Descrição do servidor '" + nome + "' modificada ==";
  }

  return "== Você não pode alterar a descrição de um servidor que não foi criado por você! ==";

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar código de convite! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não encontrado! ==";

  if(it_server->getNome() == nome && it_server->getUsuarioDonoId() == id) {
      if(codigo.empty()) {
        it_server->setCodigoConvite(codigo);
        salvar_sistema();
        return "== Código de convite do servidor '" + nome + "' removido ==";
      }
      else {
        it_server->setCodigoConvite(codigo);
        salvar_sistema();
        return "== Código de convite do servidor '" + nome + "' modificado ==";
      }
  }
  
  return "== Você não pode alterar o código de convite de um servidor que não foi criado por você! ==";

}

string Sistema::list_servers(int id) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados ==";

  cout << "## Lista de Servidores ##" << endl;

  for(int i=0; i<servidores.size(); i++) {
    cout << "   " + servidores[i].getNome();
    if(servidores[i].getCodigoConvite().empty()) 
      cout << " [Servidor Aberto]" << endl;
    else 
      cout << " [Servidor Fechado]" << endl;;
  }

  return "";

}

string Sistema::list_servers_desc(int id) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados ==";

  cout << "## Lista de Descrição dos Servidores ##" << endl;

  for(int i=0; i<servidores.size(); i++) {
    cout << "   " + servidores[i].getNome();
    if(servidores[i].getDescricao().empty()) 
      cout << " | Servidor sem descrição" << endl;
    else 
      cout << " | " + servidores[i].getDescricao() << endl;
  }

  return "";

}

string Sistema::remove_server(int id, const string nome) {
  carregar_sistema();

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
    salvar_sistema();

    return "== Servidor '" + nome + "' removido ==";
  }
  
  return "== Você não é o dono do servidor '" + nome + "' ==";

}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para entrar num servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end()) 
    return "== Servidor '" + nome + "' não existe! ==";

  auto it_user = search_it_usuariosLogados(id);
  if(it_user->second.first != "" ) 
    return "== Saia do servidor conectado atualmente! ==";

  if(it_server->getUsuarioDonoId() == id ||
    it_server->getCodigoConvite().empty() || 
    it_server->getCodigoConvite() == codigo) {
      it_server->adicionaParticipante(id);
      it_user->second.first = nome;
      salvar_sistema();
      return "== " + usuarios[id].getNome() + " entrou no servidor '" + nome + "' ==";
  } 
  else if(it_server->getCodigoConvite() != "" && codigo.empty() ) {
    return "== Servidor requer código de convite! ==";
  } 
  
  return "== Código de convite incorreto! ==";

}

string Sistema::leave_server(int id, const string nome) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para sair de um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor para sair! ==";
  
  auto it_user = search_it_usuariosLogados(id);
  if(it_user->second.first.empty())
    return "== Você não está em qualquer servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  it_server->removeParticipante(id);
  
  it_user->second.first.clear();
  it_user->second.second.clear();

  salvar_sistema();
  
  return "== Saindo do servidor '" + nome + "' ==";

}

string Sistema::list_participants(int id) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de participantes de um servidor! ==";
  
  auto it_user = search_it_usuariosLogados(id);

  string nomeServidor = it_user->second.first;

  if(it_user->first == id && nomeServidor != "") {
    // usuario está visualizando um servidor
    search_it_servidores(nomeServidor)->list_participants(usuarios);
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
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para criar um canal num servidor! ==";
  
  if(nome.empty()) 
    return "== Não é possível criar um canal sem nome! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  CanalTexto NovoCanalTexto(nome);

  string retorno;
  retorno = search_it_servidores(nomeServidor)->adicionaCanalTexto(NovoCanalTexto);

  salvar_sistema();

  return retorno;

}


string Sistema::enter_channel(int id, const string nome) {
  carregar_sistema();

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

  if(it_user->second.second != "") 
    return "== Saia do canal de texto conectado atualmente! ==";
  
  string str_erro = search_it_servidores(nomeServidor)->enter_leave_channel(nome);
  if(str_erro != "")
    return str_erro;

  it_user->second.second = nome;

  salvar_sistema();

  return "== " + usuarios[id].getNome() + " entrou no canal '" + nome + "' ==";

}

string Sistema::leave_channel(int id) {
  carregar_sistema();

  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para sair de um canal! ==";
  
  auto it_user = search_it_usuariosLogados(id);
  
  string nomeServidor = it_user->second.first;
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  string nomeCanal = it_user->second.second;
  if(nomeCanal.empty())
    return "== Você não está num canal! ==";

  string str_erro = search_it_servidores(nomeServidor)->enter_leave_channel(nomeCanal);
  if(str_erro != "")
    return str_erro;

  it_user->second.second.clear();

  salvar_sistema();

  return "== Saindo do canal '" + nomeCanal + "' ==";

}

string Sistema::send_message(int id, const string mensagem) {
  carregar_sistema();

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

  it_canaltexto->criarMensagem(mensagem, id);

  salvar_sistema();

  return "";

}

string Sistema::list_messages(int id) {
  carregar_sistema();

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

  salvar_sistema();

  return "";

}

string Sistema::list_online_users(int id) {
  carregar_sistema();

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
  carregar_sistema();
  //verificar se usuario esta no std::map<int, std::pair<std::string, std::string>> usuariosLogados;
  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                          [&](std::pair<int, std::pair<std::string, std::string>> entrada){ 
                                return entrada.first == id;
                              });
                                
  if(it != usuariosLogados.end()) { 
    //usuário logado 
    return true;
  }

  //usuário não logado 
  return false;
  
}

std::map<int, std::pair<string, string>>::iterator Sistema::search_it_usuariosLogados(int id) {
  carregar_sistema();

  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                          [&](std::pair<int, std::pair<string, string>> entrada){ 
                                return entrada.first == id;
                              });

  return it;

}

std::vector<Servidor>::iterator Sistema::search_it_servidores(string nomeServidor) {
  carregar_sistema();

  auto it_server= std::find_if(servidores.begin(), servidores.end(), 
                              [&](Servidor servidor){
                                    return servidor.getNome() == nomeServidor;
                                  });

  return it_server;

}



/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
