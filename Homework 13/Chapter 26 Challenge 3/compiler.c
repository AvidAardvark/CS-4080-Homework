static void initCompiler(Compiler* compiler, FunctionType type) {
  compiler->function = newFunction();
  // This function is referenced by the compiler
  incRef((Obj*) compiler->function);
}

static ObjFunction* endCompiler() {
  current = current->enclosing;
  // Function no longer referenced by the compiler
  decRef((Obj*)function);
  return function;
}

