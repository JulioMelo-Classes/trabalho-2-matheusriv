#include "mensagem.h"

using namespace std;

Mensagem::Mensagem(string dataHora, string conteudo, int enviadaPor) {
    this->dataHora = dataHora;
    this->conteudo = conteudo;
    this->enviadaPor = enviadaPor;
}

Mensagem::Mensagem() {}

string Mensagem::getConteudo() {
    return conteudo;
}

string Mensagem::getDataHora() {
    return dataHora;
}

int Mensagem::getEnviadaPor() {
    return enviadaPor;
}

void Mensagem::setDataHora(const string dataHora) {
  this->dataHora = dataHora;
}

void Mensagem::setConteudo(const string conteudo) {
  this->conteudo = conteudo;
}

void Mensagem::setEnviadaPor(int enviadaPor) {
  this->enviadaPor = enviadaPor;
}