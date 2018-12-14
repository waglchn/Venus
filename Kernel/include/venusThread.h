#ifndef __VENUS_THREAD_H_INCLUDED__
#define __VENUS_THREAD_H_INCLUDED__
#include "VenusMutex.h"

namespace venus
{
	enum ThreadState
	{
		TS_NONE,
		TS_WAIT,
		TS_RUNNING,
	};

	class VenusThread
	{
	private:
		static void* thread_main(void* context)
		{
			VenusThread*pthread = (VenusThread*)context;
			if (pthread != NULL)
			{
				pthread->silent();
				pthread->onEntry();
				pthread->onRun();
				pthread->onLeave();
			}
			return ((void *)0);
		}
	public:
		VenusThread()
		{
			meState = TS_NONE;
			mbopened = false;
			mbSilented = false;
			mbCanceled = false;
		}
		~VenusThread()
		{
			meState = TS_NONE;
			mbopened = false;
			mbSilented = false;
			mbCanceled = false;
		}
	
	public:
		///开启线程任务
		void open()
		{
			if (mbopened)
				return;
			
			int error = pthread_create(&mthreadId, NULL, thread_main, this);
			if (error == 0)
			{
				mbopened = true;
			}
			else
			{
				throw;
			}
		}

		///取消线程
		void cancel()
		{
			if (!mbopened)
				return;

			mbCanceled = true;
			activate();
			pthread_join(mthreadId, NULL);
			mbopened = false;
		}
		void silent()
		{
			if (!mbopened)
				return;

			mbSilented = true;
		}
		void activate()
		{
			if (mbSilented)
			{
				mbSilented = false;
			}
			if (meState == TS_WAIT)
			{
				mmutexThread.notify();
			}
		}
	protected:
		void wait()
		{
			setState(TS_WAIT);
			///立即等待
			mmutexThread.wait();
			setState(TS_RUNNING);
		}
		void timedWait(long time)
		{
			///立即等待一段时间
			setState(TS_WAIT);
			mmutexThread.timedWait(time);
			setState(TS_RUNNING);
		}
		bool working()
		{
			if (mbCanceled)
			{
				return false;
			}
			else if (mbSilented)
			{
				setState(TS_WAIT);
				mmutexThread.wait();
				setState(TS_RUNNING);
			}
			
			return true;
		}

		void setState(ThreadState eState)
		{
			meState = eState;
		}
		ThreadState getState()
		{
			return meState;
		}
	public:
		virtual void onEntry()
		{
		}

		virtual void onLeave()
		{

		}
		virtual void onRun()
		{

		}
	private: 
		Mutex mmutexWait;
		bool mbopened;
		bool mbSilented;
		bool mbCanceled;
		ConditionMutex mmutexThread;
		ThreadState meState;
		pthread_t mthreadId;
	};
}


#endif
