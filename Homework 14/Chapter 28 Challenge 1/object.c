ObjClass* newClass(ObjString* name) {
  ObjClass* klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
  klass->name = name;
  klass->initializer = NIL_VAL; 
  initTable(&klass->methods);
  return klass;
}
