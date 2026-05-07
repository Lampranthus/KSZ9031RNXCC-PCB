/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/ise/VM_ISE/gbe_spartan-6/lib/eth/rtl/eth_mac_1g_rgmii.v";
static unsigned int ng1[] = {1U, 0U};
static int ng2[] = {0, 0};
static unsigned int ng3[] = {2U, 0U};
static unsigned int ng4[] = {0U, 0U};
static int ng5[] = {1, 0};



static void Always_117_0(char *t0)
{
    char t4[8];
    char t11[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;

LAB0:    t1 = (t0 + 10056U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(117, ng0);
    t2 = (t0 + 11864);
    *((int *)t2) = 1;
    t3 = (t0 + 10088);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(117, ng0);

LAB5:    xsi_set_current_line(118, ng0);
    t5 = (t0 + 8184);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t0 + 8344);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memset(t11, 0, 8);
    t12 = (t11 + 4);
    t13 = (t10 + 4);
    t14 = *((unsigned int *)t10);
    t15 = (t14 >> 0);
    t16 = (t15 & 1);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t13);
    t18 = (t17 >> 0);
    t19 = (t18 & 1);
    *((unsigned int *)t12) = t19;
    xsi_vlogtype_concat(t4, 2, 2, 2U, t11, 1, t7, 1);
    t20 = (t0 + 8344);
    xsi_vlogvar_wait_assign_value(t20, t4, 0, 0, 2, 0LL);
    goto LAB2;

}

static void Always_124_1(char *t0)
{
    char t4[8];
    char t11[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;

LAB0:    t1 = (t0 + 10304U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(124, ng0);
    t2 = (t0 + 11880);
    *((int *)t2) = 1;
    t3 = (t0 + 10336);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(124, ng0);

LAB5:    xsi_set_current_line(125, ng0);
    t5 = (t0 + 8184);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t0 + 8504);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memset(t11, 0, 8);
    t12 = (t11 + 4);
    t13 = (t10 + 4);
    t14 = *((unsigned int *)t10);
    t15 = (t14 >> 0);
    t16 = (t15 & 1);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t13);
    t18 = (t17 >> 0);
    t19 = (t18 & 1);
    *((unsigned int *)t12) = t19;
    xsi_vlogtype_concat(t4, 2, 2, 2U, t11, 1, t7, 1);
    t20 = (t0 + 8504);
    xsi_vlogvar_wait_assign_value(t20, t4, 0, 0, 2, 0LL);
    goto LAB2;

}

static void Always_131_2(char *t0)
{
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t9;

LAB0:    t1 = (t0 + 10552U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(131, ng0);
    t2 = (t0 + 11896);
    *((int *)t2) = 1;
    t3 = (t0 + 10584);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(131, ng0);

LAB5:    xsi_set_current_line(132, ng0);
    t4 = (t0 + 8664);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = ((char*)((ng1)));
    memset(t8, 0, 8);
    xsi_vlog_unsigned_add(t8, 3, t6, 3, t7, 3);
    t9 = (t0 + 8664);
    xsi_vlogvar_wait_assign_value(t9, t8, 0, 0, 3, 0LL);
    goto LAB2;

}

static void Always_138_3(char *t0)
{
    char t4[8];
    char t8[8];
    char t17[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;

LAB0:    t1 = (t0 + 10800U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(138, ng0);
    t2 = (t0 + 11912);
    *((int *)t2) = 1;
    t3 = (t0 + 10832);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(138, ng0);

LAB5:    xsi_set_current_line(139, ng0);
    t5 = (t0 + 8664);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memset(t8, 0, 8);
    t9 = (t8 + 4);
    t10 = (t7 + 4);
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 2);
    t13 = (t12 & 1);
    *((unsigned int *)t8) = t13;
    t14 = *((unsigned int *)t10);
    t15 = (t14 >> 2);
    t16 = (t15 & 1);
    *((unsigned int *)t9) = t16;
    t18 = (t0 + 8824);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    memset(t17, 0, 8);
    t21 = (t17 + 4);
    t22 = (t20 + 4);
    t23 = *((unsigned int *)t20);
    t24 = (t23 >> 0);
    *((unsigned int *)t17) = t24;
    t25 = *((unsigned int *)t22);
    t26 = (t25 >> 0);
    *((unsigned int *)t21) = t26;
    t27 = *((unsigned int *)t17);
    *((unsigned int *)t17) = (t27 & 3U);
    t28 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t28 & 3U);
    xsi_vlogtype_concat(t4, 3, 3, 2U, t17, 2, t8, 1);
    t29 = (t0 + 8824);
    xsi_vlogvar_wait_assign_value(t29, t4, 0, 0, 3, 0LL);
    goto LAB2;

}

static void Always_145_4(char *t0)
{
    char t13[8];
    char t17[8];
    char t26[8];
    char t50[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    char *t15;
    char *t16;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    char *t46;
    char *t47;
    char *t48;
    char *t49;
    char *t51;

LAB0:    t1 = (t0 + 11048U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(145, ng0);
    t2 = (t0 + 11928);
    *((int *)t2) = 1;
    t3 = (t0 + 11080);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(145, ng0);

LAB5:    xsi_set_current_line(146, ng0);
    t4 = (t0 + 2184U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(151, ng0);

LAB10:    xsi_set_current_line(152, ng0);
    t2 = (t0 + 8984);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 7, t5, 32);
    t11 = (t0 + 8984);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 7, 0LL);
    xsi_set_current_line(154, ng0);
    t2 = (t0 + 8824);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t5 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 1);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t11);
    t10 = (t9 >> 1);
    t14 = (t10 & 1);
    *((unsigned int *)t5) = t14;
    t12 = (t0 + 8824);
    t15 = (t12 + 56U);
    t16 = *((char **)t15);
    memset(t17, 0, 8);
    t18 = (t17 + 4);
    t19 = (t16 + 4);
    t20 = *((unsigned int *)t16);
    t21 = (t20 >> 2);
    t22 = (t21 & 1);
    *((unsigned int *)t17) = t22;
    t23 = *((unsigned int *)t19);
    t24 = (t23 >> 2);
    t25 = (t24 & 1);
    *((unsigned int *)t18) = t25;
    t27 = *((unsigned int *)t13);
    t28 = *((unsigned int *)t17);
    t29 = (t27 ^ t28);
    *((unsigned int *)t26) = t29;
    t30 = (t13 + 4);
    t31 = (t17 + 4);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t30);
    t34 = *((unsigned int *)t31);
    t35 = (t33 | t34);
    *((unsigned int *)t32) = t35;
    t36 = *((unsigned int *)t32);
    t37 = (t36 != 0);
    if (t37 == 1)
        goto LAB11;

LAB12:
LAB13:    t40 = (t26 + 4);
    t41 = *((unsigned int *)t40);
    t42 = (~(t41));
    t43 = *((unsigned int *)t26);
    t44 = (t43 & t42);
    t45 = (t44 != 0);
    if (t45 > 0)
        goto LAB14;

LAB15:
LAB16:    xsi_set_current_line(158, ng0);
    t2 = (t0 + 8984);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 | t7);
    if (t8 != 127U)
        goto LAB19;

LAB18:    if (*((unsigned int *)t5) == 0)
        goto LAB20;

LAB21:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;

LAB19:    t12 = (t13 + 4);
    t9 = *((unsigned int *)t12);
    t10 = (~(t9));
    t14 = *((unsigned int *)t13);
    t20 = (t14 & t10);
    t21 = (t20 != 0);
    if (t21 > 0)
        goto LAB22;

LAB23:
LAB24:    xsi_set_current_line(166, ng0);
    t2 = (t0 + 9144);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 | t7);
    if (t8 != 3U)
        goto LAB27;

LAB26:    if (*((unsigned int *)t5) == 0)
        goto LAB28;

LAB29:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;

LAB27:    t12 = (t13 + 4);
    t9 = *((unsigned int *)t12);
    t10 = (~(t9));
    t14 = *((unsigned int *)t13);
    t20 = (t14 & t10);
    t21 = (t20 != 0);
    if (t21 > 0)
        goto LAB30;

LAB31:
LAB32:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(146, ng0);

LAB9:    xsi_set_current_line(147, ng0);
    t11 = ((char*)((ng2)));
    t12 = (t0 + 8984);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 7, 0LL);
    xsi_set_current_line(148, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 9144);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(149, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 8024);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(150, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 8184);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB8;

LAB11:    t38 = *((unsigned int *)t26);
    t39 = *((unsigned int *)t32);
    *((unsigned int *)t26) = (t38 | t39);
    goto LAB13;

LAB14:    xsi_set_current_line(154, ng0);

LAB17:    xsi_set_current_line(155, ng0);
    t46 = (t0 + 9144);
    t47 = (t46 + 56U);
    t48 = *((char **)t47);
    t49 = ((char*)((ng5)));
    memset(t50, 0, 8);
    xsi_vlog_unsigned_add(t50, 32, t48, 2, t49, 32);
    t51 = (t0 + 9144);
    xsi_vlogvar_wait_assign_value(t51, t50, 0, 0, 2, 0LL);
    goto LAB16;

LAB20:    *((unsigned int *)t13) = 1;
    goto LAB19;

LAB22:    xsi_set_current_line(158, ng0);

LAB25:    xsi_set_current_line(160, ng0);
    t15 = ((char*)((ng2)));
    t16 = (t0 + 8984);
    xsi_vlogvar_wait_assign_value(t16, t15, 0, 0, 7, 0LL);
    xsi_set_current_line(161, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 9144);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(162, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 8024);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(163, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 8184);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB24;

LAB28:    *((unsigned int *)t13) = 1;
    goto LAB27;

LAB30:    xsi_set_current_line(166, ng0);

LAB33:    xsi_set_current_line(168, ng0);
    t15 = ((char*)((ng2)));
    t16 = (t0 + 8984);
    xsi_vlogvar_wait_assign_value(t16, t15, 0, 0, 7, 0LL);
    xsi_set_current_line(169, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 9144);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(170, ng0);
    t2 = (t0 + 8984);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t5 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 5);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t11);
    t9 = (t8 >> 5);
    *((unsigned int *)t5) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 3U);
    t14 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t14 & 3U);
    t12 = (t13 + 4);
    t20 = *((unsigned int *)t12);
    t21 = (~(t20));
    t22 = *((unsigned int *)t13);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB34;

LAB35:    xsi_set_current_line(174, ng0);

LAB38:    xsi_set_current_line(176, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 8024);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(177, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 8184);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);

LAB36:    goto LAB32;

LAB34:    xsi_set_current_line(170, ng0);

LAB37:    xsi_set_current_line(172, ng0);
    t15 = ((char*)((ng1)));
    t16 = (t0 + 8024);
    xsi_vlogvar_wait_assign_value(t16, t15, 0, 0, 2, 0LL);
    xsi_set_current_line(173, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 8184);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB36;

}

static void Cont_183_5(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 11296U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(183, ng0);
    t2 = (t0 + 8024);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 12024);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 3U;
    t11 = t10;
    t12 = (t4 + 4);
    t13 = *((unsigned int *)t4);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t5, 0, 1);
    t18 = (t0 + 11944);
    *((int *)t18) = 1;

LAB1:    return;
}

static void implSig1_execute(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;

LAB0:    t1 = (t0 + 11544U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = ((char*)((ng1)));
    t3 = (t0 + 12088);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memset(t7, 0, 8);
    t8 = 1U;
    t9 = t8;
    t10 = (t2 + 4);
    t11 = *((unsigned int *)t2);
    t8 = (t8 & t11);
    t12 = *((unsigned int *)t10);
    t9 = (t9 & t12);
    t13 = (t7 + 4);
    t14 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t14 | t8);
    t15 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t15 | t9);
    xsi_driver_vfirst_trans(t3, 0, 0);

LAB1:    return;
}


extern void work_m_03038593808109315718_3215541432_init()
{
	static char *pe[] = {(void *)Always_117_0,(void *)Always_124_1,(void *)Always_131_2,(void *)Always_138_3,(void *)Always_145_4,(void *)Cont_183_5,(void *)implSig1_execute};
	xsi_register_didat("work_m_03038593808109315718_3215541432", "isim/fpga_isim_beh.exe.sim/work/m_03038593808109315718_3215541432.didat");
	xsi_register_executes(pe);
}
