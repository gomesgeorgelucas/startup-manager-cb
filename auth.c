#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "auth.h"

// Fun��o simples de hash para demonstra��o
// Esta fun��o cria um hash simples a partir de uma senha
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

// Fun��o para verificar se um arquivo existe
bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

// Fun��o para registrar um novo usu�rio
// Esta fun��o cria uma nova entrada no arquivo de usu�rios com a senha hash
bool sign_up(const char *username, const char *password) {
    // Verifica se o arquivo de usu�rios existe, se n�o cria um novo
    if (!file_exists(USERDATA_FILE)) {
        FILE *file = fopen(USERDATA_FILE, "w");
        if (!file) return false;
        fclose(file);
    }

    // Cria o hash da senha fornecida
    char *password_hash = hash_password(password);
    if (!password_hash) return false;

    // Abre o arquivo de usu�rios para adicionar o novo usu�rio
    FILE *file = fopen(USERDATA_FILE, "a");
    if (!file) {
        free(password_hash);
        return false;
    }

    // Escreve os dados do novo usu�rio no arquivo
    fprintf(file, "%s,%s,%s\n", ROLE, username, password_hash);
    fclose(file);
    free(password_hash);

    return true;
}

// Fun��o para autenticar um usu�rio
// Verifica se o nome de usu�rio e a senha fornecidos correspondem aos dados salvos no arquivo
bool sign_in(const char *username, const char *password) {
    // Retorna falso se o arquivo de usu�rios n�o existir
    if (!file_exists(USERDATA_FILE)) return false;

    // Cria o hash da senha fornecida para compara��es
    char *password_hash = hash_password(password);
    if (!password_hash) return false;

    // Abre o arquivo de usu�rios para leitura
    FILE *file = fopen(USERDATA_FILE, "r");
    if (!file) {
        free(password_hash);
        return false;
    }

    char line[256];
    bool login_success = false;

    // L� cada linha do arquivo e verifica se os dados fornecidos correspondem
    while (fgets(line, sizeof(line), file)) {
        char file_role[50], file_username[50], file_passwordhash[50];
        sscanf(line, "%49[^,],%49[^,],%49[^\n]", file_role, file_username, file_passwordhash);

        // Verifica o papel, nome de usu�rio e senha
        if (strcmp(file_role, ROLE) == 0 && strcmp(file_username, username) == 0 && strcmp(file_passwordhash, password_hash) == 0) {
            login_success = true;
            break;
        }
    }

    fclose(file);
    free(password_hash);

    return login_success;
}
