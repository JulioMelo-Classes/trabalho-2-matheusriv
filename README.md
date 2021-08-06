# Concordo - Projeto 02 de LP1

Essa atividade se trata de um sistema chamado "Concordo" com recursos similares ao Discord, mas que vai funcionar somente em modo texto e sem recursos de rede. A ideia principal é simular o “backend” de um serviço com o discord, que, embora de forma simplificada, serve para dar uma boa ideia de como as coisas são feitas nesse nicho de aplicação.

## Para executar

1. Entre na pasta `build`:
```
cd build
```
2. Execute os comandos do `cmake` para gerar os arquivos intermediários e o executável dentro de `build`.
```
cmake ..
cmake --build .
```

Isso criará um executável dentro da pasta `build` chamado de `concordo`.

Logo após a compilação, para executar o programa gerado use os comandos:

No linux:
```console
./concordo
```

No windows:
```
.\Debug\concordo.exe
```

Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER.

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

### `list-online-users` 
Lista os usuários online do sistema.

```
list-online-users [id do usuário logado]
```

Exemplo de entrada/saída:

```
list-online-users 0
## Usuários online no Concordo ##
   Renan
   Julio
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

## Lista de Servidores ##
   minha-casa
   minha-casa2
   RPG-galera
   Bate-papo-uol
```

### `list-servers-desc`

Exibe os nomes e a descrição dos servidores do sistema, um por linha:

```
list-servers-desc [id do usuário logado]
```

Exemplo de entrada/saída:

```
list-servers-desc 0

## Lista de Descrição dos Servidores ##
   minha-casa 'essa é minha casa'
   minha-casa2 'essa é minha segunda casa'
   RPG-galera 'galera do RPG'
   Bate-papo-uol Servidor sem descrição
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
## Lista de Participantes ##
   tomé
   bebé
   eu
   eu-mesmo
   irene
```

### `list-channels`

Exibe todos os nomes canais do servidor que está sendo visualizado pelo cliente.

```
list-channels [id do usuário logado]
```


Exemplo de entrada/saída:

```
list-channels 0
# Canais de texto #
  casa-de-mae-joana
  aqui-nós-faz-o-trabalho
```

### `create-channel`

Permite criar um canal no servidor que está sendo visualizado pelo usuário informando seu nome. Observe que canais dentro do servidor não podem ter o mesmo nome.

```
create-channel [id do usuário logado] [nome do canal]
```

Exemplo de entrada/saída:

```
create-channel 0 casa-de-mae-joana 
== Canal de texto 'casa-de-mae-joana' criado ==

create-channel 0 casa-de-mae-joana
== Canal de texto 'casa-de-mae-joana' já existe! ==
```

### `enter-channel`

Entra em um canal presente na lista de canais do servidor que o usuário está visualizando.

```
enter-channel [id do usuário logado] [nome do canal]
```

Exemplo de entrada/saída:

```
enter-channel 0 casa-de-mae-joana
== Entrou no canal 'casa-de-mae-joana' ==

enter-channel 0 introspecção
== Canal 'introspecção' não existe! ==
```

### `leave-channel`

Sai do canal que o usuário está visualizando no momento.

```
leave-channel [id do usuário logado]
```

Exemplo de entrada/saída:

```
leave-channel 0
== Saindo do canal ==
```

### `send-message`

Cria uma mensagem e adiciona na lista de mensagens do canal visualizado pelo usuário. A mensagem criada possui o conteúdo digitado, a data/hora atual e o ID do usuário recebido no comando.

```
send-message [id do usuário logado] [conteúdo da mensagem]
```

Exemplo de entrada/saída:

```
send-message 0 Oi pessoal querem TC?
== Mensagem enviada ==
```

### `list-messages`

Visualiza as mensagens de um canal que o usuário está visualizando no momento. A mensagem tem os seguintes campos: (1) O nome do usuário que criou a mensagem; (2) Data/hora da criação da mensagem; e (3) O conteúdo da mensagem.

```
list-messages [id do usuário logado]
```

Exemplo de entrada/saída:

```
list-messages 0
Julio<08/03/2021 - 11:53>: Assim não tem condições, como que a galera vai conseguir terminar isso tudo em 4 semanas?
Isaac<08/03/2021 - 12:00>: Eles conseguem confio na galera
Renan<08/03/2021 - 12:00>: Semestre passado fizemos assim e ninguém entregou :/

list-messages 0
== Sem mensagens para exibir ==
```

## Persistência de dados

A persistência dos dados neste projeto permite que todas as informações de usuários cadastrados, usuários logados, servidores, usuários participantes em um servidor e mensagens em cada canal são dados que não são perdidos quando o sistema termina. A persistência de dados é feita utilizando manipulação de arquivos .txt localizados na pasta `database`.

### Usuários

Para armazenar os dados dos usuários utiliza-se o arquivo `usuarios.txt` que é estruturado da seguinte forma:

- A primeira linha possui um número que informa a quantidade de usuários cadastrados;

Para cada usuário, teremos as seguintes linhas:

- Linha com o Id do usuário;
- Linha com o nome do usuário;
- Linha com o email do usuário;
- Linha com a senha do usuário.

### Usuários Logados

Para armazenar os dados dos usuários logados no sistema utiliza-se o arquivo `usuarioslogados.txt` que é estruturado da seguinte forma:

- A primeira linha possui um número que informa a quantidade de usuários logados;

Para cada usuário, teremos as seguintes linhas:

- Linha com o nome do usuário;
- Linha com o nome do servidor que o usuário está visualizando (se não estiver visualizando um servidor, uma linha vazia);
- Linha com o nome do canal de texto do servidor que o usuário está visualizando (se não estiver visualizando um canal, uma linha vazia).

### Servidores

Para armazenar os dados dos servidores cadastrados utiliza-se o arquivo `servidores.txt` que é estruturado da seguinte forma:

- A primeira linha possui um número que informa a quantidade de servidores cadastrados;

Para cada servidor, teremos as seguintes linhas:

- Linha com o Id do usuário dono do servidor;
- Linha com o nome do servidor;
- Linha com a descrição do servidor (se não existir descrição, linha vazia);
- Linha com o código de convite do servidor (se não existir código de convite, linha vazia);
- Linha com o número de participantes do servidor;

Para cada participante do servidor, teremos em seguida:

- Linha com o Id do usuário participante;

### Canais de texto

Para armazenar os dados dos canais de texto cadastrados utiliza-se o arquivo `canaistexto.txt` que é estruturado da seguinte forma:

- A primeira linha possui um número que informa a quantidade de servidores cadastrados;

Para cada servidor, teremos as seguintes linhas:

- Linha com o número de canais de texto do servidor;

Para cada canal de texto no servidor, teremos as seguintes linhas:

- Linha com o nome do canal;
- Linha com o número de mensagens do canal;

Para cada mensagem no canal, teremos as seguintes linhas:

- Linha com a data e hora em que a mensagem foi enviada;
- Linha com o Id do usuário que enviou a mensagem;
- Linha com o conteúdo da mensagem.
