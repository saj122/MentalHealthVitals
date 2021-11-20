test tcProcessUsingMemory [main=TestWithProcess]:
  assert MemoryValueAlwaysCorrect in (union { TestWithProcess }, Process);
