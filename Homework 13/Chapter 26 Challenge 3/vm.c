// Pushes trigger a reference count increase
void push(Value value) {
  if (IS_OBJ(value)) incRef(AS_OBJ(value));
  *vm.stackTop = value;
  vm.stackTop++;
}

// Pops trigger a reference count decrease
Value pop() {
  if (IS_OBJ(*vm.stackTop)) decRef(AS_OBJ(*vm.stackTop));
  vm.stackTop--;
  return *vm.stackTop;
}

static ObjUpvalue* captureUpvalue(Value* local) {
  // Upvalue is referenced immediately, so refCount is updated
  ObjUpvalue* createdUpvalue = newUpvalue(local);
  incRef((Obj*)createdUpvalue);
  // Increment the reference count of the local if it is an object
  if (IS_OBJ(*local)) incRef(AS_OBJ(*local));
  createdUpvalue->next = upvalue;
}
