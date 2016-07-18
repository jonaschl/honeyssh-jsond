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

      CURL *curl = NULL;
      CURLcode res = CURLE_FAILED_INIT;
      char *errbuf;
      struct curl_slist *headers = NULL;

      errbuf = malloc(sizeof(char)* CURL_ERROR_SIZE);
      curl = curl_easy_init();
      if(!curl) {
        fprintf(stderr, "Error: curl_easy_init failed.\n");
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
      }

      curl_easy_setopt(curl, CURLOPT_PASSWORD, CURL_LOGIN_PASSWORD);
      curl_easy_setopt(curl, CURLOPT_USERNAME, CURL_LOGIN_USERNAME);
      curl_easy_setopt(curl, CURLOPT_CAINFO, CURL_CAPATH);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
      curl_easy_setopt(curl, CURLOPT_USERAGENT, "honeyssh-jsond-1.0");

      headers = curl_slist_append(headers, "Expect:");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

      // Curl soll die Länge des String der übermittelt werden soll(Das L hinter der 1 drückt nurd aus das es sich um einen long integer handelt)
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
      curl_easy_setopt(curl, CURLOPT_URL, CURL_LOGIN_HOST);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

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
        char *tmp = json_dumps(con.json, 0);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, tmp);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
          size_t len = strlen(errbuf);
          fprintf(stderr, "\nlibcurl: (%d) ", res);
          if(len)
          // Der zweite String bedeutet Wenn der errbuf an vorletzer stellen nicht ein /n hat dann füge es hinzu wenn nicht dann tue nichts.
          fprintf(stderr, "%s%s", errbuf, ((errbuf[len - 1] != '\n') ? "\n" : ""));
          fprintf(stderr, "%s\n\n", curl_easy_strerror(res));
        }

        printf("\n");
        printf("%s\n", tmp);
        printf("\n");
        free (tmp);

        if (res == 0){
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
      curl_finish(&curl, &headers, &errbuf);
    }
  }
  mysql_close(mysql_con);
  return 0;
}
