#include "../include/tuya.h"
#include "../include/tuya_cacert.h"

void on_connected(tuya_mqtt_context_t* context, void* user_data) 
{
    syslog(LOG_INFO, "Tuya Connected.\n\n");
}

void on_disconnect(tuya_mqtt_context_t* context, void* user_data)
{
    syslog(LOG_INFO, "Tuya Disconnected.\n\n");
}

void on_messages(tuya_mqtt_context_t* context, void* user_data, const tuyalink_message_t* msg) 
{   
    syslog(LOG_INFO, "Received message: %s\n", msg->data_string);
}

int connect_init(tuya_mqtt_context_t *client, char *device_id, char *device_secret)
{   
    int ret = 0;
    ret = tuya_mqtt_init(client, &(const tuya_mqtt_config_t) {
        .host = "m2.tuyacn.com",
        .port = 8883,
        .cacert = tuya_cacert_pem,
        .cacert_len = sizeof(tuya_cacert_pem),
        .device_id = device_id,
        .device_secret = device_secret,
        .keepalive = 60,
        .timeout_ms = 2000,
        .on_connected = on_connected,
        .on_disconnect = on_disconnect,
        .on_messages = on_messages
    });
    if (ret != 0){
        syslog(LOG_ERR, "Error trying to initialize tuya_mqtt\n\n");
        return ret;
    }
    ret = tuya_mqtt_connect(client);
    if (ret != 0){
        syslog(LOG_ERR, "Error trying to connect to tuya_mqtt\n\n");
        tuya_mqtt_deinit(client);
        return ret;
    }
    return 0;
}

void invoke_tuya(tuya_mqtt_context_t *client, char *device_id, char *device_secret, struct memData *memory_data_ubus)
{ 
    cJSON *main = cJSON_CreateObject();
    if (main == NULL)
        return;
    cJSON_AddNumberToObject(main, "total_mem", memory_data_ubus->total);
    cJSON_AddNumberToObject(main, "free_mem", memory_data_ubus->free);
    cJSON_AddNumberToObject(main, "shared_mem", memory_data_ubus->shared);
    cJSON_AddNumberToObject(main, "buffered_mem", memory_data_ubus->buffered);
    cJSON_AddNumberToObject(main, "available_mem", memory_data_ubus->available);
    cJSON_AddNumberToObject(main, "cached_mem", memory_data_ubus->cached);
    char *payload = cJSON_PrintUnformatted(main);
    tuyalink_thing_property_report(client, device_id, payload);
    free(payload);
    cJSON_Delete(main);
}

void disconnect_deinit(tuya_mqtt_context_t *client)
{   
    tuya_mqtt_disconnect(client);
    tuya_mqtt_deinit(client);
}