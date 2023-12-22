#pragma once

// Reference : Timmy_A
// https://stackoverflow.com/questions/3386861/converting-a-variable-name-to-a-string-in-c

// TODO: #define VARIABLE_TO_STRING(Variable) #Variable // Lowest variable name. Ex: object.value = "value"
#define FULL_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable) // Full variable name. Ex: object.value = "object.value"

#define FUNCTION_TO_STRING(Function) (void(&Function),#Function)

#define METHOD_TO_STRING(ClassName,Method) (void(&ClassName::Method),#Method)

#define TYPE_TO_STRING(Type) (void(sizeof(Type)),#Type)

// #TODO Look into stringify reflection logic for variables, functions, types, etc
#define STRINGIFY_VARIABLE #
