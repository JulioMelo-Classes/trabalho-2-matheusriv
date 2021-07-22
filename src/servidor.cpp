#include "servidor.h"

using namespace std;

Servidor::Servidor(int usuarioDonoId, string nome) {
    this->usuarioDonoId = usuarioDonoId;
    this->nome = nome;
}

int Servidor::getUsuarioDonoId() {
    return usuarioDonoId;
}

string Servidor::getNome() {
    return nome;
}

string Servidor::getDescricao() {
    return descricao;
}

string Servidor::getCodigoConvite() {
    return codigoConvite;
}

vector<CanalTexto> Servidor::getCanaisTexto() {
    return canaisTexto;
}

vector<int> Servidor::getParticipantesIds() {
    return participantesIDs;
}

void Servidor::adicionaParticipante(int id) {
    participantesIDs.push_back(id);
}