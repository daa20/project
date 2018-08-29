#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


/* root(starting) -> user(runnig) */
static bool
switch_to_user(uid_t user_id, gid_t gp_id)
{

    /* Is not root ? */
    if ((user_id == 0) && (gp_id == 0)) {
        return false;
    }

    /* Is valid current user: root or target user. */
    gid_t gid = getgid();
    uid_t uid = getuid();
    if (((gid != 0)||(uid != 0)) && ((gid != gp_id)||(uid != user_id))) {
        return false;
    }

    if (uid != 0) {
        return true;
    }

    /* switch to target user. */
    if ((setgid(gp_id) < 0) || (setuid(user_id) < 0)) {
        return false;
    }

    return true;
}

int
main(int argc, char *const argv[])
{
    uid_t uid = getuid();
    uid_t euid = geteuid();

    fprintf(stdout, "current: userid: %d, effective userid: %d\n",
            uid, euid);
    if (switch_to_user(1000, 1000) == false) {
        fprintf(stderr, "switch to user: 1000 failed\n");
    }

    fprintf(stdout, "current: userid: %d, effective userid: %d\n",
            getuid(), geteuid());

    fprintf(stdout, "hello world!\n");
    return 0;
}
