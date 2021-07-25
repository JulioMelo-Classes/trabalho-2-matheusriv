#include "canaltexto.h"

using namespace std;

CanalTexto::CanalTexto(string nome) {
    this->nome = nome;
}

string CanalTexto::getCanalTextoNome(){
    return nome;
}