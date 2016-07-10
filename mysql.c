#include <stdio.h>
#include <time.h>
#include <mysql.h>
#include <my_global.h>
#include "config.h"
#include "struct.h"
#include <string.h>


int db_check_not_transfered(char *table){

    int number_of_connections;
    //open the mysql connection
    MYSQL *mysql_con;

    // öffne die MYSQL Verbindung
    if (mysql_start(&mysql_con) != 0){
      return -1;
    }
    char mysql_query_string[500];
    sprintf(mysql_query_string, "SELECT COUNT(id) FROM `honeyssh`.`%s` WHERE `action` = 0;", table);
    if (mysql_query(mysql_con, mysql_query_string)) {
    fprintf(stderr, "Query failed: %s\n", mysql_error(mysql_con));
    return -1;
    }
    else
    {

      MYSQL_RES *result = mysql_store_result(mysql_con);

      if (!result) {
        printf("Couldn't get results set: %s\n", mysql_error(mysql_con));
        return -1;
      }
      else
      {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
          {
            char *endp;
            number_of_connections = strtol(row[0], &endp, 0);
          }
      }
      mysql_free_result(result);
    }

    mysql_close(mysql_con);
    return number_of_connections;

}

int db_set_finished(char *mysql_query_string){

  // declare and reserve memory for the query string
  //char mysql_query_string[500];
  // build the query string
  // sprintf(mysql_query_string, "UPDATE `honeyssh`.`%s` SET `action` = 1 WHERE `id` = %llu ;",table, id);
  // execute the query
  MYSQL *mysql_con;

  // öffne die MYSQL Verbindung
  if (mysql_start(&mysql_con) != 0){
    return 1;
  }

  if (mysql_query(mysql_con, mysql_query_string)) {
        fprintf(stderr, "%s\n", mysql_error(mysql_con));
        return 1;
      }

  mysql_close(mysql_con);
  return 0;
}

int mysql_start(MYSQL **mysql_con){

*mysql_con = mysql_init(NULL);

if (*mysql_con == NULL){
    fprintf(stderr, "%s\n", mysql_error(*mysql_con));
    return 1;
}

if (mysql_real_connect(*mysql_con, MYSQL_HOST, MYSQL_USER, MYSQL_PWD, NULL, MYSQL_PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL){
    fprintf(stderr, "%s\n", mysql_error(*mysql_con));
    mysql_close(*mysql_con);
    return 1;
}

return 0;
}
