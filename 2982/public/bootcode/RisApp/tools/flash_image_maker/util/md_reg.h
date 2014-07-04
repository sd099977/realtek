/************************************************************************
 *
 *  md_reg.h
 *
 *  Defines for MacArthur2 MD registers
 *
 ************************************************************************/

#ifndef MD_REG_H
#define MD_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define MD_REG_BASE           0xb800b000

#define MD_FDMA_DDR_SADDR     (MD_REG_BASE + 0x88)
#define MD_FDMA_FL_SADDR      (MD_REG_BASE + 0x8c)
#define MD_FDMA_CTRL2         (MD_REG_BASE + 0x90)
#define MD_FDMA_CTRL1         (MD_REG_BASE + 0x94)

#endif /* #ifndef MD_REG_H */
