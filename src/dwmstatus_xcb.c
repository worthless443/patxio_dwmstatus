#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <alsa/asoundlib.h>
#include <alsa/mixer.h>
#include <libnotify/notify.h>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>

#include <memused.h>
#include <batparse.h>
#include "dwmstatus.h"

static unsigned char keep_running = 1;

/**
 * handles all memory cleanups when program is told to stop
 */
int topower(int val, int by) {
	int ret=1;
	for(int i=0;i<=by;i++) ret*=val;
	return ret;
}

int mem_avil(char *used) {
	struct sysinfo info;
	if(sysinfo(&info)<0) return -1;
	sprintf(used,"%ld\n",(info.freeram * info.mem_unit)/topower(10,9));
	//memused();
	return 0;
}

static int convt_batt_to_int(const char *st) {
	char bat_buf[3];
	memset(bat_buf, '\0',3);
	for(int i=0,j=-1;i<strlen(st);++i) 
		if(st[i]>='0' && st[i]<='9')
			bat_buf[++j] = st[i];
	return atoi(bat_buf);
}

void sigint_handler()
{
	printf("no more refreshing\n");
	keep_running = 0;
	exit(1);
}
void sigabrt_handler()
{
	printf("something went wrong :(\n");
	keep_running = 0;
	exit(1);
}
void notify_send(const char *msg) {
	notify_init("Battery");
	NotifyNotification* n = notify_notification_new ("Battery",
                                 msg,
                                  0);
	notify_notification_show(n,0);
	notify_uninit();
	free(n);

}
extern int memused_wrapper();

int main()
{
	/* format the uptime into minutes */
	unsigned int up_minutes, up_hours, volume,notify = 0,charge = 0;
	char *battery_status, *system_time;
	long uptime, alsa_vol_unit;
	static char status[100];
	struct sysinfo s_info;

	/* display number */
	int screen_default_nbr;
	/* connect to display */
	xcb_connection_t *connection = xcb_connect(NULL, &screen_default_nbr);

	/* get the screen and the root window */
	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
	xcb_window_t root_window = 0;

	signal(SIGINT, sigint_handler);
	signal(SIGABRT, sigabrt_handler);

	if (screen)
		root_window = screen->root;

	//snd_mixer_t *alsa_handle = create_alsa_handle();
	//alsa_vol_unit = alsa_get_max_vol(alsa_handle) / 100;
	//volume = alsa_volume_percent(alsa_handle, alsa_vol_unit);

	/* use a counter to update less important info less often */
	unsigned int counter = STATUS_REFRESH_RATE_LOW;
	goto l2;
	while(1) {
		int mem_int = memused_wrapper();
		struct BatSt st;
		bat_parse(&st);
		//printf("%d\n", mem_int);
		sleep(1);
		break;
	}
l2:
	//goto l1;
	while (keep_running) {
		sleep(1);
		int mem_int;
		mem_int = memused_wrapper(); // this has to be before bat_parse()
		struct BatSt st;
		bat_parse(&st);
//		if (snd_mixer_wait(alsa_handle, STATUS_REFRESH_RATE_REG * 1000) == 0) {
//			snd_mixer_handle_events(alsa_handle);
//			volume = alsa_get_max_vol(alsa_handle) / 100;
//		}
//
		if (counter >= STATUS_REFRESH_RATE_LOW) {
			counter = 0;

			/* setup sysinfo with values */
			sysinfo(&s_info);

			/* get the uptime of machine in minutes */
			uptime = s_info.uptime / 60;
			/* format the uptime into minutes */
			up_hours = uptime / 60;
			up_minutes = uptime % 60;

			/* get the battery life */
			battery_status = power_status();

			/* get the system time */
			system_time = unixtime();
		}


		char memused[3];// = malloc(100);
		mem_avil(memused);
		if(st.ret && !charge) {
			notify_send("charging");
			charge = 1;
		}
		else if(!st.ret && charge) charge = 0;
		
		// not using it, don't need it, please don't emit warnings
		(void)up_hours;
		(void)up_minutes;

		if(convt_batt_to_int(battery_status)<10 && !notify) {
			notify_send("Low Battery");
			notify = 1;
		}
	

		snprintf(status, sizeof(status),
			"%0.02fGHz \u2502 %s(%d)GiB \u2502 %s%s \u2502 %s ",
			cpufreq(), memused,mem_int,st.ret ? "+" : "-",battery_status, system_time);

		/* changed root window name */

		xcb_change_property(connection,
			XCB_PROP_MODE_REPLACE,
			root_window,
			XCB_ATOM_WM_NAME,
			XCB_ATOM_STRING,
			8,
			sizeof(status),
			status);

		/* update display */
		xcb_flush(connection);

		/* refresh rate */
		counter += STATUS_REFRESH_RATE_REG;
	}
l1:

	//snd_mixer_close(alsa_handle);
	/* disconnect from X server */
	xcb_disconnect(connection);

	return 0;
}

//		printf("%s \u2502 %uMB \u2502 %u°C \u2502 [%u%%] \u2502 %s \n",
//			get_net_carrier(), get_meminfo(), get_temp(), battery_life, unixtime());
