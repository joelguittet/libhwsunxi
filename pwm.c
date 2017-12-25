/****************************************************************************************/
/* SUNXI PWM library interface                                                          */
/****************************************************************************************/

/****************************************************************************************/
/* Includes                                                                             */
/****************************************************************************************/

#include "pwm.h"


/****************************************************************************************/
/* Definitions                                                                          */
/****************************************************************************************/

/* SUNXI PWM control IO base address */
#define SUNXI_PWM_IO_BASE                       0x01c20e00

/* Macros used to configure PWM */
#define SUNXI_PWM_EN(ch)                        ((1 << 4) << (15 * ch))
#define SUNXI_PWM_ACT_STATE(ch)                 ((1 << 5) << (15 * ch))
#define SUNXI_PWM_CLK_GATING(ch)                ((1 << 6) << (15 * ch))
#define SUNXI_PWM_PRESCALAR(ch, prescaler)      (prescaler << (15 * ch))

/* SUNXI PWM Registers */
struct sunxi_pwm_reg {
  volatile unsigned int ctrl;
  volatile unsigned int ch_period[2];
};


/****************************************************************************************/
/* Global variables                                                                     */
/****************************************************************************************/

/* SUNXI PWM registers */
static volatile struct sunxi_pwm_reg *sunxi_pwm_registers = NULL;


/****************************************************************************************/
/* Exported functions                                                                   */
/****************************************************************************************/

/**
 * Initialize PWM interface, to be called once
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_pwm_init() {
  
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
  addr_start = SUNXI_PWM_IO_BASE & page_mask;
  addr_offset = SUNXI_PWM_IO_BASE & ~page_mask;
  pc = (void *)mmap(NULL, (((sizeof(struct sunxi_pwm_reg) + addr_offset) / page_size) + 1) * page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr_start);
  if (pc == MAP_FAILED) {
    return -errno;
  }

  /* Retrieve registers address used later in this library */
  sunxi_pwm_registers = (struct sunxi_pwm_reg *)(pc + addr_offset);

  /* Close device */
  close(fd);
  
  return 0;
}

/**
 * Set PWM polarity
 * @param ch PWM channel, SUNXI_PWM_CH0 or SUNXI_PWM_CH1
 * @param pol PWM polarity, SUNXI_PWM_POLARITY_NORMAL or SUNXI_PWM_POLARITY_INVERSED
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_pwm_set_polarity(unsigned int ch, unsigned int pol) {
  
  /* Check if initialization has been performed */
  if (sunxi_pwm_registers == NULL) {
    return -EPERM;
  }

  /* Set PWM polarity */
  if (pol == SUNXI_PWM_POLARITY_NORMAL)
    sunxi_pwm_registers->ctrl |= SUNXI_PWM_ACT_STATE(ch);
  else
    sunxi_pwm_registers->ctrl &= ~SUNXI_PWM_ACT_STATE(ch);

  return 0;
}

/**
 * Configure PWM channel period and duty cycle
 * @param ch PWM channel, SUNXI_PWM_CH0 or SUNXI_PWM_CH1
 * @param period_ns PWM period in ns
 * @param duty_ns PWM duty cycle in ns
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_pwm_set_config(unsigned int ch, __u64 period_ns, __u64 duty_ns) {
  
  unsigned int prd, dty, clk_gating, prescaler = 0; __u64 div;
  unsigned int prescaler_table[] = {120, 180, 240, 360, 480, 0, 0, 0, 12000, 24000, 36000, 48000, 72000, 0, 0, 0};
    
  /* Check if initialization has been performed */
  if (sunxi_pwm_registers == NULL) {
    return -EPERM;
  }

  /* Compute PWM registers */
  for (prescaler = 0; prescaler < 0x0F; prescaler++) {
    if (!prescaler_table[prescaler]) continue;
    div = 24000000;
    div = div / prescaler_table[prescaler];
    div = div * period_ns;
    div = div / 1000000000;
    if (div - 1 <= 0xFFFF) break;
  }
  if (div - 1 > 0xFFFF) {
    return -EINVAL;
  }
  prd = div;
  div *= duty_ns;
  div = div / period_ns;
  dty = div;
  
  /* Set PWM period and duty cycle */
  clk_gating = sunxi_pwm_registers->ctrl & SUNXI_PWM_CLK_GATING(ch);
  sunxi_pwm_registers->ctrl &= ~SUNXI_PWM_CLK_GATING(ch);
  sunxi_pwm_registers->ctrl &= ~SUNXI_PWM_PRESCALAR(ch, 0x0F);
  sunxi_pwm_registers->ctrl |= SUNXI_PWM_PRESCALAR(ch, prescaler);
  sunxi_pwm_registers->ch_period[ch] = ((prd - 1) << 16) + (dty & 0xFFFF);
  if (clk_gating != 0) sunxi_pwm_registers->ctrl |= SUNXI_PWM_CLK_GATING(ch);
  
  return 0;
} 

/**
 * Enable PWM
 * @param ch PWM channel, SUNXI_PWM_CH0 or SUNXI_PWM_CH1
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_pwm_enable(unsigned int ch) {
  
  /* Check if initialization has been performed */
  if (sunxi_pwm_registers == NULL) {
    return -EPERM;
  }

  /* Enable PWM */
  sunxi_pwm_registers->ctrl |= SUNXI_PWM_EN(ch);
  sunxi_pwm_registers->ctrl |= SUNXI_PWM_CLK_GATING(ch);

  return 0;
}

/**
 * Disable PWM
 * @param ch PWM channel, SUNXI_PWM_CH0 or SUNXI_PWM_CH1
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_pwm_disable(unsigned int ch) {
  
  /* Check if initialization has been performed */
  if (sunxi_pwm_registers == NULL) {
    return -EPERM;
  }

  /* Disable PWM */
  sunxi_pwm_registers->ctrl &= ~SUNXI_PWM_EN(ch);
  sunxi_pwm_registers->ctrl &= ~SUNXI_PWM_CLK_GATING(ch);

  return 0;
}
