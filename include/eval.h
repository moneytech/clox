#ifndef EVAL_H
#define EVAL_H
#include "ds/lldict.h"
#include "resolve.h"

typedef enum obj_type_t {
    OBJ_NIL,
    OBJ_BOOL,
    OBJ_NUMBER,
    OBJ_STRING,
    OBJ_ERROR,
    OBJ_VOID,
    OBJ_CALLABLE,
    OBJ_CLASS_DEFINITION,
    OBJ_CLASS_INSTANCE
} ObjectType;

typedef struct object_t {
    void* value;
    ObjectType type;
    int valueSize;
    int shallow;
    int propagateReturn;
} Object;

typedef struct env_t {
    LLDictionary* variables;
    struct env_t* enclosing;
} ExecutionEnvironment;

typedef Object* (*CallFunc)(List* args, void* declaration, ExecutionEnvironment* env, FunctionType type);

typedef struct callable_t {
    unsigned int arity;
    CallFunc call;
    void* declaration;
    ExecutionEnvironment* closure;
    FunctionType type;
} Callable;

typedef struct class_t {
    char* name;
    Callable* ctor;
    LLDictionary* methods;
    Object* super;
} Class;

typedef struct class_instance_t {
    Class type;
    LLDictionary* fields;
} ClassInstance;

void env_init(ExecutionEnvironment* env);
ExecutionEnvironment* env_new();
void env_init_global();
int env_add_variable(ExecutionEnvironment* env, const char* variableName, Object* obj);
int env_set_variable_value(ExecutionEnvironment* env, const char* variableName, Object* obj);
Object* env_get_variable_value(ExecutionEnvironment* env, const char* variableName);
void env_destroy(ExecutionEnvironment* env);
int env_set_variable_value_at(ExecutionEnvironment* env, unsigned int order, const char* variableName, Object* value);
Object* env_get_variable_value_at(ExecutionEnvironment* env, unsigned int order, const char* variableName);

void obj_destroy(Object* obj);
Object* obj_new(ObjectType type, void* value, int valueSize);
char obj_likely(Object* obj);
char obj_unlikely(Object* expr);

extern ExecutionEnvironment GlobalExecutionEnvironment;

void eval(Stmt* stmt);

#define OPERAND_NUMBER "Syntax Error: Operands must be numbers at line: %d"
#define OPERAND_SAMETYPE "Syntax Error: Operands must be two numbers or two strings at line: %d"
#endif
