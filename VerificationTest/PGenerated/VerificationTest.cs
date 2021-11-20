using Microsoft.Coyote;
using Microsoft.Coyote.Actors;
using Microsoft.Coyote.Runtime;
using Microsoft.Coyote.Specifications;
using System;
using System.Runtime;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using Plang.CSharpRuntime;
using Plang.CSharpRuntime.Values;
using Plang.CSharpRuntime.Exceptions;
using System.Threading;
using System.Threading.Tasks;

#pragma warning disable 162, 219, 414, 1998
namespace PImplementation
{
}
namespace PImplementation
{
    internal partial class eAcqReadLock : PEvent
    {
        public eAcqReadLock() : base() {}
        public eAcqReadLock (PMachineValue payload): base(payload){ }
        public override IPrtValue Clone() { return new eAcqReadLock();}
    }
}
namespace PImplementation
{
    internal partial class eReleaseReadLock : PEvent
    {
        public eReleaseReadLock() : base() {}
        public eReleaseReadLock (PMachineValue payload): base(payload){ }
        public override IPrtValue Clone() { return new eReleaseReadLock();}
    }
}
namespace PImplementation
{
    internal partial class eAcqWriteLock : PEvent
    {
        public eAcqWriteLock() : base() {}
        public eAcqWriteLock (PMachineValue payload): base(payload){ }
        public override IPrtValue Clone() { return new eAcqWriteLock();}
    }
}
namespace PImplementation
{
    internal partial class eReleaseWriteLock : PEvent
    {
        public eReleaseWriteLock() : base() {}
        public eReleaseWriteLock (IPrtValue payload): base(payload){ }
        public override IPrtValue Clone() { return new eReleaseWriteLock();}
    }
}
namespace PImplementation
{
    internal partial class eRWLockGranted : PEvent
    {
        public eRWLockGranted() : base() {}
        public eRWLockGranted (IPrtValue payload): base(payload){ }
        public override IPrtValue Clone() { return new eRWLockGranted();}
    }
}
namespace PImplementation
{
    internal partial class doneInc : PEvent
    {
        public doneInc() : base() {}
        public doneInc (IPrtValue payload): base(payload){ }
        public override IPrtValue Clone() { return new doneInc();}
    }
}
namespace PImplementation
{
    internal partial class eSpec_MemoryValueAlwaysCorrect_Init : PEvent
    {
        public eSpec_MemoryValueAlwaysCorrect_Init() : base() {}
        public eSpec_MemoryValueAlwaysCorrect_Init (IPrtValue payload): base(payload){ }
        public override IPrtValue Clone() { return new eSpec_MemoryValueAlwaysCorrect_Init();}
    }
}
namespace PImplementation
{
    public static partial class GlobalFunctions
    {
        public static async Task<IPrtValue> AcquireReadLock(PMachineValue rwlock, PMachineValue client, PMachine currentMachine)
        {
            IPrtValue ret = null;
            PMachineValue TMP_tmp0 = null;
            PEvent TMP_tmp1 = null;
            PMachineValue TMP_tmp2 = null;
            PMachineValue TMP_tmp3 = null;
            PMachineValue TMP_tmp4 = null;
            PrtString TMP_tmp5 = ((PrtString)"");
            TMP_tmp0 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock)?.Clone()));
            TMP_tmp1 = (PEvent)(new eAcqReadLock(null));
            TMP_tmp2 = (PMachineValue)(((PMachineValue)((IPrtValue)client)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0, (Event)TMP_tmp1, TMP_tmp2);
            var PGEN_recvEvent = await currentMachine.TryReceiveEvent(typeof(eRWLockGranted));
            switch (PGEN_recvEvent) {
                case eRWLockGranted PGEN_evt: {
                    IPrtValue obj = (IPrtValue)(PGEN_evt.Payload);
                    TMP_tmp3 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock)?.Clone()));
                    TMP_tmp4 = (PMachineValue)(((PMachineValue)((IPrtValue)client)?.Clone()));
                    TMP_tmp5 = (PrtString)(((PrtString) String.Format("Read Lock {0} Acquired by {1}",TMP_tmp3,TMP_tmp4)));
                    PModule.runtime.Logger.WriteLine("<PrintLog> " + TMP_tmp5);
                    ret = (IPrtValue)(((IPrtValue)((IPrtValue)obj)?.Clone()));
                } break;
            }
            return ((IPrtValue)((IPrtValue)ret)?.Clone());
        }
    }
}
namespace PImplementation
{
    public static partial class GlobalFunctions
    {
        public static void ReleaseReadLock(PMachineValue rwlock_1, PMachineValue client_1, PMachine currentMachine)
        {
            PMachineValue TMP_tmp0_1 = null;
            PEvent TMP_tmp1_1 = null;
            PMachineValue TMP_tmp2_1 = null;
            PMachineValue TMP_tmp3_1 = null;
            PMachineValue TMP_tmp4_1 = null;
            PrtString TMP_tmp5_1 = ((PrtString)"");
            TMP_tmp0_1 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock_1)?.Clone()));
            TMP_tmp1_1 = (PEvent)(new eReleaseReadLock(null));
            TMP_tmp2_1 = (PMachineValue)(((PMachineValue)((IPrtValue)client_1)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0_1, (Event)TMP_tmp1_1, TMP_tmp2_1);
            TMP_tmp3_1 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock_1)?.Clone()));
            TMP_tmp4_1 = (PMachineValue)(((PMachineValue)((IPrtValue)client_1)?.Clone()));
            TMP_tmp5_1 = (PrtString)(((PrtString) String.Format("Read Lock {0} Released by {1}",TMP_tmp3_1,TMP_tmp4_1)));
            PModule.runtime.Logger.WriteLine("<PrintLog> " + TMP_tmp5_1);
        }
    }
}
namespace PImplementation
{
    public static partial class GlobalFunctions
    {
        public static async Task<IPrtValue> AcquireWriteLock(PMachineValue rwlock_2, PMachineValue client_2, PMachine currentMachine)
        {
            IPrtValue retObj = null;
            PMachineValue TMP_tmp0_2 = null;
            PEvent TMP_tmp1_2 = null;
            PMachineValue TMP_tmp2_2 = null;
            PMachineValue TMP_tmp3_2 = null;
            PMachineValue TMP_tmp4_2 = null;
            PrtString TMP_tmp5_2 = ((PrtString)"");
            TMP_tmp0_2 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock_2)?.Clone()));
            TMP_tmp1_2 = (PEvent)(new eAcqWriteLock(null));
            TMP_tmp2_2 = (PMachineValue)(((PMachineValue)((IPrtValue)client_2)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0_2, (Event)TMP_tmp1_2, TMP_tmp2_2);
            var PGEN_recvEvent_1 = await currentMachine.TryReceiveEvent(typeof(eRWLockGranted));
            switch (PGEN_recvEvent_1) {
                case eRWLockGranted PGEN_evt_1: {
                    IPrtValue obj_1 = (IPrtValue)(PGEN_evt_1.Payload);
                    TMP_tmp3_2 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock_2)?.Clone()));
                    TMP_tmp4_2 = (PMachineValue)(((PMachineValue)((IPrtValue)client_2)?.Clone()));
                    TMP_tmp5_2 = (PrtString)(((PrtString) String.Format("Write Lock {0} Acquired by {1}",TMP_tmp3_2,TMP_tmp4_2)));
                    PModule.runtime.Logger.WriteLine("<PrintLog> " + TMP_tmp5_2);
                    retObj = (IPrtValue)(((IPrtValue)((IPrtValue)obj_1)?.Clone()));
                } break;
            }
            return ((IPrtValue)((IPrtValue)retObj)?.Clone());
        }
    }
}
namespace PImplementation
{
    public static partial class GlobalFunctions
    {
        public static void ReleaseWriteLock(PMachineValue rwlock_3, PMachineValue client_3, IPrtValue val, PMachine currentMachine)
        {
            PMachineValue TMP_tmp0_3 = null;
            PEvent TMP_tmp1_3 = null;
            IPrtValue TMP_tmp2_3 = null;
            PMachineValue TMP_tmp3_3 = null;
            PMachineValue TMP_tmp4_3 = null;
            PrtString TMP_tmp5_3 = ((PrtString)"");
            TMP_tmp0_3 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock_3)?.Clone()));
            TMP_tmp1_3 = (PEvent)(new eReleaseWriteLock(null));
            TMP_tmp2_3 = (IPrtValue)(((IPrtValue)((IPrtValue)val)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0_3, (Event)TMP_tmp1_3, TMP_tmp2_3);
            TMP_tmp3_3 = (PMachineValue)(((PMachineValue)((IPrtValue)rwlock_3)?.Clone()));
            TMP_tmp4_3 = (PMachineValue)(((PMachineValue)((IPrtValue)client_3)?.Clone()));
            TMP_tmp5_3 = (PrtString)(((PrtString) String.Format("Write Lock {0} Released by {1}",TMP_tmp3_3,TMP_tmp4_3)));
            PModule.runtime.Logger.WriteLine("<PrintLog> " + TMP_tmp5_3);
        }
    }
}
namespace PImplementation
{
    internal partial class RWSharedObject : PMachine
    {
        private PrtSet waitingReaders = new PrtSet();
        private PrtSet waitingWriters = new PrtSet();
        private PrtSet currentReaders = new PrtSet();
        private PMachineValue currentWriter = null;
        private IPrtValue sharedObj = null;
        public class ConstructorEvent : PEvent{public ConstructorEvent(IPrtValue val) : base(val) { }}
        
        protected override Event GetConstructorEvent(IPrtValue value) { return new ConstructorEvent((IPrtValue)value); }
        public RWSharedObject() {
            this.sends.Add(nameof(doneInc));
            this.sends.Add(nameof(eAcqReadLock));
            this.sends.Add(nameof(eAcqWriteLock));
            this.sends.Add(nameof(eRWLockGranted));
            this.sends.Add(nameof(eReleaseReadLock));
            this.sends.Add(nameof(eReleaseWriteLock));
            this.sends.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
            this.sends.Add(nameof(PHalt));
            this.receives.Add(nameof(doneInc));
            this.receives.Add(nameof(eAcqReadLock));
            this.receives.Add(nameof(eAcqWriteLock));
            this.receives.Add(nameof(eRWLockGranted));
            this.receives.Add(nameof(eReleaseReadLock));
            this.receives.Add(nameof(eReleaseWriteLock));
            this.receives.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
            this.receives.Add(nameof(PHalt));
        }
        
        public void Anon(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            IPrtValue obj_2 = (IPrtValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            sharedObj = (IPrtValue)(((IPrtValue)((IPrtValue)obj_2)?.Clone()));
            currentMachine.TryGotoState<ChooseReadOrWriteLock>();
            return;
        }
        public void Anon_1(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PrtSet pickReaderOrWriter = new PrtSet();
            PMachineValue pick = null;
            PrtInt TMP_tmp0_4 = ((PrtInt)0);
            PrtBool TMP_tmp1_4 = ((PrtBool)false);
            PrtBool TMP_tmp2_4 = ((PrtBool)false);
            PrtInt TMP_tmp3_4 = ((PrtInt)0);
            PrtBool TMP_tmp4_4 = ((PrtBool)false);
            PrtBool TMP_tmp5_4 = ((PrtBool)false);
            PrtInt TMP_tmp6 = ((PrtInt)0);
            PrtBool TMP_tmp7 = ((PrtBool)false);
            PrtBool TMP_tmp8 = ((PrtBool)false);
            PrtBool TMP_tmp9 = ((PrtBool)false);
            PMachineValue TMP_tmp10 = null;
            PEvent TMP_tmp11 = null;
            PMachineValue TMP_tmp12 = null;
            PrtInt TMP_tmp13 = ((PrtInt)0);
            PrtBool TMP_tmp14 = ((PrtBool)false);
            PMachineValue TMP_tmp15 = null;
            PEvent TMP_tmp16 = null;
            PMachineValue TMP_tmp17 = null;
            PrtInt TMP_tmp18 = ((PrtInt)0);
            PrtBool TMP_tmp19 = ((PrtBool)false);
            PrtInt TMP_tmp20 = ((PrtInt)0);
            PrtBool TMP_tmp21 = ((PrtBool)false);
            PrtBool TMP_tmp22 = ((PrtBool)false);
            PrtString TMP_tmp23 = ((PrtString)"");
            TMP_tmp0_4 = (PrtInt)(((PrtInt)(waitingWriters).Count));
            TMP_tmp1_4 = (PrtBool)((TMP_tmp0_4) > (((PrtInt)0)));
            if (TMP_tmp1_4)
            {
                TMP_tmp2_4 = (PrtBool)(((PrtBool)true));
                ((PrtSet)pickReaderOrWriter).Add(TMP_tmp2_4);
            }
            TMP_tmp3_4 = (PrtInt)(((PrtInt)(waitingReaders).Count));
            TMP_tmp4_4 = (PrtBool)((TMP_tmp3_4) > (((PrtInt)0)));
            if (TMP_tmp4_4)
            {
                TMP_tmp5_4 = (PrtBool)(((PrtBool)false));
                ((PrtSet)pickReaderOrWriter).Add(TMP_tmp5_4);
            }
            TMP_tmp6 = (PrtInt)(((PrtInt)(pickReaderOrWriter).Count));
            TMP_tmp7 = (PrtBool)((TMP_tmp6) > (((PrtInt)0)));
            TMP_tmp9 = (PrtBool)(((PrtBool)((IPrtValue)TMP_tmp7)?.Clone()));
            if (TMP_tmp9)
            {
                TMP_tmp8 = (PrtBool)(((PrtBool)currentMachine.TryRandom(pickReaderOrWriter)));
                TMP_tmp9 = (PrtBool)(((PrtBool)((IPrtValue)TMP_tmp8)?.Clone()));
            }
            if (TMP_tmp9)
            {
                TMP_tmp10 = (PMachineValue)(((PMachineValue)currentMachine.TryRandom(waitingWriters)));
                pick = TMP_tmp10;
                ((PrtSet)waitingWriters).Remove(pick);
                TMP_tmp12 = (PMachineValue)(((PMachineValue)((IPrtValue)pick)?.Clone()));
                TMP_tmp11 = (PEvent)(new eAcqWriteLock(null));
                currentMachine.TryRaiseEvent((Event)TMP_tmp11, TMP_tmp12);
                return;
            }
            else
            {
                TMP_tmp13 = (PrtInt)(((PrtInt)(pickReaderOrWriter).Count));
                TMP_tmp14 = (PrtBool)((TMP_tmp13) > (((PrtInt)0)));
                if (TMP_tmp14)
                {
                    TMP_tmp15 = (PMachineValue)(((PMachineValue)currentMachine.TryRandom(waitingReaders)));
                    pick = TMP_tmp15;
                    ((PrtSet)waitingReaders).Remove(pick);
                    TMP_tmp17 = (PMachineValue)(((PMachineValue)((IPrtValue)pick)?.Clone()));
                    TMP_tmp16 = (PEvent)(new eAcqReadLock(null));
                    currentMachine.TryRaiseEvent((Event)TMP_tmp16, TMP_tmp17);
                    return;
                }
                else
                {
                    TMP_tmp18 = (PrtInt)(((PrtInt)(waitingReaders).Count));
                    TMP_tmp19 = (PrtBool)((PrtValues.SafeEquals(TMP_tmp18,((PrtInt)0))));
                    TMP_tmp22 = (PrtBool)(((PrtBool)((IPrtValue)TMP_tmp19)?.Clone()));
                    if (TMP_tmp22)
                    {
                        TMP_tmp20 = (PrtInt)(((PrtInt)(waitingWriters).Count));
                        TMP_tmp21 = (PrtBool)((PrtValues.SafeEquals(TMP_tmp20,((PrtInt)0))));
                        TMP_tmp22 = (PrtBool)(((PrtBool)((IPrtValue)TMP_tmp21)?.Clone()));
                    }
                    TMP_tmp23 = (PrtString)(((PrtString) String.Format("Logic for picking readers and writers is incorrect!")));
                    currentMachine.TryAssert(TMP_tmp22,"Assertion Failed: " + TMP_tmp23);
                }
            }
        }
        public void Anon_2(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue reader = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PMachineValue TMP_tmp0_5 = null;
            PEvent TMP_tmp1_5 = null;
            IPrtValue TMP_tmp2_5 = null;
            PMachineValue TMP_tmp3_5 = null;
            TMP_tmp0_5 = (PMachineValue)(((PMachineValue)((IPrtValue)reader)?.Clone()));
            TMP_tmp1_5 = (PEvent)(new eRWLockGranted(null));
            TMP_tmp2_5 = (IPrtValue)(((IPrtValue)((IPrtValue)sharedObj)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0_5, (Event)TMP_tmp1_5, TMP_tmp2_5);
            TMP_tmp3_5 = (PMachineValue)(((PMachineValue)((IPrtValue)reader)?.Clone()));
            ((PrtSet)currentReaders).Add(TMP_tmp3_5);
        }
        public void Anon_3(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue reader_1 = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PMachineValue TMP_tmp0_6 = null;
            PEvent TMP_tmp1_6 = null;
            IPrtValue TMP_tmp2_6 = null;
            PrtBool TMP_tmp3_6 = ((PrtBool)false);
            PrtBool TMP_tmp4_5 = ((PrtBool)false);
            PrtString TMP_tmp5_5 = ((PrtString)"");
            PMachineValue TMP_tmp6_1 = null;
            TMP_tmp0_6 = (PMachineValue)(((PMachineValue)((IPrtValue)reader_1)?.Clone()));
            TMP_tmp1_6 = (PEvent)(new eRWLockGranted(null));
            TMP_tmp2_6 = (IPrtValue)(((IPrtValue)((IPrtValue)sharedObj)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0_6, (Event)TMP_tmp1_6, TMP_tmp2_6);
            TMP_tmp3_6 = (PrtBool)(((PrtBool)(((PrtSet)currentReaders).Contains(reader_1))));
            TMP_tmp4_5 = (PrtBool)(!(TMP_tmp3_6));
            TMP_tmp5_5 = (PrtString)(((PrtString) String.Format("Trying to re-acquire the lock (reentrancy not supported)")));
            currentMachine.TryAssert(TMP_tmp4_5,"Assertion Failed: " + TMP_tmp5_5);
            TMP_tmp6_1 = (PMachineValue)(((PMachineValue)((IPrtValue)reader_1)?.Clone()));
            ((PrtSet)currentReaders).Add(TMP_tmp6_1);
        }
        public void Anon_4(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue reader_2 = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PrtBool TMP_tmp0_7 = ((PrtBool)false);
            PrtString TMP_tmp1_7 = ((PrtString)"");
            PrtInt TMP_tmp2_7 = ((PrtInt)0);
            PrtBool TMP_tmp3_7 = ((PrtBool)false);
            TMP_tmp0_7 = (PrtBool)(((PrtBool)(((PrtSet)currentReaders).Contains(reader_2))));
            TMP_tmp1_7 = (PrtString)(((PrtString) String.Format("Trying to release lock before acquiring it!!")));
            currentMachine.TryAssert(TMP_tmp0_7,"Assertion Failed: " + TMP_tmp1_7);
            ((PrtSet)currentReaders).Remove(reader_2);
            TMP_tmp2_7 = (PrtInt)(((PrtInt)(currentReaders).Count));
            TMP_tmp3_7 = (PrtBool)((PrtValues.SafeEquals(TMP_tmp2_7,((PrtInt)0))));
            if (TMP_tmp3_7)
            {
                currentMachine.TryGotoState<ChooseReadOrWriteLock>();
                return;
            }
        }
        public void Anon_5(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue writer = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PMachineValue TMP_tmp0_8 = null;
            TMP_tmp0_8 = (PMachineValue)(((PMachineValue)((IPrtValue)writer)?.Clone()));
            ((PrtSet)waitingWriters).Add(TMP_tmp0_8);
        }
        public void Anon_6(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue writer_1 = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PMachineValue TMP_tmp0_9 = null;
            PEvent TMP_tmp1_8 = null;
            IPrtValue TMP_tmp2_8 = null;
            TMP_tmp0_9 = (PMachineValue)(((PMachineValue)((IPrtValue)writer_1)?.Clone()));
            TMP_tmp1_8 = (PEvent)(new eRWLockGranted(null));
            TMP_tmp2_8 = (IPrtValue)(((IPrtValue)((IPrtValue)sharedObj)?.Clone()));
            currentMachine.TrySendEvent(TMP_tmp0_9, (Event)TMP_tmp1_8, TMP_tmp2_8);
            currentWriter = (PMachineValue)(((PMachineValue)((IPrtValue)writer_1)?.Clone()));
        }
        public void Anon_7(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            IPrtValue val_1 = (IPrtValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PMachineValue TMP_tmp0_10 = null;
            TMP_tmp0_10 = (PMachineValue)(((PMachineValue)null));
            currentWriter = TMP_tmp0_10;
            currentMachine.TryGotoState<ChooseReadOrWriteLock>();
            return;
        }
        public void Anon_8(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue reader_3 = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PMachineValue TMP_tmp0_11 = null;
            TMP_tmp0_11 = (PMachineValue)(((PMachineValue)((IPrtValue)reader_3)?.Clone()));
            ((PrtSet)waitingReaders).Add(TMP_tmp0_11);
        }
        public void Anon_9(Event currentMachine_dequeuedEvent)
        {
            RWSharedObject currentMachine = this;
            PMachineValue writer_2 = (PMachineValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PrtBool TMP_tmp0_12 = ((PrtBool)false);
            PrtString TMP_tmp1_9 = ((PrtString)"");
            PMachineValue TMP_tmp2_9 = null;
            TMP_tmp0_12 = (PrtBool)((!PrtValues.SafeEquals(writer_2,currentWriter)));
            TMP_tmp1_9 = (PrtString)(((PrtString) String.Format("Trying to re-acquire the lock (reentrancy not supported)")));
            currentMachine.TryAssert(TMP_tmp0_12,"Assertion Failed: " + TMP_tmp1_9);
            TMP_tmp2_9 = (PMachineValue)(((PMachineValue)((IPrtValue)writer_2)?.Clone()));
            ((PrtSet)waitingWriters).Add(TMP_tmp2_9);
        }
        [Start]
        [OnEntry(nameof(InitializeParametersFunction))]
        [OnEventGotoState(typeof(ConstructorEvent), typeof(Init))]
        class __InitState__ : State { }
        
        [OnEntry(nameof(Anon))]
        class Init : State
        {
        }
        [OnEntry(nameof(Anon_1))]
        [OnEventGotoState(typeof(eAcqReadLock), typeof(ReadLockAcquired))]
        [OnEventGotoState(typeof(eAcqWriteLock), typeof(WriteLockAcquired))]
        class ChooseReadOrWriteLock : State
        {
        }
        [OnEntry(nameof(Anon_2))]
        [OnEventDoAction(typeof(eAcqReadLock), nameof(Anon_3))]
        [OnEventDoAction(typeof(eReleaseReadLock), nameof(Anon_4))]
        [OnEventDoAction(typeof(eAcqWriteLock), nameof(Anon_5))]
        class ReadLockAcquired : State
        {
        }
        [OnEntry(nameof(Anon_6))]
        [OnEventDoAction(typeof(eReleaseWriteLock), nameof(Anon_7))]
        [OnEventDoAction(typeof(eAcqReadLock), nameof(Anon_8))]
        [OnEventDoAction(typeof(eAcqWriteLock), nameof(Anon_9))]
        class WriteLockAcquired : State
        {
        }
    }
}
namespace PImplementation
{
    internal partial class TestWithProcess : PMachine
    {
        private PrtInt count = ((PrtInt)0);
        private PMachineValue sharedObj_1 = null;
        public class ConstructorEvent : PEvent{public ConstructorEvent(IPrtValue val) : base(val) { }}
        
        protected override Event GetConstructorEvent(IPrtValue value) { return new ConstructorEvent((IPrtValue)value); }
        public TestWithProcess() {
            this.sends.Add(nameof(doneInc));
            this.sends.Add(nameof(eAcqReadLock));
            this.sends.Add(nameof(eAcqWriteLock));
            this.sends.Add(nameof(eRWLockGranted));
            this.sends.Add(nameof(eReleaseReadLock));
            this.sends.Add(nameof(eReleaseWriteLock));
            this.sends.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
            this.sends.Add(nameof(PHalt));
            this.receives.Add(nameof(doneInc));
            this.receives.Add(nameof(eAcqReadLock));
            this.receives.Add(nameof(eAcqWriteLock));
            this.receives.Add(nameof(eRWLockGranted));
            this.receives.Add(nameof(eReleaseReadLock));
            this.receives.Add(nameof(eReleaseWriteLock));
            this.receives.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
            this.receives.Add(nameof(PHalt));
            this.creates.Add(nameof(I_App));
            this.creates.Add(nameof(I_RWSharedObject));
        }
        
        public void Anon_10(Event currentMachine_dequeuedEvent)
        {
            TestWithProcess currentMachine = this;
            PrtInt i = ((PrtInt)0);
            PrtInt TMP_tmp0_13 = ((PrtInt)0);
            PMachineValue TMP_tmp1_10 = null;
            PrtBool TMP_tmp2_10 = ((PrtBool)false);
            PrtBool TMP_tmp3_8 = ((PrtBool)false);
            PMachineValue TMP_tmp4_6 = null;
            PMachineValue TMP_tmp5_6 = null;
            PrtInt TMP_tmp6_2 = ((PrtInt)0);
            TMP_tmp0_13 = (PrtInt)(((PrtInt)1));
            TMP_tmp1_10 = (PMachineValue)(currentMachine.CreateInterface<I_RWSharedObject>( currentMachine, TMP_tmp0_13));
            sharedObj_1 = TMP_tmp1_10;
            while (((PrtBool)true))
            {
                TMP_tmp2_10 = (PrtBool)((i) < (((PrtInt)2)));
                TMP_tmp3_8 = (PrtBool)(((PrtBool)((IPrtValue)TMP_tmp2_10)?.Clone()));
                if (TMP_tmp3_8)
                {
                }
                else
                {
                    break;
                }
                TMP_tmp4_6 = (PMachineValue)(currentMachine.self);
                TMP_tmp5_6 = (PMachineValue)(((PMachineValue)((IPrtValue)sharedObj_1)?.Clone()));
                currentMachine.CreateInterface<I_App>(currentMachine, new PrtTuple(TMP_tmp4_6,TMP_tmp5_6));
                TMP_tmp6_2 = (PrtInt)((i) + (((PrtInt)1)));
                i = TMP_tmp6_2;
            }
        }
        public async Task Anon_11(Event currentMachine_dequeuedEvent)
        {
            TestWithProcess currentMachine = this;
            PrtInt val_2 = ((PrtInt)0);
            PrtInt TMP_tmp0_14 = ((PrtInt)0);
            PrtBool TMP_tmp1_11 = ((PrtBool)false);
            PMachineValue TMP_tmp2_11 = null;
            PMachineValue TMP_tmp3_9 = null;
            IPrtValue TMP_tmp4_7 = null;
            PrtInt TMP_tmp5_7 = ((PrtInt)0);
            PrtBool TMP_tmp6_3 = ((PrtBool)false);
            PrtString TMP_tmp7_1 = ((PrtString)"");
            PMachineValue TMP_tmp8_1 = null;
            PMachineValue TMP_tmp9_1 = null;
            TMP_tmp0_14 = (PrtInt)((count) + (((PrtInt)1)));
            count = TMP_tmp0_14;
            TMP_tmp1_11 = (PrtBool)((PrtValues.SafeEquals(count,((PrtInt)2))));
            if (TMP_tmp1_11)
            {
                TMP_tmp2_11 = (PMachineValue)(((PMachineValue)((IPrtValue)sharedObj_1)?.Clone()));
                TMP_tmp3_9 = (PMachineValue)(currentMachine.self);
                TMP_tmp4_7 = (IPrtValue)(await GlobalFunctions.AcquireReadLock(TMP_tmp2_11, TMP_tmp3_9, currentMachine));
                TMP_tmp5_7 = (PrtInt)(((PrtInt)((IPrtValue)((IPrtValue)TMP_tmp4_7)?.Clone())));
                val_2 = TMP_tmp5_7;
                TMP_tmp6_3 = (PrtBool)((PrtValues.SafeEquals(val_2,((PrtInt)3))));
                TMP_tmp7_1 = (PrtString)(((PrtString) String.Format("Increment Didnt work!")));
                currentMachine.TryAssert(TMP_tmp6_3,"Assertion Failed: " + TMP_tmp7_1);
                TMP_tmp8_1 = (PMachineValue)(((PMachineValue)((IPrtValue)sharedObj_1)?.Clone()));
                TMP_tmp9_1 = (PMachineValue)(currentMachine.self);
                GlobalFunctions.ReleaseReadLock(TMP_tmp8_1, TMP_tmp9_1, currentMachine);
            }
        }
        [Start]
        [OnEntry(nameof(InitializeParametersFunction))]
        [OnEventGotoState(typeof(ConstructorEvent), typeof(Init_1))]
        class __InitState__ : State { }
        
        [OnEntry(nameof(Anon_10))]
        [OnEventDoAction(typeof(doneInc), nameof(Anon_11))]
        class Init_1 : State
        {
        }
    }
}
namespace PImplementation
{
    internal partial class App : PMachine
    {
        public class ConstructorEvent : PEvent{public ConstructorEvent(PrtTuple val) : base(val) { }}
        
        protected override Event GetConstructorEvent(IPrtValue value) { return new ConstructorEvent((PrtTuple)value); }
        public App() {
            this.sends.Add(nameof(doneInc));
            this.sends.Add(nameof(eAcqReadLock));
            this.sends.Add(nameof(eAcqWriteLock));
            this.sends.Add(nameof(eRWLockGranted));
            this.sends.Add(nameof(eReleaseReadLock));
            this.sends.Add(nameof(eReleaseWriteLock));
            this.sends.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
            this.sends.Add(nameof(PHalt));
            this.receives.Add(nameof(doneInc));
            this.receives.Add(nameof(eAcqReadLock));
            this.receives.Add(nameof(eAcqWriteLock));
            this.receives.Add(nameof(eRWLockGranted));
            this.receives.Add(nameof(eReleaseReadLock));
            this.receives.Add(nameof(eReleaseWriteLock));
            this.receives.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
            this.receives.Add(nameof(PHalt));
        }
        
        public async Task Anon_12(Event currentMachine_dequeuedEvent)
        {
            App currentMachine = this;
            PrtTuple payload = (PrtTuple)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            PrtInt val_3 = ((PrtInt)0);
            PMachineValue TMP_tmp0_15 = null;
            PMachineValue TMP_tmp1_12 = null;
            IPrtValue TMP_tmp2_12 = null;
            PrtInt TMP_tmp3_10 = ((PrtInt)0);
            PMachineValue TMP_tmp4_8 = null;
            PMachineValue TMP_tmp5_8 = null;
            PrtInt TMP_tmp6_4 = ((PrtInt)0);
            PMachineValue TMP_tmp7_2 = null;
            PMachineValue TMP_tmp8_2 = null;
            PEvent TMP_tmp9_2 = null;
            TMP_tmp0_15 = (PMachineValue)(((PrtTuple)payload)[1]);
            TMP_tmp1_12 = (PMachineValue)(currentMachine.self);
            TMP_tmp2_12 = (IPrtValue)(await GlobalFunctions.AcquireWriteLock(TMP_tmp0_15, TMP_tmp1_12, currentMachine));
            TMP_tmp3_10 = (PrtInt)(((PrtInt)((IPrtValue)((IPrtValue)TMP_tmp2_12)?.Clone())));
            val_3 = TMP_tmp3_10;
            TMP_tmp4_8 = (PMachineValue)(((PrtTuple)payload)[1]);
            TMP_tmp5_8 = (PMachineValue)(currentMachine.self);
            TMP_tmp6_4 = (PrtInt)((val_3) + (((PrtInt)1)));
            GlobalFunctions.ReleaseWriteLock(TMP_tmp4_8, TMP_tmp5_8, TMP_tmp6_4, currentMachine);
            TMP_tmp7_2 = (PMachineValue)(((PrtTuple)payload)[0]);
            TMP_tmp8_2 = (PMachineValue)(((PMachineValue)((IPrtValue)TMP_tmp7_2)?.Clone()));
            TMP_tmp9_2 = (PEvent)(new doneInc(null));
            currentMachine.TrySendEvent(TMP_tmp8_2, (Event)TMP_tmp9_2);
        }
        [Start]
        [OnEntry(nameof(InitializeParametersFunction))]
        [OnEventGotoState(typeof(ConstructorEvent), typeof(Init_2))]
        class __InitState__ : State { }
        
        [OnEntry(nameof(Anon_12))]
        class Init_2 : State
        {
        }
    }
}
namespace PImplementation
{
    internal partial class MemoryValueAlwaysCorrect : PMonitor
    {
        private IPrtValue valBalance = null;
        static MemoryValueAlwaysCorrect() {
            observes.Add(nameof(eReleaseWriteLock));
            observes.Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
        }
        
        public void Anon_13(Event currentMachine_dequeuedEvent)
        {
            MemoryValueAlwaysCorrect currentMachine = this;
            IPrtValue val_4 = (IPrtValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            valBalance = (IPrtValue)(((IPrtValue)((IPrtValue)val_4)?.Clone()));
        }
        public void Anon_14(Event currentMachine_dequeuedEvent)
        {
            MemoryValueAlwaysCorrect currentMachine = this;
            IPrtValue val_5 = (IPrtValue)(gotoPayload ?? ((PEvent)currentMachine_dequeuedEvent).Payload);
            this.gotoPayload = null;
            IPrtValue TMP_tmp0_16 = null;
            PrtString TMP_tmp1_13 = ((PrtString)"");
            TMP_tmp0_16 = (IPrtValue)(((IPrtValue)((IPrtValue)val_5)?.Clone()));
            TMP_tmp1_13 = (PrtString)(((PrtString) String.Format("val {0}",TMP_tmp0_16)));
            PModule.runtime.Logger.WriteLine("<PrintLog> " + TMP_tmp1_13);
        }
        [Start]
        [OnEventGotoState(typeof(eSpec_MemoryValueAlwaysCorrect_Init), typeof(WaitForWriteLock), nameof(Anon_13))]
        class Init_3 : State
        {
        }
        [OnEventDoAction(typeof(eReleaseWriteLock), nameof(Anon_14))]
        class WaitForWriteLock : State
        {
        }
    }
}
namespace PImplementation
{
    public class tcProcessUsingMemory {
        public static void InitializeLinkMap() {
            PModule.linkMap.Clear();
            PModule.linkMap[nameof(I_TestWithProcess)] = new Dictionary<string, string>();
            PModule.linkMap[nameof(I_TestWithProcess)].Add(nameof(I_App), nameof(I_App));
            PModule.linkMap[nameof(I_TestWithProcess)].Add(nameof(I_RWSharedObject), nameof(I_RWSharedObject));
            PModule.linkMap[nameof(I_RWSharedObject)] = new Dictionary<string, string>();
            PModule.linkMap[nameof(I_App)] = new Dictionary<string, string>();
        }
        
        public static void InitializeInterfaceDefMap() {
            PModule.interfaceDefinitionMap.Clear();
            PModule.interfaceDefinitionMap.Add(nameof(I_TestWithProcess), typeof(TestWithProcess));
            PModule.interfaceDefinitionMap.Add(nameof(I_RWSharedObject), typeof(RWSharedObject));
            PModule.interfaceDefinitionMap.Add(nameof(I_App), typeof(App));
        }
        
        public static void InitializeMonitorObserves() {
            PModule.monitorObserves.Clear();
            PModule.monitorObserves[nameof(MemoryValueAlwaysCorrect)] = new List<string>();
            PModule.monitorObserves[nameof(MemoryValueAlwaysCorrect)].Add(nameof(eReleaseWriteLock));
            PModule.monitorObserves[nameof(MemoryValueAlwaysCorrect)].Add(nameof(eSpec_MemoryValueAlwaysCorrect_Init));
        }
        
        public static void InitializeMonitorMap(IActorRuntime runtime) {
            PModule.monitorMap.Clear();
            PModule.monitorMap[nameof(I_TestWithProcess)] = new List<Type>();
            PModule.monitorMap[nameof(I_TestWithProcess)].Add(typeof(MemoryValueAlwaysCorrect));
            PModule.monitorMap[nameof(I_RWSharedObject)] = new List<Type>();
            PModule.monitorMap[nameof(I_RWSharedObject)].Add(typeof(MemoryValueAlwaysCorrect));
            PModule.monitorMap[nameof(I_App)] = new List<Type>();
            PModule.monitorMap[nameof(I_App)].Add(typeof(MemoryValueAlwaysCorrect));
            runtime.RegisterMonitor<MemoryValueAlwaysCorrect>();
        }
        
        
        [Microsoft.Coyote.SystematicTesting.Test]
        public static void Execute(IActorRuntime runtime) {
            runtime.RegisterLog(new PLogFormatter());
            PModule.runtime = runtime;
            PHelper.InitializeInterfaces();
            PHelper.InitializeEnums();
            InitializeLinkMap();
            InitializeInterfaceDefMap();
            InitializeMonitorMap(runtime);
            InitializeMonitorObserves();
            runtime.CreateActor(typeof(_GodMachine), new _GodMachine.Config(typeof(TestWithProcess)));
        }
    }
}
// TODO: NamedModule Process
namespace PImplementation
{
    public class I_RWSharedObject : PMachineValue {
        public I_RWSharedObject (ActorId machine, List<string> permissions) : base(machine, permissions) { }
    }
    
    public class I_TestWithProcess : PMachineValue {
        public I_TestWithProcess (ActorId machine, List<string> permissions) : base(machine, permissions) { }
    }
    
    public class I_App : PMachineValue {
        public I_App (ActorId machine, List<string> permissions) : base(machine, permissions) { }
    }
    
    public partial class PHelper {
        public static void InitializeInterfaces() {
            PInterfaces.Clear();
            PInterfaces.AddInterface(nameof(I_RWSharedObject), nameof(doneInc), nameof(eAcqReadLock), nameof(eAcqWriteLock), nameof(eRWLockGranted), nameof(eReleaseReadLock), nameof(eReleaseWriteLock), nameof(eSpec_MemoryValueAlwaysCorrect_Init), nameof(PHalt));
            PInterfaces.AddInterface(nameof(I_TestWithProcess), nameof(doneInc), nameof(eAcqReadLock), nameof(eAcqWriteLock), nameof(eRWLockGranted), nameof(eReleaseReadLock), nameof(eReleaseWriteLock), nameof(eSpec_MemoryValueAlwaysCorrect_Init), nameof(PHalt));
            PInterfaces.AddInterface(nameof(I_App), nameof(doneInc), nameof(eAcqReadLock), nameof(eAcqWriteLock), nameof(eRWLockGranted), nameof(eReleaseReadLock), nameof(eReleaseWriteLock), nameof(eSpec_MemoryValueAlwaysCorrect_Init), nameof(PHalt));
        }
    }
    
}
namespace PImplementation
{
    public partial class PHelper {
        public static void InitializeEnums() {
            PrtEnum.Clear();
        }
    }
    
}
#pragma warning restore 162, 219, 414
