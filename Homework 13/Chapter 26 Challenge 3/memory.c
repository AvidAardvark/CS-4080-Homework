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
