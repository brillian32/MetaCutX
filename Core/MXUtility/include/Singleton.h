//
// Created by brillan on 2023/11/29.
//

#ifndef SINGLETONSIX
#define SINGLETONSIX

#include <QMutex>
#include <QMutexLocker>
#include <QScopedPointer>

template <class T>
class Singleton
{
public:
	static T* getInstance()
	{
		if(instance.isNull())
		{
			QMutexLocker locker(&mutex);
			if(instance.isNull())
			{
				instance.reset(new T);
			}
		}
		return instance.data();
	}
public:
	~Singleton(){}
protected:
	Singleton() = default;

private:
	static QScopedPointer<T> instance;
	static QMutex    mutex;
};
template <class T>
QScopedPointer<T> Singleton<T>::instance;

template <class T>
QMutex Singleton<T>::mutex;


#define DECLARE_SINGLETON(Class) \
    friend class Singleton<Class>; \
    friend struct QScopedPointerDeleter<Class>; \
Q_DISABLE_COPY(Class) \
private: \
    Class(Class const&&) = delete; \
    Class& operator=(Class const&&) = delete; \
public: \
    static Class* Instance() \
    { \
        return Singleton<Class>::getInstance(); \
    }


class C
{
	DECLARE_SINGLETON(C)
private:
	C(){}
};

#endif // SINGLETONSIX
