event doneInc;

machine WriteProcess {
  start state Init {
    entry(payload: (machine, RWSharedObject))
    {
      var val: int;
      val = AcquireWriteLock(payload.1, this) as int;
      ReleaseWriteLock(payload.1, this, val + 1);
      send payload.0, doneInc;
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
      send payload.0, doneInc;
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
      new WriteProcess(this, sharedObj);
      new ReadProcess(this, sharedObj);
      new WriteProcess(this, sharedObj);
    }
    on doneInc do {
      count = count + 1;
      if(count == 3)
      {
        val = AcquireReadLock(sharedObj, this) as int;
        ReleaseReadLock(sharedObj, this);
      }
    }
  }
}