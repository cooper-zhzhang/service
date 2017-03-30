#ifndef MYSQL_H
#define MYSQL_H
#include "mysql.h"
#include <iostream>
#include <string>

class Mysql 
{
  public:
    Mysql(std::string IP, std::string user_name, std::string password, std::string db_name)
      :IP_(IP), user_name_(user_name), password_(password), db_name_(db_name)
    {
      if(mysql_init(&mysql_) == NULL)
      {
        exit(-1);
      }

      if(!mysql_real_connect(&mysql_, IP_.c_str(), user_name_.c_str(), password_.c_str(), db_name_.c_str(), 0, NULL, 0))
      {
        exit(-1);
      }
    }

    MYSQL_RES* query(std::string sql)
    {
      mysql_query(&mysql_, sql.c_str());
      result_ = mysql_store_result(&mysql_);
      return result_;
    }

    ~Mysql()
    {
      mysql_close(&mysql_);
    }

  private:
    std::string IP_;
    std::string user_name_;
    std::string password_;
    std::string db_name_;
    MYSQL mysql_;
    MYSQL_RES *result_;
    MYSQL_ROW row_;
};
#endif

