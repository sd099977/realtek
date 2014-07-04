/************************************************************************
 *
 *  md_reg_sirius.h
 *
 *  Defines for Sirius MD registers
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

#define MD_KFDMA_DDR_SADDR    (MD_REG_BASE + 0x180)
#define MD_KFDMA_FL_SADDR     (MD_REG_BASE + 0x184)
#define MD_KFDMA_CTRL2        (MD_REG_BASE + 0x188)
#define MD_KFDMA_CTRL1        (MD_REG_BASE + 0x18c)

#endif /* #ifndef MD_REG_H */
