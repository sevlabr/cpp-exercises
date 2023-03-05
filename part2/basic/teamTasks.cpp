#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <exception>

using namespace std;

enum class TaskStatus {
  NEW,
  IN_PROGRESS,
  TESTING,
  DONE
};

using TasksInfo = map<TaskStatus, int>;

void MakeTasksForEachStatus(const TaskStatus& current_task_status,
									const TaskStatus& next_task_status,
									const int& number_of_tasks, int& task_count,
									TasksInfo& untouched_tasks, TasksInfo& updated_tasks) {
	for (int tasks_left = number_of_tasks; tasks_left > 0; --tasks_left) {
		if (task_count > 0) {
			++updated_tasks[next_task_status];
			--untouched_tasks[current_task_status];
			--task_count;
		} else {
			break;
		}
	}
}

void MakeResultTasks(TasksInfo& untouched_tasks, TasksInfo& updated_tasks,
					  const TasksInfo& tasks, int& task_count) {
	for (const auto& [task_status, number_of_tasks] : tasks) {
		switch(task_status) {
		case TaskStatus::NEW:
			MakeTasksForEachStatus(TaskStatus::NEW, TaskStatus::IN_PROGRESS,
										  number_of_tasks, task_count,
										  untouched_tasks, updated_tasks);
			break;
		case TaskStatus::IN_PROGRESS:
			MakeTasksForEachStatus(TaskStatus::IN_PROGRESS, TaskStatus::TESTING,
										  number_of_tasks, task_count,
										  untouched_tasks, updated_tasks);
			break;
		case TaskStatus::TESTING:
			MakeTasksForEachStatus(TaskStatus::TESTING, TaskStatus::DONE,
										  number_of_tasks, task_count,
										  untouched_tasks, updated_tasks);
			break;
		case TaskStatus::DONE:
			break;
		}
		if (task_count <= 0) {
			break;
		}
	}
	vector<TaskStatus> statuses_to_erase;
	for (const auto& [task_status, number_of_tasks] : untouched_tasks) {
		if (number_of_tasks == 0) {
			statuses_to_erase.push_back(task_status);
		}
	}
	for (const auto& status : statuses_to_erase) {
		untouched_tasks.erase(status);
	}
}

void UpdateTasks(TasksInfo& tasks,
				 const TasksInfo& untouched_tasks, const TasksInfo& updated_tasks) {
	for (const auto& [task_status, number_of_tasks] : untouched_tasks) {
		tasks[task_status] += number_of_tasks;
	}
	for (const auto& [task_status, number_of_tasks] : updated_tasks) {
		tasks[task_status] += number_of_tasks;
	}
}

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
	  return person_to_tasks.at(person);
  }

  void AddNewTask(const string& person) {
	  ++person_to_tasks[person][TaskStatus::NEW];
  }

  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
	  try {
		  TasksInfo& tasks = person_to_tasks.at(person);
		  TasksInfo updated_tasks;
		  TasksInfo untouched_tasks = tasks;
		  int done_tasks = 0;
		  if (untouched_tasks.count(TaskStatus::DONE) != 0) {
			  done_tasks = untouched_tasks[TaskStatus::DONE];
			  untouched_tasks.erase(TaskStatus::DONE);
		  }
		  MakeResultTasks(untouched_tasks, updated_tasks, tasks, task_count);
		  tasks.clear();
		  if (done_tasks != 0) {
			  tasks[TaskStatus::DONE] = done_tasks;
		  }
		  UpdateTasks(tasks, untouched_tasks, updated_tasks);
		  if (untouched_tasks.empty()) {
			  untouched_tasks = TasksInfo();
		  }
		  if (updated_tasks.empty()) {
			  updated_tasks = TasksInfo();
		  }
		  return make_tuple(updated_tasks, untouched_tasks);
	  } catch (const out_of_range&) {
		  return make_tuple(TasksInfo(), TasksInfo());
	  }
  }

private:
  map<string, TasksInfo> person_to_tasks;
};

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {

  TeamTasks tasks;

  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tasks.AddNewTask("Vova");
  cout << "1) Vovas's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Vova"));

  tie(updated_tasks, untouched_tasks) =
	  tasks.PerformPersonTasks("Vova", 1);
  tie(updated_tasks, untouched_tasks) =
  	  tasks.PerformPersonTasks("Vova", 1);
  tie(updated_tasks, untouched_tasks) =
  	  tasks.PerformPersonTasks("Vova", 1);

  for (int i = 0; i < 4; ++i) {
	  tasks.AddNewTask("Vova");
  }
  tie(updated_tasks, untouched_tasks) =
    	  tasks.PerformPersonTasks("Vova", 4);
  tie(updated_tasks, untouched_tasks) =
    	  tasks.PerformPersonTasks("Vova", 4);
  cout << "2) Vovas's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Vova"));

  for (int i = 0; i < 2; ++i) {
    	  tasks.AddNewTask("Vova");
  }
  tie(updated_tasks, untouched_tasks) =
      	  tasks.PerformPersonTasks("Vova", 2);

  for (int i = 0; i < 3; ++i) {
      	  tasks.AddNewTask("Vova");
  }
  cout << "3) Vovas's tasks: ";
      PrintTasksInfo(tasks.GetPersonTasksInfo("Vova"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Vova", 4);


  cout << "Updated Vova's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Vova's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << "Vovas's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Vova"));

  tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Vova", 9);

  cout << "Vovas's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Vova"));

    cout << "Updated Vova's tasks: ";
      PrintTasksInfo(updated_tasks);
      cout << "Untouched Vova's tasks: ";
      PrintTasksInfo(untouched_tasks);

      tie(updated_tasks, untouched_tasks) =
              tasks.PerformPersonTasks("Vova", 4);

  cout << "FINAL" << endl;
  cout << "Vovas's tasks: ";
      PrintTasksInfo(tasks.GetPersonTasksInfo("Vova"));

      cout << "Updated Vova's tasks: ";
        PrintTasksInfo(updated_tasks);
        cout << "Untouched Vova's tasks: ";
        PrintTasksInfo(untouched_tasks);
  return 0;
}


/*
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  void AddNewTask(const string& person);

  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);

private:
  map<string, TasksInfo> person_tasks_;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++person_tasks_[person][TaskStatus::NEW];
}

void RemoveZeros(TasksInfo& tasks_info) {
  vector<TaskStatus> statuses_to_remove;
  for (const auto& task_item : tasks_info) {
    if (task_item.second == 0) {
      statuses_to_remove.push_back(task_item.first);
    }
  }
  for (const TaskStatus status : statuses_to_remove) {
    tasks_info.erase(status);
  }
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
    const string& person, int task_count) {
  TasksInfo updated_tasks, untouched_tasks;

  // std::map::operator[] ->
  // http://ru.cppreference.com/w/cpp/container/map/operator_at
  TasksInfo& tasks = person_tasks_[person];

  // enum class -> http://ru.cppreference.com/w/cpp/language/enum
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    task_count -= updated_tasks[Next(status)];
  }

  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

  RemoveZeros(updated_tasks);
  RemoveZeros(untouched_tasks);
  RemoveZeros(person_tasks_.at(person));

  return {updated_tasks, untouched_tasks};
} */

