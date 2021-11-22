event eAcqReadLock: machine;
event eReleaseReadLock: machine;
event eAcqWriteLock: machine;
event eReleaseWriteLock: (writer: machine, val: any);
event eRWLockGranted: any;

machine RWSharedObject {
  var waitingReaders : set[machine];
  var waitingWriters : set[machine];
  var currentReaders: set[machine];
  var currentWriter: machine;
  var sharedObj: any;

  start state Init {
    entry (obj: any) {
      sharedObj = obj;
      goto ChooseReadOrWriteLock;
    }
  }

  state ChooseReadOrWriteLock {
    entry {
      var pickReaderOrWriter: set[bool];
      var pick: machine;
      if(sizeof(waitingWriters) > 0)
        pickReaderOrWriter += (true);
      if(sizeof(waitingReaders) > 0)
        pickReaderOrWriter += (false);

      if(sizeof(pickReaderOrWriter) > 0 && choose(pickReaderOrWriter))
      {
        pick = choose(waitingWriters);
        waitingWriters -= (pick);
        raise eAcqWriteLock, pick;
      }
      else if(sizeof(pickReaderOrWriter) > 0)
      {
        pick = choose(waitingReaders);
        waitingReaders -= (pick);
        raise eAcqReadLock, pick;
      }
      else
      {
        assert sizeof(waitingReaders) == 0 && sizeof(waitingWriters) == 0, "Logic for picking readers and writers is incorrect!";
      }
    }
    on eAcqReadLock goto ReadLockAcquired;
    on eAcqWriteLock goto WriteLockAcquired;
  }

  state ReadLockAcquired {

    entry (reader: machine) {
      send reader, eRWLockGranted, sharedObj;
      currentReaders += (reader);
    }

    on eAcqReadLock do (reader: machine) {
      send reader, eRWLockGranted, sharedObj;
      assert !(reader in currentReaders), "Trying to re-acquire the lock (reentrancy not supported)";
      currentReaders += (reader);
    }

    on eReleaseReadLock do (reader: machine) {
      assert(reader in currentReaders), "Trying to release lock before acquiring it!!";
      currentReaders -= (reader);
      if(sizeof(currentReaders) == 0)
      {
        goto ChooseReadOrWriteLock;
      }
    }

    on eAcqWriteLock do (writer: machine)
    {
      waitingWriters += (writer);
    }
  }

  state WriteLockAcquired {
    entry (writer: machine){
      send writer, eRWLockGranted, sharedObj;
      currentWriter = writer;
    }

    on eReleaseWriteLock do (payload : (writer: machine, val: any)){
      assert(payload.writer == currentWriter), "Trying to release lock before acquiring it!!";
      sharedObj = payload.val;
      currentWriter = null as machine;
      goto ChooseReadOrWriteLock;
    }

    on eAcqReadLock do (reader: machine)
    {
      waitingReaders += (reader);
    }

    on eAcqWriteLock do (writer: machine)
    {
      assert(writer != currentWriter), "Trying to re-acquire the lock (reentrancy not supported)";
      waitingWriters += (writer);
    }
  }
}

fun AcquireReadLock(rwlock: RWSharedObject, client: machine) : any {
  var ret: any;
  send rwlock, eAcqReadLock, client;
  receive {
    case eRWLockGranted: (obj: any){
      print format ("Read Lock {0} Acquired by {1}", rwlock, client);
      ret = obj;
      announce eObjRead, ret;
    }
  }
  return ret;
}

fun ReleaseReadLock(rwlock: RWSharedObject, client: machine) {
  send rwlock, eReleaseReadLock, client;
  print format ("Read Lock {0} Released by {1}", rwlock, client);
}

fun AcquireWriteLock(rwlock: RWSharedObject, client: machine) : any {
  var retObj: any;
  send rwlock, eAcqWriteLock, client;
  receive {
    case eRWLockGranted: (obj: any) {
      print format ("Write Lock {0} Acquired by {1}", rwlock, client);
      retObj = obj;
    }
  }
  return retObj;
}

fun ReleaseWriteLock(rwlock: RWSharedObject, client: machine, val: any) {
  announce eObjWrite, val;
  send rwlock, eReleaseWriteLock, (writer = client, val = val);
  print format ("Write Lock {0} Released by {1}", rwlock, client);
}


