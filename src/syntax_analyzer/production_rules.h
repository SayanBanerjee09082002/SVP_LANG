#ifndef PRODUCTION_RULES
#define PRODUCTION_RULES

#include "syntax_analyzer.h"

/* Function declarations for parsing function declarations */
void parse_funDecl(void);
void parse_parms(void);
void parse_parmList(void);
void parse_parmTypeList(void);
void parse_parmIdList(void);

/* Function declarations for parsing statements and expressions */
void parse_stmtList(void);
void parse_stmt(void);
void parse_returnStmt(void);
void parse_compoundStmt(void);
void parse_localDecls(void);
void parse_scopedVarDecl(void);
void parse_selectStmt(void);
void parse_iterStmt(void);
void parse_preOp(void);
void parse_postOp(void);
void parse_idOp(void);
void parse_expStmt(void);
void parse_exp(void);
void parse_ternaryExp(void);
void parse_logicalOrExp(void);
void parse_logicalAndExp(void);
void parse_relExp(void);
void parse_sumExp(void);
void parse_mulExp(void);
void parse_powerExp(void);
void parse_unaryExp(void);
void parse_factor(void);
void parse_call(void);
void parse_args(void);

/* Function declarations for parsing variable declarations */
void parse_varDecl(void);
void parse_varDeclList(void);
void parse_varDeclInit(void);
void parse_varDeclId(void);

/* Function declarations for overall declarations and type specifiers */
void parse_declList(void);
void parse_decl(void);
void parse_typeSpec(void);

/* Utility function for token matching */
void match(TokenType expected);

#endif