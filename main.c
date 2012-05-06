#include <libusbwrap.h>
#ifdef WIN32
	#include <lusb0_usb.h>
#else
	#include <usb.h>
#endif
#include <liberror.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
	int returnCode;
	struct usb_dev_handle *device = NULL;
	const char *error = NULL;
	uint16 vid, pid;
	usbInitialise();
	if ( argc != 3 ) {
		fprintf(stderr, "Synopsis: %s <vid> <pid>\n", argv[0]);
		FAIL(1);
	}
	vid = (uint16)strtoul(argv[1], NULL, 16);
	pid = (uint16)strtoul(argv[2], NULL, 16);
	if ( usbOpenDevice(vid, pid, 1, 0, 0, &device, &error) ) {
		FAIL(2);
	}
	if ( usbPrintConfiguration(device, stdout, &error) ) {
		FAIL(3);
	}
	returnCode = 0;
cleanup:
	if ( device ) {
		usb_release_interface(device, 0);
		usb_close(device);
	}
	if ( error ) {
		fprintf(stderr, "%s: %s\n", argv[0], error);
		errFree(error);
	}
	return 0;
}
