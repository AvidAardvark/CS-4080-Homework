struct Obj {
  ObjType type;
  // Add refCount to Obj struct
  int refCount;
  struct Obj* next;
};
