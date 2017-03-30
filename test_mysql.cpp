#include <string>
#include <iostream>

#include "Mysql.h"

int main()
{
  std::string name("root");
  std::string ip("localhost");
  std::string password("110214");
  std::string db("test");
  
  Mysql mysql(ip, name, password, db);
  std::string sql("select * from books;");
  mysql.query(sql);

  return 0;
}
