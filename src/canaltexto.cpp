#include "canaltexto.h"

using namespace std;

CanalTexto::CanalTexto(const string nome) {
    this->nome = nome;
}

string CanalTexto::getNome(){
    return nome;
}

vector<Mensagem> CanalTexto::getMensagens(){
    return mensagens;
}

void CanalTexto::setNome(const string novoNome){
    this->nome = novoNome;
}

void CanalTexto::adicionaMensagem(Mensagem novaMensagem){
    mensagens.push_back(novaMensagem);
}