#ifndef __LOGGER_H__
#define __LOGGER_H__


// text color
#define BLK "\x1b[0;30m"
#define RED "\x1b[0;31m"
#define GRN "\x1b[0;32m"
#define YEL "\x1b[0;33m"
#define BLU "\x1b[0;34m"
#define MAG "\x1b[0;35m"
#define CYN "\x1b[0;36m"
#define WHT "\x1b[0;37m"
#define RST "\x1b[0m"


#define PRINT_INFO(_msg_)							printf("%s[+] %s%s\n", GRN, _msg_, RST)
#define PRINT_ERROR(_msg_)							printf("%s[*] %s%s\n", RED, _msg_, RST)
#define PRINT_RF_ERROR(_func_name_, _result_)		printf("%s[*] %s failed: %s(%d)%s\n", RED, #_func_name_, hackrf_error_name(_result_), _result_, RST)


#endif // __LOGGER_H__
