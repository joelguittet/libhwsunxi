libhwsunxi
==

SUNXI Hardware Abstraction Interface Library.

The following interfaces are currently supported:
* gpio
* lradc
* pwm
* spi


Building
--

Clone sources:

	git clone https://github.com/myfreescalewebpage/libhwsunxi.git && cd libhwsunxi

Build dynamic library libhwsunxi.so:

	make

Build static library libhwsunxi.a:

	make static


Using
--

### GPIO

Example to read input pin PA0 with SUNXI_GPIO_PIN macro:

	sunxi_gpio_init();
	sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN('A', 0), SUNXI_GPIO_INPUT);
	unsigned int value = sunxi_gpio_input(SUNXI_GPIO_PIN('A', 0));

Example to read input pin PA0 with SUNXI_GPIO_PIN_PA0 macro:

	sunxi_gpio_init();
	sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN_PA0, SUNXI_GPIO_INPUT);
	unsigned int value = sunxi_gpio_input(SUNXI_GPIO_PIN_PA0);

Example to write output pin PA0 with SUNXI_GPIO_PIN:

	sunxi_gpio_init();
	sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN('A', 0), SUNXI_GPIO_OUTPUT);
	sunxi_gpio_output(SUNXI_GPIO_PIN('A', 0), 1);

Example to write output pin PA0 with SUNXI_GPIO_PIN_PA0:

	sunxi_gpio_init();
	sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN_PA0, SUNXI_GPIO_OUTPUT);
	sunxi_gpio_output(SUNXI_GPIO_PIN_PA0, 1);

### LRADC

Example to read LRADC channel 0:

	sunxi_lradc_init();
	sunxi_lradc_set_channel(SUNXI_LRADC_CH0);
	sunxi_lradc_set_key_mode(SUNXI_LRADC_KEY_MODE_NORMAL);
	sunxi_lradc_set_hold_on(SUNXI_LRADC_HOLD_ON_DISABLE);
	sunxi_lradc_set_sample_rate(SUNXI_LRADC_SAMPLE_RATE_250HZ);
	sunxi_lradc_enable();
	while (1) {
		unsigned int value;
		sunxi_lradc_read(SUNXI_LRADC_CH0, &value);
		printf("value=%d\n", value);
		sleep(1);
	}
    
### PWM

Example to generate a 1kHz signal with 30% duty cycle on the first PWM channel:

	sunxi_pwm_init();
	sunxi_pwm_disable(SUNXI_PWM_CH0);
	sunxi_pwm_set_polarity(SUNXI_PWM_CH0, SUNXI_PWM_POLARITY_NORMAL);
	sunxi_pwm_set_config(SUNXI_PWM_CH0, 1000000, 300000);
	sunxi_pwm_enable(SUNXI_PWM_CH0);

### SPI

Example to perform an exchange on SPI interface:

	int fd = sunxi_spi_open("/dev/spidev2.0");
	sunxi_spi_write_max_speed(fd, 1000000);
	sunxi_spi_transfer(fd, tx, rx, len);
	sunxi_spi_close(fd);


Contributing
--

All contributions are welcome :-)

Use Github Issues to report anomalies or to propose enhancements (labels are available to clearly identify what you are writing) and Pull Requests to submit modifications.


References
--

* http://linux-sunxi.org
