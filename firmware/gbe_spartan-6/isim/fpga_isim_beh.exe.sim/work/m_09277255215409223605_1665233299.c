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
static const char *ng0 = "/home/ise/VM_ISE/gbe_spartan-6/rtl/debounce_switch.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {0U, 0U};



static void Cont_54_0(char *t0)
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

LAB0:    t1 = (t0 + 3728U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(54, ng0);
    t2 = (t0 + 2656);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 4392);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 1023U;
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
    xsi_driver_vfirst_trans(t5, 0, 9);
    t18 = (t0 + 4296);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Always_58_1(char *t0)
{
    char t13[8];
    char t15[8];
    char t16[8];
    char t45[8];
    char t52[8];
    char t56[8];
    char t57[8];
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
    char *t14;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    int t28;
    char *t29;
    unsigned int t30;
    int t31;
    int t32;
    unsigned int t33;
    unsigned int t34;
    int t35;
    int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    char *t46;
    char *t47;
    char *t48;
    char *t49;
    char *t50;
    char *t51;
    char *t53;
    char *t54;
    char *t55;
    char *t58;
    char *t59;
    char *t60;
    char *t61;
    char *t62;
    char *t63;
    char *t64;
    char *t65;
    char *t66;
    char *t67;
    char *t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;

LAB0:    t1 = (t0 + 3976U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(58, ng0);
    t2 = (t0 + 4312);
    *((int *)t2) = 1;
    t3 = (t0 + 4008);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(58, ng0);

LAB5:    xsi_set_current_line(59, ng0);
    t4 = (t0 + 1616U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(66, ng0);

LAB16:    xsi_set_current_line(67, ng0);
    t2 = (t0 + 2336);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 744);
    t11 = *((char **)t5);
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    if (*((unsigned int *)t5) != 0)
        goto LAB18;

LAB17:    t12 = (t11 + 4);
    if (*((unsigned int *)t12) != 0)
        goto LAB18;

LAB21:    if (*((unsigned int *)t4) < *((unsigned int *)t11))
        goto LAB19;

LAB20:    t17 = (t13 + 4);
    t6 = *((unsigned int *)t17);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB22;

LAB23:    xsi_set_current_line(69, ng0);

LAB26:    xsi_set_current_line(70, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 2336);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 24, 0LL);

LAB24:    xsi_set_current_line(73, ng0);
    t2 = (t0 + 2336);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    t12 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t11);
    t10 = *((unsigned int *)t12);
    t27 = (t9 ^ t10);
    t30 = (t8 | t27);
    t33 = *((unsigned int *)t11);
    t34 = *((unsigned int *)t12);
    t37 = (t33 | t34);
    t38 = (~(t37));
    t39 = (t30 & t38);
    if (t39 != 0)
        goto LAB30;

LAB27:    if (t37 != 0)
        goto LAB29;

LAB28:    *((unsigned int *)t13) = 1;

LAB30:    t17 = (t13 + 4);
    t40 = *((unsigned int *)t17);
    t41 = (~(t40));
    t42 = *((unsigned int *)t13);
    t43 = (t42 & t41);
    t44 = (t43 != 0);
    if (t44 > 0)
        goto LAB31;

LAB32:
LAB33:    xsi_set_current_line(79, ng0);
    xsi_set_current_line(79, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2816);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);

LAB41:    t2 = (t0 + 2816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 472);
    t11 = *((char **)t5);
    memset(t13, 0, 8);
    xsi_vlog_signed_less(t13, 32, t4, 32, t11, 32);
    t5 = (t13 + 4);
    t6 = *((unsigned int *)t5);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB42;

LAB43:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(59, ng0);

LAB9:    xsi_set_current_line(60, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 2336);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 24, 0LL);
    xsi_set_current_line(61, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2656);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 10, 0LL);
    xsi_set_current_line(63, ng0);
    xsi_set_current_line(63, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2816);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);

LAB10:    t2 = (t0 + 2816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 472);
    t11 = *((char **)t5);
    memset(t13, 0, 8);
    xsi_vlog_signed_less(t13, 32, t4, 32, t11, 32);
    t5 = (t13 + 4);
    t6 = *((unsigned int *)t5);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB11;

LAB12:    goto LAB8;

LAB11:    xsi_set_current_line(63, ng0);

LAB13:    xsi_set_current_line(64, ng0);
    t12 = ((char*)((ng1)));
    t14 = (t0 + 2496);
    t17 = (t0 + 2496);
    t18 = (t17 + 72U);
    t19 = *((char **)t18);
    t20 = (t0 + 2496);
    t21 = (t20 + 64U);
    t22 = *((char **)t21);
    t23 = (t0 + 2816);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    xsi_vlog_generic_convert_array_indices(t15, t16, t19, t22, 2, 1, t25, 32, 1);
    t26 = (t15 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (!(t27));
    t29 = (t16 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (!(t30));
    t32 = (t28 && t31);
    if (t32 == 1)
        goto LAB14;

LAB15:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 2816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t4, 32, t5, 32);
    t11 = (t0 + 2816);
    xsi_vlogvar_assign_value(t11, t13, 0, 0, 32);
    goto LAB10;

LAB14:    t33 = *((unsigned int *)t15);
    t34 = *((unsigned int *)t16);
    t35 = (t33 - t34);
    t36 = (t35 + 1);
    xsi_vlogvar_wait_assign_value(t14, t12, 0, *((unsigned int *)t16), t36, 0LL);
    goto LAB15;

LAB18:    t14 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB20;

LAB19:    *((unsigned int *)t13) = 1;
    goto LAB20;

LAB22:    xsi_set_current_line(67, ng0);

LAB25:    xsi_set_current_line(68, ng0);
    t18 = (t0 + 2336);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    t21 = ((char*)((ng3)));
    memset(t15, 0, 8);
    xsi_vlog_unsigned_add(t15, 24, t20, 24, t21, 24);
    t22 = (t0 + 2336);
    xsi_vlogvar_wait_assign_value(t22, t15, 0, 0, 24, 0LL);
    goto LAB24;

LAB29:    t14 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB30;

LAB31:    xsi_set_current_line(73, ng0);

LAB34:    xsi_set_current_line(74, ng0);
    xsi_set_current_line(74, ng0);
    t18 = ((char*)((ng1)));
    t19 = (t0 + 2816);
    xsi_vlogvar_assign_value(t19, t18, 0, 0, 32);

LAB35:    t2 = (t0 + 2816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 472);
    t11 = *((char **)t5);
    memset(t13, 0, 8);
    xsi_vlog_signed_less(t13, 32, t4, 32, t11, 32);
    t5 = (t13 + 4);
    t6 = *((unsigned int *)t5);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB36;

LAB37:    goto LAB33;

LAB36:    xsi_set_current_line(74, ng0);

LAB38:    xsi_set_current_line(75, ng0);
    t12 = (t0 + 1776U);
    t14 = *((char **)t12);
    t12 = (t0 + 1736U);
    t17 = (t12 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2816);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    xsi_vlog_generic_get_index_select_value(t16, 1, t14, t18, 2, t21, 32, 1);
    t22 = (t0 + 2496);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t0 + 2496);
    t26 = (t25 + 72U);
    t29 = *((char **)t26);
    t46 = (t0 + 2496);
    t47 = (t46 + 64U);
    t48 = *((char **)t47);
    t49 = (t0 + 2816);
    t50 = (t49 + 56U);
    t51 = *((char **)t50);
    xsi_vlog_generic_get_array_select_value(t45, 4, t24, t29, t48, 2, 1, t51, 32, 1);
    memset(t52, 0, 8);
    t53 = (t52 + 4);
    t54 = (t45 + 4);
    t27 = *((unsigned int *)t45);
    t30 = (t27 >> 0);
    *((unsigned int *)t52) = t30;
    t33 = *((unsigned int *)t54);
    t34 = (t33 >> 0);
    *((unsigned int *)t53) = t34;
    t37 = *((unsigned int *)t52);
    *((unsigned int *)t52) = (t37 & 7U);
    t38 = *((unsigned int *)t53);
    *((unsigned int *)t53) = (t38 & 7U);
    xsi_vlogtype_concat(t15, 4, 4, 2U, t52, 3, t16, 1);
    t55 = (t0 + 2496);
    t58 = (t0 + 2496);
    t59 = (t58 + 72U);
    t60 = *((char **)t59);
    t61 = (t0 + 2496);
    t62 = (t61 + 64U);
    t63 = *((char **)t62);
    t64 = (t0 + 2816);
    t65 = (t64 + 56U);
    t66 = *((char **)t65);
    xsi_vlog_generic_convert_array_indices(t56, t57, t60, t63, 2, 1, t66, 32, 1);
    t67 = (t56 + 4);
    t39 = *((unsigned int *)t67);
    t28 = (!(t39));
    t68 = (t57 + 4);
    t40 = *((unsigned int *)t68);
    t31 = (!(t40));
    t32 = (t28 && t31);
    if (t32 == 1)
        goto LAB39;

LAB40:    xsi_set_current_line(74, ng0);
    t2 = (t0 + 2816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t4, 32, t5, 32);
    t11 = (t0 + 2816);
    xsi_vlogvar_assign_value(t11, t13, 0, 0, 32);
    goto LAB35;

LAB39:    t41 = *((unsigned int *)t56);
    t42 = *((unsigned int *)t57);
    t35 = (t41 - t42);
    t36 = (t35 + 1);
    xsi_vlogvar_wait_assign_value(t55, t15, 0, *((unsigned int *)t57), t36, 0LL);
    goto LAB40;

LAB42:    xsi_set_current_line(79, ng0);

LAB44:    xsi_set_current_line(80, ng0);
    t12 = (t0 + 2496);
    t14 = (t12 + 56U);
    t17 = *((char **)t14);
    t18 = (t0 + 2496);
    t19 = (t18 + 72U);
    t20 = *((char **)t19);
    t21 = (t0 + 2496);
    t22 = (t21 + 64U);
    t23 = *((char **)t22);
    t24 = (t0 + 2816);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    xsi_vlog_generic_get_array_select_value(t16, 4, t17, t20, t23, 2, 1, t26, 32, 1);
    memset(t15, 0, 8);
    t29 = (t16 + 4);
    t27 = *((unsigned int *)t29);
    t30 = (~(t27));
    t33 = *((unsigned int *)t16);
    t34 = (t33 & t30);
    t37 = (t34 & 15U);
    if (t37 != 0)
        goto LAB45;

LAB46:    if (*((unsigned int *)t29) != 0)
        goto LAB47;

LAB48:    t47 = ((char*)((ng1)));
    memset(t45, 0, 8);
    t48 = (t15 + 4);
    t49 = (t47 + 4);
    t38 = *((unsigned int *)t15);
    t39 = *((unsigned int *)t47);
    t40 = (t38 ^ t39);
    t41 = *((unsigned int *)t48);
    t42 = *((unsigned int *)t49);
    t43 = (t41 ^ t42);
    t44 = (t40 | t43);
    t69 = *((unsigned int *)t48);
    t70 = *((unsigned int *)t49);
    t71 = (t69 | t70);
    t72 = (~(t71));
    t73 = (t44 & t72);
    if (t73 != 0)
        goto LAB52;

LAB49:    if (t71 != 0)
        goto LAB51;

LAB50:    *((unsigned int *)t45) = 1;

LAB52:    t51 = (t45 + 4);
    t74 = *((unsigned int *)t51);
    t75 = (~(t74));
    t76 = *((unsigned int *)t45);
    t77 = (t76 & t75);
    t78 = (t77 != 0);
    if (t78 > 0)
        goto LAB53;

LAB54:    xsi_set_current_line(82, ng0);
    t2 = (t0 + 2496);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2496);
    t11 = (t5 + 72U);
    t12 = *((char **)t11);
    t14 = (t0 + 2496);
    t17 = (t14 + 64U);
    t18 = *((char **)t17);
    t19 = (t0 + 2816);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    xsi_vlog_generic_get_array_select_value(t15, 4, t4, t12, t18, 2, 1, t21, 32, 1);
    memset(t13, 0, 8);
    t22 = (t15 + 4);
    t6 = *((unsigned int *)t15);
    t7 = *((unsigned int *)t22);
    t8 = (t6 | t7);
    if (t8 != 15U)
        goto LAB60;

LAB59:    if (*((unsigned int *)t22) == 0)
        goto LAB61;

LAB62:    t23 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t23) = 1;

LAB60:    t24 = ((char*)((ng2)));
    memset(t16, 0, 8);
    t25 = (t13 + 4);
    t26 = (t24 + 4);
    t9 = *((unsigned int *)t13);
    t10 = *((unsigned int *)t24);
    t27 = (t9 ^ t10);
    t30 = *((unsigned int *)t25);
    t33 = *((unsigned int *)t26);
    t34 = (t30 ^ t33);
    t37 = (t27 | t34);
    t38 = *((unsigned int *)t25);
    t39 = *((unsigned int *)t26);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB66;

LAB63:    if (t40 != 0)
        goto LAB65;

LAB64:    *((unsigned int *)t16) = 1;

LAB66:    t46 = (t16 + 4);
    t43 = *((unsigned int *)t46);
    t44 = (~(t43));
    t69 = *((unsigned int *)t16);
    t70 = (t69 & t44);
    t71 = (t70 != 0);
    if (t71 > 0)
        goto LAB67;

LAB68:    xsi_set_current_line(84, ng0);

LAB73:    xsi_set_current_line(85, ng0);
    t2 = (t0 + 2656);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2656);
    t11 = (t5 + 72U);
    t12 = *((char **)t11);
    t14 = (t0 + 2816);
    t17 = (t14 + 56U);
    t18 = *((char **)t17);
    xsi_vlog_generic_get_index_select_value(t13, 1, t4, t12, 2, t18, 32, 1);
    t19 = (t0 + 2656);
    t20 = (t0 + 2656);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t23 = (t0 + 2816);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    xsi_vlog_generic_convert_bit_index(t15, t22, 2, t25, 32, 1);
    t26 = (t15 + 4);
    t6 = *((unsigned int *)t26);
    t28 = (!(t6));
    if (t28 == 1)
        goto LAB74;

LAB75:
LAB69:
LAB55:    xsi_set_current_line(79, ng0);
    t2 = (t0 + 2816);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t4, 32, t5, 32);
    t11 = (t0 + 2816);
    xsi_vlogvar_assign_value(t11, t13, 0, 0, 32);
    goto LAB41;

LAB45:    *((unsigned int *)t15) = 1;
    goto LAB48;

LAB47:    t46 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t46) = 1;
    goto LAB48;

LAB51:    t50 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t50) = 1;
    goto LAB52;

LAB53:    xsi_set_current_line(80, ng0);

LAB56:    xsi_set_current_line(81, ng0);
    t53 = ((char*)((ng1)));
    t54 = (t0 + 2656);
    t55 = (t0 + 2656);
    t58 = (t55 + 72U);
    t59 = *((char **)t58);
    t60 = (t0 + 2816);
    t61 = (t60 + 56U);
    t62 = *((char **)t61);
    xsi_vlog_generic_convert_bit_index(t52, t59, 2, t62, 32, 1);
    t63 = (t52 + 4);
    t79 = *((unsigned int *)t63);
    t28 = (!(t79));
    if (t28 == 1)
        goto LAB57;

LAB58:    goto LAB55;

LAB57:    xsi_vlogvar_wait_assign_value(t54, t53, 0, *((unsigned int *)t52), 1, 0LL);
    goto LAB58;

LAB61:    *((unsigned int *)t13) = 1;
    goto LAB60;

LAB65:    t29 = (t16 + 4);
    *((unsigned int *)t16) = 1;
    *((unsigned int *)t29) = 1;
    goto LAB66;

LAB67:    xsi_set_current_line(82, ng0);

LAB70:    xsi_set_current_line(83, ng0);
    t47 = ((char*)((ng2)));
    t48 = (t0 + 2656);
    t49 = (t0 + 2656);
    t50 = (t49 + 72U);
    t51 = *((char **)t50);
    t53 = (t0 + 2816);
    t54 = (t53 + 56U);
    t55 = *((char **)t54);
    xsi_vlog_generic_convert_bit_index(t45, t51, 2, t55, 32, 1);
    t58 = (t45 + 4);
    t72 = *((unsigned int *)t58);
    t28 = (!(t72));
    if (t28 == 1)
        goto LAB71;

LAB72:    goto LAB69;

LAB71:    xsi_vlogvar_wait_assign_value(t48, t47, 0, *((unsigned int *)t45), 1, 0LL);
    goto LAB72;

LAB74:    xsi_vlogvar_wait_assign_value(t19, t13, 0, *((unsigned int *)t15), 1, 0LL);
    goto LAB75;

}


extern void work_m_09277255215409223605_1665233299_init()
{
	static char *pe[] = {(void *)Cont_54_0,(void *)Always_58_1};
	xsi_register_didat("work_m_09277255215409223605_1665233299", "isim/fpga_isim_beh.exe.sim/work/m_09277255215409223605_1665233299.didat");
	xsi_register_executes(pe);
}
