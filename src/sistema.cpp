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

/*
Extra arquivos: usuários ok
*/
void Sistema::salvar_usuarios() {
  ofstream ofstream_usuarios("../database/usuarios.txt");

  if(!ofstream_usuarios) {
    cerr << "Erro ao salvar usuários! " << endl;
    return; 
  }

  // Imprime a quantidade de usuários cadastrados
  ofstream_usuarios << usuarios.size() << endl;

  // Imprime os dados de cada usuário
  for(auto it_user = usuarios.begin(); it_user != usuarios.end(); it_user++) {
    ofstream_usuarios << it_user->getId() << endl;
    ofstream_usuarios << it_user->getNome() << endl;
    ofstream_usuarios << it_user->getEmail() << endl;
    ofstream_usuarios << it_user->getSenha() << endl;
  }
  
  ofstream_usuarios.close();

}

void Sistema::salvar_usuariosLogados() {
  ofstream ofstream_usuariosLog("../database/usuarioslogados.txt");

  if(!ofstream_usuariosLog) {
    cerr << "Erro ao salvar usuários logados!" << endl;
    return;
  }

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

  ofstream_usuariosLog.close();

}

/*
Extra arquivos: servidores e canais incompleto 0,5
Essa parte aqui parece estar com algum problema,
  nos testes de "enter-server" os usuários ficam repetidos como se, a cada vez que o sistema roda ele não reconhecesse
  que aqueles usuários estão logados naquele servidor e apenas os readicionasse
  */
void Sistema::salvar_servidores() {
  ofstream ofstream_servidores("../database/servidores.txt");
  ofstream ofstream_canaistexto("../database/canaistexto.txt");

  if(!ofstream_servidores || !ofstream_canaistexto) {
    cerr << "Erro ao salvar servidores!" << endl;
    return;
  }

  // Imprime a quantidade de servidores cadastrados
  ofstream_servidores << servidores.size() << endl;
  // Imprime os dados de cada servidor
  for(auto it_server = servidores.begin(); it_server != servidores.end(); it_server++) {
    ofstream_servidores << it_server->getUsuarioDonoId() << endl;
    ofstream_servidores << it_server->getNome() << endl;
    ofstream_servidores << it_server->getDescricao() << endl;
    ofstream_servidores << it_server->getCodigoConvite() << endl;
    it_server->salvarIdsOfstream(ofstream_servidores);
  }

  // Imprime a quantidade de servidores cadastrados
  ofstream_canaistexto << servidores.size() << endl;
  // Imprime os dados de cada servidor
  for(auto it_server = servidores.begin(); it_server != servidores.end(); it_server++) {
    ofstream_canaistexto << it_server->getNome() << endl;
    it_server->salvarCanaisOfstream(ofstream_canaistexto);
  }

  ofstream_servidores.close();
  ofstream_canaistexto.close();

}

void Sistema::carregar_sistema() {
  carregar_usuarios();
  carregar_usuariosLogados();
  carregar_servidores();
}

void Sistema::carregar_usuarios() {
  ifstream ifstream_usuarios("../database/usuarios.txt");

  if(!ifstream_usuarios) {
    cerr << "Erro ao restaurar usuários!" << endl;
    return;
  }

  // Verifica se o arquivo não está vazio
  if(ifstream_usuarios.peek() != ifstream::traits_type::eof()) {
    string users_qtd, id, nome, email, senha;

    // Lê a quantidade de usuários cadastrados
    getline(ifstream_usuarios, users_qtd);

    countId = stoi(users_qtd) - 1;

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

void Sistema::carregar_usuariosLogados() {
  ifstream ifstream_usuariosLog("../database/usuarioslogados.txt");

  if(!ifstream_usuariosLog) {
    cerr << "Erro ao restaurar usuários logados!" << endl;
    return;
  }

  // Verifica se o arquivo não está vazio
  if(ifstream_usuariosLog.peek() != std::ifstream::traits_type::eof()) {
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

void Sistema::carregar_servidores() {
  ifstream ifstream_servidores("../database/servidores.txt");
  ifstream ifstream_canaistexto("../database/canaistexto.txt");

  if(!ifstream_servidores || !ifstream_canaistexto) {
    cerr << "Erro ao restaurar servidores!" << endl;
    return;
  }

  // Verifica se o arquivo não está vazio
  if(ifstream_servidores.peek() != ifstream::traits_type::eof()) {
    string server_qtd, server_donoId, server_nome, server_desc;
    string server_cod, server_qtdParticipantes, server_partId;

    // Lê a quantidade de servidores cadastrados
    getline(ifstream_servidores, server_qtd);

    // Lê os dados de cada servidor
    for(int server = 0; server<stoi(server_qtd); server++) {
      getline(ifstream_servidores, server_donoId);
      getline(ifstream_servidores, server_nome);
      getline(ifstream_servidores, server_desc);
      getline(ifstream_servidores, server_cod);
      
      Servidor novoServidor(stoi(server_donoId), server_nome);
      novoServidor.setDescricao(server_desc);
      novoServidor.setCodigoConvite(server_cod);

      // Lê a quantidade de participantes do servidor
      getline(ifstream_servidores, server_qtdParticipantes);

      // Faz a leitura do Id dos participantes e os adiciona ao servidor
      for(int part = 0; part<stoi(server_qtdParticipantes); part++) {
        getline(ifstream_servidores, server_partId);
        novoServidor.adicionaParticipante(stoi(server_partId));
      }

      // Adiciona o servidor
      servidores.push_back(novoServidor);
    }
  }

  // Verifica se o arquivo não está vazio
  if(ifstream_canaistexto.peek() != ifstream::traits_type::eof()) {
    string server_qtd, server_nome, canal_qtd, canal_Id, canal_nome;
    string mensagem_qtd, mensagem_donoId, mensagem_dataHora, mensagem_cont;

    // Lê a quantidade de servidores cadastrados
    getline(ifstream_canaistexto, server_qtd);

    for(int server = 0; server<stoi(server_qtd); server++) {
      // Lê o nome do servidor
      getline(ifstream_canaistexto, server_nome);

      // Lê a quantidade de canais do servidor
      getline(ifstream_canaistexto, canal_qtd);

      // Lê os dados dos canais e insere no servidor
      for(int canal = 0; canal<stoi(canal_qtd); canal++) {
        getline(ifstream_canaistexto, canal_nome);

        CanalTexto novoCanalTexto(canal_nome);

        // Lê a quantidade de mensagens do canal
        getline(ifstream_canaistexto, mensagem_qtd);

        // Faz a leitura dos dados das mensagens do canal
        for(int m = 0; m<stoi(mensagem_qtd); m++) {
          getline(ifstream_canaistexto, mensagem_dataHora);
          getline(ifstream_canaistexto, mensagem_donoId);
          getline(ifstream_canaistexto, mensagem_cont);

          // Cria e adiciona a mensagem ao canal
          Mensagem novaMensagem(mensagem_dataHora, stoi(mensagem_donoId), mensagem_cont);
          novoCanalTexto.adicionaMensagem(novaMensagem);
        }

        // Adiciona o canal de texto ao servidor
        auto it_server = search_it_servidores(server_nome);
        it_server->adicionaCanalTexto_(novoCanalTexto);
      } 
    }
  }

}

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user(const string email, const string senha, const string nome) {
  if(email.empty() || senha.empty() || nome.empty())
    return "== Informe todos os dados necessários! ==";

  auto it = std::find_if(usuarios.begin(), usuarios.end(), 
                          [email](Usuario usuario){
                            return usuario.getEmail() == email;
                          });

  if(it != usuarios.end())
    return "== Usuário " + email + " já existe! ==";
  
  countId++;
  Usuario novoUsuario(countId, nome, email, senha);
  usuarios.push_back(novoUsuario);

  salvar_sistema();

  return "== Usuário Criado ==";

}

string Sistema::login(const string email, const string senha) {
  if(email.empty() || senha.empty())
    return "== Informe todos os dados necessários! ==";

  auto it = std::find_if(usuarios.begin(), usuarios.end(), 
                            [email, senha](Usuario usuario){
                              return usuario.getEmail() == email && 
                                      usuario.getSenha() == senha;
                            });

  if(it == usuarios.end()) 
    return "== Senha ou Usuário Inválidos! ==";

  if(search_usuariosLogados(it->getId())) 
    return "== Usuário " + email + " já encontra-se logado! ==";
  
  usuariosLogados.insert({it->getId(), {"",""}});

  salvar_sistema();

  return "== Logado como " + email + " ==";

}

string Sistema::disconnect(int id) {
  if(search_usuariosLogados(id) == false)  
    return "== Usuário precisa estar logado para desconectar! ==";

  usuariosLogados.erase(search_it_usuariosLogados(id));

  salvar_sistema();

  return "== Desconectando usuário " + usuarios[id].getEmail() + " ==";

}

string Sistema::create_server(int id, const string nome) {
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
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar descrição de um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  if(it_server->getUsuarioDonoId() != id)
    return "== Você não pode alterar a descrição de um servidor que não foi criado por você! ==";

  if(descricao.empty()) {
    if(it_server->getDescricao().empty()) {
      return "== Descrição do servidor '" + nome + "' já está vazia! ==";
    } 
    else { 
      it_server->setDescricao(descricao);
      salvar_sistema();
      return "== Descrição do servidor '" + nome + "' removida ==";
    }
  }

  it_server->setDescricao(descricao);

  salvar_sistema();

  return "== Descrição do servidor '" + nome + "' modificada ==";

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para mudar código de convite! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  if(it_server->getUsuarioDonoId() != id)
    return "== Você não pode alterar o código de convite de um servidor que não foi criado por você! ==";

  if(codigo.empty()) {
    if(it_server->getCodigoConvite().empty()) {
      return "== Servidor '" + nome + "' já não possui código de convite! ==";
    }
    else {
      it_server->setCodigoConvite(codigo);
      salvar_sistema();
      return "== Código de convite do servidor '" + nome + "' removido ==";
    }
  }
    
  it_server->setCodigoConvite(codigo);
  
  salvar_sistema();
  
  return "== Código de convite do servidor '" + nome + "' modificado ==";

}

string Sistema::list_servers(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados! ==";

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
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de servidores! ==";

  if(servidores.empty()) 
    return "== Não há servidores cadastrados! ==";

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
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para remover um servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor para remover! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  if(it_server->getUsuarioDonoId() != id) 
    return "== Você não é o dono do servidor '" + nome + "'! ==";

  for(auto it = usuariosLogados.begin(); it != usuariosLogados.end(); it++) { 
    // atualizar usuariosLogados que estejam visualizando o servidor e apagar servidor
    if(it->second.first == nome) { 
        // second.first Campo do nome do servidor
        it->second.first.clear();
        // second.second Campo do nome do canal de texto
        it->second.second.clear(); 
    }
  }

  servidores.erase(it_server);
  
  salvar_sistema();

  return "== Servidor '" + nome + "' removido ==";

}

/*
A2.7 0,8
*/
string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para entrar num servidor! ==";
  
  if(nome.empty())
    return "== Adicione nome do servidor! ==";
  
  auto it_server = search_it_servidores(nome);
  if(it_server == servidores.end()) 
    return "== Servidor '" + nome + "' não existe! ==";

  auto it_user = search_it_usuariosLogados(id);
  if(it_user->second.first == nome) 
    return "== Usuário já está no servidor! ==";
  //isso aqui não está na especificação! Se o usuário precisa sair de um servidor pra entrar em outro,
  //não tem sentido a ideia de guardar qual servidor que ele está visualizando. Vou remover 20% por isso
  if(it_user->second.first != "")
    return "== Saia do servidor conectado atualmente! ==";

  if(it_server->getUsuarioDonoId() == id ||
    it_server->getCodigoConvite().empty() || 
    it_server->getCodigoConvite() == codigo) {
      it_server->adicionaParticipante(id);
      it_user->second.first = nome;
      salvar_sistema();
      return "== " + usuarios[id].getNome() + " entrou no servidor '" + nome + "' ==";
  } 
  else if(!(it_server->getCodigoConvite().empty()) && codigo.empty()) {
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
  if(it_server == servidores.end())
    return "== Servidor '" + nome + "' não existe! ==";

  it_server->removeParticipante(id);
  
  it_user->second.first.clear();
  it_user->second.second.clear();

  salvar_sistema();
  
  return "== Saindo do servidor '" + nome + "' ==";

}

string Sistema::list_participants(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de participantes de um servidor! ==";
  
  auto it_user = search_it_usuariosLogados(id);

  if(it_user->second.first.empty()) 
    return "== Você não está em qualquer servidor! ==";

  search_it_servidores(it_user->second.first)->list_participants(usuarios);

  return "";

}

/*
B1.1 ok
*/
string Sistema::list_channels(int id) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para acessar lista de canais de um servidor! ==";

  auto it_user = search_it_usuariosLogados(id);

  if(it_user->second.first.empty()) 
    return "== Você não está em qualquer servidor! ==";
  
  search_it_servidores(it_user->second.first)->list_channels();

  return "";

}

/*
B1.2 ok
*/
string Sistema::create_channel(int id, const string nome) {
  if(search_usuariosLogados(id) == false) 
    return "== Usuário precisa estar logado para criar um canal num servidor! ==";
  
  if(nome.empty()) 
    return "== Não é possível criar um canal sem nome! ==";

  string nomeServidor = search_it_usuariosLogados(id)->second.first;
  if(nomeServidor.empty())
    return "== Você não está em qualquer servidor! ==";

  CanalTexto novoCanalTexto(nome);

  string retorno;
  retorno = search_it_servidores(nomeServidor)->adicionaCanalTexto(novoCanalTexto);

  salvar_sistema();

  return retorno;

}

/*
B1.3 0,9
*/
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
  //essa operação também não estava na especificação, um usuario pode apenas entrar em um canal sem fazer leave do anterior!, vou tirar 10% por isso
  if(it_user->second.second != "") 
    return "== Saia do canal de texto conectado atualmente! ==";
  
  string retorno = search_it_servidores(nomeServidor)->enter_leave_channel(nome);
  if(retorno != "")
    return retorno;

  it_user->second.second = nome;

  salvar_sistema();

  return "== " + usuarios[id].getNome() + " entrou no canal '" + nome + "' ==";

}

/*
B1.4 ok
*/
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

  string retorno = search_it_servidores(nomeServidor)->enter_leave_channel(nomeCanal);
  if(retorno != "")
    return retorno;

  it_user->second.second.clear();

  salvar_sistema();

  return "== Saindo do canal '" + nomeCanal + "' ==";

}

/*
B2.1 ok
*/
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

  it_canaltexto->criarMensagem(mensagem, id);

  salvar_sistema();

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
  auto it = std::find_if(usuariosLogados.begin(), usuariosLogados.end(), 
                          [&](std::pair<int, std::pair<string, string>> entrada){ 
                                return entrada.first == id;
                              });

  return it;

}

std::vector<Servidor>::iterator Sistema::search_it_servidores(string nomeServidor) {
  auto it_server = std::find_if(servidores.begin(), servidores.end(), 
                              [&](Servidor servidor){
                                    return servidor.getNome() == nomeServidor;
                                  });

  return it_server;

}



/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
