#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "chunk.h"
#include "value.h"
#define OBJ_TYPE(value)        (AS_OBJ(value)->type)
#define IS_STRING(value)       isObjType(value, OBJ_STRING)
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)
#define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
#define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))
#define IS_CLOSURE(value)      isObjType(value, OBJ_CLOSURE)
#define AS_CLOSURE(value)      ((ObjClosure*)AS_OBJ(value))
#define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
#define AS_NATIVE(value) \
    (((ObjNative*)AS_OBJ(value))->function)
typedef enum {
  OBJ_CLOSURE,
  OBJ_STRING,
  OBJ_FUNCTION,
  OBJ_NATIVE,
  OBJ_UPVALUE
} ObjType;

struct Obj {
  ObjType type;
  struct Obj* next;
};


typedef struct {
  Obj obj;
  int arity;
  Chunk chunk;
  ObjString* name;
  int upvalueCount;
} ObjFunction;
typedef struct ObjUpvalue {
  Obj obj;
  Value* location;
  struct ObjUpvalue* next;
  Value closed;
} ObjUpvalue;


typedef struct {
  Obj obj;
  ObjFunction* function;
    ObjUpvalue** upvalues;
  int upvalueCount;
} ObjClosure;
ObjClosure* newClosure(ObjFunction* function);


typedef Value (*NativeFn)(int argCount, Value* args);

typedef struct {
  Obj obj;
  NativeFn function;
} ObjNative;


struct ObjString {
  Obj obj;
  int length;
char* chars;
  uint32_t hash;
};


ObjString* takeString(char* chars, int length);
ObjFunction* newFunction();
ObjNative* newNative(NativeFn function);


ObjString* copyString(const char* chars, int length);
ObjUpvalue* newUpvalue(Value* slot);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
