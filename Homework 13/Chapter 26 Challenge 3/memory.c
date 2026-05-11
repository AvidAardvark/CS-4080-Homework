static void sweep() {
  Obj* previous = NULL;
  Obj* object = vm.objects;
  while (object != NULL) {
    // Changing sweep to free refCounts of 0
    if (object->refCount > 0) {
      previous = object;
      object = object->next;
    }
  }
}

void collectGarbage() {
#ifdef DEBUG_LOG_GC
  printf("-- gc begin\n");
  size_t before = vm.bytesAllocated;
#endif

  sweep();

  vm.nextGC = vm.bytesAllocated * GC_HEAP_GROW_FACTOR;
}

void incRef(Obj* value) {
  value->refCount++;
}

static void decrementValue(Value value) {
  if (IS_OBJ(value)) decRef(AS_OBJ(value));
}

static void decrementArray(ValueArray* value_array) {
  for (int i = 0; i < value_array->count; i++) {
    decrementValue(value_array->values[i]);
  }
}

void decRef(Obj* value) {
  if (value->refCount > 1) {
    value->refCount--;
  } else {
    // Decrement refAll of objects referenced by the current object
    switch (value->type) {
      case OBJ_FUNCTION: {
        ObjFunction* function = (ObjFunction*)value;
        if (function->name != NULL) decRef((Obj*)function->name);
        decrementArray(&function->chunk.constants);
        break;
      }
      case OBJ_UPVALUE: {
        ObjUpvalue* upvalue = (ObjUpvalue*)value;
        decrementValue(upvalue->closed);
        break;
      }
      case OBJ_CLOSURE: {
        ObjClosure* closure = (ObjClosure*)value;
        decRef((Obj*)closure->function);
        for (int i = 0; i < closure->upvalueCount; i++) {
          decRef((Obj*)closure->upvalues[i]);
        }
        break;
      }
      case OBJ_NATIVE:
      case OBJ_STRING:
        break;
    }
  }
}
