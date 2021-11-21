test tcRW [main=ReadProcess]:
  assert ValIsAlwaysCorrect in {WriteProcess, ReadProcess, RWSharedObject};