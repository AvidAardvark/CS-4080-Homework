static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, oldSize: 0, newSize: size);
  object->type = type;
  object->refCount = 0;  // Initiate refcount to zero
