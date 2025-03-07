# Jogo de Adivinhação de Palavras

Bem-vindo ao repositório do **Jogo de Adivinhação de Palavras**! O objetivo deste jogo é adivinhar a palavra correta a partir de chutes de letras, com foco em otimizar a eliminação de palavras erradas para facilitar o processo de adivinhação.

---

## 🚀 Funcionalidades

- **Leitura de Arquivo**: O programa lê um arquivo contendo várias palavras para o jogo.
- **Chutes Estratégicos**: O sistema começa com uma vogal e elimina o maior número possível de palavras, tornando o jogo mais fácil.
- **Estrutura de Dados Eficiente**: Utilização de **double pointer** para manipulação dinâmica de palavras.
- **Verificação de Palavras Chutadas**: Uso de **bool** para rastrear palavras já chutadas.
- **Simplificação com Ternários**: Uso de operadores ternários para simplificar verificações.
- **Código Modular**: O código é organizado em funções e procedimentos para manter a função `main` limpa e concisa.
- **Verificação de Palavras com Switch**: O uso de `switch` otimiza a captura da primeira ocorrência de cada palavra.

---

## 🛠️ Tecnologias e Técnicas Utilizadas

- **Double Pointer**: Para manipulação dinâmica de palavras.
- **Funções e Procedimentos**: Para garantir que a função `main` esteja limpa e fácil de entender.
- **Uso de `bool`**: Para verificar se uma palavra já foi chutada e deve ser descartada.
- **Ternários**: Para simplificar condições e verificações de forma compacta.
- **`strcat`**: Concatena palavras em uma string única, facilitando a verificação.
- **`switch`**: Utilizado para otimizar a busca pela primeira ocorrência de cada palavra.

---

## ⚙️ Como Usar

## 1. Clone o Repositório

Clone este repositório para o seu computador utilizando o Git:

git clone https://github.com/seu_usuario/jogo-de-adivinhacao.git

## 2. Compile o Código
O código está escrito em C. Para compilá-lo, utilize o GCC:

bash
Copiar
Editar
gcc -o jogo_adivinhacao main.c

## 3. Execute o Programa
Após compilar, execute o jogo no terminal:

bash
Copiar
Editar
./jogo_adivinhacao

## 4. Forneça um Arquivo de Palavras
O programa requer um arquivo de palavras. O arquivo deve conter uma lista de palavras, uma por linha. Exemplo de arquivo palavras.txt:

nginx
Copiar
Editar
apple
banana
grape

## 📁 Estrutura de Arquivos
main.c: Arquivo principal com a lógica do jogo.
palavras.txt: Arquivo de exemplo com palavras para o jogo. (Você pode substituir por um arquivo próprio.)

## 🤝 Contribuindo
Contribuições são bem-vindas! Se você encontrou um problema ou tem sugestões para melhorias, sinta-se à vontade para abrir uma issue ou enviar um pull request.
