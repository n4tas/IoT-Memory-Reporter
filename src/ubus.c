#include "../include/ubus.h"

struct memData *memory_data_ubus;

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
	[MEMORY_DATA] = { .name = "memory", .type = BLOBMSG_TYPE_TABLE },
};

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
	[TOTAL_MEMORY] = { .name = "total", .type = BLOBMSG_TYPE_INT64 },
	[FREE_MEMORY] = { .name = "free", .type = BLOBMSG_TYPE_INT64 },
	[SHARED_MEMORY]	= { .name = "shared", .type = BLOBMSG_TYPE_INT64 },
	[BUFFERED_MEMORY] = { .name = "buffered", .type = BLOBMSG_TYPE_INT64 },
    [AVAILABLE_MEMORY] = { .name = "available", .type = BLOBMSG_TYPE_INT64 },
    [CACHED_MEMORY] = { .name = "cached", .type = BLOBMSG_TYPE_INT64 }
};

struct ubus_context* ubus_ctx()
{
    struct ubus_context *ctx = ubus_connect(NULL);
	if (!ctx) 
        return NULL;
    return ctx;
}

int callback(struct ubus_request *req, int type, struct blob_attr *msg)
{   
    memory_data_ubus = (struct memData *)req->priv;
	struct blob_attr *tb[__INFO_MAX];
	struct blob_attr *memory[__MEMORY_MAX];
    blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg),
		      blob_len(msg));
	if (!tb[MEMORY_DATA]) 
		return -1;
    blobmsg_parse(memory_policy, __MEMORY_MAX, memory, blobmsg_data(tb[MEMORY_DATA]), 
                blobmsg_data_len(tb[MEMORY_DATA]));
    if (!memory[MEMORY_DATA]) 
		return -1;
	memory_data_ubus->total = blobmsg_get_u64(memory[TOTAL_MEMORY]);
	memory_data_ubus->free = blobmsg_get_u64(memory[FREE_MEMORY]);
	memory_data_ubus->shared = blobmsg_get_u64(memory[SHARED_MEMORY]);
	memory_data_ubus->buffered = blobmsg_get_u64(memory[BUFFERED_MEMORY]);
    memory_data_ubus->available = blobmsg_get_u64(memory[AVAILABLE_MEMORY]);
    memory_data_ubus->cached = blobmsg_get_u64(memory[CACHED_MEMORY]);  
}

int get_memory_info(struct ubus_context *ctx, void *memory)
{
	if ((ubus_lookup_id(ctx, "system", 0)) || (ubus_invoke(ctx, 0, "info", NULL, callback, memory, 3000))){
            return -1;
            ubus_free(ctx);
			closelog();
    }
	return 0;
}