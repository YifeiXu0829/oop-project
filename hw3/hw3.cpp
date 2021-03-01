#include <string>
#include <iostream>
#include <memory>
#include <vector>
struct instructor
{
    virtual ~instructor(){}
    virtual std::string ScheduleTeachingLoad(int id)
    {
        return "Teaching Load is Scheduled";
    }

    virtual std::string BecomeDepartmentChairperson(int id)
    {
        return "I can't be a Department Chairperson";
    }

};


struct TeachingAssistant : public instructor
{
    virtual std::string ScheduleTeachingLoad(int id) override
    { 
         return "TA Teaching Load is Scheduled";
    }
};

struct FullProfessor : public instructor
{
    // professors (the only people who could possibly become chairpersons)
    virtual std::string BecomeDepartmentChairperson(int id) override
    { 
         return "Damn";
    }

	virtual std::string ScheduleTeachingLoad(int id) override
	{
		return "FullProfessor Teaching Load is Scheduled";
	}
};

struct ContractualInstructor : public instructor
{
	virtual std::string ScheduleTeachingLoad(int id) override
    { 
         return "ContractualInstructor Teaching Load is Scheduled";
    }
};



int main ()
{
	std::vector<std::unique_ptr<instructor> > instructorList;
	instructorList.emplace_back(new FullProfessor);
	instructorList.emplace_back(new TeachingAssistant);
	instructorList.emplace_back(new ContractualInstructor);

	for(const auto& role : instructorList)
	{
		std::cout<<role->BecomeDepartmentChairperson(12345)<<std::endl;
	}
    return 0;
}
