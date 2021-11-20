event doneInc;

machine App {
  start state Init {
    entry(payload: (machine, RWSharedObject))
    {
      var val: int;
      val = AcquireWriteLock(payload.1, this) as int;
      ReleaseWriteLock(payload.1, this, val+1);
      send payload.0, doneInc;
    }
  }
}