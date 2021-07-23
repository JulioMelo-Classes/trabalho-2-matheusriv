#include "usuario.h"

using namespace std;

Usuario::Usuario(int id, string nome, string email, string senha){
  this->id = id;
  this->nome = nome;
  this->email = email;
  this->senha = senha;
}

Usuario::Usuario() {}

void Usuario::setId(int id){
  this->id = id;
}
void Usuario::setNome(string nome){
  this->nome = nome;
}

void Usuario::setEmail(string email){
  this->email = email;
}

void Usuario::setSenha(string senha){
  this->senha = senha;
}

int Usuario::getId(){
  return id;
}

string Usuario::getNome(){
  return nome;
}

string Usuario::getEmail(){
  return email;
}

string Usuario::getSenha(){
  return senha;
}

vector<string> Usuario::getServidores_usuario(){
  return servidores_usuario;
}

void Usuario::adicionaServidor(string nome_servidor) {
    servidores_usuario.push_back(nome_servidor);
}