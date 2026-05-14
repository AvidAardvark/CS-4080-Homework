typedef struct ObjClass {
  Obj obj;
  ObjString* name;
  Value initializer; 
  Table methods;
} ObjClass;


