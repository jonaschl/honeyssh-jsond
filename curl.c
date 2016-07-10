#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "config.h"

int PostJSON(char *data, char *url, char *username, char *password)
{
  CURL *curl = NULL;
  CURLcode res = CURLE_FAILED_INIT;
  char errbuf[CURL_ERROR_SIZE];
  struct curl_slist *headers = NULL;

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "Error: curl_easy_init failed.\n");
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return -1;
  }

  curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
  curl_easy_setopt(curl, CURLOPT_USERNAME, username);
  curl_easy_setopt(curl, CURLOPT_CAINFO, CURL_CAPATH);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "honeyssh-jsond-1.0");

  headers = curl_slist_append(headers, "Expect:");
  headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
  // Curl soll die Länge des String der übermittelt werden soll(Das L hinter der 1 drückt nurd aus das es sich um einen long integer handelt)
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

  res = curl_easy_perform(curl);
  if(res != CURLE_OK) {
    size_t len = strlen(errbuf);
    fprintf(stderr, "\nlibcurl: (%d) ", res);
    if(len)
    // Der zweite String bedeutet Wenn der errbuf an vorletzer stellen nicht ein /n hat dann füge es hinzu wenn nicht dann tue nichts.
    fprintf(stderr, "%s%s", errbuf, ((errbuf[len - 1] != '\n') ? "\n" : ""));
    fprintf(stderr, "%s\n\n", curl_easy_strerror(res));
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return -1;
  }

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);
  return 0;
}
