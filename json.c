#include <stdio.h>
#include <time.h>
#include <mysql.h>
#include <my_global.h>
#include "config.h"
#include <string.h>
#include <jansson.h>
#include "struct.h"

int login_to_json(struct login *s, MYSQL_ROW row) {

  s->json = json_object();
  json_object_set_new(s->json, "number", json_string(row[0]));
  json_object_set_new(s->json, "time", json_string(row[1]));
  json_object_set_new(s->json, "username", json_string(row[2]));
  json_object_set_new(s->json, "password", json_string(row[3]));
  json_object_set_new(s->json, "session-id", json_string(row[4]));
  json_object_set_new(s->json, "id", json_string(row[5]));
  return 0;
}

int connection_to_json(struct connection *s, MYSQL_ROW row) {

  s->json = json_object();
  json_object_set_new(s->json, "session-id", json_string(row[0]));
  json_object_set_new(s->json, "ip-adress", json_string(row[1]));
  json_object_set_new(s->json, "start-time", json_string(row[2]));
  json_object_set_new(s->json, "end-time", json_string(row[3]));
  //json_object_set_new(s->json, "duration", json_integer(get_duration_session(row[2],row[3])));
  if(strcmp(row[3], "1970-01-01 00:00:00") != 0) {
    char *endp;
    int duration = 0;
    uint64_t start = 0;
    uint64_t end = 0;
    start = strtoull(row[11], &endp, 0);
    end = strtoull(row[12], &endp, 0);
    duration =end - start;
    json_object_set_new(s->json, "duration", json_integer(duration));
  }
  json_object_set_new(s->json, "banner", json_string(row[4]));
  json_object_set_new(s->json, "cipher-in", json_string(row[5]));
  json_object_set_new(s->json, "cipher-out", json_string(row[6]));
  json_object_set_new(s->json, "protocol-version", json_string(row[7]));
  json_object_set_new(s->json, "openssh-version", json_string(row[8]));
  json_object_set_new(s->json, "potmode", json_string(row[9]));
  json_object_set_new(s->json, "id", json_string(row[10]));
  return 0;
}
