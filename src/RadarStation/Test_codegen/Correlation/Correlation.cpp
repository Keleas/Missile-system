/*
 * Correlation.cpp
 *
 * Code generation for function 'Correlation'
 *
 */

/* Include files */
#include "Correlation.h"
#include "Correlation_data.h"
#include "mtimes.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"
#include "xcorr.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 10,    /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtMCInfo emlrtMCI = { 2,     /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo b_emlrtMCI = { 12,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo c_emlrtMCI = { 13,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo d_emlrtMCI = { 14,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo e_emlrtMCI = { 15,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo f_emlrtMCI = { 16,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo g_emlrtMCI = { 17,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo h_emlrtMCI = { 18,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo i_emlrtMCI = { 20,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo j_emlrtMCI = { 21,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo k_emlrtMCI = { 22,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo l_emlrtMCI = { 23,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo m_emlrtMCI = { 24,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo n_emlrtMCI = { 25,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo o_emlrtMCI = { 27,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo p_emlrtMCI = { 28,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo q_emlrtMCI = { 29,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo r_emlrtMCI = { 30,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo s_emlrtMCI = { 31,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo t_emlrtMCI = { 32,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo u_emlrtMCI = { 34,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo v_emlrtMCI = { 35,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo w_emlrtMCI = { 36,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo x_emlrtMCI = { 37,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static emlrtMCInfo y_emlrtMCI = { 38,  /* lineNo */
  5,                                   /* colNo */
  "Correlation",                       /* fName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pName */
};

static const real_T dv[801] = { -10.0, -9.975, -9.95, -9.925, -9.9, -9.875,
  -9.85, -9.825, -9.8, -9.775, -9.75, -9.725, -9.7, -9.675, -9.65, -9.625, -9.6,
  -9.575, -9.55, -9.525, -9.5, -9.475, -9.45, -9.425, -9.4, -9.375, -9.35,
  -9.325, -9.3, -9.275, -9.25, -9.225, -9.2, -9.175, -9.15, -9.125, -9.1, -9.075,
  -9.05, -9.025, -9.0, -8.975, -8.95, -8.925, -8.9, -8.875, -8.85, -8.825, -8.8,
  -8.775, -8.75, -8.725, -8.7, -8.675, -8.65, -8.625, -8.6, -8.575, -8.55,
  -8.525, -8.5, -8.475, -8.45, -8.425, -8.4, -8.375, -8.35, -8.325, -8.3, -8.275,
  -8.25, -8.225, -8.2, -8.175, -8.15, -8.125, -8.1, -8.075, -8.05, -8.025, -8.0,
  -7.975, -7.9499999999999993, -7.925, -7.9, -7.875, -7.85, -7.8249999999999993,
  -7.8, -7.775, -7.75, -7.725, -7.6999999999999993, -7.675, -7.65, -7.625, -7.6,
  -7.5749999999999993, -7.55, -7.525, -7.5, -7.475, -7.4499999999999993, -7.425,
  -7.4, -7.375, -7.35, -7.3249999999999993, -7.3, -7.275, -7.25, -7.225,
  -7.1999999999999993, -7.175, -7.15, -7.125, -7.1, -7.0749999999999993, -7.05,
  -7.025, -7.0, -6.975, -6.9499999999999993, -6.925, -6.9, -6.875, -6.85,
  -6.8249999999999993, -6.8, -6.775, -6.75, -6.725, -6.6999999999999993, -6.675,
  -6.65, -6.625, -6.6, -6.5749999999999993, -6.55, -6.525, -6.5, -6.475,
  -6.4499999999999993, -6.425, -6.4, -6.375, -6.35, -6.3249999999999993, -6.3,
  -6.275, -6.25, -6.225, -6.1999999999999993, -6.175, -6.15, -6.125, -6.1,
  -6.0749999999999993, -6.05, -6.025, -6.0, -5.975, -5.95, -5.925,
  -5.8999999999999995, -5.875, -5.85, -5.825, -5.8, -5.7749999999999995, -5.75,
  -5.725, -5.7, -5.675, -5.6499999999999995, -5.625, -5.6, -5.575, -5.55,
  -5.5249999999999995, -5.5, -5.475, -5.45, -5.425, -5.3999999999999995, -5.375,
  -5.35, -5.325, -5.3, -5.2749999999999995, -5.25, -5.225, -5.1999999999999993,
  -5.175, -5.1499999999999995, -5.125, -5.1, -5.0749999999999993, -5.05,
  -5.0249999999999995, -5.0, -4.9750000000000005, -4.95, -4.9250000000000007,
  -4.9, -4.875, -4.8500000000000005, -4.825, -4.8000000000000007, -4.775, -4.75,
  -4.7250000000000005, -4.7, -4.675, -4.65, -4.625, -4.6000000000000005, -4.575,
  -4.55, -4.525, -4.5, -4.4750000000000005, -4.45, -4.425, -4.4, -4.375,
  -4.3500000000000005, -4.325, -4.3, -4.275, -4.25, -4.2250000000000005, -4.2,
  -4.175, -4.15, -4.125, -4.1000000000000005, -4.075, -4.05, -4.025, -4.0,
  -3.975, -3.95, -3.9250000000000003, -3.9000000000000004, -3.875, -3.85, -3.825,
  -3.8000000000000003, -3.7750000000000004, -3.75, -3.725, -3.7,
  -3.6750000000000003, -3.6500000000000004, -3.625, -3.6, -3.575,
  -3.5500000000000003, -3.5250000000000004, -3.5, -3.475, -3.45,
  -3.4250000000000003, -3.4000000000000004, -3.375, -3.35, -3.325,
  -3.3000000000000003, -3.2750000000000004, -3.25, -3.225, -3.2,
  -3.1750000000000003, -3.1500000000000004, -3.125, -3.1, -3.075,
  -3.0500000000000003, -3.0250000000000004, -3.0, -2.975, -2.95,
  -2.9250000000000003, -2.9000000000000004, -2.875, -2.85, -2.825,
  -2.8000000000000003, -2.7750000000000004, -2.75, -2.725, -2.7,
  -2.6750000000000003, -2.6500000000000004, -2.625, -2.6, -2.575,
  -2.5500000000000003, -2.5250000000000004, -2.5, -2.475, -2.45,
  -2.4250000000000003, -2.4000000000000004, -2.375, -2.35, -2.325,
  -2.3000000000000003, -2.275, -2.25, -2.225, -2.2, -2.1750000000000003, -2.15,
  -2.125, -2.1, -2.075, -2.0500000000000003, -2.025, -2.0, -1.975,
  -1.9500000000000002, -1.925, -1.9000000000000001, -1.875, -1.85,
  -1.8250000000000002, -1.8, -1.7750000000000001, -1.75, -1.725,
  -1.7000000000000002, -1.675, -1.6500000000000001, -1.625, -1.6,
  -1.5750000000000002, -1.55, -1.5250000000000001, -1.5, -1.475,
  -1.4500000000000002, -1.425, -1.4000000000000001, -1.375, -1.35,
  -1.3250000000000002, -1.3, -1.2750000000000001, -1.25, -1.225,
  -1.2000000000000002, -1.175, -1.1500000000000001, -1.125, -1.1, -1.075, -1.05,
  -1.0250000000000001, -1.0, -0.97500000000000009, -0.95000000000000007, -0.925,
  -0.9, -0.875, -0.85000000000000009, -0.82500000000000007, -0.8, -0.775, -0.75,
  -0.72500000000000009, -0.70000000000000007, -0.675, -0.65, -0.625,
  -0.60000000000000009, -0.57500000000000007, -0.55, -0.525, -0.5,
  -0.47500000000000003, -0.45, -0.42500000000000004, -0.4, -0.375,
  -0.35000000000000003, -0.325, -0.30000000000000004, -0.275, -0.25, -0.225,
  -0.2, -0.17500000000000002, -0.15000000000000002, -0.125, -0.1,
  -0.075000000000000011, -0.05, -0.025, 0.0, 0.025, 0.05, 0.075000000000000011,
  0.1, 0.125, 0.15000000000000002, 0.17500000000000002, 0.2, 0.225, 0.25, 0.275,
  0.30000000000000004, 0.325, 0.35000000000000003, 0.375, 0.4,
  0.42500000000000004, 0.45, 0.47500000000000003, 0.5, 0.525, 0.55,
  0.57500000000000007, 0.60000000000000009, 0.625, 0.65, 0.675,
  0.70000000000000007, 0.72500000000000009, 0.75, 0.775, 0.8,
  0.82500000000000007, 0.85000000000000009, 0.875, 0.9, 0.925,
  0.95000000000000007, 0.97500000000000009, 1.0, 1.0250000000000001, 1.05, 1.075,
  1.1, 1.125, 1.1500000000000001, 1.175, 1.2000000000000002, 1.225, 1.25,
  1.2750000000000001, 1.3, 1.3250000000000002, 1.35, 1.375, 1.4000000000000001,
  1.425, 1.4500000000000002, 1.475, 1.5, 1.5250000000000001, 1.55,
  1.5750000000000002, 1.6, 1.625, 1.6500000000000001, 1.675, 1.7000000000000002,
  1.725, 1.75, 1.7750000000000001, 1.8, 1.8250000000000002, 1.85, 1.875,
  1.9000000000000001, 1.925, 1.9500000000000002, 1.975, 2.0, 2.025,
  2.0500000000000003, 2.075, 2.1, 2.125, 2.15, 2.1750000000000003, 2.2, 2.225,
  2.25, 2.275, 2.3000000000000003, 2.325, 2.35, 2.375, 2.4000000000000004,
  2.4250000000000003, 2.45, 2.475, 2.5, 2.5250000000000004, 2.5500000000000003,
  2.575, 2.6, 2.625, 2.6500000000000004, 2.6750000000000003, 2.7, 2.725, 2.75,
  2.7750000000000004, 2.8000000000000003, 2.825, 2.85, 2.875, 2.9000000000000004,
  2.9250000000000003, 2.95, 2.975, 3.0, 3.0250000000000004, 3.0500000000000003,
  3.075, 3.1, 3.125, 3.1500000000000004, 3.1750000000000003, 3.2, 3.225, 3.25,
  3.2750000000000004, 3.3000000000000003, 3.325, 3.35, 3.375, 3.4000000000000004,
  3.4250000000000003, 3.45, 3.475, 3.5, 3.5250000000000004, 3.5500000000000003,
  3.575, 3.6, 3.625, 3.6500000000000004, 3.6750000000000003, 3.7, 3.725, 3.75,
  3.7750000000000004, 3.8000000000000003, 3.825, 3.85, 3.875, 3.9000000000000004,
  3.9250000000000003, 3.95, 3.975, 4.0, 4.025, 4.05, 4.075, 4.1000000000000005,
  4.125, 4.15, 4.175, 4.2, 4.2250000000000005, 4.25, 4.275, 4.3, 4.325,
  4.3500000000000005, 4.375, 4.4, 4.425, 4.45, 4.4750000000000005, 4.5, 4.525,
  4.55, 4.575, 4.6000000000000005, 4.625, 4.65, 4.675, 4.7, 4.7250000000000005,
  4.75, 4.775, 4.8000000000000007, 4.825, 4.8500000000000005, 4.875, 4.9,
  4.9250000000000007, 4.95, 4.9750000000000005, 5.0, 5.0249999999999995, 5.05,
  5.0749999999999993, 5.1, 5.125, 5.1499999999999995, 5.175, 5.1999999999999993,
  5.225, 5.25, 5.2749999999999995, 5.3, 5.325, 5.35, 5.375, 5.3999999999999995,
  5.425, 5.45, 5.475, 5.5, 5.5249999999999995, 5.55, 5.575, 5.6, 5.625,
  5.6499999999999995, 5.675, 5.7, 5.725, 5.75, 5.7749999999999995, 5.8, 5.825,
  5.85, 5.875, 5.8999999999999995, 5.925, 5.95, 5.975, 6.0, 6.025, 6.05,
  6.0749999999999993, 6.1, 6.125, 6.15, 6.175, 6.1999999999999993, 6.225, 6.25,
  6.275, 6.3, 6.3249999999999993, 6.35, 6.375, 6.4, 6.425, 6.4499999999999993,
  6.475, 6.5, 6.525, 6.55, 6.5749999999999993, 6.6, 6.625, 6.65, 6.675,
  6.6999999999999993, 6.725, 6.75, 6.775, 6.8, 6.8249999999999993, 6.85, 6.875,
  6.9, 6.925, 6.9499999999999993, 6.975, 7.0, 7.025, 7.05, 7.0749999999999993,
  7.1, 7.125, 7.15, 7.175, 7.1999999999999993, 7.225, 7.25, 7.275, 7.3,
  7.3249999999999993, 7.35, 7.375, 7.4, 7.425, 7.4499999999999993, 7.475, 7.5,
  7.525, 7.55, 7.5749999999999993, 7.6, 7.625, 7.65, 7.675, 7.6999999999999993,
  7.725, 7.75, 7.775, 7.8, 7.8249999999999993, 7.85, 7.875, 7.9, 7.925,
  7.9499999999999993, 7.975, 8.0, 8.025, 8.05, 8.075, 8.1, 8.125, 8.15, 8.175,
  8.2, 8.225, 8.25, 8.275, 8.3, 8.325, 8.35, 8.375, 8.4, 8.425, 8.45, 8.475, 8.5,
  8.525, 8.55, 8.575, 8.6, 8.625, 8.65, 8.675, 8.7, 8.725, 8.75, 8.775, 8.8,
  8.825, 8.85, 8.875, 8.9, 8.925, 8.95, 8.975, 9.0, 9.025, 9.05, 9.075, 9.1,
  9.125, 9.15, 9.175, 9.2, 9.225, 9.25, 9.275, 9.3, 9.325, 9.35, 9.375, 9.4,
  9.425, 9.45, 9.475, 9.5, 9.525, 9.55, 9.575, 9.6, 9.625, 9.65, 9.675, 9.7,
  9.725, 9.75, 9.775, 9.8, 9.825, 9.85, 9.875, 9.9, 9.925, 9.95, 9.975, 10.0 };

static emlrtRSInfo v_emlrtRSI = { 2,   /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo w_emlrtRSI = { 12,  /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo x_emlrtRSI = { 34,  /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo y_emlrtRSI = { 27,  /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo ab_emlrtRSI = { 20, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo bb_emlrtRSI = { 13, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo cb_emlrtRSI = { 28, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo db_emlrtRSI = { 21, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo eb_emlrtRSI = { 14, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo fb_emlrtRSI = { 36, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo gb_emlrtRSI = { 29, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo hb_emlrtRSI = { 22, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo ib_emlrtRSI = { 15, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo jb_emlrtRSI = { 37, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo kb_emlrtRSI = { 30, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo lb_emlrtRSI = { 23, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo mb_emlrtRSI = { 16, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo nb_emlrtRSI = { 31, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo ob_emlrtRSI = { 24, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo pb_emlrtRSI = { 17, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo qb_emlrtRSI = { 32, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo rb_emlrtRSI = { 25, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo sb_emlrtRSI = { 18, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo tb_emlrtRSI = { 35, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

static emlrtRSInfo ub_emlrtRSI = { 38, /* lineNo */
  "Correlation",                       /* fcnName */
  "D:\\My Work\\CodeGen\\Correlation.m"/* pathName */
};

/* Function Declarations */
static const mxArray *b_emlrt_marshallOut(const real_T u[2]);
static const mxArray *c_emlrt_marshallOut(const real_T u[1601]);
static void close(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void corrtf(CorrelationStackData *SD, const emlrtStack *sp, const real_T
                   u[801], real_T ro[1282401], real_T t[1601]);
static const mxArray *emlrt_marshallOut(const real_T u[801]);
static void figure(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                   const mxArray *d, const mxArray *e, emlrtMCInfo *location);
static void grid(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void plot(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                 emlrtMCInfo *location);
static void subplot(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    const mxArray *d, emlrtMCInfo *location);
static void surf(const emlrtStack *sp, const mxArray *b, const mxArray *c, const
                 mxArray *d, const mxArray *e, const mxArray *f, const mxArray
                 *g, const mxArray *h, emlrtMCInfo *location);
static void u1(const real_T x[801], real_T y[801]);
static void xlabel(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void ylabel(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void ylim(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static void zlabel(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);

/* Function Definitions */
static const mxArray *b_emlrt_marshallOut(const real_T u[2])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 1, 2 };

  real_T *pData;
  y = NULL;
  m = emlrtCreateNumericArray(2, iv, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  pData[0] = u[0];
  pData[1] = u[1];
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *c_emlrt_marshallOut(const real_T u[1601])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 1, 1601 };

  real_T *pData;
  int32_T i;
  int32_T b_i;
  y = NULL;
  m = emlrtCreateNumericArray(2, iv, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < 1601; b_i++) {
    pData[i] = u[b_i];
    i++;
  }

  emlrtAssign(&y, m);
  return y;
}

static void close(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "close", true, location);
}

static void corrtf(CorrelationStackData *SD, const emlrtStack *sp, const real_T
                   u[801], real_T ro[1282401], real_T t[1601])
{
  int32_T y_re;
  creal_T b_u[801];
  creal_T resst[1601];
  int32_T i;
  real_T r;
  real_T y_im;
  int32_T k;
  real_T re;
  real_T im;
  for (y_re = 0; y_re < 801; y_re++) {
    b_u[y_re].re = u[y_re];
    b_u[y_re].im = u[y_re] * 2.4492935982947065E-15;
  }

  xcorr(b_u, u, resst, t);
  for (y_re = 0; y_re < 1601; y_re++) {
    t[y_re] *= 0.05;
  }

  for (i = 0; i < 801; i++) {
    y_re = static_cast<int32_T>((dv[i] * 0.0));
    y_im = dv[i] * 6.2831853071795862;
    for (k = 0; k < 801; k++) {
      r = t[k + 800];
      re = r * static_cast<real_T>(y_re);
      im = r * y_im;
      if (im == 0.0) {
        re = muDoubleScalarExp(re);
        im = 0.0;
      } else {
        r = muDoubleScalarExp(re / 2.0);
        re = r * (r * muDoubleScalarCos(im));
        im = r * (r * muDoubleScalarSin(im));
      }

      re *= u[k];
      im *= u[k];
      b_u[k].re = re;
      b_u[k].im = im;
    }

    b_xcorr(b_u, u, resst);
    for (y_re = 0; y_re < 1601; y_re++) {
      SD->f0.ro[i + 801 * y_re] = resst[y_re];
    }

    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  r = mtimes(u, u);
  for (k = 0; k < 1282401; k++) {
    if (SD->f0.ro[k].im == 0.0) {
      re = SD->f0.ro[k].re / r;
      im = 0.0;
    } else if (SD->f0.ro[k].re == 0.0) {
      re = 0.0;
      im = SD->f0.ro[k].im / r;
    } else {
      re = SD->f0.ro[k].re / r;
      im = SD->f0.ro[k].im / r;
    }

    SD->f0.ro[k].re = re;
    SD->f0.ro[k].im = im;
    ro[k] = muDoubleScalarHypot(re, im);
  }
}

static const mxArray *emlrt_marshallOut(const real_T u[801])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 1, 801 };

  real_T *pData;
  int32_T i;
  int32_T b_i;
  y = NULL;
  m = emlrtCreateNumericArray(2, iv, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < 801; b_i++) {
    pData[i] = u[b_i];
    i++;
  }

  emlrtAssign(&y, m);
  return y;
}

static void figure(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                   const mxArray *d, const mxArray *e, emlrtMCInfo *location)
{
  const mxArray *pArrays[4];
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  pArrays[3] = e;
  emlrtCallMATLABR2012b(sp, 0, NULL, 4, pArrays, "figure", true, location);
}

static void grid(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "grid", true, location);
}

static void plot(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                 emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  pArrays[0] = b;
  pArrays[1] = c;
  emlrtCallMATLABR2012b(sp, 0, NULL, 2, pArrays, "plot", true, location);
}

static void subplot(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    const mxArray *d, emlrtMCInfo *location)
{
  const mxArray *pArrays[3];
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  emlrtCallMATLABR2012b(sp, 0, NULL, 3, pArrays, "subplot", true, location);
}

static void surf(const emlrtStack *sp, const mxArray *b, const mxArray *c, const
                 mxArray *d, const mxArray *e, const mxArray *f, const mxArray
                 *g, const mxArray *h, emlrtMCInfo *location)
{
  const mxArray *pArrays[7];
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  pArrays[3] = e;
  pArrays[4] = f;
  pArrays[5] = g;
  pArrays[6] = h;
  emlrtCallMATLABR2012b(sp, 0, NULL, 7, pArrays, "surf", true, location);
}

static void u1(const real_T x[801], real_T y[801])
{
  int32_T k;
  real_T r;
  for (k = 0; k < 801; k++) {
    if (x[k] == 0.0) {
      r = 0.0;
    } else {
      r = muDoubleScalarRem(x[k], 2.0);
      if (r == 0.0) {
        r = 0.0;
      }
    }

    y[k] = static_cast<real_T>((r < 0.5)) * static_cast<real_T>
      (!(muDoubleScalarFloor(x[k] / 20.0 / 2.0) != 0.0));
  }
}

static void xlabel(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "xlabel", true, location);
}

static void ylabel(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "ylabel", true, location);
}

static void ylim(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "ylim", true, location);
}

static void zlabel(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "zlabel", true, location);
}

void Correlation(CorrelationStackData *SD, const emlrtStack *sp)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 1, 3 };

  static const char_T u[3] = { 'a', 'l', 'l' };

  static const real_T t[801] = { 0.0, 0.05, 0.1, 0.15000000000000002, 0.2, 0.25,
    0.30000000000000004, 0.35000000000000003, 0.4, 0.45, 0.5, 0.55,
    0.60000000000000009, 0.65, 0.70000000000000007, 0.75, 0.8,
    0.85000000000000009, 0.9, 0.95000000000000007, 1.0, 1.05, 1.1,
    1.1500000000000001, 1.2000000000000002, 1.25, 1.3, 1.35, 1.4000000000000001,
    1.4500000000000002, 1.5, 1.55, 1.6, 1.6500000000000001, 1.7000000000000002,
    1.75, 1.8, 1.85, 1.9000000000000001, 1.9500000000000002, 2.0,
    2.0500000000000003, 2.1, 2.15, 2.2, 2.25, 2.3000000000000003, 2.35,
    2.4000000000000004, 2.45, 2.5, 2.5500000000000003, 2.6, 2.6500000000000004,
    2.7, 2.75, 2.8000000000000003, 2.85, 2.9000000000000004, 2.95, 3.0,
    3.0500000000000003, 3.1, 3.1500000000000004, 3.2, 3.25, 3.3000000000000003,
    3.35, 3.4000000000000004, 3.45, 3.5, 3.5500000000000003, 3.6,
    3.6500000000000004, 3.7, 3.75, 3.8000000000000003, 3.85, 3.9000000000000004,
    3.95, 4.0, 4.05, 4.1000000000000005, 4.15, 4.2, 4.25, 4.3,
    4.3500000000000005, 4.4, 4.45, 4.5, 4.55, 4.6000000000000005, 4.65, 4.7,
    4.75, 4.8000000000000007, 4.8500000000000005, 4.9, 4.95, 5.0,
    5.0500000000000007, 5.1000000000000005, 5.15, 5.2, 5.25, 5.3000000000000007,
    5.3500000000000005, 5.4, 5.45, 5.5, 5.5500000000000007, 5.6000000000000005,
    5.65, 5.7, 5.75, 5.8000000000000007, 5.8500000000000005, 5.9, 5.95, 6.0,
    6.0500000000000007, 6.1000000000000005, 6.15, 6.2, 6.25, 6.3000000000000007,
    6.3500000000000005, 6.4, 6.45, 6.5, 6.5500000000000007, 6.6000000000000005,
    6.65, 6.7, 6.75, 6.8000000000000007, 6.8500000000000005, 6.9, 6.95, 7.0,
    7.0500000000000007, 7.1000000000000005, 7.15, 7.2, 7.25, 7.3000000000000007,
    7.3500000000000005, 7.4, 7.45, 7.5, 7.5500000000000007, 7.6000000000000005,
    7.65, 7.7, 7.75, 7.8000000000000007, 7.8500000000000005, 7.9, 7.95, 8.0,
    8.05, 8.1, 8.15, 8.2000000000000011, 8.25, 8.3, 8.35, 8.4,
    8.4500000000000011, 8.5, 8.55, 8.6, 8.65, 8.7000000000000011, 8.75, 8.8,
    8.85, 8.9, 8.9500000000000011, 9.0, 9.05, 9.1, 9.15, 9.2000000000000011,
    9.25, 9.3, 9.35, 9.4, 9.4500000000000011, 9.5, 9.55, 9.6000000000000014,
    9.65, 9.7000000000000011, 9.75, 9.8, 9.8500000000000014, 9.9,
    9.9500000000000011, 10.0, 10.05, 10.100000000000001, 10.15,
    10.200000000000001, 10.25, 10.3, 10.350000000000001, 10.4,
    10.450000000000001, 10.5, 10.55, 10.600000000000001, 10.65,
    10.700000000000001, 10.75, 10.8, 10.850000000000001, 10.9,
    10.950000000000001, 11.0, 11.05, 11.100000000000001, 11.15,
    11.200000000000001, 11.25, 11.3, 11.350000000000001, 11.4,
    11.450000000000001, 11.5, 11.55, 11.600000000000001, 11.65,
    11.700000000000001, 11.75, 11.8, 11.850000000000001, 11.9,
    11.950000000000001, 12.0, 12.05, 12.100000000000001, 12.15,
    12.200000000000001, 12.25, 12.3, 12.350000000000001, 12.4,
    12.450000000000001, 12.5, 12.55, 12.600000000000001, 12.65,
    12.700000000000001, 12.75, 12.8, 12.850000000000001, 12.9,
    12.950000000000001, 13.0, 13.05, 13.100000000000001, 13.15,
    13.200000000000001, 13.25, 13.3, 13.350000000000001, 13.4,
    13.450000000000001, 13.5, 13.55, 13.600000000000001, 13.65,
    13.700000000000001, 13.75, 13.8, 13.850000000000001, 13.9,
    13.950000000000001, 14.0, 14.05, 14.100000000000001, 14.15,
    14.200000000000001, 14.25, 14.3, 14.350000000000001, 14.4,
    14.450000000000001, 14.5, 14.55, 14.600000000000001, 14.65,
    14.700000000000001, 14.75, 14.8, 14.850000000000001, 14.9,
    14.950000000000001, 15.0, 15.05, 15.100000000000001, 15.15,
    15.200000000000001, 15.25, 15.3, 15.350000000000001, 15.4,
    15.450000000000001, 15.5, 15.55, 15.600000000000001, 15.65,
    15.700000000000001, 15.75, 15.8, 15.850000000000001, 15.9,
    15.950000000000001, 16.0, 16.05, 16.1, 16.150000000000002, 16.2, 16.25, 16.3,
    16.35, 16.400000000000002, 16.45, 16.5, 16.55, 16.6, 16.650000000000002,
    16.7, 16.75, 16.8, 16.85, 16.900000000000002, 16.95, 17.0, 17.05, 17.1,
    17.150000000000002, 17.2, 17.25, 17.3, 17.35, 17.400000000000002, 17.45,
    17.5, 17.55, 17.6, 17.650000000000002, 17.7, 17.75, 17.8, 17.85,
    17.900000000000002, 17.95, 18.0, 18.05, 18.1, 18.150000000000002, 18.2,
    18.25, 18.3, 18.35, 18.400000000000002, 18.45, 18.5, 18.55, 18.6,
    18.650000000000002, 18.7, 18.75, 18.8, 18.85, 18.900000000000002, 18.95,
    19.0, 19.05, 19.1, 19.150000000000002, 19.200000000000003, 19.25, 19.3,
    19.35, 19.400000000000002, 19.450000000000003, 19.5, 19.55, 19.6,
    19.650000000000002, 19.700000000000003, 19.75, 19.8, 19.85,
    19.900000000000002, 19.950000000000003, 20.0, 20.049999999999997,
    20.099999999999998, 20.15, 20.2, 20.25, 20.299999999999997,
    20.349999999999998, 20.4, 20.45, 20.5, 20.549999999999997,
    20.599999999999998, 20.65, 20.7, 20.75, 20.799999999999997,
    20.849999999999998, 20.9, 20.95, 21.0, 21.05, 21.099999999999998, 21.15,
    21.2, 21.25, 21.3, 21.349999999999998, 21.4, 21.45, 21.5, 21.55,
    21.599999999999998, 21.65, 21.7, 21.75, 21.8, 21.849999999999998, 21.9,
    21.95, 22.0, 22.05, 22.099999999999998, 22.15, 22.2, 22.25, 22.3,
    22.349999999999998, 22.4, 22.45, 22.5, 22.55, 22.599999999999998, 22.65,
    22.7, 22.75, 22.8, 22.849999999999998, 22.9, 22.95, 23.0, 23.05,
    23.099999999999998, 23.15, 23.2, 23.25, 23.3, 23.349999999999998, 23.4,
    23.45, 23.5, 23.55, 23.599999999999998, 23.65, 23.7, 23.75, 23.8,
    23.849999999999998, 23.9, 23.95, 24.0, 24.049999999999997, 24.1, 24.15, 24.2,
    24.25, 24.299999999999997, 24.35, 24.4, 24.45, 24.5, 24.549999999999997,
    24.6, 24.65, 24.7, 24.75, 24.799999999999997, 24.85, 24.9, 24.95, 25.0,
    25.049999999999997, 25.1, 25.15, 25.2, 25.25, 25.299999999999997, 25.35,
    25.4, 25.45, 25.5, 25.549999999999997, 25.6, 25.65, 25.7, 25.75,
    25.799999999999997, 25.85, 25.9, 25.95, 26.0, 26.049999999999997, 26.1,
    26.15, 26.2, 26.25, 26.299999999999997, 26.35, 26.4, 26.45, 26.5,
    26.549999999999997, 26.6, 26.65, 26.7, 26.75, 26.799999999999997, 26.85,
    26.9, 26.95, 27.0, 27.049999999999997, 27.1, 27.15, 27.2, 27.25,
    27.299999999999997, 27.35, 27.4, 27.45, 27.5, 27.549999999999997, 27.6,
    27.65, 27.7, 27.75, 27.799999999999997, 27.85, 27.9, 27.95, 28.0,
    28.049999999999997, 28.1, 28.15, 28.2, 28.25, 28.299999999999997, 28.35,
    28.4, 28.45, 28.5, 28.549999999999997, 28.6, 28.65, 28.7, 28.75,
    28.799999999999997, 28.85, 28.9, 28.95, 29.0, 29.049999999999997, 29.1,
    29.15, 29.2, 29.25, 29.299999999999997, 29.35, 29.4, 29.45, 29.5,
    29.549999999999997, 29.6, 29.65, 29.7, 29.75, 29.799999999999997, 29.85,
    29.9, 29.95, 30.0, 30.049999999999997, 30.1, 30.15, 30.2, 30.25,
    30.299999999999997, 30.35, 30.4, 30.45, 30.5, 30.549999999999997, 30.6,
    30.65, 30.7, 30.75, 30.799999999999997, 30.85, 30.9, 30.95, 31.0,
    31.049999999999997, 31.1, 31.15, 31.2, 31.25, 31.299999999999997, 31.35,
    31.4, 31.45, 31.5, 31.549999999999997, 31.6, 31.65, 31.7, 31.75,
    31.799999999999997, 31.85, 31.9, 31.95, 32.0, 32.05, 32.1, 32.15, 32.2,
    32.25, 32.3, 32.35, 32.4, 32.45, 32.5, 32.55, 32.6, 32.65, 32.7, 32.75, 32.8,
    32.85, 32.9, 32.95, 33.0, 33.05, 33.1, 33.15, 33.2, 33.25, 33.3, 33.35, 33.4,
    33.45, 33.5, 33.55, 33.6, 33.65, 33.7, 33.75, 33.8, 33.85, 33.9, 33.95, 34.0,
    34.05, 34.1, 34.15, 34.2, 34.25, 34.3, 34.35, 34.4, 34.45, 34.5, 34.55, 34.6,
    34.65, 34.7, 34.75, 34.8, 34.85, 34.9, 34.95, 35.0, 35.05, 35.1, 35.15, 35.2,
    35.25, 35.3, 35.35, 35.4, 35.45, 35.5, 35.55, 35.6, 35.65, 35.7, 35.75, 35.8,
    35.85, 35.9, 35.95, 36.0, 36.05, 36.1, 36.15, 36.2, 36.25, 36.3, 36.35, 36.4,
    36.45, 36.5, 36.55, 36.6, 36.65, 36.7, 36.75, 36.8, 36.85, 36.9, 36.95, 37.0,
    37.05, 37.1, 37.15, 37.2, 37.25, 37.3, 37.35, 37.4, 37.45, 37.5, 37.55, 37.6,
    37.65, 37.7, 37.75, 37.8, 37.85, 37.9, 37.95, 38.0, 38.05, 38.1, 38.15, 38.2,
    38.25, 38.3, 38.35, 38.4, 38.45, 38.5, 38.55, 38.6, 38.65, 38.7, 38.75, 38.8,
    38.85, 38.9, 38.95, 39.0, 39.05, 39.1, 39.15, 39.2, 39.25, 39.3, 39.35, 39.4,
    39.45, 39.5, 39.55, 39.6, 39.65, 39.7, 39.75, 39.8, 39.85, 39.9, 39.95, 40.0
  };

  real_T b_u[801];
  real_T tc[1601];
  const mxArray *m1;
  static const int32_T iv1[2] = { 1, 4 };

  static const char_T c_u[4] = { 'N', 'a', 'm', 'e' };

  const mxArray *b_y;
  const mxArray *m2;
  static const int32_T iv2[2] = { 1, 20 };

  static const char_T d_u[20] = { 'C', 'o', 'r', 'r', 'e', 'l', 'a', 't', 'i',
    'o', 'n', ' ', 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n' };

  const mxArray *c_y;
  const mxArray *m3;
  static const int32_T iv3[2] = { 1, 11 };

  static const char_T e_u[11] = { 'W', 'i', 'n', 'd', 'o', 'w', 'S', 't', 'a',
    't', 'e' };

  const mxArray *d_y;
  const mxArray *m4;
  static const int32_T iv4[2] = { 1, 9 };

  static const char_T f_u[9] = { 'm', 'a', 'x', 'i', 'm', 'i', 'z', 'e', 'd' };

  const mxArray *m5;
  const mxArray *m6;
  const mxArray *m7;
  const mxArray *m8;
  const mxArray *m9;
  real_T ex;
  real_T b_ex;
  int32_T k;
  real_T c_ex[2];
  real_T d;
  const mxArray *m10;
  static const int32_T iv5[2] = { 1, 2 };

  static const char_T g_u[2] = { 'o', 'n' };

  const mxArray *m11;
  const mxArray *m12;
  const mxArray *m13;
  real_T ro[1601];
  const mxArray *m14;
  const mxArray *m15;
  static const int32_T iv6[2] = { 1, 4 };

  static const char_T h_u[4] = { '\\', 'r', 'h', 'o' };

  const mxArray *m16;
  static const int32_T iv7[2] = { 1, 2 };

  const mxArray *m17;
  const mxArray *m18;
  const mxArray *m19;
  const mxArray *m20;
  const mxArray *m21;
  static const int32_T iv8[2] = { 1, 4 };

  const mxArray *m22;
  static const int32_T iv9[2] = { 1, 2 };

  const mxArray *m23;
  const mxArray *m24;
  const mxArray *m25;
  const mxArray *m26;
  static const int32_T iv10[2] = { 801, 1601 };

  real_T *pData;
  int32_T i;
  int32_T b_i;
  const mxArray *m27;
  static const int32_T iv11[2] = { 1, 9 };

  static const char_T i_u[9] = { 'E', 'd', 'g', 'e', 'C', 'o', 'l', 'o', 'r' };

  const mxArray *m28;
  static const int32_T iv12[2] = { 1, 4 };

  static const char_T j_u[4] = { 'n', 'o', 'n', 'e' };

  const mxArray *m29;
  static const int32_T iv13[2] = { 1, 9 };

  static const char_T k_u[9] = { 'F', 'a', 'c', 'e', 'C', 'o', 'l', 'o', 'r' };

  const mxArray *e_y;
  const mxArray *m30;
  static const int32_T iv14[2] = { 1, 10 };

  static const char_T l_u[10] = { 't', 'e', 'x', 't', 'u', 'r', 'e', 'm', 'a',
    'p' };

  const mxArray *m31;
  const mxArray *m32;
  static const int32_T iv15[2] = { 1, 8 };

  static const char_T m_u[8] = { '\\', 'D', 'e', 'l', 't', 'a', ' ', 'f' };

  const mxArray *m33;
  static const int32_T iv16[2] = { 1, 4 };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  y = NULL;
  m = emlrtCreateCharArray(2, iv);
  emlrtInitCharArrayR2013a(sp, 3, m, &u[0]);
  emlrtAssign(&y, m);
  st.site = &v_emlrtRSI;
  close(&st, y, &emlrtMCI);
  u1(t, b_u);
  st.site = &emlrtRSI;
  corrtf(SD, &st, b_u, SD->f1.ro, tc);
  y = NULL;
  m1 = emlrtCreateCharArray(2, iv1);
  emlrtInitCharArrayR2013a(sp, 4, m1, &c_u[0]);
  emlrtAssign(&y, m1);
  b_y = NULL;
  m2 = emlrtCreateCharArray(2, iv2);
  emlrtInitCharArrayR2013a(sp, 20, m2, &d_u[0]);
  emlrtAssign(&b_y, m2);
  c_y = NULL;
  m3 = emlrtCreateCharArray(2, iv3);
  emlrtInitCharArrayR2013a(sp, 11, m3, &e_u[0]);
  emlrtAssign(&c_y, m3);
  d_y = NULL;
  m4 = emlrtCreateCharArray(2, iv4);
  emlrtInitCharArrayR2013a(sp, 9, m4, &f_u[0]);
  emlrtAssign(&d_y, m4);
  st.site = &w_emlrtRSI;
  figure(&st, y, b_y, c_y, d_y, &b_emlrtMCI);
  y = NULL;
  m5 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&y, m5);
  b_y = NULL;
  m6 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&b_y, m6);
  c_y = NULL;
  m7 = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&c_y, m7);
  st.site = &bb_emlrtRSI;
  subplot(&st, y, b_y, c_y, &c_emlrtMCI);
  st.site = &eb_emlrtRSI;
  plot(&st, emlrt_marshallOut(t), emlrt_marshallOut(b_u), &d_emlrtMCI);
  y = NULL;
  m8 = emlrtCreateString1('t');
  emlrtAssign(&y, m8);
  st.site = &ib_emlrtRSI;
  xlabel(&st, y, &e_emlrtMCI);
  y = NULL;
  m9 = emlrtCreateString1('u');
  emlrtAssign(&y, m9);
  st.site = &mb_emlrtRSI;
  ylabel(&st, y, &f_emlrtMCI);
  ex = b_u[0];
  b_ex = b_u[0];
  for (k = 0; k < 800; k++) {
    d = b_u[k + 1];
    if (ex > d) {
      ex = d;
    }

    if (b_ex < d) {
      b_ex = d;
    }
  }

  c_ex[0] = ex * 1.1;
  c_ex[1] = b_ex * 1.1;
  st.site = &pb_emlrtRSI;
  ylim(&st, b_emlrt_marshallOut(c_ex), &g_emlrtMCI);
  y = NULL;
  m10 = emlrtCreateCharArray(2, iv5);
  emlrtInitCharArrayR2013a(sp, 2, m10, &g_u[0]);
  emlrtAssign(&y, m10);
  st.site = &sb_emlrtRSI;
  grid(&st, y, &h_emlrtMCI);
  y = NULL;
  m11 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&y, m11);
  b_y = NULL;
  m12 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&b_y, m12);
  c_y = NULL;
  m13 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&c_y, m13);
  st.site = &ab_emlrtRSI;
  subplot(&st, y, b_y, c_y, &i_emlrtMCI);
  for (k = 0; k < 1601; k++) {
    ro[k] = SD->f1.ro[801 * k + 400];
  }

  st.site = &db_emlrtRSI;
  plot(&st, c_emlrt_marshallOut(tc), c_emlrt_marshallOut(ro), &j_emlrtMCI);
  y = NULL;
  m14 = emlrtCreateString1('t');
  emlrtAssign(&y, m14);
  st.site = &hb_emlrtRSI;
  xlabel(&st, y, &k_emlrtMCI);
  y = NULL;
  m15 = emlrtCreateCharArray(2, iv6);
  emlrtInitCharArrayR2013a(sp, 4, m15, &h_u[0]);
  emlrtAssign(&y, m15);
  st.site = &lb_emlrtRSI;
  ylabel(&st, y, &l_emlrtMCI);
  ex = b_u[0];
  b_ex = b_u[0];
  for (k = 0; k < 800; k++) {
    d = b_u[k + 1];
    if (ex > d) {
      ex = d;
    }

    if (b_ex < d) {
      b_ex = d;
    }
  }

  c_ex[0] = ex * 1.1;
  c_ex[1] = b_ex * 1.1;
  st.site = &ob_emlrtRSI;
  ylim(&st, b_emlrt_marshallOut(c_ex), &m_emlrtMCI);
  y = NULL;
  m16 = emlrtCreateCharArray(2, iv7);
  emlrtInitCharArrayR2013a(sp, 2, m16, &g_u[0]);
  emlrtAssign(&y, m16);
  st.site = &rb_emlrtRSI;
  grid(&st, y, &n_emlrtMCI);
  y = NULL;
  m17 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&y, m17);
  b_y = NULL;
  m18 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&b_y, m18);
  c_y = NULL;
  m19 = emlrtCreateDoubleScalar(3.0);
  emlrtAssign(&c_y, m19);
  st.site = &y_emlrtRSI;
  subplot(&st, y, b_y, c_y, &o_emlrtMCI);
  st.site = &cb_emlrtRSI;
  plot(&st, emlrt_marshallOut(dv), emlrt_marshallOut(*(real_T (*)[801])&
        SD->f1.ro[640800]), &p_emlrtMCI);
  y = NULL;
  m20 = emlrtCreateString1('f');
  emlrtAssign(&y, m20);
  st.site = &gb_emlrtRSI;
  xlabel(&st, y, &q_emlrtMCI);
  y = NULL;
  m21 = emlrtCreateCharArray(2, iv8);
  emlrtInitCharArrayR2013a(sp, 4, m21, &h_u[0]);
  emlrtAssign(&y, m21);
  st.site = &kb_emlrtRSI;
  ylabel(&st, y, &r_emlrtMCI);
  ex = b_u[0];
  b_ex = b_u[0];
  for (k = 0; k < 800; k++) {
    d = b_u[k + 1];
    if (ex > d) {
      ex = d;
    }

    if (b_ex < d) {
      b_ex = d;
    }
  }

  c_ex[0] = ex * 1.1;
  c_ex[1] = b_ex * 1.1;
  st.site = &nb_emlrtRSI;
  ylim(&st, b_emlrt_marshallOut(c_ex), &s_emlrtMCI);
  y = NULL;
  m22 = emlrtCreateCharArray(2, iv9);
  emlrtInitCharArrayR2013a(sp, 2, m22, &g_u[0]);
  emlrtAssign(&y, m22);
  st.site = &qb_emlrtRSI;
  grid(&st, y, &t_emlrtMCI);
  y = NULL;
  m23 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&y, m23);
  b_y = NULL;
  m24 = emlrtCreateDoubleScalar(2.0);
  emlrtAssign(&b_y, m24);
  c_y = NULL;
  m25 = emlrtCreateDoubleScalar(4.0);
  emlrtAssign(&c_y, m25);
  st.site = &x_emlrtRSI;
  subplot(&st, y, b_y, c_y, &u_emlrtMCI);
  y = NULL;
  m26 = emlrtCreateNumericArray(2, iv10, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m26);
  k = 0;
  for (i = 0; i < 1601; i++) {
    for (b_i = 0; b_i < 801; b_i++) {
      pData[k] = SD->f1.ro[b_i + 801 * i];
      k++;
    }
  }

  emlrtAssign(&y, m26);
  b_y = NULL;
  m27 = emlrtCreateCharArray(2, iv11);
  emlrtInitCharArrayR2013a(sp, 9, m27, &i_u[0]);
  emlrtAssign(&b_y, m27);
  c_y = NULL;
  m28 = emlrtCreateCharArray(2, iv12);
  emlrtInitCharArrayR2013a(sp, 4, m28, &j_u[0]);
  emlrtAssign(&c_y, m28);
  d_y = NULL;
  m29 = emlrtCreateCharArray(2, iv13);
  emlrtInitCharArrayR2013a(sp, 9, m29, &k_u[0]);
  emlrtAssign(&d_y, m29);
  e_y = NULL;
  m30 = emlrtCreateCharArray(2, iv14);
  emlrtInitCharArrayR2013a(sp, 10, m30, &l_u[0]);
  emlrtAssign(&e_y, m30);
  st.site = &tb_emlrtRSI;
  surf(&st, c_emlrt_marshallOut(tc), emlrt_marshallOut(dv), y, b_y, c_y, d_y,
       e_y, &v_emlrtMCI);
  y = NULL;
  m31 = emlrtCreateString1('t');
  emlrtAssign(&y, m31);
  st.site = &fb_emlrtRSI;
  xlabel(&st, y, &w_emlrtMCI);
  y = NULL;
  m32 = emlrtCreateCharArray(2, iv15);
  emlrtInitCharArrayR2013a(sp, 8, m32, &m_u[0]);
  emlrtAssign(&y, m32);
  st.site = &jb_emlrtRSI;
  ylabel(&st, y, &x_emlrtMCI);
  y = NULL;
  m33 = emlrtCreateCharArray(2, iv16);
  emlrtInitCharArrayR2013a(sp, 4, m33, &h_u[0]);
  emlrtAssign(&y, m33);
  st.site = &ub_emlrtRSI;
  zlabel(&st, y, &y_emlrtMCI);
}

/* End of code generation (Correlation.cpp) */
