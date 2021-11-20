machine TestWithProcess {
  var count: int;
  var sharedObj: RWSharedObject;
  start state Init {
    entry {
      var i : int;
      
      sharedObj = new RWSharedObject(1);
      while (i < 2)
      {
        new App(this, sharedObj);
        i = i + 1;
      }
    }
    on doneInc do {
      var val : int;
      count = count + 1;
      if(count == 2)
      {
        val = AcquireReadLock(sharedObj, this) as int;
        assert val == 3, "Increment Didnt work!";
        ReleaseReadLock(sharedObj, this);
      }
    }
  }
}