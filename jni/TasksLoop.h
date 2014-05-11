#ifndef TASKSLOOP_H_
#define TASKSLOOP_H_

#include <list>
#include "Task.hpp"

class TasksLoop
{
	private:
		typedef std::list<Task*>			TaskList;
		typedef std::list<Task*>::iterator	TaskListIterator;

		TaskList	m_tasks;
		TaskList	m_pausedTasks;

		void		PriorityAdd(Task* pTask);

	public:
		TasksLoop();
		virtual ~TasksLoop();

		void	Execute();

		bool 	AddTask(Task* pTask);
		void	SuspendTask(Task* task);
		void	ResumeTask(Task* task);
		void	RemoveTask(Task* task);
		void	KillAllTasks();

		bool	HasTasks()	{ return m_tasks.size(); }
};

#endif // TASKSLOOP_H_
