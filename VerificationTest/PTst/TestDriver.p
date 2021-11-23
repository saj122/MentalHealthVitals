machine WriteProcess {
  start state Init {
    entry(payload: (machine, RWSharedObject))
    {
      var val: int;
      val = AcquireWriteLock(payload.1, this) as int;
      ReleaseWriteLock(payload.1, this, val + 1);
    }
  }
}

machine ReadProcess {
  start state Init {
    entry(payload: (machine, RWSharedObject))
    {
      var val: int;
      val = AcquireReadLock(payload.1, this) as int;
      ReleaseReadLock(payload.1, this);
    }
  }
}

machine OS {
  var count: int;
  var val: int;
  var sharedObj: RWSharedObject;
  start state Init {
    entry {
      var i : int;
      announce eSpec_ValIsAlwaysCorrect_Init, val;
      sharedObj = new RWSharedObject(0);
      new ReadProcess(this, sharedObj);
      new WriteProcess(this, sharedObj);
      new ReadProcess(this, sharedObj);
      new WriteProcess(this, sharedObj);
    }
  }
}