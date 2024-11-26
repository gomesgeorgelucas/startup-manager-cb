#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "company.h"

// Função para gerar hash de strings (demonstração apenas)
// Esta função cria um hash simples com base no conteúdo de uma string
char *hash_data(const char *data) {
    int hash = 0;
    for (size_t i = 0; i < strlen(data); ++i) {
        hash += data[i] * (i + 1);
    }
    int hash_len = snprintf(NULL, 0, "%d", hash);
    char *hash_str = malloc(hash_len + 1);
    snprintf(hash_str, hash_len + 1, "%d", hash);
    return hash_str;
}

// Obtém o próximo ID de empresa com base no número de linhas do arquivo
// Cada linha do arquivo representa uma empresa
int get_next_company_id() {
    FILE *file = fopen("companies.csv", "r");
    if (!file) {
        return 1; // Retorna 1 se o arquivo não existir
    }

    int lines = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        lines++;
    }
    fclose(file);

    return lines + 1;
}

// Função simples para criptografar dados (demonstração apenas)
// Realiza um deslocamento de cada caractere por um valor fixo
char *encrypt_data(const char *plain_text) {
    size_t length = strlen(plain_text);
    char *encrypted = malloc(length + 1);
    if (!encrypted) return NULL;

    for (size_t i = 0; i < length; ++i) {
        encrypted[i] = plain_text[i] + 5; // Desloca cada caractere por 5 posições
    }
    encrypted[length] = '\0';
    return encrypted;
}

// Função simples para descriptografar dados
// Reverte o deslocamento aplicado na criptografia
char *decrypt_data(const char *encrypted_text) {
    size_t length = strlen(encrypted_text);
    char *decrypted = malloc(length + 1);
    if (!decrypted) return NULL;

    for (size_t i = 0; i < length; ++i) {
        decrypted[i] = encrypted_text[i] - 5; // Reverte o deslocamento
    }
    decrypted[length] = '\0';
    return decrypted;
}

// Salva os dados de uma empresa em um arquivo
bool save_company_to_file(const Company *company) {
    FILE *file = fopen("companies.csv", "a");
    if (!file) {
        return false;
    }

    // Criptografa cada campo da empresa antes de salvar
    char *encrypted_fields[14];
    encrypted_fields[0] = encrypt_data(company->name);
    encrypted_fields[1] = encrypt_data(company->cnpj);
    encrypted_fields[2] = encrypt_data(company->razao_social);
    encrypted_fields[3] = encrypt_data(company->nome_fantasia);
    encrypted_fields[4] = encrypt_data(company->phone);
    encrypted_fields[5] = encrypt_data(company->street);
    encrypted_fields[6] = encrypt_data(company->address_number);
    encrypted_fields[7] = encrypt_data(company->neighborhood);
    encrypted_fields[8] = encrypt_data(company->city);
    encrypted_fields[9] = encrypt_data(company->state);
    encrypted_fields[10] = encrypt_data(company->zipcode);
    encrypted_fields[11] = encrypt_data(company->representative_name);
    encrypted_fields[12] = encrypt_data(company->representative_cpf);
    encrypted_fields[13] = encrypt_data(company->representative_rg);

    // Escreve os dados criptografados no arquivo
    fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            company->id, encrypted_fields[0], encrypted_fields[1], encrypted_fields[2],
            encrypted_fields[3], encrypted_fields[4], encrypted_fields[5],
            encrypted_fields[6], encrypted_fields[7], encrypted_fields[8],
            encrypted_fields[9], encrypted_fields[10], encrypted_fields[11],
            encrypted_fields[12], encrypted_fields[13]);
    fclose(file);

    // Libera a memória alocada para os campos criptografados
    for (int i = 0; i < 14; i++) {
        free(encrypted_fields[i]);
    }

    return true;
}

// Lê uma entrada de comprimento fixo do usuário
void read_fixed_length_input(char *buffer, size_t length) {
    fgets(buffer, length + 1, stdin); // Lê até o tamanho especificado
    buffer[strcspn(buffer, "\n")] = 0; // Remove a nova linha, se presente

    // Limpa os caracteres excedentes do buffer de entrada
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Descarta até o final da linha
    }
}

// Registra uma nova empresa no sistema
void register_company() {
    Company company;

    company.id = get_next_company_id(); // Atribui o próximo ID disponível

    printf("Digite o nome da empresa: ");
    fgets(company.name, sizeof(company.name), stdin);
    company.name[strcspn(company.name, "\n")] = 0;

    printf("Digite o CNPJ (14 digitos): ");
    read_fixed_length_input(company.cnpj, 14);

    printf("Digite a razao social: ");
    fgets(company.razao_social, sizeof(company.razao_social), stdin);
    company.razao_social[strcspn(company.razao_social, "\n")] = 0;

    printf("Digite o nome fantasia: ");
    fgets(company.nome_fantasia, sizeof(company.nome_fantasia), stdin);
    company.nome_fantasia[strcspn(company.nome_fantasia, "\n")] = 0;

    printf("Digite o telefone (14 digitos): ");
    read_fixed_length_input(company.phone, 14);

    printf("Digite o endereco - Rua: ");
    fgets(company.street, sizeof(company.street), stdin);
    company.street[strcspn(company.street, "\n")] = 0;

    printf("Digite o endereco - Numero: ");
    fgets(company.address_number, sizeof(company.address_number), stdin);
    company.address_number[strcspn(company.address_number, "\n")] = 0;

    printf("Digite o bairro: ");
    fgets(company.neighborhood, sizeof(company.neighborhood), stdin);
    company.neighborhood[strcspn(company.neighborhood, "\n")] = 0;

    printf("Digite a cidade: ");
    fgets(company.city, sizeof(company.city), stdin);
    company.city[strcspn(company.city, "\n")] = 0;

    printf("Digite o estado: ");
    fgets(company.state, sizeof(company.state), stdin);
    company.state[strcspn(company.state, "\n")] = 0;

    printf("Digite o CEP (10 digitos): ");
    read_fixed_length_input(company.zipcode, 10);

    printf("Digite o nome do representante: ");
    fgets(company.representative_name, sizeof(company.representative_name), stdin);
    company.representative_name[strcspn(company.representative_name, "\n")] = 0;

    printf("Digite o CPF do representante (11 digitos): ");
    read_fixed_length_input(company.representative_cpf, 11);

    printf("Digite o RG do representante (9 digitos): ");
    read_fixed_length_input(company.representative_rg, 9);

    // Salva os dados da empresa no arquivo
    if (save_company_to_file(&company)) {
        printf("Empresa registrada com sucesso.\n");
    } else {
        printf("Erro: Nao foi possivel salvar os dados da empresa.\n");
    }
}

// Lista e descreve as empresas registradas
void list_and_describe_companies() {
    FILE *file = fopen("companies.csv", "r");
    if (!file) {
        printf("Nenhuma empresa registrada ainda.\n");
        return;
    }

    char line[1024];
    printf("ID   | Nome da Empresa           | CNPJ            | Nome do Representante\n");
    printf("-----|---------------------------|-----------------|-----------------------\n");

    // Exibe a lista de empresas
    while (fgets(line, sizeof(line), file)) {
        Company company;
        sscanf(line, "%d,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^\n]",
               &company.id);

        // Usa `get_company_by_id` para carregar e descriptografar os detalhes
        if (get_company_by_id(company.id, &company)) {
            printf("%-5d| %-25s| %-15s| %-20s\n",
                   company.id, company.name, company.cnpj, company.representative_name);
        }
    }
    fclose(file);

    // Permite que o usuário escolha uma empresa para visualizar detalhes
    int choice;
    while (1) {
        printf("Digite o ID de uma empresa para ver detalhes ou 0 para voltar: ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        if (choice == 0) {
            break;
        }

        Company company;
        if (get_company_by_id(choice, &company)) {
            // Exibe os detalhes descriptografados da empresa
            printf("\nDetalhes da Empresa:\n");
            printf("ID: %d\n", company.id);
            printf("Nome: %s\n", company.name);
            printf("CNPJ: %s\n", company.cnpj);
            printf("Razao Social: %s\n", company.razao_social);
            printf("Nome Fantasia: %s\n", company.nome_fantasia);
            printf("Telefone: %s\n", company.phone);
            printf("Endereco: %s, %s, %s, %s, %s\n",
                   company.street, company.address_number, company.neighborhood, company.city, company.state);
            printf("CEP: %s\n", company.zipcode);
            printf("Representante: %s\n", company.representative_name);
            printf("CPF do Representante: %s\n", company.representative_cpf);
            printf("RG do Representante: %s\n", company.representative_rg);
        } else {
            printf("ID da empresa invalido. Tente novamente.\n");
        }
    }
}
