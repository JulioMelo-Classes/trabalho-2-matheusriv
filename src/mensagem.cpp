#include "mensagem.h"

using namespace std;

Mensagem::Mensagem(string dataHora, int enviadaPor, string conteudo) {
    this->dataHora = dataHora;
    this->enviadaPor = enviadaPor;
    this->conteudo = conteudo;
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