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

void CanalTexto::criarMensagem(const string mensagem_cont, int id) {
    char dataHora[64];
    time_t now = time(nullptr);

    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y - %R", localtime(&now));

    Mensagem novaMensagem(dataHora, id, mensagem_cont);

    adicionaMensagem(novaMensagem);

    cout << "== Mensagem enviada ==";
}

void CanalTexto::adicionaMensagem(Mensagem novaMensagem) {
    mensagens.push_back(novaMensagem);
}

void CanalTexto::list_messages(vector<Usuario> &usuarios) {
    if(mensagens.empty()) { 
        cout << "== Sem mensagens para exibir! ==";
        return;
    }

    cout << "\n== Mensagens '" << nome << "' ==" << endl;

    for(int i=0; i<mensagens.size(); i++) {
        string nomeUsuario = usuarios[mensagens[i].getEnviadaPor()].getNome();
        cout << nomeUsuario << " <" << mensagens[i].getDataHora() 
            << ">: " << mensagens[i].getConteudo() << endl;
    }
}

void CanalTexto::salvarMensagensOfstream(std::ofstream &ofs) {
    // Imprime a quantidade de mensagens do canal de texto
    ofs << mensagens.size() << endl;

    // Imprime os dados de cada mensagem
    for(auto it_m = mensagens.begin(); it_m != mensagens.end(); ++it_m) {
        ofs << it_m->getDataHora() << endl;
        ofs << it_m->getEnviadaPor() << endl;
        ofs << it_m->getConteudo() << endl;
    }
}