#include<pthread.h>
#include<assert.h>
class MutexLock
{
public:
	//构造时初始化
	MutexLock():holder_(0)
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	//析构时销毁
	~MutexLock()
	{
		assert(holder_ == 0);
		pthread_mutex_destroy(&mutex_);
	}
	//判断互斥锁持有者是否为当前线程
	bool isLockedByThisThread()
	{
		return holder_ == CurrentThread::tid();
	}
	//
	void assertLocked()
	{
		assert(isLockedByThisThread());
	}
	//上锁
	void lock()
	{
		pthread_mutex_lock(&mutex_);
		holder_ = CurrentThread::tid();
	}
	void unlock()
	{
		holder_ = 0;
		pthread_mutex_unlock(&mutex_);
	}
	pthread_mutex_t getPthreadMutex()
	{
		return &mutex_;
	}
private:
	pthread_mutex_t mutex_;
	pid_t holder_;
};


class MutexLockGuard
{
public:
	explicit MutexLockGuard(MutexLock& mutex):mutex_(mutex)
	{
		mutex_.lock();y
	}
	MutexLockGuard()
	{
		mutex_.unlock();
	}
private:
	MutexLock& mutex_;
};