#include "include/ftpserver.h"
#include "include/network.h"

__uint16_t ftp_server()
{
    __uint8_t display = TRUE;
    while (TRUE)
    {
        if (display)
        {
            PRINT_APP_HEADER(VERSION);
            printf("\r\n");
            if (check_network_connection() > 0)
            {
                // No network connection. Back to main menu
                return 0;
            }
            printf("\r\n");
            printf("\r\n");

#ifndef _DEBUG
            if (check_network_connection() > 0)
            {
                // No network connection. Back to main menu
                return 0;
            }
#endif

            printf("FTP Server:\r\n");
            printf("\r\n");
            printf("\r\n");
            printf("\r\n");
            printf("Options:\r\n\n");
            printf("[U] - Set Username\r\n");
            printf("[P] - Set Password\r\n");
            printf("\r\n[S] - Start Server\r\n");
            printf("\n");
            printf("Press an option key or [ESC] to exit:");

            flush_kbd();
            display = FALSE;
        }

        if (Bconstat(2) != 0)
        {
            int fullkey = Bconin(2);
            __uint16_t key = fullkey & 0xFF;
            if (fullkey == KEY_ESC)
            {
                // Back to main menu
                return 0; // 0 return to menu, no ask
            }
            if ((key == 'S') || (key == 's'))
            {
                send_sync_command(FTPSERVER, NULL, 0, RTC_WAIT_TIME, TRUE);
                __uint16_t err = read_config();

                display = TRUE;
            }
        }
    }
}
