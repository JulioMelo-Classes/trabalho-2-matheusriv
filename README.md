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

No linux:
```console
./concordo
```

No windows:
```
.\Debug\concordo.exe
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
./concordo < script_comandos.txt
```

## Comandos

Assim que executar o sistema, o usuário não estará logado e precisará seguir os comandos para criar um usuário e fazer login no Concordo. 

Observe que cada usuário tem um atributo chamado "id" que é inteiro. Esse ID é gerado automaticamente pelo sistema durante o cadastro e é incremental, ou seja, o primeiro usuário criado tem id==0, o segundo id==1 e assim por diante.

Todas as referências para um usuário devem ser feitas por esse ID.

### `quit`

Encerra a aplicação, este comando pode ser executado a qualquer momento pelo usuário:

Exemplo de entrada/saída:

```
quit

Saindo...
```

### `create-user`

Deve ser informado e-mail, senha e nome do usuário e tentar cadastrar o usuário no sistema. Lembre-se que o ID do usuário é criado automaticamente pelo sistema, como dito anteriormente. O cadastro só é efetivado se o e-mail não for o mesmo de outro usuário já cadastrado anteriormente:

```
create-user [e-mail] [senha] [nome do usuário]
```

Exemplo de entrada/saída:

```
create-user julio.melo@imd.ufrn.br 12ab34cd Julio Melo
== Usuário criado ==

create-user julio.melo@imd.ufrn.br 12ab34cd Julio Melo
== Usuário já existe! ==
```

### `login` 

Faz o login de um usuário que já possui cadastro no sistema:

```
login [e-mail] [senha]
```

Exemplo de entrada/saída:

```
login julio.melo@imd.ufrn.br 12ab34cd
== Logado como julio.melo@imd.ufrn.br ==

login julio.melo@imd.ufrn.br 1326
== Senha ou usuário inválidos! ==
```

### `disconnect` 

Desconecta o usuário com o ID passado, caso esteja conectado:

```
disconnect [id do usuário logado]
```

Exemplo de entrada/saída:

```
disconnect 0
== Desconectando usuário isaacfranco@imd.ufrn.br ==

disconnect 0
== Usuário precisa estar logado para desconectar! ==
```

### `create-server`

Cria um novo servidor como o nome informado. Na criação de um novo servidor o dono desse servidor se torna usuário passado no [id do usuário logado]:

```
create-server [id do usuário logado] [nome do servidor]
```
Exemplo de entrada/saída:

```
create-server 0 minha-casa
== Servidor criado ==

create-server 0 minha-casa
== Servidor com o nome 'minha-casa' já existe! ==
```

### `set-server-desc` 

Muda a descrição do servidor. Apenas o dono do servidor pode fazer essa alteração:

```
set-server-desc [id do usuário logado dono do servidor] [nome do servidor] [descrição]
```
Exemplo de entrada/saída:

```
set-server-desc 0 minha-casa Este servidor serve como minha casa, sempre estarei nele
== Descrição do servidor 'minha-casa' modificada ==

set-server-desc 0 minha-casa2 Este servidor serve como minha casa, sempre estarei nele
== Servidor 'minha-casa2' não encontrado! ==

set-server-desc 0 minha-casa55 Trocando a descrição de servidor dos outros
== Você não pode alterar a descrição de um servidor que não foi criado por você! ==
```

### `set-server-invite-code`

Modifica o Código de Convite necessário para entrar no servidor, apenas o dono do servidor pode fazer essa alteração. Se você utilizar o comando sem nenhum código, então o servidor apaga o código de convite e o servidor fica liberado para qualquer pessoa entrar:

```
set-server-invite-code [id do usuário logado dono do servidor] [nome do servidor] [código de convite]
```

Exemplo de entrada/saída:

```
set-server-invite-code 0 minha-casa 4567
== Código de convite do servidor 'minha-casa' modificado ==

set-server-invite-code 0 minha-casa
== Código de convite do servidor 'minha-casa' removido ==
```

### `list-servers`

Exibe os nomes dos servidores do sistema, um por linha:

```
list-servers [id do usuário logado]
```

Exemplo de entrada/saída:

```
list-servers 0

== Lista de Servidores ==
  minha-casa
  minha-casa2
  RPG-galera
  Bate-papo-uol
```

### `remove-server`

Remove um servidor do Concordo. Só tem sucesso na remoção se o dono do servidor for o usuário logado:

```
remove-server [id do usuário logado dono do servidor] [nome do servidor]
```

Exemplo de entrada/saída:

```
remove-server 0 minha-casa
== Servidor 'minha-casa' removido ==

remove-server 0 minha-casa
== Você não é o dono do servidor 'minha-casa' ==

remove-server 0 minha-casa3
== Servidor 'minha-casa3' não existe! ==
```

### `enter-server`

Entra e visualiza um servidor do Concordo. O ID do usuário é inserido na lista de participantes do servidor automaticamente. Se o servidor tiver código de convite, ele também deve ser inserido:

```
enter-server [id do usuário logado] [nome do servidor] [código de convite]
```

Exemplo de entrada/saída:

```
enter-server 0 dotalovers
== Entrou no servidor com sucesso ==

enter-server 0 concordo-members
== Servidor requer código de convite! ==

enter-server 0 concordo-members 123456
== Entrou no servidor com sucesso ==
```

### `leave-server`

Desconecta de um servidor, desta forma o usuário é removido da lista de participantes daquele servidor atualmente conectado:

```
leave-server [id do usuário logado]
```

Exemplo de entrada/saída (caso ele esteja visualizando algum servidor):

```
leave-server 0 minha-casa
== Saindo do servidor 'minha-casa' ==
```

Exemplo de entrada/saída (caso ele não seja membro de nenhum servidor, isto é o usuário já saiu de todos os servidores que participava ou não fez enter-server em qualquer servidor):

```
leave-server 0 minha-casa
== Você não está em qualquer servidor! ==
```

### `list-participants`

Exibe todos os usuários que estão no servidor que o usuário está visualizando atualmente (somente o nome de cada):

```
list-participants [id do usuário logado]
```

Exemplo de entrada/saída:

```
list-participants 0

== Lista de Participantes ==
  tomé
  bebé
  eu
  eu-mesmo
  irene
```