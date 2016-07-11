#ifndef LOGIN_H

#define LOGIN_H

#include <jansson.h>
#include <stdint.h>
#include <mysql.h>
#include <my_global.h>
#include <time.h>
#include <curl/curl.h>

struct login {
  json_t *json;
  uint64_t id;
};

struct connection {
  json_t *json;
  uint64_t id;
  int action;
};

struct time {
  time_t start_time;
  time_t end_time;
};

int login_to_json(struct login *s, MYSQL_ROW row);
int connection_to_json(struct connection *s, MYSQL_ROW row);
int connection();
int connection_finished_date();
int login();
int mysql_start(MYSQL **mysql_con);
int db_set_finished(char *mysql_query_string);
int db_check_not_transfered(char *table);
int PostJSON(char *data, char *url, char *username, char *password);
int curl_finish(CURL **curl, struct curl_slist **headers, char **errbuf);
int set_start_time(struct time *s);
int set_end_time(struct time *s);
int get_sleeptime(struct time *s);

#endif
