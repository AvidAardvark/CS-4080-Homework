static Value hasFieldNative(int argCount, Value* args) {
  if (argCount != 2) return FALSE_VAL;
  if (!IS_INSTANCE(args[0])) return FALSE_VAL;
  if (!IS_STRING(args[1])) return FALSE_VAL;

  ObjInstance* instance = AS_INSTANCE(args[0]);
  Value dummy;
  return BOOL_VAL(tableGet(&instance->fields, AS_STRING(args[1]), &dummy));
}

void initVM() {
  defineNative("hasField", hasFieldNative);

  case OP_GET_PROPERTY: {
  // get-not-instance
  if (!IS_INSTANCE(peek(0))) {
    runtimeError("Only instances have properties.");
    return INTERPRET_RUNTIME_ERROR;
  }

  // get-not-instance
  ObjInstance* instance = AS_INSTANCE(peek(0));
  ObjString* name = READ_STRING();

  Value value;
  if (tableGet(&instance->fields, name, &value)) {
    pop(); // Instance.
    push(value);
    break;
  }

  // get-undefined
  // Classes and Instances get-undefined < Methods and Initializers get-method
  runtimeError("Undefined property '%s'.", name->chars);
  return INTERPRET_RUNTIME_ERROR;

  // Methods and Initializers get-method
  if (!bindMethod(instance->klass, name)) {
    return INTERPRET_RUNTIME_ERROR;
  }
  break;
  // Methods and Initializers get-method
}
}


