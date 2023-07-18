#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#define DEBUG 0

#define EXIT_CODE -1
#define DISCONNECT_ACTION 0
#define CONNECT_ACTION 1
#define READ_ACTION 2
#define UPDATE_ACTION 3
#define WRITE_ACTION 4
#define DELETE_ACTION 5

/*****Special Actions*****/
#define READ_ALL 0
/*****Special Actions*****/

#define FILEMODE "rb+"

enum exit_status {
    NULL_PTR = 1,
    USER_STOP,
};

enum io_status {
    EOF_ = 100,
};

#endif
