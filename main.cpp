#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
#include "event.h"

class CFile
{
public:
    typedef std::function<void(std::string)> name_changed_delegate;
    Event<name_changed_delegate> NameChanged;

    void ChangeName(std::string name)
    {
        NameChanged(name);
    }
};

class CFileManager
{
public:
    CFileManager()
        : m_file(new CFile)
    {
        m_file->NameChanged += std::bind(&CFileManager::NameChanged, this, std::placeholders::_1);
    }
    void SetName()
    {
        m_file->ChangeName("new_file.txt");
    }
    void NameChanged(std::string name)
    {
        std::cout << "CFileManager::NameChanged " << name << std::endl;
    }
private:
    CFile* m_file;
};

int main()
{
    CFileManager m;
    m.SetName();
}
