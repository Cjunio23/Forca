Jogo de Adivinhação de Palavras
Bem-vindo ao repositório do Jogo de Adivinhação de Palavras! Este projeto foi desenvolvido com o objetivo de criar um jogo onde o sistema tenta adivinhar a palavra correta com base em chutes de letras, otimizando a eliminação de palavras erradas para facilitar o processo de adivinhação.

🚀 Funcionalidades
Leitura de Arquivo: O jogo lê um arquivo contendo várias palavras e escolhe a palavra a ser adivinhada.
Chutes Estratégicos: O primeiro chute é uma vogal e o sistema elimina o maior número possível de palavras, tornando o jogo mais fácil.
Estrutura de Dados Eficiente: Utiliza double pointer para manipulação dinâmica de palavras.
Verificação de Palavras Chutadas: Utiliza bool para rastrear e eliminar palavras já chutadas.
Simplificação com Ternários: Uso de operadores ternários para simplificar as verificações.
Procedimentos Organizados: O código é modularizado com funções e procedimentos para garantir que a função main esteja limpa e organizada.
Verificação de Palavras com Switch: O uso de switch ajuda a capturar a primeira ocorrência de cada palavra.
📝 Estrutura do Código
Principais Conceitos e Técnicas Utilizadas:
Double Pointer: Manipula a lista de palavras de forma dinâmica.
Funções e Procedimentos: Manter a função main limpa e organizada, delegando tarefas específicas para funções auxiliares.
Uso de bool: Verifica se uma palavra foi chutada e deve ser descartada.
Ternários: Simplifica condições e verificações de forma compacta.
Uso de strcat: Concatena palavras em uma string única para facilitar a verificação.
Switch: Verifica a primeira ocorrência de cada palavra, otimizando o processo de eliminação.
⚙️ Como Usar
1. Clone o Repositório
Clone este repositório para o seu computador utilizando o Git:

bash
Copiar
Editar
git clone https://github.com/seu_usuario/jogo-de-adivinhacao.git
2. Compile o Código
O código foi escrito em C. Para compilá-lo, utilize o GCC:

bash
Copiar
Editar
gcc -o jogo_adivinhacao main.c
3. Execute o Programa
Após compilar, execute o jogo no terminal:

bash
Copiar
Editar
./jogo_adivinhacao
4. Forneça um Arquivo de Palavras
O jogo requer um arquivo de palavras. O arquivo deve conter uma lista de palavras, uma por linha. Exemplo de arquivo palavras.txt:

nginx
Copiar
Editar
apple
banana
grape
📁 Estrutura de Arquivos
main.c: Arquivo principal com a lógica do jogo.
palavras.txt: Arquivo de exemplo com palavras para o jogo. (Você pode substituir este arquivo pelo seu próprio.)
👥 Contribuindo
Contribuições são sempre bem-vindas! Se você encontrou algum problema ou deseja sugerir melhorias, sinta-se à vontade para abrir uma issue ou enviar um pull request.
