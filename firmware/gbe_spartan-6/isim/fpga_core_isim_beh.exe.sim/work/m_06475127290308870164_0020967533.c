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
static const char *ng0 = "/home/ise/VM_ISE/gbe_spartan-6/mdio_controller.v";
static int ng1[] = {1, 0};
static int ng2[] = {2, 0};
static unsigned int ng3[] = {0U, 1U};
static unsigned int ng4[] = {0U, 0U};
static int ng5[] = {0, 0};
static unsigned int ng6[] = {7U, 0U};
static unsigned int ng7[] = {1U, 0U};
static int ng8[] = {31, 0};
static unsigned int ng9[] = {2U, 0U};
static unsigned int ng10[] = {3U, 0U};
static unsigned int ng11[] = {4U, 0U};
static int ng12[] = {4, 0};
static unsigned int ng13[] = {5U, 0U};
static unsigned int ng14[] = {6U, 0U};
static int ng15[] = {15, 0};
static unsigned int ng16[] = {8U, 0U};



static void NetDecl_61_0(char *t0)
{
    char t7[8];
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    unsigned int t29;
    unsigned int t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    char *t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;

LAB0:    t1 = (t0 + 7808U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(61, ng0);
    t2 = (t0 + 5776);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1968);
    t6 = *((char **)t5);
    t5 = ((char*)((ng1)));
    memset(t7, 0, 8);
    xsi_vlog_unsigned_minus(t7, 32, t6, 32, t5, 32);
    memset(t8, 0, 8);
    t9 = (t4 + 4);
    t10 = (t7 + 4);
    t11 = *((unsigned int *)t4);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t9);
    t15 = *((unsigned int *)t10);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t9);
    t19 = *((unsigned int *)t10);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB7;

LAB4:    if (t20 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t8) = 1;

LAB7:    t24 = (t0 + 9792);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    memset(t28, 0, 8);
    t29 = 1U;
    t30 = t29;
    t31 = (t8 + 4);
    t32 = *((unsigned int *)t8);
    t29 = (t29 & t32);
    t33 = *((unsigned int *)t31);
    t30 = (t30 & t33);
    t34 = (t28 + 4);
    t35 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t35 | t29);
    t36 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t36 | t30);
    xsi_driver_vfirst_trans(t24, 0, 0U);
    t37 = (t0 + 9616);
    *((int *)t37) = 1;

LAB1:    return;
LAB6:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB7;

}

static void Cont_77_1(char *t0)
{
    char t7[8];
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;

LAB0:    t1 = (t0 + 8056U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(77, ng0);
    t2 = (t0 + 5776);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1968);
    t6 = *((char **)t5);
    t5 = ((char*)((ng2)));
    memset(t7, 0, 8);
    xsi_vlog_unsigned_divide(t7, 32, t6, 32, t5, 32);
    memset(t8, 0, 8);
    t9 = (t4 + 4);
    if (*((unsigned int *)t9) != 0)
        goto LAB5;

LAB4:    t10 = (t7 + 4);
    if (*((unsigned int *)t10) != 0)
        goto LAB5;

LAB8:    if (*((unsigned int *)t4) < *((unsigned int *)t7))
        goto LAB6;

LAB7:    t12 = (t0 + 9856);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    memset(t16, 0, 8);
    t17 = 1U;
    t18 = t17;
    t19 = (t8 + 4);
    t20 = *((unsigned int *)t8);
    t17 = (t17 & t20);
    t21 = *((unsigned int *)t19);
    t18 = (t18 & t21);
    t22 = (t16 + 4);
    t23 = *((unsigned int *)t16);
    *((unsigned int *)t16) = (t23 | t17);
    t24 = *((unsigned int *)t22);
    *((unsigned int *)t22) = (t24 | t18);
    xsi_driver_vfirst_trans(t12, 0, 0);
    t25 = (t0 + 9632);
    *((int *)t25) = 1;

LAB1:    return;
LAB5:    t11 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB7;

LAB6:    *((unsigned int *)t8) = 1;
    goto LAB7;

}

static void Cont_80_2(char *t0)
{
    char t3[8];
    char t4[8];
    char *t1;
    char *t2;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;
    unsigned int t34;
    unsigned int t35;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    char *t39;

LAB0:    t1 = (t0 + 8304U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(80, ng0);
    t2 = (t0 + 5936);
    t5 = (t2 + 56U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t7);
    t9 = (~(t8));
    t10 = *((unsigned int *)t6);
    t11 = (t10 & t9);
    t12 = (t11 & 1U);
    if (t12 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t7) != 0)
        goto LAB6;

LAB7:    t14 = (t4 + 4);
    t15 = *((unsigned int *)t4);
    t16 = *((unsigned int *)t14);
    t17 = (t15 || t16);
    if (t17 > 0)
        goto LAB8;

LAB9:    t21 = *((unsigned int *)t4);
    t22 = (~(t21));
    t23 = *((unsigned int *)t14);
    t24 = (t22 || t23);
    if (t24 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t14) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t25, 8);

LAB16:    t26 = (t0 + 9920);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = (t28 + 56U);
    t30 = *((char **)t29);
    memset(t30, 0, 8);
    t31 = 1U;
    t32 = t31;
    t33 = (t3 + 4);
    t34 = *((unsigned int *)t3);
    t31 = (t31 & t34);
    t35 = *((unsigned int *)t33);
    t32 = (t32 & t35);
    t36 = (t30 + 4);
    t37 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t37 | t31);
    t38 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t38 | t32);
    xsi_driver_vfirst_trans(t26, 0, 0);
    t39 = (t0 + 9648);
    *((int *)t39) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    t13 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t13) = 1;
    goto LAB7;

LAB8:    t18 = (t0 + 6256);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    goto LAB9;

LAB10:    t25 = ((char*)((ng3)));
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 1, t20, 1, t25, 1);
    goto LAB16;

LAB14:    memcpy(t3, t20, 8);
    goto LAB16;

}

static void Cont_83_3(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 8552U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(83, ng0);
    t2 = (t0 + 5136);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB5;

LAB4:    if (t18 != 0)
        goto LAB6;

LAB7:    t22 = (t0 + 9984);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 1U;
    t28 = t27;
    t29 = (t6 + 4);
    t30 = *((unsigned int *)t6);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 0, 0);
    t35 = (t0 + 9664);
    *((int *)t35) = 1;

LAB1:    return;
LAB5:    *((unsigned int *)t6) = 1;
    goto LAB7;

LAB6:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

}

static void Always_90_4(char *t0)
{
    char t4[8];
    char t21[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;

LAB0:    t1 = (t0 + 8800U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(90, ng0);
    t2 = (t0 + 9680);
    *((int *)t2) = 1;
    t3 = (t0 + 8832);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(90, ng0);

LAB5:    xsi_set_current_line(91, ng0);
    t5 = (t0 + 2976U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t6 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t5) == 0)
        goto LAB6;

LAB8:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;

LAB9:    t13 = (t4 + 4);
    t14 = *((unsigned int *)t13);
    t15 = (~(t14));
    t16 = *((unsigned int *)t4);
    t17 = (t16 & t15);
    t18 = (t17 != 0);
    if (t18 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(93, ng0);
    t2 = (t0 + 5776);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 1968);
    t12 = *((char **)t6);
    t6 = ((char*)((ng1)));
    memset(t4, 0, 8);
    xsi_vlog_unsigned_minus(t4, 32, t12, 32, t6, 32);
    memset(t21, 0, 8);
    t13 = (t5 + 4);
    t19 = (t4 + 4);
    t7 = *((unsigned int *)t5);
    t8 = *((unsigned int *)t4);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t13);
    t11 = *((unsigned int *)t19);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t13);
    t17 = *((unsigned int *)t19);
    t18 = (t16 | t17);
    t22 = (~(t18));
    t23 = (t15 & t22);
    if (t23 != 0)
        goto LAB17;

LAB14:    if (t18 != 0)
        goto LAB16;

LAB15:    *((unsigned int *)t21) = 1;

LAB17:    t24 = (t21 + 4);
    t25 = *((unsigned int *)t24);
    t26 = (~(t25));
    t27 = *((unsigned int *)t21);
    t28 = (t27 & t26);
    t29 = (t28 != 0);
    if (t29 > 0)
        goto LAB18;

LAB19:    xsi_set_current_line(95, ng0);

LAB22:    xsi_set_current_line(96, ng0);
    t2 = (t0 + 5776);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t4, 0, 8);
    xsi_vlog_unsigned_add(t4, 32, t5, 6, t6, 32);
    t12 = (t0 + 5776);
    xsi_vlogvar_wait_assign_value(t12, t4, 0, 0, 6, 0LL);

LAB20:
LAB12:    goto LAB2;

LAB6:    *((unsigned int *)t4) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(91, ng0);

LAB13:    xsi_set_current_line(92, ng0);
    t19 = ((char*)((ng5)));
    t20 = (t0 + 5776);
    xsi_vlogvar_wait_assign_value(t20, t19, 0, 0, 6, 0LL);
    goto LAB12;

LAB16:    t20 = (t21 + 4);
    *((unsigned int *)t21) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB17;

LAB18:    xsi_set_current_line(93, ng0);

LAB21:    xsi_set_current_line(94, ng0);
    t30 = ((char*)((ng5)));
    t31 = (t0 + 5776);
    xsi_vlogvar_wait_assign_value(t31, t30, 0, 0, 6, 0LL);
    goto LAB20;

}

static void Always_101_5(char *t0)
{
    char t4[8];
    char t21[8];
    char t35[8];
    char t43[8];
    char t75[8];
    char t89[8];
    char t96[8];
    char t134[8];
    char t137[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    char *t34;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    char *t47;
    char *t48;
    char *t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    char *t57;
    char *t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    int t67;
    int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    char *t82;
    char *t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    char *t87;
    char *t88;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    char *t95;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    char *t100;
    char *t101;
    char *t102;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    char *t110;
    char *t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    int t120;
    int t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    unsigned int t126;
    unsigned int t127;
    char *t128;
    unsigned int t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    unsigned int t133;
    char *t135;
    char *t136;
    char *t138;
    char *t139;
    char *t140;
    char *t141;
    unsigned int t142;
    unsigned int t143;
    unsigned int t144;
    unsigned int t145;
    unsigned int t146;
    unsigned int t147;
    char *t148;

LAB0:    t1 = (t0 + 9048U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(101, ng0);
    t2 = (t0 + 9696);
    *((int *)t2) = 1;
    t3 = (t0 + 9080);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(101, ng0);

LAB5:    xsi_set_current_line(102, ng0);
    t5 = (t0 + 2976U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t6 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t5) == 0)
        goto LAB6;

LAB8:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;

LAB9:    t13 = (t4 + 4);
    t14 = *((unsigned int *)t13);
    t15 = (~(t14));
    t16 = *((unsigned int *)t4);
    t17 = (t16 & t15);
    t18 = (t17 != 0);
    if (t18 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(110, ng0);

LAB14:    xsi_set_current_line(112, ng0);
    t2 = (t0 + 5296);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 5136);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 4, 0LL);
    xsi_set_current_line(113, ng0);
    t2 = (t0 + 5616);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 5456);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(114, ng0);
    t2 = (t0 + 6096);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 5936);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(115, ng0);
    t2 = (t0 + 6416);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 6256);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(116, ng0);
    t2 = (t0 + 6736);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 4816);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 16, 0LL);
    xsi_set_current_line(117, ng0);
    t2 = (t0 + 6896);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 4976);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(120, ng0);
    t2 = (t0 + 4416U);
    t3 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t3 + 4);
    t7 = *((unsigned int *)t2);
    t8 = (~(t7));
    t9 = *((unsigned int *)t3);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB15;

LAB16:    if (*((unsigned int *)t2) != 0)
        goto LAB17;

LAB18:    t6 = (t4 + 4);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t6);
    t16 = (t14 || t15);
    if (t16 > 0)
        goto LAB19;

LAB20:    memcpy(t43, t4, 8);

LAB21:    memset(t75, 0, 8);
    t76 = (t43 + 4);
    t77 = *((unsigned int *)t76);
    t78 = (~(t77));
    t79 = *((unsigned int *)t43);
    t80 = (t79 & t78);
    t81 = (t80 & 1U);
    if (t81 != 0)
        goto LAB33;

LAB34:    if (*((unsigned int *)t76) != 0)
        goto LAB35;

LAB36:    t83 = (t75 + 4);
    t84 = *((unsigned int *)t75);
    t85 = *((unsigned int *)t83);
    t86 = (t84 || t85);
    if (t86 > 0)
        goto LAB37;

LAB38:    memcpy(t96, t75, 8);

LAB39:    t128 = (t96 + 4);
    t129 = *((unsigned int *)t128);
    t130 = (~(t129));
    t131 = *((unsigned int *)t96);
    t132 = (t131 & t130);
    t133 = (t132 != 0);
    if (t133 > 0)
        goto LAB47;

LAB48:
LAB49:
LAB12:    goto LAB2;

LAB6:    *((unsigned int *)t4) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(102, ng0);

LAB13:    xsi_set_current_line(103, ng0);
    t19 = ((char*)((ng4)));
    t20 = (t0 + 5136);
    xsi_vlogvar_wait_assign_value(t20, t19, 0, 0, 4, 0LL);
    xsi_set_current_line(104, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5456);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 5, 0LL);
    xsi_set_current_line(105, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 5936);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    xsi_set_current_line(106, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 6256);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    xsi_set_current_line(107, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 6576);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 16, 0LL);
    xsi_set_current_line(108, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 4816);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 16, 0LL);
    xsi_set_current_line(109, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 4976);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB12;

LAB15:    *((unsigned int *)t4) = 1;
    goto LAB18;

LAB17:    t5 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t5) = 1;
    goto LAB18;

LAB19:    t12 = (t0 + 5136);
    t13 = (t12 + 56U);
    t19 = *((char **)t13);
    t20 = ((char*)((ng6)));
    memset(t21, 0, 8);
    t22 = (t19 + 4);
    t23 = (t20 + 4);
    t17 = *((unsigned int *)t19);
    t18 = *((unsigned int *)t20);
    t24 = (t17 ^ t18);
    t25 = *((unsigned int *)t22);
    t26 = *((unsigned int *)t23);
    t27 = (t25 ^ t26);
    t28 = (t24 | t27);
    t29 = *((unsigned int *)t22);
    t30 = *((unsigned int *)t23);
    t31 = (t29 | t30);
    t32 = (~(t31));
    t33 = (t28 & t32);
    if (t33 != 0)
        goto LAB25;

LAB22:    if (t31 != 0)
        goto LAB24;

LAB23:    *((unsigned int *)t21) = 1;

LAB25:    memset(t35, 0, 8);
    t36 = (t21 + 4);
    t37 = *((unsigned int *)t36);
    t38 = (~(t37));
    t39 = *((unsigned int *)t21);
    t40 = (t39 & t38);
    t41 = (t40 & 1U);
    if (t41 != 0)
        goto LAB26;

LAB27:    if (*((unsigned int *)t36) != 0)
        goto LAB28;

LAB29:    t44 = *((unsigned int *)t4);
    t45 = *((unsigned int *)t35);
    t46 = (t44 & t45);
    *((unsigned int *)t43) = t46;
    t47 = (t4 + 4);
    t48 = (t35 + 4);
    t49 = (t43 + 4);
    t50 = *((unsigned int *)t47);
    t51 = *((unsigned int *)t48);
    t52 = (t50 | t51);
    *((unsigned int *)t49) = t52;
    t53 = *((unsigned int *)t49);
    t54 = (t53 != 0);
    if (t54 == 1)
        goto LAB30;

LAB31:
LAB32:    goto LAB21;

LAB24:    t34 = (t21 + 4);
    *((unsigned int *)t21) = 1;
    *((unsigned int *)t34) = 1;
    goto LAB25;

LAB26:    *((unsigned int *)t35) = 1;
    goto LAB29;

LAB28:    t42 = (t35 + 4);
    *((unsigned int *)t35) = 1;
    *((unsigned int *)t42) = 1;
    goto LAB29;

LAB30:    t55 = *((unsigned int *)t43);
    t56 = *((unsigned int *)t49);
    *((unsigned int *)t43) = (t55 | t56);
    t57 = (t4 + 4);
    t58 = (t35 + 4);
    t59 = *((unsigned int *)t4);
    t60 = (~(t59));
    t61 = *((unsigned int *)t57);
    t62 = (~(t61));
    t63 = *((unsigned int *)t35);
    t64 = (~(t63));
    t65 = *((unsigned int *)t58);
    t66 = (~(t65));
    t67 = (t60 & t62);
    t68 = (t64 & t66);
    t69 = (~(t67));
    t70 = (~(t68));
    t71 = *((unsigned int *)t49);
    *((unsigned int *)t49) = (t71 & t69);
    t72 = *((unsigned int *)t49);
    *((unsigned int *)t49) = (t72 & t70);
    t73 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t73 & t69);
    t74 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t74 & t70);
    goto LAB32;

LAB33:    *((unsigned int *)t75) = 1;
    goto LAB36;

LAB35:    t82 = (t75 + 4);
    *((unsigned int *)t75) = 1;
    *((unsigned int *)t82) = 1;
    goto LAB36;

LAB37:    t87 = (t0 + 3296U);
    t88 = *((char **)t87);
    memset(t89, 0, 8);
    t87 = (t88 + 4);
    t90 = *((unsigned int *)t87);
    t91 = (~(t90));
    t92 = *((unsigned int *)t88);
    t93 = (t92 & t91);
    t94 = (t93 & 1U);
    if (t94 != 0)
        goto LAB40;

LAB41:    if (*((unsigned int *)t87) != 0)
        goto LAB42;

LAB43:    t97 = *((unsigned int *)t75);
    t98 = *((unsigned int *)t89);
    t99 = (t97 & t98);
    *((unsigned int *)t96) = t99;
    t100 = (t75 + 4);
    t101 = (t89 + 4);
    t102 = (t96 + 4);
    t103 = *((unsigned int *)t100);
    t104 = *((unsigned int *)t101);
    t105 = (t103 | t104);
    *((unsigned int *)t102) = t105;
    t106 = *((unsigned int *)t102);
    t107 = (t106 != 0);
    if (t107 == 1)
        goto LAB44;

LAB45:
LAB46:    goto LAB39;

LAB40:    *((unsigned int *)t89) = 1;
    goto LAB43;

LAB42:    t95 = (t89 + 4);
    *((unsigned int *)t89) = 1;
    *((unsigned int *)t95) = 1;
    goto LAB43;

LAB44:    t108 = *((unsigned int *)t96);
    t109 = *((unsigned int *)t102);
    *((unsigned int *)t96) = (t108 | t109);
    t110 = (t75 + 4);
    t111 = (t89 + 4);
    t112 = *((unsigned int *)t75);
    t113 = (~(t112));
    t114 = *((unsigned int *)t110);
    t115 = (~(t114));
    t116 = *((unsigned int *)t89);
    t117 = (~(t116));
    t118 = *((unsigned int *)t111);
    t119 = (~(t118));
    t120 = (t113 & t115);
    t121 = (t117 & t119);
    t122 = (~(t120));
    t123 = (~(t121));
    t124 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t124 & t122);
    t125 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t125 & t123);
    t126 = *((unsigned int *)t96);
    *((unsigned int *)t96) = (t126 & t122);
    t127 = *((unsigned int *)t96);
    *((unsigned int *)t96) = (t127 & t123);
    goto LAB46;

LAB47:    xsi_set_current_line(120, ng0);

LAB50:    xsi_set_current_line(121, ng0);
    t135 = (t0 + 4256U);
    t136 = *((char **)t135);
    t135 = (t0 + 6576);
    t138 = (t135 + 56U);
    t139 = *((char **)t138);
    memset(t137, 0, 8);
    t140 = (t137 + 4);
    t141 = (t139 + 4);
    t142 = *((unsigned int *)t139);
    t143 = (t142 >> 0);
    *((unsigned int *)t137) = t143;
    t144 = *((unsigned int *)t141);
    t145 = (t144 >> 0);
    *((unsigned int *)t140) = t145;
    t146 = *((unsigned int *)t137);
    *((unsigned int *)t137) = (t146 & 32767U);
    t147 = *((unsigned int *)t140);
    *((unsigned int *)t140) = (t147 & 32767U);
    xsi_vlogtype_concat(t134, 16, 16, 2U, t137, 15, t136, 1);
    t148 = (t0 + 6576);
    xsi_vlogvar_wait_assign_value(t148, t134, 0, 0, 16, 0LL);
    goto LAB49;

}

static void Always_129_6(char *t0)
{
    char t16[8];
    char t40[8];
    char t45[8];
    char t53[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t17;
    char *t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    char *t38;
    char *t39;
    int t41;
    int t42;
    int t43;
    int t44;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    char *t49;
    char *t50;
    char *t51;
    char *t52;
    char *t54;
    char *t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    char *t68;
    char *t69;

LAB0:    t1 = (t0 + 9296U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(129, ng0);
    t2 = (t0 + 9712);
    *((int *)t2) = 1;
    t3 = (t0 + 9328);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(129, ng0);

LAB5:    xsi_set_current_line(131, ng0);
    t4 = (t0 + 5136);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t0 + 5296);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 4);
    xsi_set_current_line(132, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 5616);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 5);
    xsi_set_current_line(133, ng0);
    t2 = (t0 + 5936);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 6096);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(134, ng0);
    t2 = (t0 + 6256);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 6416);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(135, ng0);
    t2 = (t0 + 4816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 6736);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 16);
    xsi_set_current_line(136, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 6896);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(139, ng0);
    t2 = (t0 + 5136);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);

LAB6:    t5 = ((char*)((ng4)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t5, 4);
    if (t8 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng10)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng11)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng13)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng14)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng16)));
    t8 = xsi_vlog_unsigned_case_compare(t4, 4, t2, 4);
    if (t8 == 1)
        goto LAB23;

LAB24:
LAB26:
LAB25:    xsi_set_current_line(202, ng0);

LAB136:    xsi_set_current_line(203, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 5296);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);

LAB27:    xsi_set_current_line(209, ng0);
    t2 = (t0 + 5136);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);

LAB137:    t6 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t5, 4, t6, 4);
    if (t8 == 1)
        goto LAB138;

LAB139:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t8 == 1)
        goto LAB140;

LAB141:    t3 = ((char*)((ng10)));
    t41 = xsi_vlog_unsigned_case_compare(t5, 4, t3, 4);
    if (t41 == 1)
        goto LAB142;

LAB143:    t6 = ((char*)((ng11)));
    t42 = xsi_vlog_unsigned_case_compare(t5, 4, t6, 4);
    if (t42 == 1)
        goto LAB144;

LAB145:    t7 = ((char*)((ng13)));
    t43 = xsi_vlog_unsigned_case_compare(t5, 4, t7, 4);
    if (t43 == 1)
        goto LAB146;

LAB147:    t14 = ((char*)((ng14)));
    t44 = xsi_vlog_unsigned_case_compare(t5, 4, t14, 4);
    if (t44 == 1)
        goto LAB148;

LAB149:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t8 == 1)
        goto LAB150;

LAB151:
LAB153:
LAB152:    xsi_set_current_line(212, ng0);
    t3 = ((char*)((ng4)));
    t6 = (t0 + 6096);
    xsi_vlogvar_assign_value(t6, t3, 0, 0, 1);

LAB154:    xsi_set_current_line(216, ng0);
    t2 = (t0 + 5136);
    t3 = (t2 + 56U);
    t6 = *((char **)t3);

LAB161:    t7 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t7, 4);
    if (t8 == 1)
        goto LAB162;

LAB163:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t2, 4);
    if (t8 == 1)
        goto LAB164;

LAB165:    t2 = ((char*)((ng10)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t2, 4);
    if (t8 == 1)
        goto LAB166;

LAB167:    t2 = ((char*)((ng11)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t2, 4);
    if (t8 == 1)
        goto LAB168;

LAB169:    t2 = ((char*)((ng13)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t2, 4);
    if (t8 == 1)
        goto LAB170;

LAB171:    t2 = ((char*)((ng14)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t2, 4);
    if (t8 == 1)
        goto LAB172;

LAB173:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 4, t2, 4);
    if (t8 == 1)
        goto LAB174;

LAB175:
LAB177:
LAB176:    xsi_set_current_line(224, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 6416);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB178:    goto LAB2;

LAB7:    xsi_set_current_line(140, ng0);

LAB28:    xsi_set_current_line(141, ng0);
    t6 = (t0 + 3136U);
    t7 = *((char **)t6);
    t6 = (t7 + 4);
    t9 = *((unsigned int *)t6);
    t10 = (~(t9));
    t11 = *((unsigned int *)t7);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB29;

LAB30:
LAB31:    goto LAB27;

LAB9:    xsi_set_current_line(146, ng0);

LAB33:    xsi_set_current_line(147, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB34;

LAB35:
LAB36:    goto LAB27;

LAB11:    xsi_set_current_line(156, ng0);

LAB47:    xsi_set_current_line(157, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB48;

LAB49:
LAB50:    goto LAB27;

LAB13:    xsi_set_current_line(162, ng0);

LAB61:    xsi_set_current_line(163, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB62;

LAB63:
LAB64:    goto LAB27;

LAB15:    xsi_set_current_line(168, ng0);

LAB75:    xsi_set_current_line(169, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB76;

LAB77:
LAB78:    goto LAB27;

LAB17:    xsi_set_current_line(174, ng0);

LAB89:    xsi_set_current_line(175, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB90;

LAB91:
LAB92:    goto LAB27;

LAB19:    xsi_set_current_line(180, ng0);

LAB103:    xsi_set_current_line(181, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB104;

LAB105:
LAB106:    goto LAB27;

LAB21:    xsi_set_current_line(186, ng0);

LAB117:    xsi_set_current_line(187, ng0);
    t3 = (t0 + 4416U);
    t5 = *((char **)t3);
    t3 = (t5 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t5);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB118;

LAB119:
LAB120:    goto LAB27;

LAB23:    xsi_set_current_line(199, ng0);

LAB135:    xsi_set_current_line(200, ng0);
    t3 = ((char*)((ng4)));
    t5 = (t0 + 5296);
    xsi_vlogvar_assign_value(t5, t3, 0, 0, 4);
    goto LAB27;

LAB29:    xsi_set_current_line(141, ng0);

LAB32:    xsi_set_current_line(142, ng0);
    t14 = ((char*)((ng7)));
    t15 = (t0 + 5296);
    xsi_vlogvar_assign_value(t15, t14, 0, 0, 4);
    xsi_set_current_line(143, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB31;

LAB34:    xsi_set_current_line(147, ng0);

LAB37:    xsi_set_current_line(148, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng8)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB41;

LAB38:    if (t28 != 0)
        goto LAB40;

LAB39:    *((unsigned int *)t16) = 1;

LAB41:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB42;

LAB43:    xsi_set_current_line(151, ng0);

LAB46:    xsi_set_current_line(152, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB44:    goto LAB36;

LAB40:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB41;

LAB42:    xsi_set_current_line(148, ng0);

LAB45:    xsi_set_current_line(149, ng0);
    t38 = ((char*)((ng9)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(150, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB44;

LAB48:    xsi_set_current_line(157, ng0);

LAB51:    xsi_set_current_line(158, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng1)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB55;

LAB52:    if (t28 != 0)
        goto LAB54;

LAB53:    *((unsigned int *)t16) = 1;

LAB55:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB56;

LAB57:    xsi_set_current_line(159, ng0);

LAB60:    xsi_set_current_line(159, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB58:    goto LAB50;

LAB54:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB55;

LAB56:    xsi_set_current_line(158, ng0);

LAB59:    xsi_set_current_line(158, ng0);
    t38 = ((char*)((ng10)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(158, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB58;

LAB62:    xsi_set_current_line(163, ng0);

LAB65:    xsi_set_current_line(164, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng1)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB69;

LAB66:    if (t28 != 0)
        goto LAB68;

LAB67:    *((unsigned int *)t16) = 1;

LAB69:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB70;

LAB71:    xsi_set_current_line(165, ng0);

LAB74:    xsi_set_current_line(165, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB72:    goto LAB64;

LAB68:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB69;

LAB70:    xsi_set_current_line(164, ng0);

LAB73:    xsi_set_current_line(164, ng0);
    t38 = ((char*)((ng11)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(164, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB72;

LAB76:    xsi_set_current_line(169, ng0);

LAB79:    xsi_set_current_line(170, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng12)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB83;

LAB80:    if (t28 != 0)
        goto LAB82;

LAB81:    *((unsigned int *)t16) = 1;

LAB83:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB84;

LAB85:    xsi_set_current_line(171, ng0);

LAB88:    xsi_set_current_line(171, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB86:    goto LAB78;

LAB82:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB83;

LAB84:    xsi_set_current_line(170, ng0);

LAB87:    xsi_set_current_line(170, ng0);
    t38 = ((char*)((ng13)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(170, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB86;

LAB90:    xsi_set_current_line(175, ng0);

LAB93:    xsi_set_current_line(176, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng12)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB97;

LAB94:    if (t28 != 0)
        goto LAB96;

LAB95:    *((unsigned int *)t16) = 1;

LAB97:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB98;

LAB99:    xsi_set_current_line(177, ng0);

LAB102:    xsi_set_current_line(177, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB100:    goto LAB92;

LAB96:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB97;

LAB98:    xsi_set_current_line(176, ng0);

LAB101:    xsi_set_current_line(176, ng0);
    t38 = ((char*)((ng14)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(176, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB100;

LAB104:    xsi_set_current_line(181, ng0);

LAB107:    xsi_set_current_line(182, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng1)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB111;

LAB108:    if (t28 != 0)
        goto LAB110;

LAB109:    *((unsigned int *)t16) = 1;

LAB111:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB112;

LAB113:    xsi_set_current_line(183, ng0);

LAB116:    xsi_set_current_line(183, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB114:    goto LAB106;

LAB110:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB111;

LAB112:    xsi_set_current_line(182, ng0);

LAB115:    xsi_set_current_line(182, ng0);
    t38 = ((char*)((ng6)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(182, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5616);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    goto LAB114;

LAB118:    xsi_set_current_line(187, ng0);

LAB121:    xsi_set_current_line(188, ng0);
    t6 = (t0 + 5456);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng15)));
    memset(t16, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = (t21 | t24);
    t26 = *((unsigned int *)t17);
    t27 = *((unsigned int *)t18);
    t28 = (t26 | t27);
    t29 = (~(t28));
    t30 = (t25 & t29);
    if (t30 != 0)
        goto LAB125;

LAB122:    if (t28 != 0)
        goto LAB124;

LAB123:    *((unsigned int *)t16) = 1;

LAB125:    t32 = (t16 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t16);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB126;

LAB127:    xsi_set_current_line(194, ng0);

LAB134:    xsi_set_current_line(195, ng0);
    t2 = (t0 + 5456);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = ((char*)((ng1)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t5, 5, t6, 32);
    t7 = (t0 + 5616);
    xsi_vlogvar_assign_value(t7, t16, 0, 0, 5);

LAB128:    goto LAB120;

LAB124:    t31 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB125;

LAB126:    xsi_set_current_line(188, ng0);

LAB129:    xsi_set_current_line(189, ng0);
    t38 = ((char*)((ng16)));
    t39 = (t0 + 5296);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 4);
    xsi_set_current_line(190, ng0);
    t2 = (t0 + 3296U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t9 = *((unsigned int *)t2);
    t10 = (~(t9));
    t11 = *((unsigned int *)t3);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB130;

LAB131:
LAB132:    goto LAB128;

LAB130:    xsi_set_current_line(190, ng0);

LAB133:    xsi_set_current_line(191, ng0);
    t5 = (t0 + 4256U);
    t6 = *((char **)t5);
    t5 = (t0 + 6576);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    memset(t40, 0, 8);
    t15 = (t40 + 4);
    t17 = (t14 + 4);
    t19 = *((unsigned int *)t14);
    t20 = (t19 >> 0);
    *((unsigned int *)t40) = t20;
    t21 = *((unsigned int *)t17);
    t22 = (t21 >> 0);
    *((unsigned int *)t15) = t22;
    t23 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t23 & 32767U);
    t24 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t24 & 32767U);
    xsi_vlogtype_concat(t16, 16, 16, 2U, t40, 15, t6, 1);
    t18 = (t0 + 6736);
    xsi_vlogvar_assign_value(t18, t16, 0, 0, 16);
    xsi_set_current_line(192, ng0);
    t2 = ((char*)((ng7)));
    t3 = (t0 + 6896);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB132;

LAB138:    xsi_set_current_line(210, ng0);
    t7 = ((char*)((ng7)));
    t14 = (t0 + 6096);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 1);
    goto LAB154;

LAB140:    goto LAB138;

LAB142:    goto LAB138;

LAB144:    goto LAB138;

LAB146:    goto LAB138;

LAB148:    xsi_set_current_line(211, ng0);
    t15 = (t0 + 3296U);
    t17 = *((char **)t15);
    memset(t16, 0, 8);
    t15 = (t17 + 4);
    t9 = *((unsigned int *)t15);
    t10 = (~(t9));
    t11 = *((unsigned int *)t17);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB158;

LAB156:    if (*((unsigned int *)t15) == 0)
        goto LAB155;

LAB157:    t18 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t18) = 1;

LAB158:    t31 = (t16 + 4);
    t32 = (t17 + 4);
    t19 = *((unsigned int *)t17);
    t20 = (~(t19));
    *((unsigned int *)t16) = t20;
    *((unsigned int *)t31) = 0;
    if (*((unsigned int *)t32) != 0)
        goto LAB160;

LAB159:    t25 = *((unsigned int *)t16);
    *((unsigned int *)t16) = (t25 & 1U);
    t26 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t26 & 1U);
    t38 = (t0 + 6096);
    xsi_vlogvar_assign_value(t38, t16, 0, 0, 1);
    goto LAB154;

LAB150:    goto LAB148;

LAB155:    *((unsigned int *)t16) = 1;
    goto LAB158;

LAB160:    t21 = *((unsigned int *)t16);
    t22 = *((unsigned int *)t32);
    *((unsigned int *)t16) = (t21 | t22);
    t23 = *((unsigned int *)t31);
    t24 = *((unsigned int *)t32);
    *((unsigned int *)t31) = (t23 | t24);
    goto LAB159;

LAB162:    xsi_set_current_line(217, ng0);
    t14 = ((char*)((ng7)));
    t15 = (t0 + 6416);
    xsi_vlogvar_assign_value(t15, t14, 0, 0, 1);
    goto LAB178;

LAB164:    xsi_set_current_line(218, ng0);
    t3 = (t0 + 5456);
    t7 = (t3 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng5)));
    memset(t45, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t9 = *((unsigned int *)t14);
    t10 = *((unsigned int *)t15);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t17);
    t13 = *((unsigned int *)t18);
    t19 = (t12 ^ t13);
    t20 = (t11 | t19);
    t21 = *((unsigned int *)t17);
    t22 = *((unsigned int *)t18);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB182;

LAB179:    if (t23 != 0)
        goto LAB181;

LAB180:    *((unsigned int *)t45) = 1;

LAB182:    memset(t40, 0, 8);
    t32 = (t45 + 4);
    t26 = *((unsigned int *)t32);
    t27 = (~(t26));
    t28 = *((unsigned int *)t45);
    t29 = (t28 & t27);
    t30 = (t29 & 1U);
    if (t30 != 0)
        goto LAB183;

LAB184:    if (*((unsigned int *)t32) != 0)
        goto LAB185;

LAB186:    t39 = (t40 + 4);
    t33 = *((unsigned int *)t40);
    t34 = *((unsigned int *)t39);
    t35 = (t33 || t34);
    if (t35 > 0)
        goto LAB187;

LAB188:    t36 = *((unsigned int *)t40);
    t37 = (~(t36));
    t47 = *((unsigned int *)t39);
    t48 = (t37 || t47);
    if (t48 > 0)
        goto LAB189;

LAB190:    if (*((unsigned int *)t39) > 0)
        goto LAB191;

LAB192:    if (*((unsigned int *)t40) > 0)
        goto LAB193;

LAB194:    memcpy(t16, t49, 8);

LAB195:    t50 = (t0 + 6416);
    xsi_vlogvar_assign_value(t50, t16, 0, 0, 1);
    goto LAB178;

LAB166:    xsi_set_current_line(219, ng0);
    t3 = (t0 + 3296U);
    t7 = *((char **)t3);
    memset(t40, 0, 8);
    t3 = (t7 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (~(t9));
    t11 = *((unsigned int *)t7);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB196;

LAB197:    if (*((unsigned int *)t3) != 0)
        goto LAB198;

LAB199:    t15 = (t40 + 4);
    t19 = *((unsigned int *)t40);
    t20 = *((unsigned int *)t15);
    t21 = (t19 || t20);
    if (t21 > 0)
        goto LAB200;

LAB201:    t36 = *((unsigned int *)t40);
    t37 = (~(t36));
    t47 = *((unsigned int *)t15);
    t48 = (t37 || t47);
    if (t48 > 0)
        goto LAB202;

LAB203:    if (*((unsigned int *)t15) > 0)
        goto LAB204;

LAB205:    if (*((unsigned int *)t40) > 0)
        goto LAB206;

LAB207:    memcpy(t16, t53, 8);

LAB208:    t69 = (t0 + 6416);
    xsi_vlogvar_assign_value(t69, t16, 0, 0, 1);
    goto LAB178;

LAB168:    xsi_set_current_line(220, ng0);
    t3 = (t0 + 3456U);
    t7 = *((char **)t3);
    t3 = (t0 + 3416U);
    t14 = (t3 + 72U);
    t15 = *((char **)t14);
    t17 = ((char*)((ng12)));
    t18 = (t0 + 5456);
    t31 = (t18 + 56U);
    t32 = *((char **)t31);
    memset(t40, 0, 8);
    xsi_vlog_unsigned_minus(t40, 32, t17, 32, t32, 5);
    xsi_vlog_generic_get_index_select_value(t16, 1, t7, t15, 2, t40, 32, 2);
    t38 = (t0 + 6416);
    xsi_vlogvar_assign_value(t38, t16, 0, 0, 1);
    goto LAB178;

LAB170:    xsi_set_current_line(221, ng0);
    t3 = (t0 + 3616U);
    t7 = *((char **)t3);
    t3 = (t0 + 3576U);
    t14 = (t3 + 72U);
    t15 = *((char **)t14);
    t17 = ((char*)((ng12)));
    t18 = (t0 + 5456);
    t31 = (t18 + 56U);
    t32 = *((char **)t31);
    memset(t40, 0, 8);
    xsi_vlog_unsigned_minus(t40, 32, t17, 32, t32, 5);
    xsi_vlog_generic_get_index_select_value(t16, 1, t7, t15, 2, t40, 32, 2);
    t38 = (t0 + 6416);
    xsi_vlogvar_assign_value(t38, t16, 0, 0, 1);
    goto LAB178;

LAB172:    xsi_set_current_line(222, ng0);
    t3 = (t0 + 5456);
    t7 = (t3 + 56U);
    t14 = *((char **)t7);
    t15 = ((char*)((ng5)));
    memset(t45, 0, 8);
    t17 = (t14 + 4);
    t18 = (t15 + 4);
    t9 = *((unsigned int *)t14);
    t10 = *((unsigned int *)t15);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t17);
    t13 = *((unsigned int *)t18);
    t19 = (t12 ^ t13);
    t20 = (t11 | t19);
    t21 = *((unsigned int *)t17);
    t22 = *((unsigned int *)t18);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB220;

LAB217:    if (t23 != 0)
        goto LAB219;

LAB218:    *((unsigned int *)t45) = 1;

LAB220:    memset(t40, 0, 8);
    t32 = (t45 + 4);
    t26 = *((unsigned int *)t32);
    t27 = (~(t26));
    t28 = *((unsigned int *)t45);
    t29 = (t28 & t27);
    t30 = (t29 & 1U);
    if (t30 != 0)
        goto LAB221;

LAB222:    if (*((unsigned int *)t32) != 0)
        goto LAB223;

LAB224:    t39 = (t40 + 4);
    t33 = *((unsigned int *)t40);
    t34 = *((unsigned int *)t39);
    t35 = (t33 || t34);
    if (t35 > 0)
        goto LAB225;

LAB226:    t36 = *((unsigned int *)t40);
    t37 = (~(t36));
    t47 = *((unsigned int *)t39);
    t48 = (t37 || t47);
    if (t48 > 0)
        goto LAB227;

LAB228:    if (*((unsigned int *)t39) > 0)
        goto LAB229;

LAB230:    if (*((unsigned int *)t40) > 0)
        goto LAB231;

LAB232:    memcpy(t16, t49, 8);

LAB233:    t50 = (t0 + 6416);
    xsi_vlogvar_assign_value(t50, t16, 0, 0, 1);
    goto LAB178;

LAB174:    xsi_set_current_line(223, ng0);
    t3 = (t0 + 3776U);
    t7 = *((char **)t3);
    t3 = (t0 + 3736U);
    t14 = (t3 + 72U);
    t15 = *((char **)t14);
    t17 = ((char*)((ng15)));
    t18 = (t0 + 5456);
    t31 = (t18 + 56U);
    t32 = *((char **)t31);
    memset(t40, 0, 8);
    xsi_vlog_unsigned_minus(t40, 32, t17, 32, t32, 5);
    xsi_vlog_generic_get_index_select_value(t16, 1, t7, t15, 2, t40, 32, 2);
    t38 = (t0 + 6416);
    xsi_vlogvar_assign_value(t38, t16, 0, 0, 1);
    goto LAB178;

LAB181:    t31 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB182;

LAB183:    *((unsigned int *)t40) = 1;
    goto LAB186;

LAB185:    t38 = (t40 + 4);
    *((unsigned int *)t40) = 1;
    *((unsigned int *)t38) = 1;
    goto LAB186;

LAB187:    t46 = ((char*)((ng4)));
    goto LAB188;

LAB189:    t49 = ((char*)((ng7)));
    goto LAB190;

LAB191:    xsi_vlog_unsigned_bit_combine(t16, 1, t46, 1, t49, 1);
    goto LAB195;

LAB193:    memcpy(t16, t46, 8);
    goto LAB195;

LAB196:    *((unsigned int *)t40) = 1;
    goto LAB199;

LAB198:    t14 = (t40 + 4);
    *((unsigned int *)t40) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB199;

LAB200:    t17 = (t0 + 5456);
    t18 = (t17 + 56U);
    t31 = *((char **)t18);
    t32 = ((char*)((ng5)));
    memset(t45, 0, 8);
    t38 = (t31 + 4);
    t39 = (t32 + 4);
    t22 = *((unsigned int *)t31);
    t23 = *((unsigned int *)t32);
    t24 = (t22 ^ t23);
    t25 = *((unsigned int *)t38);
    t26 = *((unsigned int *)t39);
    t27 = (t25 ^ t26);
    t28 = (t24 | t27);
    t29 = *((unsigned int *)t38);
    t30 = *((unsigned int *)t39);
    t33 = (t29 | t30);
    t34 = (~(t33));
    t35 = (t28 & t34);
    if (t35 != 0)
        goto LAB212;

LAB209:    if (t33 != 0)
        goto LAB211;

LAB210:    *((unsigned int *)t45) = 1;

LAB212:    goto LAB201;

LAB202:    t49 = (t0 + 5456);
    t50 = (t49 + 56U);
    t51 = *((char **)t50);
    t52 = ((char*)((ng1)));
    memset(t53, 0, 8);
    t54 = (t51 + 4);
    t55 = (t52 + 4);
    t56 = *((unsigned int *)t51);
    t57 = *((unsigned int *)t52);
    t58 = (t56 ^ t57);
    t59 = *((unsigned int *)t54);
    t60 = *((unsigned int *)t55);
    t61 = (t59 ^ t60);
    t62 = (t58 | t61);
    t63 = *((unsigned int *)t54);
    t64 = *((unsigned int *)t55);
    t65 = (t63 | t64);
    t66 = (~(t65));
    t67 = (t62 & t66);
    if (t67 != 0)
        goto LAB216;

LAB213:    if (t65 != 0)
        goto LAB215;

LAB214:    *((unsigned int *)t53) = 1;

LAB216:    goto LAB203;

LAB204:    xsi_vlog_unsigned_bit_combine(t16, 1, t45, 1, t53, 1);
    goto LAB208;

LAB206:    memcpy(t16, t45, 8);
    goto LAB208;

LAB211:    t46 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t46) = 1;
    goto LAB212;

LAB215:    t68 = (t53 + 4);
    *((unsigned int *)t53) = 1;
    *((unsigned int *)t68) = 1;
    goto LAB216;

LAB219:    t31 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB220;

LAB221:    *((unsigned int *)t40) = 1;
    goto LAB224;

LAB223:    t38 = (t40 + 4);
    *((unsigned int *)t40) = 1;
    *((unsigned int *)t38) = 1;
    goto LAB224;

LAB225:    t46 = ((char*)((ng7)));
    goto LAB226;

LAB227:    t49 = ((char*)((ng4)));
    goto LAB228;

LAB229:    xsi_vlog_unsigned_bit_combine(t16, 1, t46, 1, t49, 1);
    goto LAB233;

LAB231:    memcpy(t16, t46, 8);
    goto LAB233;

}


extern void work_m_06475127290308870164_0020967533_init()
{
	static char *pe[] = {(void *)NetDecl_61_0,(void *)Cont_77_1,(void *)Cont_80_2,(void *)Cont_83_3,(void *)Always_90_4,(void *)Always_101_5,(void *)Always_129_6};
	xsi_register_didat("work_m_06475127290308870164_0020967533", "isim/fpga_core_isim_beh.exe.sim/work/m_06475127290308870164_0020967533.didat");
	xsi_register_executes(pe);
}
