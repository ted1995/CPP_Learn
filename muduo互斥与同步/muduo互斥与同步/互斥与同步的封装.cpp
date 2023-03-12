#include<pthread.h>
#include<assert.h>
class MutexLock
{
public:
	//����ʱ��ʼ��
	MutexLock():holder_(0)
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	//����ʱ����
	~MutexLock()
	{
		assert(holder_ == 0);
		pthread_mutex_destroy(&mutex_);
	}
	//�жϻ������������Ƿ�Ϊ��ǰ�߳�
	bool isLockedByThisThread()
	{
		return holder_ == CurrentThread::tid();
	}
	//
	void assertLocked()
	{
		assert(isLockedByThisThread());
	}
	//����
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