#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv, char **envp){
  
  gid_t gid;
  uid_t uid;

  gid = getegid();
  uid = geteuid();

  setregid(gid,gid,gid);
  setreuid(uid,uid,uid);

  return 0;
}
