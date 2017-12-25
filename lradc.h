/****************************************************************************************/
/* SUNXI LRADC library interface                                                        */
/****************************************************************************************/

#ifndef SUNXI_LRADC_H_
#define SUNXI_LRADC_H_


/****************************************************************************************/
/* Includes                                                                             */
/****************************************************************************************/

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


/****************************************************************************************/
/* Definitions                                                                          */
/****************************************************************************************/

/* SUNXI LRADC channels */
#define SUNXI_LRADC_CH0                         0
#define SUNXI_LRADC_CH1                         1
#define SUNXI_LRADC_CH0_CH1                     2

/* SUNXI LRADC key mode */
#define SUNXI_LRADC_KEY_MODE_NORMAL             0
#define SUNXI_LRADC_KEY_MODE_SINGLE             1
#define SUNXI_LRADC_KEY_MODE_CONTINUE           2

/* SUNXI LRADC hold on */
#define SUNXI_LRADC_HOLD_ON_DISABLE             0
#define SUNXI_LRADC_HOLD_ON_ENABLE              1

/* SUNXI LRADC level B voltage */
#define SUNXI_LRADC_LEVEL_B_1_9VOLT             0
#define SUNXI_LRADC_LEVEL_B_1_8VOLT             1
#define SUNXI_LRADC_LEVEL_B_1_7VOLT             2
#define SUNXI_LRADC_LEVEL_B_1_6VOLT             3

/* SUNXI LRADC sample rate */
#define SUNXI_LRADC_SAMPLE_RATE_250HZ           0
#define SUNXI_LRADC_SAMPLE_RATE_125HZ           1
#define SUNXI_LRADC_SAMPLE_RATE_62_5HZ          2
#define SUNXI_LRADC_SAMPLE_RATE_32_25HZ         3


/****************************************************************************************/
/* Prototypes                                                                           */
/****************************************************************************************/

int sunxi_lradc_init();
int sunxi_lradc_set_first_convert_delay(unsigned int delay);
int sunxi_lradc_set_channel(unsigned int ch);
int sunxi_lradc_set_continue_time_select(unsigned int time);
int sunxi_lradc_set_key_mode(unsigned int key_mode);
int sunxi_lradc_set_level_a_b_cnt(unsigned int cnt);
int sunxi_lradc_set_hold_on(unsigned int hold_on);
int sunxi_lradc_set_level_b_volt(unsigned int volt);
int sunxi_lradc_set_sample_rate(unsigned int sample_rate);
int sunxi_lradc_read(unsigned int ch, unsigned int *val);
int sunxi_lradc_enable();
int sunxi_lradc_disable();


#endif
