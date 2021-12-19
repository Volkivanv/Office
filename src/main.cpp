#include <iostream>
#include <vector>

class Employee
{
    int index = 0;
    char task = 'N';
    bool busy = false;
public:
    char getTask(){
        return task;
    }
    void setTask(int inTask){
        inTask %= 4;
        if(inTask == 3){
            task = 'N';
            busy = false;
        }else{
            task = 'A' + inTask;
            busy = true;
        }

    }
    bool getBusy(){
        return busy;
    }
    Employee(int inIndex): index(inIndex){};


    void showTask(){
        std::cout<<"Employee number "<<index<<", task "<<task<<" "<<std::boolalpha<<busy<<std::endl;
    }
};

class Manager{
    int index = 0;
    int count = 0;
    int task = 0;
    int free = 0;
    std::vector<Employee*> employees;
    std::vector<int> freeIndexes;
    bool busy = false;

public:
    int getTask(){
        return task;
    }
    bool getBusy(){
        return busy;
    }
    void setBusy(bool inBusy){
        busy = inBusy;
    }
    int getCount(){
        return  count;
    }


    Manager(int inIndex, int inCount):index(inIndex),count(inCount)
    {
        employees.resize(inCount);
        free = inCount;
        freeIndexes.resize(inCount);
        for(int i = 0; i < inCount; i++){
            employees[i] = new Employee(i);
            freeIndexes[i] = i;
        }


    }
    void setTasksToEmployee(int inTask){
        task = inTask+index;
        srand(task);
        int need = rand()%count;
        if(need>=free)need = free;
        for(int i = 0; i < need; i++){
            int c = freeIndexes.size();
            int emp = rand()%c;
            employees[freeIndexes[emp]]->setTask(rand()%3);
            freeIndexes.erase(freeIndexes.begin()+emp);
        }
        free = freeIndexes.size();
        if(free == 0) busy = true;



    }
    void showMangerWork(){
        std::cout<<"Manager "<<index<<" task "<<task<<std::endl;
        std::cout<<"Number of free employee "<<free<<std::endl;
        for(int i = 0; i < count; i++){
            employees[i]->showTask();
        }
    }


};

class Boss : public Manager{
    std::vector<Manager*> managers;
public:
    Boss(int inIndex, int inCount): Manager(inIndex,inCount){
        managers.resize(inCount);
        for(int i = 0; i < inCount; i++){
            int localCount;
            std::cout<<"Input size of team of manager "<<i<<std::endl;
            std::cin>>localCount;
            managers[i] = new Manager(i,localCount);
        }

    }
    void setTaskToManagers(int inTask){
        srand(inTask);
        int taskToMangers = rand();
        int busyCount = 0;
        for(int i = 0; i < getCount(); i++){
            if(!(managers[i]->getBusy())) {
                managers[i]->setTasksToEmployee(taskToMangers);
            }
            if(managers[i]->getBusy()) busyCount++;
        }
        if(busyCount == getCount()) setBusy(true);
    }
    void showWork(){
        std::cout<<"Number of managers: "<<getCount()<<std::endl;
        for(int i = 0; i < getCount();i++){
            managers[i]->showMangerWork();
        }
    }

};


int main() {
    int managerCount;
    std::cout<<"Input number of manegers"<<std::endl;
    std::cin>>managerCount;
    auto boss = new Boss(0,managerCount);
    boss->showWork();
    while(!(boss->getBusy())) {
        std::cout << "Input task" << std::endl;
        int taskNumber;
        std::cin >> taskNumber;
        boss->setTaskToManagers(taskNumber);
        boss->showWork();
    }

    delete boss;
    return 0;
}
