/****************************************************************************************/
/* SUNXI LRADC library interface                                                        */
/****************************************************************************************/

/****************************************************************************************/
/* Includes                                                                             */
/****************************************************************************************/

#include "lradc.h"


/****************************************************************************************/
/* Definitions                                                                          */
/****************************************************************************************/

/* SUNXI LRADC control IO base address */
#define SUNXI_LRADC_IO_BASE                     0x01c22800

/* Macros used to configure LRADC */
#define SUNXI_LRADC_FIRST_CONVERT_DELAY(delay)  (delay << 24)
#define SUNXI_LRADC_CHANNEL(ch)                 (ch << 22)
#define SUNXI_LRADC_CONTINUE_TIME_SELECT(time)  (time << 16)
#define SUNXI_LRADC_KEY_MODE(key_mode)          (key_mode << 12)
#define SUNXI_LRADC_LEVEL_A_B_CNT(cnt)          (cnt << 8)
#define SUNXI_LRADC_HOLD_ON                     (1 << 6)
#define SUNXI_LRADC_LEVEL_B_VOLT(volt)          (volt << 4)
#define SUNXI_LRADC_SAMPLE_RATE(sample_rate)    (sample_rate << 2)
#define SUNXI_LRADC_EN                          (1 << 0)

/* SUNXI LRADC Registers */
struct sunxi_lradc_reg {
  volatile unsigned int ctrl;
  volatile unsigned int intc;
  volatile unsigned int ints;
  volatile unsigned int data[2];
};


/****************************************************************************************/
/* Global variables                                                                     */
/****************************************************************************************/

/* SUNXI LRADC registers */
static volatile struct sunxi_lradc_reg *sunxi_lradc_registers = NULL;


/****************************************************************************************/
/* Exported functions                                                                   */
/****************************************************************************************/

/**
 * Initialize LRADC interface, to be called once
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_init() {
  
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
  addr_start = SUNXI_LRADC_IO_BASE & page_mask;
  addr_offset = SUNXI_LRADC_IO_BASE & ~page_mask;
  pc = mmap(NULL, (((sizeof(struct sunxi_lradc_reg) + addr_offset) / page_size) + 1) * page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr_start);
  if (pc == MAP_FAILED) {
    return -errno;
  }

  /* Retrieve registers address used later in this library */
  sunxi_lradc_registers = (struct sunxi_lradc_reg *)(pc + addr_offset);

  /* Close device */
  close(fd);
  
  return 0;
}

/**
 * Set LRADC first convert delay
 * @param delay LRADC first convert delay (0 to 255)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_first_convert_delay(unsigned int delay) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC first convert delay */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_FIRST_CONVERT_DELAY(255);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_FIRST_CONVERT_DELAY(delay);
  
  return 0;
}

/**
 * Set LRADC channel
 * @param ch LRADC channel, SUNXI_LRADC_CH0, SUNXI_LRADC_CH1 or SUNXI_LRADC_CH0_CH1
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_channel(unsigned int ch) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC channel */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_CHANNEL(3);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_CHANNEL(ch);
  
  return 0;
}

/**
 * Set LRADC continue time select
 * @param time LRADC continue time select (0 to 15)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_continue_time_select(unsigned int time) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC continue time select */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_CONTINUE_TIME_SELECT(15);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_CONTINUE_TIME_SELECT(time);
  
  return 0;
}

/**
 * Set LRADC key mode
 * @param key_mode LRADC key mode, SUNXI_LRADC_KEY_MODE_NORMAL, SUNXI_LRADC_KEY_MODE_SINGLE or SUNXI_LRADC_KEY_MODE_CONTINUE
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_key_mode(unsigned int key_mode) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC key mode */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_KEY_MODE(3);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_KEY_MODE(key_mode);
  
  return 0;
}

/**
 * Set LRADC level A to level B cnt
 * @param cnt LRADC level A to level B cnt (0 to 15)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_level_a_b_cnt(unsigned int cnt) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC level A to level B cnt */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_LEVEL_A_B_CNT(15);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_LEVEL_A_B_CNT(cnt);
  
  return 0;
}

/**
 * Set LRADC hold on
 * @param hold_on LRADC hold on, SUNXI_LRADC_HOLD_ON_DISABLE or SUNXI_LRADC_HOLD_ON_ENABLE
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_hold_on(unsigned int hold_on) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC hold on */
  if (hold_on == SUNXI_LRADC_HOLD_ON_DISABLE)
    sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_HOLD_ON;
  else
    sunxi_lradc_registers->ctrl |= SUNXI_LRADC_HOLD_ON;
  
  return 0;
}

/**
 * Set LRADC level B voltage
 * @param volt LRADC level B voltage, SUNXI_LRADC_LEVEL_B_1_9VOLT, SUNXI_LRADC_LEVEL_B_1_8VOLT, SUNXI_LRADC_LEVEL_B_1_7VOLT or SUNXI_LRADC_LEVEL_B_1_6VOLT
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_level_b_volt(unsigned int volt) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC level B voltage */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_LEVEL_B_VOLT(3);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_LEVEL_B_VOLT(volt);
  
  return 0;
}

/**
 * Set LRADC sample rate
 * @param sample_rate LRADC sample rate, SUNXI_LRADC_SAMPLE_RATE_250HZ, SUNXI_LRADC_SAMPLE_RATE_125HZ, SUNXI_LRADC_SAMPLE_RATE_62_5HZ or SUNXI_LRADC_SAMPLE_RATE_32_25HZ
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_set_sample_rate(unsigned int sample_rate) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Set LRADC sample rate */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_SAMPLE_RATE(3);
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_SAMPLE_RATE(sample_rate);
  
  return 0;
}

/**
 * Read LRADC channel
 * @param ch LRADC channel, SUNXI_LRADC_CH0 or SUNXI_LRADC_CH1
 * @param val LRADC channel value
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_read(unsigned int ch, unsigned int *val) {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Read LRADC channel */
  *val = sunxi_lradc_registers->data[ch];
  
  return 0;
}

/**
 * Enable LRADC
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_enable() {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Enable LRADC */
  sunxi_lradc_registers->ctrl |= SUNXI_LRADC_EN;

  return 0;
}

/**
 * Disable LRADC
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_lradc_disable() {
  
  /* Check if initialization has been performed */
  if (sunxi_lradc_registers == NULL) {
    return -EPERM;
  }

  /* Disable LRADC */
  sunxi_lradc_registers->ctrl &= ~SUNXI_LRADC_EN;

  return 0;
}
