#include "usuario.h"

using namespace std;

Usuario::Usuario(int id, const string nome, const string email, const string senha){
  this->id = id;
  this->nome = nome;
  this->email = email;
  this->senha = senha;
}

Usuario::Usuario() {}

void Usuario::setId(int id){
  this->id = id;
}
void Usuario::setNome(const string nome){
  this->nome = nome;
}

void Usuario::setEmail(const string email){
  this->email = email;
}

void Usuario::setSenha(const string senha){
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