/*
 * Configuration settings for the MYZR i.MX6 Evaluation Kit (DIMM200).
 */

#ifndef __MYIMX6_COMMON_CONFIG_H
#define __MYIMX6_COMMON_CONFIG_H

#define CONFIG_MX6

#ifdef CONFIG_MX6SOLO
#define CONFIG_MX6DL
#endif

/* uncomment for PLUGIN mode support */
/* #define CONFIG_USE_PLUGIN */

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

#include "mx6_common.h"
#include <linux/sizes.h>

#define CONFIG_SYS_GENERIC_BOARD
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(10 * SZ_1M)

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_MXC_GPIO

#define CONFIG_MXC_UART

#define CONFIG_CMD_FUSE
#ifdef CONFIG_CMD_FUSE
#define CONFIG_MXC_OCOTP
#endif

/* MMC Configs */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR      0

#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION

#define CONFIG_SUPPORT_EMMC_BOOT /* eMMC specific */

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RMII
#define CONFIG_ETHPRIME			"FEC"
#define CONFIG_FEC_MXC_PHYADDR	0
#define CONFIG_FEC_ENET_DEV 	0

#define CONFIG_PHYLIB
#define CONFIG_PHY_SMSC

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX              1
#define CONFIG_BAUDRATE                        115200

/* Command definition */
#include <config_cmd_default.h>

#define CONFIG_CMD_BMODE
#define CONFIG_CMD_BOOTZ
#define CONFIG_CMD_SETEXPR
#undef CONFIG_CMD_IMLS

#define CONFIG_BOOTDELAY               1

#define CONFIG_LOADADDR                        0x12000000
#define CONFIG_SYS_TEXT_BASE           0x17800000
#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=" CONFIG_CONSOLE_DEV ",115200 " \
		"rdinit=/linuxrc " \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 " \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "\
		"enable_wait_mode=off\0" \
		"initrd_addr=0x12C00000\0" \
		"initrd_high=0xffffffff\0" \
		"bootcmd_mfg=run mfgtool_args;bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0" \

#define CONFIG_EXTRA_ENV_SETTINGS \
		CONFIG_MFG_ENV_SETTINGS \
		"fdt_addr=0x18000000\0" \
		"fdt_high=0xffffffff\0" \
		"bootargs_base=console=" CONFIG_CONSOLE_DEV ",115200 \0" \
		"mmcdev="__stringify(CONFIG_SYS_USE_MMC_DEV)"\0" \
		"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
		"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
		"serverip=" CONFIG_SERVERIP "\0" \
		"ipaddr=" CONFIG_IPADDR "\0" \
		"ethaddr=00:00:00:00:00:03\0" \
		"nfsroot=/home/myzr/nfsroot\0" \
		"u-boot=uboot-"CONFIG_BOARD_NAME"-"CPU_TYPE".imx\0" \
		"kernel=zImage-"CONFIG_BOARD_NAME"\0" \
		"fdt_file="CONFIG_BOARD_NAME"-"CPU_TYPE".dtb\0" \
		"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${kernel}\0" \
		"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
		"bootargs_mmc=setenv bootargs; setenv bootargs ${bootargs_base} root=${mmcroot} \0" \
		"bootcmd_mmc=run bootargs_mmc; run loadimage; run loadfdt; " \
			"bootz ${loadaddr} - ${fdt_addr} \0" \
		"bootcmd_tftp=run bootargs_mmc; "\
			"tftpboot ${loadaddr} ${kernel}; " \
			"tftpboot ${fdt_addr} ${fdt_file}; " \
			"bootz ${loadaddr} - ${fdt_addr} \0" \
		"bootargs_nfs=setenv bootargs; setenv bootargs ${bootargs_base} " \
			"root=/dev/nfs ip=${ipaddr} nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
		"bootcmd_nfs=run bootargs_nfs; " \
			"tftpboot ${loadaddr} ${kernel}; " \
			"tftpboot ${fdt_addr} ${fdt_file}; " \
			"bootz ${loadaddr} - ${fdt_addr}\0" \
		"bootargs_mem=setenv bootargs; setenv bootargs ${bootargs_base} " \
			"rdinit=/etc/inittab enable_wait_mode=off \0" \
		"bootcmd_mem=run bootargs_mem; " \
			"tftpboot ${loadaddr} uImage.ramdisk; " \
			"tftpboot ${fdt_addr} rootfs.ramdisk; " \
			"bootm ${loadaddr} ${fdt_addr}\0" \
		"update_uboot=tftpboot ${loadaddr} ${u-boot};" \
			"sf probe; sf erase 0 0x200000;" \
			"sf write ${loadaddr} 0x400 0x80000\0" \
		"bootcmd=run bootcmd_mmc \0" 

#define CONFIG_ARP_TIMEOUT     200UL

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2     "> "
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE              1024

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS             256
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START       0x10000000
#define CONFIG_SYS_MEMTEST_END         0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH     0x10800000

#define CONFIG_SYS_LOAD_ADDR           CONFIG_LOADADDR

#define CONFIG_CMDLINE_EDITING
#define CONFIG_STACKSIZE               (128 * 1024)

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS           1
#define PHYS_SDRAM                     MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE          PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_SIZE			(8 * 1024)

#ifndef CONFIG_SYS_NOSMP
#define CONFIG_SYS_NOSMP
#endif

#define CONFIG_SYS_USE_SPINOR
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_CMD_SF
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_SST
#define CONFIG_MXC_SPI
#define CONFIG_SF_DEFAULT_BUS  0
#define CONFIG_SF_DEFAULT_SPEED 20000000
#define CONFIG_SF_DEFAULT_MODE (SPI_MODE_0)

#define CONFIG_ENV_OFFSET              (768 * 1024)
#define CONFIG_ENV_SECT_SIZE           (64 * 1024)
#define CONFIG_ENV_SPI_BUS             CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS              CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE            CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ          CONFIG_SF_DEFAULT_SPEED
#define CONFIG_OF_LIBFDT

#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif

/*
 * I2C configs
 */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED		100000

/* Framebuffer */
#define CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#ifdef CONFIG_MX6DL
#define CONFIG_IPUV3_CLK 198000000
#else
#define CONFIG_IPUV3_CLK 264000000
#endif
#define CONFIG_IMX_HDMI

#if defined(CONFIG_ANDROID_SUPPORT)
#include "myimx6android_common.h"
#endif

#endif                         /* __MYIMX6_COMMON_CONFIG_H */
