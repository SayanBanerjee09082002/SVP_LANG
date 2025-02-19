#ifndef STAT_PRODUCTION_H
#define STAT_PRODUCTION_H

#include "production_rules.h"

void parse_stmtList();
void parse_stmt();
void parse_returnStmt();
void parse_compoundStmt();
void parse_localDecls();
void parse_scopedVarDecl();
void parse_selectStmt();
void parse_iterStmt();

#endif