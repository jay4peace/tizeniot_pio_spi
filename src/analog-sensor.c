#include <tizen.h>
#include <service_app.h>

static bool service_app_create(void *data)
{
    // Todo: add your code here.
    return true;
}

static void service_app_terminate(void *data)
{
    // Todo: add your code here.
    return;
}

static void service_app_control(app_control_h app_control, void *data)
{
    // Todo: add your code here.
    return;
}

int main(int argc, char* argv[])
{
    char ad[50] = {0,};
	service_app_lifecycle_callback_s event_callback;

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	return service_app_main(argc, argv, &event_callback, ad);
}
