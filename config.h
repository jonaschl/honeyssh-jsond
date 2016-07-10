#ifndef CONFIG_H
#define CONFIG_H
#include <mysql.h>
#include <my_global.h>

// MYSQL Connection database
#define MYSQL_HOST  "192.168.103.125"
#define MYSQL_USER  "honeyssh"
#define MYSQL_PWD   "bMYC5yZma9LrVHR9"
#define MYSQL_MAX_CONNECTIONS 140
#define MYSQL_MAX_CONNECTIONS_WAIT 2
// logstash curl
//session
#define CURL_SESSION_HOST "http://bree:31313"
#define CURL_SESSION_USERNAME "user"
#define CURL_SESSION_PASSWORD "pass"

//login
#define CURL_LOGIN_HOST "http://bree:31314"
#define CURL_LOGIN_USERNAME "user"
#define CURL_LOGIN_PASSWORD "pass"

#define CURL_CAPATH "/home/jonatan/git/honeyssh-transferdaemon/root-pub.pem"

//login
// command


#define MAX_SESSION_TIME 86400
#define PERIODE_TIME 120

#endif
