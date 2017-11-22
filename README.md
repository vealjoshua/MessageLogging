Joshua Veal-Briscoe
02/19/2016

# 2.13 Exercise: Message Logging 
The exercise in this section describes a logging library that is similar to the list object defined in listlib.h and listlib.c of Program 2.6 and Program 2.7, respectively. 
The logging utility allows the caller to save a message at the end of a list. 
The logger also records the time that the message was logged. 
Program 2.11 shows the log.h file for the logger. 
The data_t structure and the addmsg function have the same respective roles as the list_t structure and adddata function of listlib.h. 
The savelog function saves the logged messages to a disk file. 
The clearlog function releases all the storage that has been allocated for the logged messages and empties the list of logged messages. 
The getlog function allocates enough space for a string containing the entire log, copies the log into this string, and returns a pointer to the string. 
It is the responsibility of the calling program to free this memory when necessary. 
If successful, addmsg and savelog return 0. A successful getlog call returns a pointer to the log string. 
If unsuccessful , addmsg and savelog return “1. 
An unsuccessful getlog call returns NULL . 
These three functions also set errno on failure. 

