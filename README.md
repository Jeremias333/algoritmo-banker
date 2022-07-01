# algoritmo-banker
### Este é um programa implementa o algoritmo de banker, sua teoria é baseada em um banqueiro, um banqueiro tem recursos, e ele só empresta recursos se a transação for de confiança, ele não empresta para quem não confia.

## Para utiliza-lo é necessário ter uma máquina UNIX (linux ou mac) e os seguintes arquivos:

### - Arquivo commands.txt com todos os comandos que serão executados pelo algoritmo
### - Arquivo customer.txt com todos os consumidores de recursos.


## Como executar:

### - Existem 3 parametros extremamente necessários para execução. 

### - Exemplo: ./banker 10 5 7

### - Utilizar o seguinte comando para limpar o arquivo executável gerado: make clean

### - Utilizar o seguinte comando para gerar um novo arquivo executável: make

### - A execução dele não funciona no make por conta dos parametros que devem ser passados, utilize o exemplo mostrado.