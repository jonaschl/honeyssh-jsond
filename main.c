#include "config.h"
#include "struct.h"
#include <curl/curl.h>


int main(){
  // breitet alles für die weitere Nutzung von Curl vor (nicht threadsafe), sollte beim start des programmens aufgerufen werden.
 if(curl_global_init(CURL_GLOBAL_ALL)) {
   fprintf(stderr, "Fatal: The initialization of libcurl has failed.\n");
   return 1;
 }
 if(mysql_library_init(0, NULL, NULL)){
    fprintf(stderr, "Fatal: The initialization of libmysql has failed.\n");
    return 1;
 }
 // setzt eine funktion die beim ende aufgerufen werden soll (Folglich wird die funktion curl_global_cleanup() beim ende des Programms aufgerufen um alle ressourcen die von Curl benutzt wurden wieder freizugeben. )
 if(atexit(curl_global_cleanup)) {
   fprintf(stderr, "Fatal: atexit failed to register curl_global_cleanup.\n");
   curl_global_cleanup();
   mysql_library_end();
   return 1;
 }

 if(atexit(mysql_library_end)) {
   fprintf(stderr, "Fatal: atexit failed to register mysql_library_end.\n");
   mysql_library_end();
   return 1;
 }
struct time stime;

 while (1) {
   set_start_time(&stime);
   connection_finished_date();

   int check = db_check_not_transfered("connection");
   if ( check == 0){
     printf("Nothing to transfer\n");
   }
   else
   {
     printf("Transfer %d data sets\n",check );
     connection();
   }


   check = db_check_not_transfered("login");
  if ( check == 0){
    printf("Nothing to transfer");
  }
  else
  {
    printf("Transfer %d data sets\n",check );
    login();
  }

  set_end_time(&stime);
  int sleeptime = get_sleeptime(&stime);
  printf("Wait %d seconds\n", sleeptime);
  sleep(sleeptime);

 }
 return 0;
 }




//login();
