#ifndef COMPANY_H
#define COMPANY_H

#include <stdbool.h>

// Define a struct for company and representative data
typedef struct {
    int id;  // Unique sequential ID for the company
    char name[50];
    char cnpj[15];
    char razao_social[50];
    char nome_fantasia[50];
    char phone[15];
    char street[50];
    char address_number[10];
    char neighborhood[50];
    char city[50];
    char state[50];
    char zipcode[11];
    char representative_name[50];
    char representative_cpf[15];
    char representative_rg[15];
} Company;

// Estrutura para armazenar os dados do registro de resíduos ambientais
typedef struct {
    int record_id;          // ID único do registro
    int company_id;         // ID da empresa
    char username[50];      // Nome do usuário que realizou o registro
    int year;               // Ano do registro
    int month;              // Mês do registro
    double waste_quantity;  // Quantidade de resíduos
    double cost;            // Custo estimado
} WasteRecord;

// Function declarations
void register_company();
bool save_company_to_file(const Company *company);
void list_and_describe_companies();
int get_next_company_id();
char *encrypt_data(const char *plain_text);
char *decrypt_data(const char *encrypted_text);
void read_fixed_length_input(char *buffer, size_t length);
bool get_company_name_by_id(int company_id, char *company_name, size_t size);

#endif // COMPANY_H
