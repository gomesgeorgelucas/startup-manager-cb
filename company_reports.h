#ifndef COMPANY_REPORTS_H
#define COMPANY_REPORTS_H

#include "company.h"

// Declaração das funções do menu de relatórios
void company_reports_menu(const Company *company);

// Funções específicas para relatórios
void total_waste_by_year(const Company *company);
void total_cost_by_year(const Company *company);
void average_waste_by_month(const Company *company);
void average_cost_by_month(const Company *company);

#endif // COMPANY_REPORTS_H
