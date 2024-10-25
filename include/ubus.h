#ifndef UBUS_H
#define UBUS_H

#include <libubox/blobmsg.h>
#include <libubox/blobmsg_json.h>
#include <libubus.h>
#include <stdio.h>
#include <syslog.h>

// Structure to hold memory data.
struct memData {
    int total;      // Total memory in bytes.
    int free;       // Free memory in bytes.
    int shared;     // Shared memory in bytes.
    int buffered;   // Buffered memory in bytes.
    int available;  // Available memory in bytes.
    int cached;     // Cached memory in bytes.
};

// Enum for general memory information.
static enum memory_general {
    MEMORY_DATA,
    __INFO_MAX,
};

// Enum for specific memory metrics.
static enum memory_specifics {
    TOTAL_MEMORY,
    FREE_MEMORY,
    SHARED_MEMORY,
    BUFFERED_MEMORY,
    AVAILABLE_MEMORY,
    CACHED_MEMORY,
    __MEMORY_MAX,
};

// Pointer to the ubus_context static structure which holds specific requests and items.
// Static variable for the blob buffer.
// static struct blob_buf b; // Uncomment if used elsewhere

// Result buffer from ubus invoke.
struct ubus_context* ubus_ctx();

// External pointer to memory data structure used for ubus operations.
extern struct memData *memory_data_ubus;

/**
 * Callback function to handle responses from an UBUS request.
 * It processes the response, formats the message into JSON,
 * parses specific fields, and extracts values.
 *
 * @param req Pointer to the UBUS request structure.
 * @param type The type of the request.
 * @param msg Pointer to the blob attribute containing the message data.
 * @return Status of the callback execution.
 */
int callback(struct ubus_request *req, int type, struct blob_attr *msg);

/**
 * Retrieves memory information from the ubus system info object.
 *
 * @param ctx Pointer to the ubus context.
 * @param id ID of the ubus object to query.
 * @param memory Pointer to the memory structure to populate.
 * @return Status of the memory retrieval operation.
 */
int get_memory_info(struct ubus_context *ctx, void *memory);

#endif