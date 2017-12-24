/****************************************************************************************/
/* SUNXI SPI library interface                                                          */
/****************************************************************************************/

#ifndef SUNXI_SPI_H_
#define SUNXI_SPI_H_


/****************************************************************************************/
/* Prototypes                                                                           */
/****************************************************************************************/

int sunxi_spi_open(char* filename);
int sunxi_spi_read_mode(int fd, __u8 *mode);
int sunxi_spi_write_mode(int fd, __u8 mode);
int sunxi_spi_read_mode32(int fd, __u32 *mode);
int sunxi_spi_write_mode32(int fd, __u32 mode);
int sunxi_spi_read_lsb(int fd, __u8 *lsb);
int sunxi_spi_write_lsb(int fd, __u8 lsb);
int sunxi_spi_read_bits(int fd, __u8 *bits);
int sunxi_spi_write_bits(int fd, __u8 bits);
int sunxi_spi_read_max_speed(int fd, __u32 *speed);
int sunxi_spi_write_max_speed(int fd, __u32 speed);
int sunxi_spi_transfer(int fd, unsigned char *tx, unsigned char *rx, __u32 len);
int sunxi_spi_transfer_speed_delay_cs(int fd, unsigned char *tx, unsigned char *rx, __u32 len, __u32 speed, __u16 delay_usecs, __u8 cs_change);
int sunxi_spi_close(int fd);


#endif
