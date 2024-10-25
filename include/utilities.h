#ifndef UTILS_H
#define UTILS_H

#include <argp.h>
#include <signal.h>
#include <string.h>
#include "tuya.h"
#include "ubus.h"

// Structure to hold the context for signal handling,
// which includes a Tuya MQTT client and a UBUS context.
typedef struct {
    tuya_mqtt_context_t *client;
    struct ubus_context *ctx;
} signal_context_t;

/**
 * Retrieves a pointer to the static signal context structure.
 * This structure holds information related to the MQTT client
 * and the UBUS context for signal handling.
 *
 * @return Pointer to the signal context structure.
 */
signal_context_t* get_signal_context();

/**
 * Structure to hold command-line arguments parsed from the input.
 */
struct arguments {
    char device_secret[25]; // Device secret for authentication.
    char product_id[25];    // Product ID associated with the device.
    char device_id[25];     // Unique device ID.
    int daemon;             // Flag indicating if the application should run as a daemon.
};

// Global variable to hold the parsed command-line arguments.
extern struct arguments arguments;

/**
 * Retrieves a pointer to the static signal context structure.
 * Duplicate of the earlier declaration, can be removed for clarity.
 *
 * @return Pointer to the signal context structure.
 */
signal_context_t* get_signal_context();

/**
 * Sets the signal context with the provided Tuya MQTT client
 * and UBUS context.
 *
 * @param client Pointer to the Tuya MQTT client context.
 * @param ctx Pointer to the UBUS context.
 */
void set_signal_context(tuya_mqtt_context_t *client, struct ubus_context *ctx);

/**
 * Command-line option definitions for argument parsing.
 */
__attribute__((unused)) static struct argp_option options[] = {
    {"device_secret", 'S', "DEVICE_SECRET", 0, "Direct passing of \"Device Secret\".", 0},
    {"product_id", 'P', "PRODUCT_ID", 0, "Direct passing of \"Product ID\"", 0},
    {"device_id", 'D', "DEVICE_ID", 0, "Direct passing \"Device ID\"", 0},
    {"daemon", 'd', 0, OPTION_ARG_OPTIONAL, "Direct passing \"Daemon\"", 0},
    {"help", 'h', 0, OPTION_ARG_OPTIONAL, "Args information", -1},
    {"usage", 'u', 0, OPTION_ARG_OPTIONAL, "Show usage", 0},
    {0} // End of options.
};

/**
 * Parses command-line options passed to the program.
 *
 * @param key The option key that was matched.
 * @param arg The argument associated with the option (if any).
 * @param state Pointer to the argp_state structure that holds the parsing state.
 * @return Error code (0 for success, ARGP_ERR_UNKNOWN for unknown option).
 */
error_t parse_opt(int key, char *arg, struct argp_state *state);

/**
 * Loads command-line arguments into the global arguments structure.
 *
 * @param argc The count of command-line arguments.
 * @param argv Array of command-line arguments.
 */
void load_arguments(int argc, char **argv);

/**
 * Handles signals received by the application.
 * This function gracefully disconnects the MQTT client,
 * frees the UBUS context, and exits the application.
 *
 * @param sig The signal number received.
 */
void handle_signal(int sig);

#endif
