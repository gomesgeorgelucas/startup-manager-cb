#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "auth.h"

// Função simples de hash para demonstração
// Esta função cria um hash simples a partir de uma senha
char *hash_password(const char *password) {
    int hash = 0;
    for (size_t i = 0; i < strlen(password); ++i) {
        hash += password[i] * (i + 1);
    }
    int hash_len = snprintf(NULL, 0, "%d", hash);
    char *hash_str = malloc(hash_len + 1);
    snprintf(hash_str, hash_len + 1, "%d", hash);
    return hash_str;
}

// Função para verificar se um arquivo existe
bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

// Função para registrar um novo usuário
// Esta função cria uma nova entrada no arquivo de usuários com a senha hash
bool sign_up(const char *username, const char *password) {
    // Verifica se o arquivo de usuários existe, se não cria um novo
    if (!file_exists(USERDATA_FILE)) {
        FILE *file = fopen(USERDATA_FILE, "w");
        if (!file) return false;
        fclose(file);
    }

    // Cria o hash da senha fornecida
    char *password_hash = hash_password(password);
    if (!password_hash) return false;

    // Abre o arquivo de usuários para adicionar o novo usuário
    FILE *file = fopen(USERDATA_FILE, "a");
    if (!file) {
        free(password_hash);
        return false;
    }

    // Escreve os dados do novo usuário no arquivo
    fprintf(file, "%s,%s,%s\n", ROLE, username, password_hash);
    fclose(file);
    free(password_hash);

    return true;
}

// Função para autenticar um usuário
// Verifica se o nome de usuário e a senha fornecidos correspondem aos dados salvos no arquivo
bool sign_in(const char *username, const char *password) {
    // Retorna falso se o arquivo de usuários não existir
    if (!file_exists(USERDATA_FILE)) return false;

    // Cria o hash da senha fornecida para comparações
    char *password_hash = hash_password(password);
    if (!password_hash) return false;

    // Abre o arquivo de usuários para leitura
    FILE *file = fopen(USERDATA_FILE, "r");
    if (!file) {
        free(password_hash);
        return false;
    }

    char line[256];
    bool login_success = false;

    // Lê cada linha do arquivo e verifica se os dados fornecidos correspondem
    while (fgets(line, sizeof(line), file)) {
        char file_role[50], file_username[50], file_passwordhash[50];
        sscanf(line, "%49[^,],%49[^,],%49[^\n]", file_role, file_username, file_passwordhash);

        // Verifica o papel, nome de usuário e senha
        if (strcmp(file_role, ROLE) == 0 && strcmp(file_username, username) == 0 && strcmp(file_passwordhash, password_hash) == 0) {
            login_success = true;
            break;
        }
    }

    fclose(file);
    free(password_hash);

    return login_success;
}
