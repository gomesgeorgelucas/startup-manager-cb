#ifndef COMPANY_REPORTS_H
#define COMPANY_REPORTS_H

#include "company.h"

// Declara��o das fun��es do menu de relat�rios
void company_reports_menu(const Company *company);

// Fun��es espec�ficas para relat�rios
void total_waste_by_year(const Company *company);
void total_cost_by_year(const Company *company);
void average_waste_by_month(const Company *company);
void average_cost_by_month(const Company *company);

#endif // COMPANY_REPORTS_H
