#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <stdlib.h>

static volatile UA_Boolean running = true;

static int size_mb = 10;

static void
stopHandler (int sig) {
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");

	running = false;
}

void
callback (UA_Server *server, void *data)
{
	UA_ByteString byte_string;
	UA_Variant value;
	static int counter = 0;

	byte_string.length = size_mb * 1024* 1024;
	byte_string.data = malloc (byte_string.length);

	*((int *) byte_string.data) = counter++;

	printf ("Send %lu bytes\n", byte_string.length);

	UA_Variant_setScalar (&value, &byte_string, &UA_TYPES[UA_TYPES_BYTESTRING]);

	UA_Server_writeValue (server,
			      UA_NODEID_STRING(1, "frame"),
			      value);

	free (byte_string.data);
}

int
main (int argc, char **argv)
{
	UA_Server *server;
	UA_ServerConfig *config;

	signal(SIGINT, stopHandler);
	signal(SIGTERM, stopHandler);

	if (argc > 1)
		size_mb = atoi (argv[1]);

	server = UA_Server_new ();
	config = UA_Server_getConfig (server);
	UA_ServerConfig_setDefault (config);

	UA_VariableAttributes attribute = UA_VariableAttributes_default;
	UA_ByteString byteStringTypeVal = UA_BYTESTRING_NULL;

	attribute.displayName = UA_LOCALIZEDTEXT("en-US", "Frame");
	attribute.accessLevel = UA_ACCESSLEVELMASK_READ;
	attribute.historizing = false;
	UA_Variant_setScalar(&attribute.value, &byteStringTypeVal, &UA_TYPES[UA_TYPES_BYTESTRING]);

	UA_Server_addVariableNode (server,
				   UA_NODEID_STRING(1, "frame"),
				   UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
				   UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
				   UA_QUALIFIEDNAME(1, "frame"),
				   UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
				   attribute, NULL, NULL);

	UA_Server_addRepeatedCallback (server,  callback, NULL, 1000, NULL);

	UA_Server_run (server, &running);

	UA_Server_delete (server);

	return EXIT_SUCCESS;
}
