#ifndef TUYA_H
#define TUYA_H
#include <signal.h>
#include <stdlib.h>
#include <tuya/mqtt_client_interface.h>
#include <tuya/tuyalink_core.h>
#include <syslog.h>
#include "ubus.h"
/*
Callback function called when the MQTT connection is established.
This function logs the connection event when the MQTT client successfully connects to
the broker.
@param context Pointer to the MQTT context structure, providing the necessary
context for the MQTT operations.
@param user_data Pointer to user-defined data passed to the callback function.
This can be used to carry additional information or state.
*/
void on_connected(tuya_mqtt_context_t* context, void* user_data);

/*
Callback function called when the MQTT connection is lost or disconnected.
This function is designed to handle the event of the MQTT client disconnecting
from the broker.
@param context Pointer to the MQTT context structure, providing the necessary
context for the MQTT operations.
@param user_data Pointer to user-defined data passed to the callback function.
This can be used to carry additional information or state.
*/
void on_disconnect(tuya_mqtt_context_t* context, void* user_data);

/*
Callback function called when an MQTT message is received.
This function is executed whenever the MQTT client receives a message from the broker.
It logs the received message data.
@param context Pointer to the MQTT context structure, providing the necessary
context for the MQTT operations.
@param user_data Pointer to user-defined data passed to the callback function.
This can be used to carry additional information or state.
@param msg Pointer to the received message structure containing the message data.
*/
void on_messages(tuya_mqtt_context_t* context, void* user_data, const tuyalink_message_t* msg);

/**
 * Initializing and connecting to MQTT.
 * *device_id device ID
 * *device_secret device Secret
 */
int connect_init(tuya_mqtt_context_t *client, char *device_id, char *device_secret);

/**
 * Deinitializing and disconnecting from MQTT
 */
void disconnect_deinit(tuya_mqtt_context_t *client);

/**
 * Stores memory data in memData structure.
 */
void invoke_tuya(tuya_mqtt_context_t *client, char *device_id, char *device_secret, struct memData *memory_data_ubus);

#endif