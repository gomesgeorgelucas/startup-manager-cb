#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "company.h"
#include "company_management.h"

// Função para limpar a tela
// Verifica o sistema operacional para executar o comando correto
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para pausar e esperar entrada do usuário
// Exibe uma mensagem e aguarda que o usuário pressione Enter
void pause_for_user() {
    printf("Pressione Enter para continuar...");
    getchar(); // Aguarda o usuário pressionar Enter
}

// Função do menu principal
// Oferece opções de registro de empresas, listagem e gerenciamento
void main_menu(const char *username) {
    int choice;

    while (1) {
        clear_screen();
        printf("Menu Principal\n");
        printf("1. Registrar Nova Empresa\n");
        printf("2. Listar e Descrever Empresas\n");
        printf("3. Gerenciar Empresa\n");
        printf("0. Sair\n");
        printf("> ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        if (choice == 0) {
            printf("Saindo...\n");
            break;
        } else if (choice == 1) {
            register_company(); // Registrar nova empresa
        } else if (choice == 2) {
            list_and_describe_companies(); // Listar e descrever empresas
        } else if (choice == 3) {
            printf("Digite o ID de uma empresa para gerenciar ou 0 para voltar: ");
            int company_id;
            scanf("%d", &company_id);
            getchar(); // Limpa o buffer de entrada

            if (company_id == 0) {
                continue;
            }

            // Carregar os dados da empresa pelo ID
            Company company;
            if (!get_company_by_id(company_id, &company)) {
                printf("ID da empresa invalido.\n");
                pause_for_user();
                continue;
            }

            // Abrir o menu de gerenciamento da empresa
            company_management_menu(&company, username);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }

        pause_for_user();
    }
}

// Função principal
// Gerencia o menu de autenticação e redireciona para o menu principal após login
int main() {
    int choice;
    char username[50], password[50];

    while (1) {
        clear_screen();
        printf("Menu de Autenticacao:\n");
        printf("1. Registrar Usuario\n");
        printf("2. Entrar\n");
        printf("0. Sair\n");
        printf("> ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        if (choice == 0) {
            printf("Saindo do programa.\n");
            break;
        }

        printf("Digite o nome de usuario: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // Remove o caractere de nova linha

        printf("Digite a senha: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0; // Remove o caractere de nova linha

        if (choice == 1) {
            if (sign_up(username, password)) {
                printf("Usuario registrado com sucesso!\n");
            } else {
                printf("Falha ao registrar o usuario.\n");
            }
        } else if (choice == 2) {
            if (sign_in(username, password)) {
                printf("Login bem-sucedido! Redirecionando para o menu principal...\n");
                pause_for_user();
                main_menu(username); // Redireciona para o menu principal após login bem-sucedido
            } else {
                printf("Falha no login. Tente novamente.\n");
            }
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }

        pause_for_user();
    }

    return 0;
}
