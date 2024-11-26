Projeto Integrado Multidisciplinar IV (PIM IV)

Descrição do Projeto

Este projeto é o Projeto Integrado Multidisciplinar IV (PIM IV), cujo principal objetivo é integrar os conhecimentos teóricos adquiridos em aula com práticas gerenciais. Ele segue as normas da ABNT (Associação Brasileira de Normas Técnicas).

A aplicação foi desenvolvida para uma startup de soluções ambientais que gerencia indústrias que necessitam abater materiais particulados e gases provenientes de seus processos produtivos. O sistema permite o cadastro de clientes industriais, a atualização mensal de dados de resíduos ambientais tratados e estimativas de custo, além de gerar relatórios detalhados.

Contextualização do Caso

A startup, inicialmente regional, viu seu número de contratos crescer exponencialmente, demandando o desenvolvimento de um sistema computacional para gerenciar tarefas de cadastro e relatórios.

Funcionalidades do Sistema

	1.	Autenticação:
	•	Cadastro e login de usuários (com senhas armazenadas criptografadas).
	2.	Cadastro de Indústrias:
	•	Cadastro de nome, CNPJ, razão social, nome fantasia, telefone, endereço, dados do responsável e outras informações.
	3.	Atualização Mensal:
	•	Registro da quantidade de resíduos tratados e custo estimado.
	4.	Relatórios:
	•	Relatórios detalhados com dados individuais, como:
	•	Total de resíduos tratados por ano.
	•	Total de custos estimados por ano.
	•	Média de resíduos tratados por mês em um ano específico.
	•	Média de custos estimados por mês em um ano específico.

Tecnologias Utilizadas

	•	IDE: Code::Blocks
	•	Compilador: MinGW (GCC)
	•	Sistema Operacional de Desenvolvimento e Testes: Windows 11 (ARM)

Principais Arquivos

	•	main.c: Ponto de entrada da aplicação.
	•	auth.c e auth.h: Gerenciamento de autenticação de usuários.
	•	company.c e company.h: Cadastro e gerenciamento de indústrias.
	•	company_management.c e company_management.h: Atualização de dados de resíduos e custos.
	•	company_reports.c e company_reports.h: Geração de relatórios detalhados.

Executando o Projeto no Windows 11 com MinGW (Linha de Comando)

Pré-requisitos

	1.	Instalar MinGW:
	•	Baixe e instale MinGW pelo site oficial: MinGW.
	•	Durante a instalação, certifique-se de incluir o gcc e o g++.
	2.	Configurar o Path:
	•	Adicione o diretório bin do MinGW ao PATH do Windows:
	•	Exemplo: C:\MinGW\bin.
	3.	Download do Projeto:
	•	Faça o download do código fonte e extraia-o em um diretório de sua escolha.

Etapas para Compilar e Executar

	1.	Abra o Terminal:
	•	Use o terminal do Windows (Prompt de Comando ou PowerShell).
	2.	Navegue até o Diretório do Projeto:

cd caminho/para/o/diretorio/do/projeto


	3.	Compile o Projeto:
	•	Execute o seguinte comando:

gcc src/*.c -Iinclude -o PIM_IV.exe


	4.	Execute o Programa:
	•	Após a compilação bem-sucedida, execute o programa:

./PIM_IV.exe

Relatórios Gerados pela Aplicação

	1.	Relatórios Individuais:
	•	Total de resíduos tratados por ano específico.
	•	Total de custos estimados por ano específico.
	•	Média de resíduos tratados por mês, em um ano específico.
	•	Média de custos estimados por mês, em um ano específico.

Observações

	•	LGPD: Todos os dados sensíveis (como senhas e informações críticas) são armazenados criptografados, em conformidade com as boas práticas de proteção de dados.
	•	Portabilidade: O projeto foi desenvolvido para Windows 11, mas pode ser adaptado para outros sistemas operacionais ajustando-se o compilador e o ambiente de execução.

Autor(es): George Lucas Gomes
