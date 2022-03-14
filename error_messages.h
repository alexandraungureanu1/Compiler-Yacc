#ifndef ERROR_MSG_H
#define ERROR_MSG_H
// Folosire a ceva nedeclarat/declarat anterior
#define M_ERROR_INEXISTENT_TYPE \
    printf("Error: Tip inexisitent\n");

#define M_ERROR_EXISTS_FUNC \
    printf("Error: Functia a fost deja definita anterior!\n");

#define M_ERROR_EXISTS_VAR \
    printf("Error: Variabila a fost deja definita anterior!\n");

#define M_ERROR_EXISTS_CLASS \
    printf("Error: Clasa a fost deja definita anterior!\n");

#define M_ERROR_EXISTS_DATA_MEMBER \
    printf("Error: Data member definit anterior in aceeasi clasa!\n");

#define M_ERROR_NOT_EXISTS_CLASS \
    printf("Error: Clasa folosita n-a fost declarata!\n");

#define M_ERROR_NOT_EXISTS_FUNC \
    printf("Error: Functia folosita n-a fost declarata!\n");

#define M_ERROR_NOT_EXISTS_VAR \
    printf("Error: Variabila folosita n-a fost declarata!\n");

// Ai uitat punct si virgula
#define M_ERROR_PCT_SI_VIRGULA \
    printf("Error: Ai uitat punct si virgula!\n");

// Asignari gresite catre bool
#define M_ERROR_INT_TO_BOOL \
    printf("Error: Incercare de asignare a unui int intr-un bool\n");

#define M_ERROR_CHAR_TO_BOOL \
    printf("Error: Incercare de asignare a unui char intr-un bool\n");

#define M_ERROR_STRING_TO_BOOL \
    printf("Error: Incercare de asignare a unui string intr-un bool\n");

#define M_ERROR_FLOAT_TO_BOOL \
    printf("Error: Incercare de asignare a unui float intr-un bool\n");

#define M_ERROR_ARRAY_TO_BOOL \
    printf("Error: Incercare de asignare a unui array intr-un bool\n");

// Asignari gresitre catre char
#define M_ERROR_INT_TO_CHAR \
    printf("Error: Incercare de asignare a unui int intr-un char\n");

#define M_ERROR_BOOL_TO_CHAR \
    printf("Error: Incercare de asignare a unui bool intr-un char\n");

#define M_ERROR_STRING_TO_CHAR \
    printf("Error: Incercare de asignare a unui string intr-un char\n");

#define M_ERROR_FLOAT_TO_CHAR \
    printf("Error: Incercare de asignare a unui float intr-un char\n");

#define M_ERROR_ARRAY_TO_CHAR \
    printf("Error: Incercare de asignare a unui array intr-un char\n");

// Asignari gresite catre string
#define M_ERROR_INT_TO_STRING \
    printf("Error: Incercare de asignare a unui int intr-un string\n");

#define M_ERROR_BOOL_TO_STRING \
    printf("Error: Incercare de asignare a unui bool intr-un string\n");

#define M_ERROR_CHAR_TO_STRING \
    printf("Error: Incercare de asignare a unui char intr-un string\n");

#define M_ERROR_FLOAT_TO_STRING \
    printf("Error: Incercare de asignare a unui float intr-un string\n");

#define M_ERROR_ARRAY_TO_STRING \
    printf("Error: Incercare de asignare a unui array intr-un string\n");

// Asignari gresite catre int
#define M_ERROR_STRING_TO_INT \
    printf("Error: Incercare de asignare a unui string intr-un int\n");

#define M_ERROR_BOOL_TO_INT \
    printf("Error: Incercare de asignare a unui bool intr-un int\n");

#define M_ERROR_CHAR_TO_INT \
    printf("Error: Incercare de asignare a unui char intr-un int\n");

#define M_ERROR_FLOAT_TO_INT \
    printf("Error: Incercare de asignare a unui float intr-un int\n");

#define M_ERROR_ARRAY_TO_INT \
    printf("Error: Incercare de asignare a unui array intr-un int\n");

// Asignari gresite catre array
#define M_ERROR_STRING_TO_ARRAY \
    printf("Error: Incercare de asignare a unui string intr-un array\n");

#define M_ERROR_BOOL_TO_ARRAY \
    printf("Error: Incercare de asignare a unui bool intr-un array\n");

#define M_ERROR_CHAR_TO_ARRAY \
    printf("Error: Incercare de asignare a unui char intr-un array\n");

#define M_ERROR_FLOAT_TO_ARRAY \
    printf("Error: Incercare de asignare a unui float intr-un inarrayt\n");

#define M_ERROR_INT_TO_ARRAY \
    printf("Error: Incercare de asignare a unui int intr-un array\n");

// Erori logice

#define M_DIVISION_BY_ZERO \
    printf("Error: Impartire la zero\n");

// Debug
#define M_DEBUG \
    printf("Am ajuns aici!\n");

#endif ERROR_MSG_H