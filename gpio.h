/*
 * SUNXI GPIO library interface
 * 
 * Example to read input pin GPA0:
 * sunxi_gpio_init();
 * sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN(A, 0), SUNXI_GPIO_INPUT);
 * unsigned int value = sunxi_gpio_input(SUNXI_GPIO_PIN(A, 0));
 * 
 * Example to write output pin GPA0:
 * sunxi_gpio_init();
 * sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN(A, 0), SUNXI_GPIO_OUTPUT);
 * sunxi_gpio_output(SUNXI_GPIO_PIN(A, 0), 1);
 */

#ifndef SUNXI_GPIO_H_
#define SUNXI_GPIO_H_


/****************************************************************************************/
/* Definitions                                                                          */
/****************************************************************************************/

/* SUNXI GPIO macro */
#define SUNXI_GPIO_PIN(port, pin)             ((port - 'A') << 5) + pin

/* SUNXI GPIO pin function configuration */
#define SUNXI_GPIO_INPUT                      0
#define SUNXI_GPIO_OUTPUT                     1
#define SUNXI_GPIO_PER                        2


/****************************************************************************************/
/* Prototypes                                                                           */
/****************************************************************************************/

int sunxi_gpio_init();
int sunxi_gpio_set_cfgpin(unsigned int pin, unsigned int val);
int sunxi_gpio_get_cfgpin(unsigned int pin);
int sunxi_gpio_input(unsigned int pin);
int sunxi_gpio_output(unsigned int pin, unsigned int val);


#endif
