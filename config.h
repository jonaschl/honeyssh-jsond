#ifndef CONFIG_H
#define CONFIG_H
#include <mysql.h>
#include <my_global.h>

// MYSQL Connection database
#define MYSQL_HOST  "mysql_host"
#define MYSQL_USER  "honeyssh"
#define MYSQL_PWD   "mysql_pass"
// logstash curl
//session
#define CURL_SESSION_HOST "logstash_session_host"
#define CURL_SESSION_USERNAME "logstash_session_user"
#define CURL_SESSION_PASSWORD "logstash_session_password"

//login
#define CURL_LOGIN_HOST "logstash_login_host"
#define CURL_LOGIN_USERNAME "logstash_login_user"
#define CURL_LOGIN_PASSWORD "logstash_login_password"

#define CURL_CAPATH "/opt/honeyssh-transfer-daemon/ca/root-pub.pem"


#define MAX_SESSION_TIME 86400
#define PERIODE_TIME 120

#endif
