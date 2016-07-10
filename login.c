#include <stdio.h>
#include <time.h>
#include <mysql.h>
#include <my_global.h>
#include "config.h"
#include <string.h>
#include "struct.h"
#include <jansson.h>
#include <stdlib.h>


int login(){

  MYSQL *mysql_con;

  // öffne die MYSQL Verbindung
  if (mysql_start(&mysql_con) != 0){
    return 1;
  }

  if (mysql_query(mysql_con, "SELECT `number`, `time`, `user`, `password`,  `session-id`, `id` FROM `honeyssh`.`login` WHERE `action` = 0")) {
  fprintf(stderr, "Query failed: %s\n", mysql_error(mysql_con));
  return 1;
  }
  else
  {

    MYSQL_RES *result = mysql_store_result(mysql_con);
    if (!result) {
      printf("Couldn't get results set: %s\n", mysql_error(mysql_con));
    }
    else
    {
      MYSQL_ROW row;
      int i = 0;
      char *finish = malloc(sizeof(char)*(1500*90+500));
      //printf("%d\n",(num_rows_result*90+500) );
      sprintf(finish, "");

      while ((row = mysql_fetch_row(result))){
        if (i > 1000){
          db_set_finished(finish);
          sprintf(finish, "");
          i=0;
        }
        struct login con;
        char *endp;
        con.id = strtoull(row[5], &endp, 0);
        login_to_json(&con, row);
        int curl_res = PostJSON(json_dumps(con.json, 0), CURL_LOGIN_HOST, CURL_LOGIN_USERNAME, CURL_LOGIN_PASSWORD);
        printf("\n");
        printf("%s\n", json_dumps(con.json, 0));
        printf("\n");
        if (curl_res == 0){
          sprintf(finish, "%sUPDATE `honeyssh`.`%s` SET `action` = 1 WHERE `id` = %llu; ",finish, "login", con.id);
          i++;
        }
        json_decref(con.json);
      }
      if (i != 0){
      db_set_finished(finish);
      }
      free(finish);
      mysql_free_result(result);
    }
  }
  mysql_close(mysql_con);
  return 0;
}
