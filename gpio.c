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

/****************************************************************************************/
/* Includes                                                                             */
/****************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include "gpio.h"


/****************************************************************************************/
/* Definitions                                                                          */
/****************************************************************************************/

/* SUNXI GPIO control IO base address */
#define SUNXI_GPIO_SW_PORTC_IO_BASE           0x01c20800

/* Macros used to configure GPIOs */
#define SUNXI_GPIO_BANK(pin)                  ((pin) >> 5)
#define SUNXI_GPIO_NUM(pin)                   ((pin) & 0x1F)
#define SUNXI_GPIO_CFG_INDEX(pin)             (((pin) & 0x1F) >> 3)
#define SUNXI_GPIO_CFG_OFFSET(pin)            ((((pin) & 0x1F) & 0x7) << 2)

/* SUNXI GPIO Bank */
struct sunxi_gpio_bank {
  unsigned int cfg[4];
  unsigned int dat;
  unsigned int drv[2];
  unsigned int pull[2];
};

/* SUNXI GPIO Interrupt control */
struct sunxi_gpio_int {
  unsigned int cfg[3];
  unsigned int ctl;
  unsigned int sta;
  unsigned int deb;
};

/* SUNXI GPIO Registers */
struct sunxi_gpio_reg {
  struct sunxi_gpio_bank gpio_bank[9];
  unsigned char res[0xbc];
  struct sunxi_gpio_int gpio_int;
};


/****************************************************************************************/
/* Global variables                                                                     */
/****************************************************************************************/

/* SUNXI GPIO base address */
static unsigned int sunxi_gpio_base_address = 0;


/****************************************************************************************/
/* Global variables                                                                     */
/****************************************************************************************/

/**
 * Initialize GPIO interface, to be called once
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_gpio_init() {
  
  int fd;
  unsigned int page_size, page_mask;
  unsigned int addr_start, addr_offset;
  void *pc;

  /* Open device */
  fd = open("/dev/mem", O_RDWR);
  if (fd < 0) {
    return -errno;
  }
  
  /* Map to device */
  page_size = sysconf(_SC_PAGESIZE);
  page_mask = (~(page_size-1));
  addr_start = SUNXI_GPIO_SW_PORTC_IO_BASE & page_mask;
  addr_offset = SUNXI_GPIO_SW_PORTC_IO_BASE & ~page_mask;
  pc = (void *)mmap(0, page_size * 2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr_start);
  if (pc == MAP_FAILED) {
    return -errno;
  }

  /* Retrieve base address used later in this library */
  sunxi_gpio_base_address = (unsigned int)pc;
  sunxi_gpio_base_address += addr_offset; 

  /* Close device */
  close(fd);
  
  return 0;
}

/**
 * Set pin configuration
 * @param pin Expected pin, see SUNXI_GPIO_PIN macro
 * @param val Expected function, SUNXI_GPIO_INPUT or SUNXI_GPIO_OUTPUT
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_gpio_set_cfgpin(unsigned int pin, unsigned int val) {
  
  unsigned int cfg;
  unsigned int bank = SUNXI_GPIO_BANK(pin);
  unsigned int index = SUNXI_GPIO_CFG_INDEX(pin);
  unsigned int offset = SUNXI_GPIO_CFG_OFFSET(pin);

  /* Check if initialization has been performed */
  if (sunxi_gpio_base_address == 0) {
    return -EPERM;
  }

  /* Set pin configuration */
  struct sunxi_gpio_bank *pio = &((struct sunxi_gpio_reg *)sunxi_gpio_base_address)->gpio_bank[bank];
  cfg = *(&pio->cfg[0] + index);
  cfg &= ~(0xf << offset);
  cfg |= val << offset;
  *(&pio->cfg[0] + index) = cfg;

  return 0;
}

/**
 * Get pin configuration
 * @param pin Expected pin, see SUNXI_GPIO_PIN macro
 * @return Pin function if the function succeeds, error code otherwise
 */
int sunxi_gpio_get_cfgpin(unsigned int pin) {

  unsigned int cfg;
  unsigned int bank = SUNXI_GPIO_BANK(pin);
  unsigned int index = SUNXI_GPIO_CFG_INDEX(pin);
  unsigned int offset = SUNXI_GPIO_CFG_OFFSET(pin);
  
  /* Check if initialization has been performed */
  if (sunxi_gpio_base_address == 0) {
    return -EPERM;
  }
  
  /* Get pin configuration */
  struct sunxi_gpio_bank *pio = &((struct sunxi_gpio_reg *)sunxi_gpio_base_address)->gpio_bank[bank];
  cfg = *(&pio->cfg[0] + index);
  cfg >>= offset;
  return (cfg & 0xf);
}

/**
 * Get pin input value
 * @param pin Expected pin, see SUNXI_GPIO_PIN macro
 * @return Pin input value if the function succeeds, error code otherwise
 */
int sunxi_gpio_input(unsigned int pin) {
  
  unsigned int dat;
  unsigned int bank = SUNXI_GPIO_BANK(pin);
  unsigned int num = SUNXI_GPIO_NUM(pin);
  
  /* Check if initialization has been performed */
  if (sunxi_gpio_base_address == 0) {
    return -EPERM;
  }
  
  /* Get pin value */
  struct sunxi_gpio_bank *pio = &((struct sunxi_gpio_reg *)sunxi_gpio_base_address)->gpio_bank[bank];
  dat = *(&pio->dat);
  dat >>= num;
  return (dat & 0x1);
}

/**
 * Set pin output value
 * @param pin Expected pin, see SUNXI_GPIO_PIN macro
 * @param val Expected pin value, 0 or 1
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_gpio_output(unsigned int pin, unsigned int val) {

  unsigned int bank = SUNXI_GPIO_BANK(pin);
  unsigned int num = SUNXI_GPIO_NUM(pin);
  
  /* Check if initialization has been performed */
  if (sunxi_gpio_base_address == 0) {
    return -EPERM;
  }
  
  /* Set pin value */
  struct sunxi_gpio_bank *pio = &((struct sunxi_gpio_reg *)sunxi_gpio_base_address)->gpio_bank[bank];
  if (val)
    *(&pio->dat) |= 1 << num;
  else
    *(&pio->dat) &= ~(1 << num);
  return 0;
}
