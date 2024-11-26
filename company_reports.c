#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "company_reports.h"
#include "company_management.h"

// Relatório: Total de resíduos por ano
// Calcula e exibe o total de resíduos para um ano específico
void total_waste_by_year(const Company *company) {
    int year, total_records = 0;
    double total_waste = 0.0;

    printf("Digite o ano para o relatorio de residuos: ");
    scanf("%d", &year);

    char file_name[50];
    get_waste_file_name(company->id, file_name, sizeof(file_name));

    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Erro: Nao ha dados de residuos para esta empresa.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int record_id, company_id, record_year, record_month;
        double waste_quantity, cost;
        char username[50];

        sscanf(line, "%d,%d,%49[^,],%d,%d,%lf,%lf", &record_id, &company_id, username, &record_year, &record_month, &waste_quantity, &cost);

        if (record_year == year) {
            total_waste += waste_quantity;
            total_records++;
        }
    }
    fclose(file);

    if (total_records > 0) {
        printf("Total de residuos no ano %d: %.2lf\n", year, total_waste);
    } else {
        printf("Nenhum registro encontrado para o ano %d.\n", year);
    }
}

// Relatório: Total de custos por ano
// Calcula e exibe o total de custos para um ano específico
void total_cost_by_year(const Company *company) {
    int year, total_records = 0;
    double total_cost = 0.0;

    printf("Digite o ano para o relatorio de custos: ");
    scanf("%d", &year);

    char file_name[50];
    get_waste_file_name(company->id, file_name, sizeof(file_name));

    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Erro: Nao ha dados de custos para esta empresa.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int record_id, company_id, record_year, record_month;
        double waste_quantity, cost;
        char username[50];

        sscanf(line, "%d,%d,%49[^,],%d,%d,%lf,%lf", &record_id, &company_id, username, &record_year, &record_month, &waste_quantity, &cost);

        if (record_year == year) {
            total_cost += cost;
            total_records++;
        }
    }
    fclose(file);

    if (total_records > 0) {
        printf("Total de custos no ano %d: %.2lf\n", year, total_cost);
    } else {
        printf("Nenhum registro encontrado para o ano %d.\n", year);
    }
}

// Relatório: Média de resíduos por mês
// Calcula e exibe a média de resíduos por mês para um ano específico
void average_waste_by_month(const Company *company) {
    int year, total_months = 0;
    double total_waste = 0.0;

    printf("Digite o ano para o relatorio de media de residuos: ");
    scanf("%d", &year);

    char file_name[50];
    get_waste_file_name(company->id, file_name, sizeof(file_name));

    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Erro: Nao ha dados de residuos para esta empresa.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int record_id, company_id, record_year, record_month;
        double waste_quantity, cost;
        char username[50];

        sscanf(line, "%d,%d,%49[^,],%d,%d,%lf,%lf", &record_id, &company_id, username, &record_year, &record_month, &waste_quantity, &cost);

        if (record_year == year) {
            total_waste += waste_quantity;
            total_months++;
        }
    }
    fclose(file);

    if (total_months > 0) {
        printf("Media de residuos por mes no ano %d: %.2lf\n", year, total_waste / total_months);
    } else {
        printf("Nenhum registro encontrado para o ano %d.\n", year);
    }
}

// Relatório: Média de custos por mês
// Calcula e exibe a média de custos por mês para um ano específico
void average_cost_by_month(const Company *company) {
    int year, total_months = 0;
    double total_cost = 0.0;

    printf("Digite o ano para o relatorio de media de custos: ");
    scanf("%d", &year);

    char file_name[50];
    get_waste_file_name(company->id, file_name, sizeof(file_name));

    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Erro: Nao ha dados de custos para esta empresa.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int record_id, company_id, record_year, record_month;
        double waste_quantity, cost;
        char username[50];

        sscanf(line, "%d,%d,%49[^,],%d,%d,%lf,%lf", &record_id, &company_id, username, &record_year, &record_month, &waste_quantity, &cost);

        if (record_year == year) {
            total_cost += cost;
            total_months++;
        }
    }
    fclose(file);

    if (total_months > 0) {
        printf("Media de custos por mes no ano %d: %.2lf\n", year, total_cost / total_months);
    } else {
        printf("Nenhum registro encontrado para o ano %d.\n", year);
    }
}

// Menu de relatórios da empresa
// Oferece opções de relatórios com base em dados da empresa
void company_reports_menu(const Company *company) {
    int choice;

    while (1) {
        printf("\nMenu de Relatorios para a Empresa: %s (ID: %d)\n", company->name, company->id);
        printf("1. Total de Residuos por Ano\n");
        printf("2. Total de Custos por Ano\n");
        printf("3. Media de Residuos por Mes no Ano\n");
        printf("4. Media de Custos por Mes no Ano\n");
        printf("0. Voltar ao Menu de Gerenciamento\n");
        printf("> ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            total_waste_by_year(company);
        } else if (choice == 2) {
            total_cost_by_year(company);
        } else if (choice == 3) {
            average_waste_by_month(company);
        } else if (choice == 4) {
            average_cost_by_month(company);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }

        printf("\n");
    }
}
