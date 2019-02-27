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
			eState = TS_NONE;
			opened = false;
			silented = false;
			canceled = false;
		}
		~VenusThread()
		{
			eState = TS_NONE;
			opened = false;
			silented = false;
			canceled = false;
		}
	
	public:
		///开启线程任务
		void open()
		{
			if (opened)
				return;
			
			int error = pthread_create(&threadId, NULL, thread_main, this);
			if (error == 0)
			{
				opened = true;
			}
			else
			{
				throw;
			}
		}

		///取消线程
		void cancel()
		{
			if (!opened)
				return;

			canceled = true;
			activate();
			pthread_join(threadId, NULL);
			opened = false;
		}
		void silent()
		{
			if (!opened)
				return;

			silented = true;
		}
		void activate()
		{
			if (silented)
			{
				silented = false;
			}
			if (eState == TS_WAIT)
			{
				mutexThread.notify();
			}
		}
	protected:
		void wait()
		{
			setState(TS_WAIT);
			///立即等待
			mutexThread.wait();
			setState(TS_RUNNING);
		}
		void timedWait(long time)
		{
			///立即等待一段时间
			setState(TS_WAIT);
			mutexThread.timedWait(time);
			setState(TS_RUNNING);
		}
		bool working()
		{
			if (canceled)
			{
				return false;
			}
			else if (silented)
			{
				setState(TS_WAIT);
				mutexThread.wait();
				setState(TS_RUNNING);
			}
			
			return true;
		}

		void setState(ThreadState eState)
		{
			eState = eState;
		}
		ThreadState getState()
		{
			return eState;
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
		bool opened;
		bool silented;
		bool canceled;
		ConditionMutex mutexThread;
		ThreadState eState;
		pthread_t threadId;
	};
}


#endif
