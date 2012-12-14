#include <libusbwrap.h>
#include <liberror.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
	int returnCode = 0;
	struct USBDevice *device = NULL;
	const char *error = NULL;
	const char *vp;
	if ( argc != 2 ) {
		fprintf(stderr, "Synopsis: %s <VID:PID>\n", argv[0]);
		FAIL(2);
	}
	if ( usbInitialise(0, &error) ) {
		FAIL(1);
	}
	vp = argv[1];
	if ( usbOpenDevice(vp, 1, 0, 0, &device, &error) ) {
		FAIL(3);
	}
	if ( usbPrintConfiguration(device, stdout, &error) ) {
		FAIL(4);
	}
cleanup:
	if ( device ) {
		usbCloseDevice(device, 0);
	}
	if ( error ) {
		fprintf(stderr, "%s: %s\n", argv[0], error);
		errFree(error);
	}
	return returnCode;
}
