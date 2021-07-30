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

void Servidor::setDescricao(string descricao) {
    this->descricao = descricao;
}

void Servidor::setConvite(string codigoConvite) {
    this->codigoConvite = codigoConvite;
}

void Servidor::adicionaParticipante(int id) {
    participantesIDs.push_back(id);
}

void Servidor::removeParticipante(int id) {
    participantesIDs.erase(std::remove(participantesIDs.begin(), participantesIDs.end(), id), participantesIDs.end());
}

void Servidor::adicionaCanalTexto(CanalTexto novoCanalTexto) {
    canaisTexto.push_back(novoCanalTexto);
}

void Servidor::list_channels() {
    if(canaisTexto.empty()) { 
        cout << "== Nenhum canal de texto em '" << nome << "' foi encontrado! ==";
    }

    cout << "# Canais de texto '" << nome << "' #" << endl;

    for(int i=0; i<canaisTexto.size(); i++) {
        cout << "  " << canaisTexto[i].getNome() << endl;
    }

}

void Servidor::list_participants(vector<Usuario> &usuarios) {
    cout << "## Lista de Participantes '" << nome << "' ##" << endl;
    
    for(int i=0; i<usuarios.size(); i++) {
        for(int j=0; j<participantesIDs.size(); j++) {
            if(usuarios[i].getId() == participantesIDs[j])
                cout << "   " << usuarios[i].getNome() << endl;
        }
    }

}

string Servidor::enter_leave_channel(string nomeCanal) {
    if(canaisTexto.empty()) { 
        return "== Nenhum canal de texto em '" + nome + "' foi encontrado! ==";
    }

    if(search_it_canalTexto(nomeCanal) == canaisTexto.end())
        return "== Canal '" + nomeCanal + "' não existe! ==";
    
    return "";

}

vector<CanalTexto>::iterator Servidor::search_it_canalTexto(string nomeCanal) {
    auto it_canaltexto = canaisTexto.begin();
    for(; it_canaltexto != canaisTexto.end(); it_canaltexto++) {
        if(it_canaltexto->getNome() == nomeCanal)
            return it_canaltexto;
    }

    return canaisTexto.end();

}