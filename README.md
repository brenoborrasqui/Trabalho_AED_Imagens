# Trabalho_AED_Imagens

Trabalho feito para a disciplina Algoritmos e Estrutura de dados, utilizando o conceito de lista ligada para modificar pixels específicos de uma imagem.

Para executar o código é necessário escolher qual método de inserção de lista você vai usar, assim poderá observar a diferença de otimização entre os diferentes tipos de inserções de diferentes listas.

RESUMINDO:

	MODO 0: Lista ligada comum, pegando sempre como referência o começo da lista e percorrendo ela para inserir no final.

	MODO 1: Lista ligada comum, porém tendo como referẽncia o começo e o fim da lista para não precisar percorrer toda a lista.

	MODO 2: Lista duplamente ligada, adicionando sempre no começo da lista para não percorrer até o final da lista e, posteriormente, é feito uma reversão dessa lista.

Após selecionar o modo, coloque quantas vezes será executado o código para tirar uma média dos tempos de execução.

Ao solicitar o nome do arquivo para processar, foi disponibilizado algumas imagens no formato .pgm dentro da pasta "imagens_teste". Não precisa colocar a extensão.

EXEMPLO: imagens_teste/4k

Posteriormente, selecione qual valor de pixel você deseja mudar na imagem inteira, são valores que variam de 0 a 255, onde 0 = preto e 255 = branco.

E logicamente agora selecione por qual cor deseja substituir.

Finalmente, o nome da nova imagem que será gerada com as modificações (não precisa da extensão .pgm)

Obs: o código foi feito para um trabalho de uma disciplina, portanto não tem todas as otimizações e boas práticas de programação, na verdade o algoritimo tem muito a ser trabalhado. Há um respositório com uma variação desse algoritimo.

Bom aproveito =).
=======
