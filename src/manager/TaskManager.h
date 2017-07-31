#ifndef _TASKMANAGER_H
#define _TASKMANAGER_H

#include <list>

// Task abstract class
class Task
{
public:
	// override run() function to make it works :)
	virtual bool run() = 0;

	void	setId( int id );
	int		getId();

private:
	int _id;
};


// TaskManager class
class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	void	begin();
	void	stop();
	void	appendTask( Task *job );
	void	clear();
	int		getTaskCount();

private:
	int		_taskCount;
	std::list<Task*>	_jobQueue;

	// deallocator
	struct Deallocator
	{
		void operator()( const Task* p )
		{
			delete p;
		}
	};
};



#endif