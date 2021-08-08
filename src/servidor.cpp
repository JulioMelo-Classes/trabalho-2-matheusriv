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

void Servidor::setCodigoConvite(string codigoConvite) {
    this->codigoConvite = codigoConvite;
}

void Servidor::adicionaParticipante(int id) {
    participantesIDs.push_back(id);
}

void Servidor::removeParticipante(int id) {
    participantesIDs.erase(std::remove(participantesIDs.begin(), participantesIDs.end(), id), participantesIDs.end());
}

string Servidor::adicionaCanalTexto(CanalTexto novoCanalTexto) {
    string nomeCanal = novoCanalTexto.getNome();

    if(search_it_canalTexto(nomeCanal) != canaisTexto.end()) 
        return "== Canal de texto '" + nomeCanal + "' já existe! ==";

    adicionaCanalTexto_(novoCanalTexto);

    return "== Canal de texto '" + nomeCanal + "' em '" + nome + "' criado ==";

}

void Servidor::adicionaCanalTexto_(CanalTexto novoCanalTexto) {
    canaisTexto.push_back(novoCanalTexto);

}

void Servidor::list_channels() {
    if(canaisTexto.empty()) { 
        cout << "== Nenhum canal de texto em '" << nome << "' foi encontrado! ==";
        return;
    }

    cout << "# Canais de texto '" << nome << "' #" << endl;

    for(int i=0; i<canaisTexto.size(); i++) {
        cout << "  " << canaisTexto[i].getNome() << endl;
    }

}

void Servidor::list_participants(vector<Usuario> &usuarios) {
    cout << "## Lista de Participantes do Servidor '" << nome << "' ##" << endl;
    
    for(int i=0; i<usuarios.size(); i++) {
        for(int j=0; j<participantesIDs.size(); j++) {
            if(usuarios[i].getId() == participantesIDs[j])
                cout << "   " << usuarios[i].getNome() << endl;
        }
    }

}

string Servidor::enter_leave_channel(string nomeCanal) {
    if(canaisTexto.empty()) 
        return "== Nenhum canal de texto em '" + nome + "' foi encontrado! ==";

    if(search_it_canalTexto(nomeCanal) == canaisTexto.end()) 
        return "== Canal '" + nomeCanal + "' não existe! ==";
    
    return "";

}

void Servidor::salvarIdsOfstream(ofstream &ofs) {
    // Imprime a quantidade de participantes do servidor
    ofs << participantesIDs.size() << endl;
    // Imprime o id de cada participante do servidor
    for(auto it_p = participantesIDs.begin(); it_p != participantesIDs.end(); it_p++)
        ofs << *it_p << endl;
}

void Servidor::salvarCanaisOfstream(ofstream &ofs) {
    // Imprime a quantidade de canais de texto do servidor
    ofs << canaisTexto.size() << endl;
    // Imprime os dados de cada canal de texto
    for(auto it_canal = canaisTexto.begin(); it_canal != canaisTexto.end(); it_canal++) {
        // Imprime o nome do canal
        ofs << it_canal->getNome() << endl;
        // Imprime os dados das mensagens dos canais
        it_canal->salvarMensagensOfstream(ofs);
    }
}

vector<CanalTexto>::iterator Servidor::search_it_canalTexto(string nomeCanal) {
    auto it_canaltexto = std::find_if(canaisTexto.begin(), canaisTexto.end(), 
                                [nomeCanal](CanalTexto canal){
                                  return canal.getNome() == nomeCanal;
                                });

    return it_canaltexto;

}