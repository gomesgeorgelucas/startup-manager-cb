#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "company_management.h"

// Gera o nome do arquivo de resíduos com base no ID da empresa
// O nome do arquivo segue o formato "<company_id>-data.csv"
void get_waste_file_name(int company_id, char *file_name, size_t size) {
    snprintf(file_name, size, "%d-data.csv", company_id);
}

// Obtém o próximo ID de registro com base no número de linhas do arquivo
// Cada linha do arquivo representa um registro de resíduos
int get_next_record_id(const char *file_name) {
    FILE *file = fopen(file_name, "r");
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

// Atualiza o registro de resíduos ambientais
// Pede ao usuário os dados necessários e salva no arquivo correspondente
void update_waste_record(const Company *company, const char *username) {
    WasteRecord record;
    record.company_id = company->id;
    strncpy(record.username, username, sizeof(record.username) - 1);
    record.username[sizeof(record.username) - 1] = '\0';

    // Solicita e valida os dados do registro (ano, mês, quantidade e custo)
    do {
        printf("Digite o ano do registro (maior que 0): ");
        scanf("%d", &record.year);
    } while (record.year <= 0);

    do {
        printf("Digite o mes do registro (1-12): ");
        scanf("%d", &record.month);
    } while (record.month < 1 || record.month > 12);

    do {
        printf("Digite a quantidade de residuos (maior ou igual a 0): ");
        scanf("%lf", &record.waste_quantity);
    } while (record.waste_quantity < 0);

    do {
        printf("Digite o custo estimado (maior ou igual a 0): ");
        scanf("%lf", &record.cost);
    } while (record.cost < 0);

    getchar(); // Limpa o buffer de entrada

    // Gera o nome do arquivo de registros e obtém o próximo ID
    char file_name[50];
    get_waste_file_name(company->id, file_name, sizeof(file_name));
    record.record_id = get_next_record_id(file_name);

    // Abre o arquivo para salvar o novo registro
    FILE *file = fopen(file_name, "a");
    if (!file) {
        printf("Erro: Nao foi possivel abrir ou criar o arquivo de registros.\n");
        return;
    }

    fprintf(file, "%d,%d,%s,%d,%d,%.2lf,%.2lf\n", record.record_id, record.company_id, record.username,
            record.year, record.month, record.waste_quantity, record.cost);
    fclose(file);

    printf("Registro de residuos atualizado com sucesso.\n");
}

// Lista os registros de resíduos de uma empresa
// Lê os registros do arquivo correspondente e os exibe formatados
void list_waste_records(const Company *company) {
    char file_name[50];
    get_waste_file_name(company->id, file_name, sizeof(file_name));

    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Nenhum registro de residuos encontrado para esta empresa.\n");
        return;
    }

    WasteRecord record;
    char line[1024];
    printf("ID   | Empresa ID | Usuario          | Ano  | Mes  | Quantidade (Unidade) | Custo (Moeda)\n");
    printf("-----|------------|------------------|------|------|----------------------|---------------\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%d,%49[^,],%d,%d,%lf,%lf", &record.record_id, &record.company_id,
               record.username, &record.year, &record.month, &record.waste_quantity, &record.cost);

        printf("%-5d| %-10d| %-17s| %-4d | %-4d | %-20.2lf | %-15.2lf\n", record.record_id, record.company_id,
               record.username, record.year, record.month, record.waste_quantity, record.cost);
    }
    fclose(file);
}

// Menu de gerenciamento da empresa
// Oferece opções para atualizar registros, listar registros e acessar relatórios
void company_management_menu(const Company *company, const char *username) {
    int choice;

    while (1) {
        printf("\nMenu de Gerenciamento para: %s (ID: %d)\n", company->name, company->id);
        printf("1. Atualizar Quantidade de Residuos Ambientais\n");
        printf("2. Listar Registros de Residuos Ambientais\n");
        printf("3. Relatorios da Empresa\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("> ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            update_waste_record(company, username);
        } else if (choice == 2) {
            list_waste_records(company);
        } else if (choice == 3) {
            company_reports_menu(company);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

// Obtém os dados de uma empresa pelo ID
// Lê os dados do arquivo, descriptografa e preenche a struct Company
bool get_company_by_id(int company_id, Company *company) {
    FILE *file = fopen("companies.csv", "r");
    if (!file) {
        return false;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Campos criptografados lidos diretamente do arquivo
        char encrypted_name[50], encrypted_cnpj[15], encrypted_razao_social[50], encrypted_nome_fantasia[50];
        char encrypted_phone[15], encrypted_street[50], encrypted_address_number[10], encrypted_neighborhood[50];
        char encrypted_city[50], encrypted_state[50], encrypted_zipcode[11], encrypted_rep_name[50];
        char encrypted_rep_cpf[15], encrypted_rep_rg[15];

        sscanf(line, "%d,%49[^,],%14[^,],%49[^,],%49[^,],%14[^,],%49[^,],%10[^,],%49[^,],%49[^,],%10[^,],%49[^,],%14[^,],%14[^\n]",
               &company->id, encrypted_name, encrypted_cnpj, encrypted_razao_social, encrypted_nome_fantasia,
               encrypted_phone, encrypted_street, encrypted_address_number, encrypted_neighborhood, encrypted_city,
               encrypted_state, encrypted_zipcode, encrypted_rep_name, encrypted_rep_cpf, encrypted_rep_rg);

        if (company->id == company_id) {
            // Descriptografa os dados e os armazena na struct
            char *decrypted_name = decrypt_data(encrypted_name);
            char *decrypted_cnpj = decrypt_data(encrypted_cnpj);
            char *decrypted_razao_social = decrypt_data(encrypted_razao_social);
            char *decrypted_nome_fantasia = decrypt_data(encrypted_nome_fantasia);
            char *decrypted_phone = decrypt_data(encrypted_phone);
            char *decrypted_street = decrypt_data(encrypted_street);
            char *decrypted_address_number = decrypt_data(encrypted_address_number);
            char *decrypted_neighborhood = decrypt_data(encrypted_neighborhood);
            char *decrypted_city = decrypt_data(encrypted_city);
            char *decrypted_state = decrypt_data(encrypted_state);
            char *decrypted_zipcode = decrypt_data(encrypted_zipcode);
            char *decrypted_rep_name = decrypt_data(encrypted_rep_name);
            char *decrypted_rep_cpf = decrypt_data(encrypted_rep_cpf);
            char *decrypted_rep_rg = decrypt_data(encrypted_rep_rg);

            // Copia os dados descriptografados para a struct
            strncpy(company->name, decrypted_name, sizeof(company->name));
            strncpy(company->cnpj, decrypted_cnpj, sizeof(company->cnpj));
            strncpy(company->razao_social, decrypted_razao_social, sizeof(company->razao_social));
            strncpy(company->nome_fantasia, decrypted_nome_fantasia, sizeof(company->nome_fantasia));
            strncpy(company->phone, decrypted_phone, sizeof(company->phone));
            strncpy(company->street, decrypted_street, sizeof(company->street));
            strncpy(company->address_number, decrypted_address_number, sizeof(company->address_number));
            strncpy(company->neighborhood, decrypted_neighborhood, sizeof(company->neighborhood));
            strncpy(company->city, decrypted_city, sizeof(company->city));
            strncpy(company->state, decrypted_state, sizeof(company->state));
            strncpy(company->zipcode, decrypted_zipcode, sizeof(company->zipcode));
            strncpy(company->representative_name, decrypted_rep_name, sizeof(company->representative_name));
            strncpy(company->representative_cpf, decrypted_rep_cpf, sizeof(company->representative_cpf));
            strncpy(company->representative_rg, decrypted_rep_rg, sizeof(company->representative_rg));

            // Libera a memória alocada para os campos descriptografados
            free(decrypted_name);
            free(decrypted_cnpj);
            free(decrypted_razao_social);
            free(decrypted_nome_fantasia);
            free(decrypted_phone);
            free(decrypted_street);
            free(decrypted_address_number);
            free(decrypted_neighborhood);
            free(decrypted_city);
            free(decrypted_state);
            free(decrypted_zipcode);
            free(decrypted_rep_name);
            free(decrypted_rep_cpf);
            free(decrypted_rep_rg);

            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}
