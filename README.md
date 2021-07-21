# Concordo - Projeto 02 de LP1

Essa atividade se trata de um sistema chamado "Concordo" com recursos similares ao Discord, mas que vai funcionar somente em modo texto e sem recursos de rede. A ideia principal é simular o “backend” de um serviço com o discord, que, embora de forma simplificada, serve para dar uma boa ideia de como as coisas são feitas nesse nicho de aplicação.

## Para compilar

```console
cd build
cmake ..
cmake --build .
```

## Para executar
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
./concordo < script_comandos.txt
```
## Para executar