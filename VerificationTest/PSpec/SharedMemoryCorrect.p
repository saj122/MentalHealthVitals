event eSpec_ValIsAlwaysCorrect_Init: int;
event eObjWrite: int;

spec ValIsAlwaysCorrect observes eObjWrite ,eSpec_ValIsAlwaysCorrect_Init {
  var memoryVal: int;

  start state Init {
    on eSpec_ValIsAlwaysCorrect_Init goto WaitForWriteLock with (val: int) {
      memoryVal = val;
    }
  }

  state WaitForWriteLock {
      on eObjWrite do (val: int) {
          print format ("Value after write: {0}", val);
      }
  }
}