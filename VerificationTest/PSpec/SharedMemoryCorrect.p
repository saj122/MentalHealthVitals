event eSpec_MemoryValueAlwaysCorrect_Init: any;

spec MemoryValueAlwaysCorrect observes eReleaseWriteLock, eSpec_MemoryValueAlwaysCorrect_Init {
    var valBalance: any;

    start state Init {
        on eSpec_MemoryValueAlwaysCorrect_Init goto WaitForWriteLock with (val: any){
            valBalance = val;
        }
    }

    state WaitForWriteLock {
        on eReleaseWriteLock do (val: any) {
        }
    }
}