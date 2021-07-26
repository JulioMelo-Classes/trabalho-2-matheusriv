#include "servidor.h"

using namespace std;

Servidor::Servidor(int usuarioDonoId, const string nome) {
    this->usuarioDonoId = usuarioDonoId;
    this->nome = nome;
}

Servidor::Servidor() {}

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

vector<Mensagem> Servidor::getMensagens(const string nomeCanal) {
    auto it_canal = canaisTexto.begin();
    for(; it_canal != canaisTexto.end(); it_canal++){
        if(it_canal->getNome() == nomeCanal)
            break;
    }

    return it_canal->getMensagens();
}

void Servidor::setDescricao(string descricao) {
    this->descricao = descricao;
}

void Servidor::setConvite(string codigoConvite) {
    this->codigoConvite = codigoConvite;
}

void Servidor::adicionaParticipante(int id) {
    participantesIDs.push_back(id);
}

void Servidor::removeParticipante(int id){
    participantesIDs.erase(std::remove(participantesIDs.begin(), participantesIDs.end(), id), participantesIDs.end());
}

void Servidor::adicionaCanalTexto(CanalTexto novoCanalTexto){
    canaisTexto.push_back(novoCanalTexto);
}

void Servidor::enviaMensagem(string nomeCanal, Mensagem mensagem) {
    auto it_canal = canaisTexto.begin();
    for(; it_canal != canaisTexto.end(); it_canal++){
        if(it_canal->getNome() == nomeCanal)
            break;
    }

    it_canal->adicionaMensagem(mensagem);
}