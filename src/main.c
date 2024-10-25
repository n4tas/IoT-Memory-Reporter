#include "../include/ubus.h"
#include "../include/tuya.h"
#include "../include/utilities.h"
#include "../include/daemon.h"

int main(int argc, char **argv){

    struct ubus_context *ctx = NULL;
    tuya_mqtt_context_t client_instance;
    tuya_mqtt_context_t *client = &client_instance;
    ctx = ubus_ctx();
    if (ctx == NULL)
        return 1;
    if (connect_init(client, arguments.device_id, arguments.device_secret) != 0){
        ubus_free(ctx);
        return 1;
    }
    set_signal_context(client, ctx);
    signal(SIGINT, handle_signal);
    signal(SIGCONT, handle_signal);
    signal(SIGSEGV, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGCHLD, handle_signal);
    signal(SIGHUP, handle_signal);
    openlog ("iotmemd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    load_arguments(argc, argv);
    if (arguments.daemon == 1)
        daemon_initialize();
    struct memData memory = { 0 };
    for (;;){
        if (get_memory_info(ctx, &memory) != 0){
            disconnect_deinit(client);
            return -1;
        }
        invoke_tuya(client, arguments.device_id, arguments.device_secret, &memory);
        sleep(5); // Send memory data every 5 seconds.
    }
    disconnect_deinit(client);
    ubus_free(ctx);
    closelog();
}