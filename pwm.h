/****************************************************************************************/
/* SUNXI PWM library interface                                                          */
/****************************************************************************************/

#ifndef SUNXI_PWM_H_
#define SUNXI_PWM_H_


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

/* SUNXI PWM channels */
#define SUNXI_PWM_CH0                           0
#define SUNXI_PWM_CH1                           1

/* SUNXI PWM polarity */
#define SUNXI_PWM_POLARITY_NORMAL               0
#define SUNXI_PWM_POLARITY_INVERSED             1


/****************************************************************************************/
/* Prototypes                                                                           */
/****************************************************************************************/

int sunxi_pwm_init();
int sunxi_pwm_set_polarity(unsigned int ch, unsigned int pol);
int sunxi_pwm_set_config(unsigned int ch, __u64 period_ns, __u64 duty_ns);
int sunxi_pwm_enable(unsigned int ch);
int sunxi_pwm_disable(unsigned int ch);


#endif
