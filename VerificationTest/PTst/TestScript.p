test tcRW [main=OS]:
  assert ValIsAlwaysCorrect in {WriteProcess, ReadProcess, OS, RWSharedObject};