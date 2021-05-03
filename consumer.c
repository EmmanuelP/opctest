/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */
/*
 * A simple server instance which registers with the discovery server (see server_lds.c).
 * Before shutdown it has to unregister itself.
 */

#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/client_config_default.h>
#include <open62541/client_subscriptions.h>

#include <signal.h>
#include <stdlib.h>

UA_Boolean running = true;

static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

static void
frame_cb (UA_Client *client, UA_UInt32 subId, void *subContext,
	  UA_UInt32 monId, void *monContext, UA_DataValue *value)
{
	static int last_counter = -1;

	if (UA_Variant_hasScalarType (&value->value, &UA_TYPES[UA_TYPES_BYTESTRING])) {
		UA_ByteString *byte_string = (UA_ByteString *) value->value.data;
		int counter;

		counter = * ((int *) byte_string->data);

		printf ("[%d] Received %lu bytes\n", counter, byte_string->length);

		if (counter - last_counter != 1 && last_counter != -1) {
			printf ("	*****************\n");
			printf ("	***** Error *****\n");
			printf ("	*****************\n");
		}
		last_counter = counter;
	}
}

int
main(int argc, char **argv)
{
	UA_Client *client;
	UA_ClientConfig *config;
	UA_CreateSubscriptionRequest request;
	UA_CreateSubscriptionResponse response;
	UA_MonitoredItemCreateRequest monitoring_request;

	signal(SIGINT, stopHandler);
	signal(SIGTERM, stopHandler);

	client = UA_Client_new();
	config = UA_Client_getConfig (client);
	UA_ClientConfig_setDefault(config);

	if (argc > 1)
		UA_Client_connect (client, argv[1]);
	else
		UA_Client_connect (client, "opc.tcp://localhost:4840/");

	request = UA_CreateSubscriptionRequest_default();
	request.requestedPublishingInterval = 500.0;
	response = UA_Client_Subscriptions_create(client, request, NULL, NULL, NULL);

	monitoring_request = UA_MonitoredItemCreateRequest_default (UA_NODEID_STRING (1, "frame"));
	monitoring_request.requestedParameters.queueSize = 10;
	monitoring_request.requestedParameters.samplingInterval = 250;
	monitoring_request.monitoringMode = UA_MONITORINGMODE_REPORTING;
	UA_Client_MonitoredItems_createDataChange (client,
						   response.subscriptionId,
						   UA_TIMESTAMPSTORETURN_SOURCE,
						   monitoring_request, NULL,
						   frame_cb, NULL);

	while (running) {
		UA_Client_run_iterate (client, 0);
		usleep (100);
	}

	UA_Client_delete (client);

	return EXIT_SUCCESS;
}
