#include "Registrar.h"
#include "Instructor.h"
#include "Student.h"

int main()
{
    Registrar registrar_;
    registrar_.create_class();
    registrar_.log();

    Instructor instructor_;
    instructor_.teach_class();
    instructor_.log();

    Student student_;
    student_.register_for_class();
    student_.log();

}
