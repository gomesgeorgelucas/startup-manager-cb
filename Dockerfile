# Usar uma imagem base com GCC e Make
FROM gcc:latest

# Criar diretório de trabalho
WORKDIR /app

# Copiar os arquivos do projeto para o contêiner
COPY . .

# Compilar o programa
RUN gcc ./*.c -o PIM_IV

# Comando padrão ao iniciar o contêiner
CMD ["./PIM_IV"]
