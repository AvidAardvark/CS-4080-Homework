static Value getFieldNative(int argCount, Value* args) {
  if (argCount != 2) return FALSE_VAL;
  if (!IS_INSTANCE(args[0])) return FALSE_VAL;
  if (!IS_STRING(args[1])) return FALSE_VAL;

  ObjInstance* instance = AS_INSTANCE(args[0]);
  Value value;
  tableGet(&instance->fields, AS_STRING(args[1]), &value);
  return value;
}

static Value setFieldNative(int argCount, Value* args) {
  if (argCount != 3) return FALSE_VAL;
  if (!IS_INSTANCE(args[0])) return FALSE_VAL;
  if (!IS_STRING(args[1])) return FALSE_VAL;

  ObjInstance* instance = AS_INSTANCE(args[0]);
  tableSet(&instance->fields, AS_STRING(args[1]), args[2]);
  return args[2];
}

void initVM() {
  defineNative("getField", getFieldNative);
  defineNative("setField", setFieldNative);
}
