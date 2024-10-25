#include "../include/utilities.h"

struct arguments arguments;

error_t parse_opt(int key, char *arg, struct argp_state *state)
{   
    switch (key) {
        case 'D':
            strcpy(arguments.device_id, arg);
            break;

        case 'P':
            strcpy(arguments.product_id, arg);
            break;

        case 'S':
            strcpy(arguments.device_secret, arg);
            break;

        case 'd':
            arguments.daemon = 1;
            break;

        case 'h':
            argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP | OPTION_ARG_OPTIONAL);
            break;

        case 'u':
            argp_state_help(state, state->out_stream, ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK | OPTION_ARG_OPTIONAL);
            break;

        case ARGP_KEY_ARG:
            argp_usage(state);
            break;

        case ARGP_KEY_END:
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

void load_arguments(int argc, char **argv)
{   
    if (argc == 0){
        syslog(LOG_ERR, "No arguments passed");
        exit(EXIT_FAILURE);
    }
    static struct argp argp = {options, parse_opt, 0, 0};
    memset(&arguments, 0, sizeof(arguments)); 
    argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &arguments);
}

signal_context_t* get_signal_context() 
{
    static signal_context_t context;
    return &context;
}

void set_signal_context(tuya_mqtt_context_t *client, struct ubus_context *ctx) 
{
    signal_context_t *context = get_signal_context();
    context->client = client;
    context->ctx = ctx;
}

void handle_signal(int sig) 
{
    signal_context_t *context = get_signal_context(); 
    printf("Received termination signal %d. Exiting...\n", sig); 
    disconnect_deinit(context->client);
    ubus_free(context->ctx);
    closelog();
    exit(sig); 
}