bool tableSet(Table* table, ObjString* key, Value value) {
  // Increase reference when assigning to global variable
  if (IS_OBJ(value)) incRef(AS_OBJ(value));

  // If entry exists, decrement the reference value of the object stored
  if (!isNewKey && IS_OBJ(entry->value)) decRef(AS_OBJ(entry->value));
}
