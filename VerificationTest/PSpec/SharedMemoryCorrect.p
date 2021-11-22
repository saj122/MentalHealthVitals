event eSpec_ValIsAlwaysCorrect_Init: int;
event eObjWrite: int;
event eObjRead: int;

spec ValIsAlwaysCorrect observes eObjWrite , eObjRead, eSpec_ValIsAlwaysCorrect_Init {
  var memoryVal: int;

  start state Init {
    on eSpec_ValIsAlwaysCorrect_Init do (val: int) {
      memoryVal = val;
    }

    on eObjWrite do (val: int) {
        print format ("Value after write: {0}", val);
    }

    on eObjRead do (val: any) {
        print format ("Value after read: {0}", val);
    }
  }
}