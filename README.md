# Auto Complete para Sistemas de Busca de Jogos

Autores:
- Jose Pedro Dresch
- Phelipe Gabriel Lima da Silva

## Descrição do Projeto

Neste trabalho implementamos um sistema de autocomplete de jogos utilizando uma estrutura de dados chamada Trie. A Trie armazena os títulos dos jogos caractere por caractere, permitindo buscas eficientes por prefixo. Dado um prefixo e um número k, o sistema retorna ate k jogos cujo título começa com esse prefixo, ordenados por popularidade e, em caso de empate, por ordem alfabética da chave de busca. A base de dados utilizada conta com milhares de jogos reais, cada um com título, descrição curta e popularidade.

## Instruções de Compilação

Para compilar o projeto, execute no terminal:

```
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

Obs.: a compilação pode demorar alguns minutos devido ao grande volume de dados em GamesDatabase.cpp. Para agilizar testes locais, recomenda-se compilar os arquivos separadamente, recompilando apenas o que foi alterado:

```
g++ -c GamesDatabase.cpp
g++ -c Game.cpp
g++ -c Trie.cpp
g++ -c main.cpp
g++ main.o Game.o Trie.o GamesDatabase.o -o app
```

## Instruções de Execução

O programa deve ser executado no formato:

```
./app k prefixo
```

Onde:
- `k` e a quantidade maxima de sugestões desejadas
- `prefixo` e o prefixo usado na busca (entre aspas se tiver espaços)

Exemplos de uso:

```
./app 3 ha
./app 5 counter
./app 3 "half l"
./app 10 dark
```

Caso nenhum resultado seja encontrado:

```
./app 3 zelda
```

Saida esperada:

```
No results found
```

Caso o número de argumentos esteja incorreto:

```
./app
```

Saída esperada:

```
Usage: ./app k prefix
```

## Organização dos Arquivos

- `main.cpp`: arquivo principal que carrega os jogos, insere na Trie e executa a busca
- `Game.hpp` / `Game.cpp`: definição e implementação da classe Game
- `Trie.hpp` / `Trie.cpp`: definição e implementação das classes TrieNode e Trie
- `GamesDatabase.hpp` / `GamesDatabase.cpp`: declaração e definição da base de jogos
- `check_database.cpp`: programa auxiliar para testar o carregamento da base
- `relatorio.pdf`: relatório com análise da implementação e custos computacionais
- `README.md`: este arquivo

## Exemplos de Uso

Busca pelos 3 jogos mais populares com prefixo "ha":

```
./app 3 ha
```

Saida:

```
Hades | Defy the god of the dead as you hack and slash out of the Underworld... | 213542
Half Life 2 | 1998 HALF LIFE sends a shock through the game industry... | 131995
Half Life Alyx | Half Life Alyx is Valve s VR return to the Half Life series... | 71194
```

Busca ignorando espacos e maíusculas (prefixos equivalentes):

```
./app 5 "half l"
./app 5 HalfL
./app 5 HALF L
```

Todos retornam os mesmos resultados, pois a busca e case-insensitive e ignora espaços em branco.