#include "TaskManager.h"
#include <algorithm>


// Task class definitions
void Task::setId( int id )
{
	_id = id;
}


int Task::getId()
{
	return _id;
}


//-----------------------------------------------------------------



// TaskManager definitions
TaskManager::TaskManager()
{
	_taskCount = 0;
}


TaskManager::~TaskManager()
{
}


void TaskManager::begin()
{
	if( !_jobQueue.empty() )
	{
		auto it = _jobQueue.begin();
		while( it != _jobQueue.end() )
		{
			(*it)->run();
			_taskCount = _jobQueue.size();
			++it;
		}
	}
}


/* Currently runs nothing */
void TaskManager::stop()
{
	// fill this function while multithreading is available :P
}


void TaskManager::appendTask( Task *job )
{
	if( job )
		_jobQueue.push_back( job );
}


void TaskManager::clear()
{
	if( !_jobQueue.empty() )
	{
		std::for_each( _jobQueue.begin(), _jobQueue.end(), Deallocator() );
		_jobQueue.clear();
		_taskCount = _jobQueue.size();
	}
}


int TaskManager::getTaskCount()
{
	return _taskCount;
}