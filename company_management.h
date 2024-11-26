#ifndef COMPANY_MANAGEMENT_H
#define COMPANY_MANAGEMENT_H

#include "company.h"

// Declaração de funções
void company_management_menu(const Company *company, const char *username);
void update_waste_record(const Company *company, const char *username);
void list_waste_records(const Company *company);

#endif // COMPANY_MANAGEMENT_H
