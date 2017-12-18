libhwsunxi
==

SUNXI Hardware Abstraction Interface Library.

The following interfaces are currently supported:
* gpio


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

Example to read input pin PA0:

	sunxi_gpio_init();
	sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN('A', 0), SUNXI_GPIO_INPUT);
	unsigned int value = sunxi_gpio_input(SUNXI_GPIO_PIN('A', 0));

Example to write output pin PA0:

	sunxi_gpio_init();
	sunxi_gpio_set_cfgpin(SUNXI_GPIO_PIN('A', 0), SUNXI_GPIO_OUTPUT);
	sunxi_gpio_output(SUNXI_GPIO_PIN('A', 0), 1);


Contributing
--

All contributions are welcome :-)

Use Github Issues to report anomalies or to propose enhancements (labels are available to clearly identify what you are writing) and Pull Requests to submit modifications.


References
--

* http://linux-sunxi.org
