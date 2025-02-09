# Computação gráfica
Exemplos de desenhos e animações em opengl em C.

## Dependências
Para que os programas funcionem corretamente, eles dependem que um ambiente C/C++ esteja configurado em seu computador, além das dependências do opengl em C/C++.

Para configurar o opengl no linux, execute no terminal:
```
sudo apt update
sudo apt install freeglut3-dev libglew-dev libglfw3-dev
```

## Como executar

Execute os seguintes comandos:
```
git clone https://github.com/Daniel-Alencar/exemplos-computacao-grafica
```
```
cd exemplos-computacao-grafica
```
```
gcc <NOME_DO_ARQUIVO>.cpp -o <NOME_DO_ARQUIVO> -lGL -lGLU -lglut -lm
```
```
./<NOME_DO_ARQUIVO>
```
Pronto, o desenho ou animação deve ser exibido!
