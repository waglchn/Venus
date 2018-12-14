#ifndef __VENUS_MUTEX_H_INCLUDED__
#define __VENUS_MUTEX_H_INCLUDED__
#include <pthread.h>

#if defined(_MSC_VER)
#include <time.h>
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace venus
{
	class Mutex 
	{
		friend class ConditionMutex;
	public:
		Mutex()
		{
			mbInited = false;
			init();
		}
		~Mutex() 
		{
			destroy();
			mbInited = false;
		}

		void lock()
		{
			if (!mbInited)
				return;
			
			pthread_mutex_lock(&m_mutex);
			
		}
		void unlock()
		{
			if (!mbInited)
				return;
			
			pthread_mutex_unlock(&m_mutex);
		}

		bool tryLock()
		{
			if (!mbInited)
				return false;
			
			return pthread_mutex_trylock(&m_mutex)==0;
		}
	protected:
		void init()
		{
			if (pthread_mutex_init(&m_mutex, NULL) == 0)
			{
				mbInited = true;
			}
		}
		void destroy()
		{
			if (!mbInited)
				return;

			pthread_mutex_destroy(&m_mutex);	
		}
	private:
		pthread_mutex_t m_mutex;
		volatile bool mbInited;
	};
	class AutoMutex : Mutex
	{
	public:
		AutoMutex()
		{
			lock();
		}
		~AutoMutex()
		{
			unlock();
		}
	};

	class ConditionMutex : Mutex
	{
	public:
		explicit ConditionMutex()
		{
			pthread_cond_init(&m_cond, NULL);
		}

		~ConditionMutex()
		{
			pthread_cond_destroy(&m_cond);
		}

		void notify()
		{
			pthread_cond_signal(&m_cond);
		}

		void notifyAll()
		{
			pthread_cond_broadcast(&m_cond);
		}

		void wait()
		{
			pthread_cond_wait(&m_cond, &(m_mutex));
		}

		int gettime(struct timeval *tp, void *tzp)
		{
#if defined(_MSC_VER)
			time_t clock;
			struct tm tm;
			SYSTEMTIME wtm;
			GetLocalTime(&wtm);
			tm.tm_year = wtm.wYear - 1900;
			tm.tm_mon = wtm.wMonth - 1;
			tm.tm_mday = wtm.wDay;
			tm.tm_hour = wtm.wHour;
			tm.tm_min = wtm.wMinute;
			tm.tm_sec = wtm.wSecond;
			tm.tm_isdst = -1;
			clock = mktime(&tm);
			tp->tv_sec = (long)clock;
			tp->tv_usec = wtm.wMilliseconds * 1000;
			return (0);
#else
			return gettimeofday(tp, tzp);
#endif
 		}
 		bool timedWait(long delay_in_ms)
 		{
			struct timeval now;
			struct timespec timeout;
			gettime(&now, NULL);
 			timeout.tv_sec = now.tv_sec + static_cast<long>(delay_in_ms / 1000);
 			timeout.tv_nsec = now.tv_usec +static_cast<long>(delay_in_ms % 1000) * 1000;
 			if (timeout.tv_nsec >= 1000000)
 			{
 				++timeout.tv_sec;
 				timeout.tv_nsec = timeout.tv_nsec % 1000000;
 			}
 			timeout.tv_nsec = timeout.tv_nsec * 1000;
 
 			int ret = 0;
 			while (true)
 			{
 				ret = pthread_cond_timedwait(&m_cond, &(m_mutex), &timeout);
 				if (ret != EINTR)
 				{
 					break;
 				}
 			}
 
 			return ret == 0;
 		}
	private:
		pthread_cond_t m_cond;
	};
}


#endif
