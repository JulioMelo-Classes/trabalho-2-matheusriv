#include "canaltexto.h"

using namespace std;

CanalTexto::CanalTexto(const string nome) {
    this->nome = nome;
}

string CanalTexto::getNome() {
    return nome;
}

void CanalTexto::setNome(const string novoNome){ 
    this->nome = novoNome;
}

void CanalTexto::criarMensagem(const string mensagem, int id) {
    char dataHora[64];
    time_t now = time(nullptr);

    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y - %R", localtime(&now));

    Mensagem novaMensagem(dataHora, mensagem, id);

    addMensagem(novaMensagem);

    cout << "== Mensagem enviada ==";
}

void CanalTexto::addMensagem(Mensagem novaMensagem) {
    mensagens.push_back(novaMensagem);
}

void CanalTexto::list_messages(vector<Usuario> &usuarios) {
    if(mensagens.empty()) { 
        cout << "== Sem mensagens para exibir ==";
        return;
    }

    cout << "\n== Mensagens '" << nome << "' ==" << endl;

    for(int i=0; i<mensagens.size(); i++) {
        string nomeUsuario = usuarios[mensagens[i].getEnviadaPor()].getNome();
        cout << nomeUsuario << " <" << mensagens[i].getDataHora() 
            << ">: " + mensagens[i].getConteudo() << endl;
    }
}