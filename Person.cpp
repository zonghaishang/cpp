#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person {
    public:
        string name;
        shared_ptr<Person> mother;
        shared_ptr<Person> father;
        vector<weak_ptr<Person> > kids;

        Person(const string & n, shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f) {

        }

        ~Person(){
            cout << "delete " << name << endl;
        }
};

shared_ptr<Person> initFamily(const string& name) {

    shared_ptr<Person> mom(new Person(name + "'s mom"));
    shared_ptr<Person> dad(new Person(name + "'s dad"));
    shared_ptr<Person> kids(new Person(name, mom, dad));
    mom->kids.push_back(kids);
    dad->kids.push_back(kids);
    return kids;
}

int main(int args, char** argv){

    shared_ptr<Person> p = initFamily("nico");

    cout << "nico's family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times " << endl;
    cout <<  "- name of 1st kid of nico's mom: " << p->mother->kids[0]->name << endl;

    p = initFamily("jim");

    cout << "jim's family exist" << endl;

    return 0;

}