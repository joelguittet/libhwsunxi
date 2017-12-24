/****************************************************************************************/
/* SUNXI SPI library interface                                                          */
/****************************************************************************************/

/****************************************************************************************/
/* Includes                                                                             */
/****************************************************************************************/

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "spi.h"


/****************************************************************************************/
/* Exported functions                                                                   */
/****************************************************************************************/

/**
 * Open SPI device, to be called once
 * @param filename /dev/spidev*.* path
 * @return File descriptor if the function succeeds, error code otherwise
 */
int sunxi_spi_open(char* filename) {
    
    int r;
    if ((r = open(filename, O_RDWR)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Read SPI device mode
 * @param fd File descriptor get from sunxi_spi_open
 * @param mode Mode read from SPI device, 8bits format (bitwise of SPI_CPHA, SPI_CPOL, SPI_CS_HIGH, SPI_LSB_FIRST, SPI_3WIRE, SPI_LOOP, SPI_NO_CS, SPI_READY)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_read_mode(int fd, __u8 *mode) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_RD_MODE, mode)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Write SPI device mode
 * @param fd File descriptor get from sunxi_spi_open
 * @param mode Mode written to SPI device, 8bits format (bitwise of SPI_CPHA, SPI_CPOL, SPI_CS_HIGH, SPI_LSB_FIRST, SPI_3WIRE, SPI_LOOP, SPI_NO_CS, SPI_READY)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_write_mode(int fd, __u8 mode) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_WR_MODE, &mode)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Read SPI device mode
 * @param fd File descriptor get from sunxi_spi_open
 * @param mode Mode read from SPI device, 32bits format (bitwise of SPI_CPHA, SPI_CPOL, SPI_CS_HIGH, SPI_LSB_FIRST, SPI_3WIRE, SPI_LOOP, SPI_NO_CS, SPI_READY, SPI_TX_DUAL, SPI_TX_QUAD, SPI_RX_DUAL, SPI_RX_QUAD)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_read_mode32(int fd, __u32 *mode) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_RD_MODE32, mode)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Write SPI device mode
 * @param fd File descriptor get from sunxi_spi_open
 * @param mode Mode written to SPI device, 32bits format (bitwise of SPI_CPHA, SPI_CPOL, SPI_CS_HIGH, SPI_LSB_FIRST, SPI_3WIRE, SPI_LOOP, SPI_NO_CS, SPI_READY, SPI_TX_DUAL, SPI_TX_QUAD, SPI_RX_DUAL, SPI_RX_QUAD)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_write_mode32(int fd, __u32 mode) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_WR_MODE32, &mode)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Read SPI device LSB first
 * @param fd File descriptor get from sunxi_spi_open
 * @param lsb LSB first read from SPI device, 1 if LSB first, 0 if not LSB first
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_read_lsb(int fd, __u8 *lsb) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_RD_LSB_FIRST, lsb)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Write SPI device LSB first
 * @param fd File descriptor get from sunxi_spi_open
 * @param lsb LSB first written to SPI device, 1 if LSB first, 0 if not LSB first
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_write_lsb(int fd, __u8 lsb) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Read SPI device bits per word
 * @param fd File descriptor get from sunxi_spi_open
 * @param bits Bits per word read from SPI device
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_read_bits(int fd, __u8 *bits) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, bits)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Write SPI device bits per words
 * @param fd File descriptor get from sunxi_spi_open
 * @param bits Bits per word written to SPI device
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_write_bits(int fd, __u8 bits) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Read SPI device max speed
 * @param fd File descriptor get from sunxi_spi_open
 * @param speed Speed read from SPI device, 32bits format (Hz)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_read_max_speed(int fd, __u32 *speed) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, speed)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Write SPI device max speed
 * @param fd File descriptor get from sunxi_spi_open
 * @param speed Speed written to SPI device, 32bits format (Hz)
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_write_max_speed(int fd, __u32 speed) {
    
    int r;
    if ((r = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Perform SPI device transfer
 * @param fd File descriptor get from sunxi_spi_open
 * @param tx Data to be written to the SPi interface, NULL if not defined
 * @param rx Data to be read from the SPi interface, NULL if not defined
 * @param len Length of data to be writen/read, maximal size is 64 bytes on SUN4I, 128 bytes on SUN6I
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_transfer(int fd, unsigned char *tx, unsigned char *rx, __u32 len) {
    return sunxi_spi_transfer_speed_delay_cs(fd, tx, rx, len, 0, 0, 0);
}
    
/**
 * Perform SPI device transfer
 * @param fd File descriptor get from sunxi_spi_open
 * @param tx Data to be written to the SPi interface, NULL if not defined
 * @param rx Data to be read from the SPi interface, NULL if not defined
 * @param len Length of data to be writen/read, maximal size is 64 bytes on SUN4I, 128 bytes on SUN6I
 * @param speed Speed of SPI interface, 32bits format (Hz), 0 to use max speed
 * @param delay_usecs Delay before release of CS line, 0 if not used
 * @param cs_change CS behavior, 1 to not release CS after the transfer, 0 otherwise
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_transfer_speed_delay_cs(int fd, unsigned char *tx, unsigned char *rx, __u32 len, __u32 speed, __u16 delay_usecs, __u8 cs_change) {

    int r;
    struct spi_ioc_transfer ioc_transfer;
    memset(&ioc_transfer, 0, sizeof(struct spi_ioc_transfer));
    ioc_transfer.tx_buf = (unsigned long)tx;
    ioc_transfer.rx_buf = (unsigned long)rx;
    ioc_transfer.len = len;
    ioc_transfer.speed_hz = speed;
    ioc_transfer.delay_usecs = delay_usecs;
    ioc_transfer.cs_change = cs_change;
    if ((r = ioctl(fd, SPI_IOC_MESSAGE(1), &ioc_transfer)) < 0) {
        return errno;
    }
    return r;
}

/**
 * Close SPI device
 * @param fd File descriptor get from sunxi_spi_open
 * @return 0 if the function succeeds, error code otherwise
 */
int sunxi_spi_close(int fd) {
    
    return close(fd);
}
