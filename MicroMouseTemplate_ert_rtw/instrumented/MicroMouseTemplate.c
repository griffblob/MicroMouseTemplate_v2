/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate.c
 *
 * Code generated for Simulink model 'MicroMouseTemplate'.
 *
 * Model version                  : 3.20
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Oct  3 03:42:29 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MicroMouseTemplate.h"
#include "rtwtypes.h"
#include "MicroMouseTemplate_types.h"
#include "MicroMouseTemplate_private.h"
#include <string.h>
#include <math.h>
#include "stm_timer_ll.h"
#include "stm_adc_ll.h"

/* Named constants for Chart: '<Root>/Lameo' */
#define MicroMouseTempla_IN_Calibration ((uint8_T)1U)
#define MicroMouseTemplat_IN_Fuckmeeeee ((uint8_T)6U)
#define MicroMouseTemplat_IN_TurnWrong1 ((uint8_T)11U)
#define MicroMouseTemplat_IN_TurnWrong2 ((uint8_T)12U)
#define MicroMouseTemplate_IN_Crossing ((uint8_T)2U)
#define MicroMouseTemplate_IN_Delay    ((uint8_T)3U)
#define MicroMouseTemplate_IN_Drive    ((uint8_T)4U)
#define MicroMouseTemplate_IN_Flip     ((uint8_T)5U)
#define MicroMouseTemplate_IN_Idle     ((uint8_T)7U)
#define MicroMouseTemplate_IN_TurnLeft ((uint8_T)8U)
#define MicroMouseTemplate_IN_TurnRight ((uint8_T)9U)
#define MicroMouseTemplate_IN_TurnWrong ((uint8_T)10U)

/* user code (top of source file) */
/* System '<Root>' */
extern I2C_HandleTypeDef hi2c2;

/* Exported block states */
real32_T IMU_Accel[3];                 /* '<S10>/Data Store Memory' */
real32_T IMU_Gyro[3];                  /* '<S10>/Data Store Memory1' */
int32_T currTicksRS;                   /* '<S1>/Data Store Memory2' */
int32_T currTicksLS;                   /* '<S1>/Data Store Memory4' */
uint16_T ADC1s[9];                     /* '<S9>/Data Store Memory' */
uint16_T ADC_H[9];                     /* '<S9>/Data Store Memory1' */
uint16_T ADC_L[9];                     /* '<S9>/Data Store Memory2' */
uint16_T Thresholds[8];                /* '<S1>/Data Store Memory1' */
boolean_T Detections[8];               /* '<S1>/Data Store Memory' */

/* Block signals (default storage) */
B_MicroMouseTemplate_T MicroMouseTemplate_B;

/* Block states (default storage) */
DW_MicroMouseTemplate_T MicroMouseTemplate_DW;

/* Real-time model */
static RT_MODEL_MicroMouseTemplate_T MicroMouseTemplate_M_;
RT_MODEL_MicroMouseTemplate_T *const MicroMouseTemplate_M =
  &MicroMouseTemplate_M_;

/* Forward declaration for local functions */
static void MicroMouseTemplate_Init(void);
static void MicroMouseTemplat_delConnection(int16_T x1, int16_T b_y1, int16_T x2,
  int16_T y2);
static void MicroMouseTemplate_route(int16_T *pathend, int16_T path[400]);
static real_T MicroMouseTemplate_thingy(int16_T *pathend, const real_T Sensors[8]);
static void MicroMouseTemplate_FollowLine(real_T Drive, const real_T b_Sensors[8],
  real_T *Left, real_T *Right);
static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj);
static void MicroMouseT_PWMOutput_setupImpl(stm32cube_blocks_PWMOutput_Mi_T *obj);
static void MicroMous_PWMOutput_setupImpl_d(stm32cube_blocks_PWMOutput_Mi_T *obj);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void MicroMouseTemplate_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(MicroMouseTemplate_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid rate: 1 */
  MicroMouseTemplate_M->Timing.RateInteraction.TID0_1 =
    (MicroMouseTemplate_M->Timing.TaskCounters.TID[1] == 0);

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (MicroMouseTemplate_M->Timing.TaskCounters.TID[1])++;
  if ((MicroMouseTemplate_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.1s, 0.0s] */
    MicroMouseTemplate_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* System initialize for atomic system: */
void MicroMou_MATLABSystem1_Init(DW_MATLABSystem1_MicroMouseTe_T *localDW,
  P_MATLABSystem1_MicroMouseTem_T *localP)
{
  int32_T i;

  /* Start for MATLABSystem: '<S52>/MATLAB System1' */
  localDW->objisempty = true;
  localDW->obj.InitialCondition = localP->MATLABSystem1_InitialCondition;
  localDW->obj.isInitialized = 1;

  /*  Number of inputs */
  /*  Initialize the buffer during the first call */
  for (i = 0; i < 25; i++) {
    localDW->obj.Buffer[i] = localDW->obj.InitialCondition;
  }

  /* End of Start for MATLABSystem: '<S52>/MATLAB System1' */
}

/* Output and update for atomic system: */
void MicroMouseTem_MATLABSystem1(real_T rtu_0, B_MATLABSystem1_MicroMouseTem_T
  *localB, DW_MATLABSystem1_MicroMouseTe_T *localDW,
  P_MATLABSystem1_MicroMouseTem_T *localP)
{
  /* MATLABSystem: '<S52>/MATLAB System1' */
  if (localDW->obj.InitialCondition != localP->MATLABSystem1_InitialCondition) {
    localDW->obj.InitialCondition = localP->MATLABSystem1_InitialCondition;
  }

  /*  Number of inputs */
  /*  Number of outputs */
  /*  Output the current state of the buffer */
  memcpy(&localB->MATLABSystem1[0], &localDW->obj.Buffer[0], 25U * sizeof(real_T));

  /*  Update the buffer */
  localB->rtu_0[0] = rtu_0;
  memcpy(&localB->rtu_0[1], &localDW->obj.Buffer[0], 24U * sizeof(real_T));
  memcpy(&localDW->obj.Buffer[0], &localB->rtu_0[0], 25U * sizeof(real_T));

  /* End of MATLABSystem: '<S52>/MATLAB System1' */
}

/* System initialize for atomic system: */
void MicroMou_MATLABSystem3_Init(DW_MATLABSystem3_MicroMouseTe_T *localDW,
  P_MATLABSystem3_MicroMouseTem_T *localP)
{
  int32_T i;

  /* Start for MATLABSystem: '<S52>/MATLAB System3' */
  localDW->objisempty = true;
  localDW->obj.InitialCondition = localP->MATLABSystem3_InitialCondition;
  localDW->obj.isInitialized = 1;

  /*  Number of inputs */
  /*  Initialize the buffer during the first call */
  for (i = 0; i < 10; i++) {
    localDW->obj.Buffer[i] = localDW->obj.InitialCondition;
  }

  /* End of Start for MATLABSystem: '<S52>/MATLAB System3' */
}

/* Output and update for atomic system: */
void MicroMouseTem_MATLABSystem3(real_T rtu_0, B_MATLABSystem3_MicroMouseTem_T
  *localB, DW_MATLABSystem3_MicroMouseTe_T *localDW,
  P_MATLABSystem3_MicroMouseTem_T *localP)
{
  /* MATLABSystem: '<S52>/MATLAB System3' */
  if (localDW->obj.InitialCondition != localP->MATLABSystem3_InitialCondition) {
    localDW->obj.InitialCondition = localP->MATLABSystem3_InitialCondition;
  }

  /*  Number of inputs */
  /*  Number of outputs */
  /*  Output the current state of the buffer */
  memcpy(&localB->MATLABSystem3[0], &localDW->obj.Buffer[0], 10U * sizeof(real_T));

  /*  Update the buffer */
  localB->rtu_0[0] = rtu_0;
  memcpy(&localB->rtu_0[1], &localDW->obj.Buffer[0], 9U * sizeof(real_T));
  memcpy(&localDW->obj.Buffer[0], &localB->rtu_0[0], 10U * sizeof(real_T));

  /* End of MATLABSystem: '<S52>/MATLAB System3' */
}

/* Function for Chart: '<Root>/Lameo' */
static void MicroMouseTemplate_Init(void)
{
  int32_T i;
  int32_T tmp;
  int32_T y;
  int16_T connectionend;
  MicroMouseTemplate_DW.direction[0] = 1;
  MicroMouseTemplate_DW.direction[1] = 0;
  MicroMouseTemplate_DW.direction[2] = 0;
  MicroMouseTemplate_DW.direction[3] = 0;
  MicroMouseTemplate_DW.pos[0] = 1;
  MicroMouseTemplate_DW.dest[0] = 2;
  MicroMouseTemplate_DW.pos[1] = 2;
  MicroMouseTemplate_DW.dest[1] = 1;
  memset(&MicroMouseTemplate_DW.connection[0], 0, 672U * sizeof(int16_T));
  connectionend = 0;
  for (i = 0; i < 7; i++) {
    for (y = 0; y < 7; y++) {
      if (i + 1 > 1) {
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        MicroMouseTemplate_DW.connection[tmp - 1] = (int16_T)(i + 1);
        MicroMouseTemplate_DW.connection[tmp + 167] = (int16_T)(y + 1);
        MicroMouseTemplate_DW.connection[tmp + 335] = (int16_T)i;
        MicroMouseTemplate_DW.connection[tmp + 503] = (int16_T)(y + 1);
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        connectionend = (int16_T)tmp;
      }

      if (y + 1 > 1) {
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        MicroMouseTemplate_DW.connection[tmp - 1] = (int16_T)(i + 1);
        MicroMouseTemplate_DW.connection[tmp + 167] = (int16_T)(y + 1);
        MicroMouseTemplate_DW.connection[tmp + 335] = (int16_T)(i + 1);
        MicroMouseTemplate_DW.connection[tmp + 503] = (int16_T)y;
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        connectionend = (int16_T)tmp;
      }

      if (i + 1 < 7) {
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        MicroMouseTemplate_DW.connection[tmp - 1] = (int16_T)(i + 1);
        MicroMouseTemplate_DW.connection[tmp + 167] = (int16_T)(y + 1);
        MicroMouseTemplate_DW.connection[tmp + 335] = (int16_T)(i + 2);
        MicroMouseTemplate_DW.connection[tmp + 503] = (int16_T)(y + 1);
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        connectionend = (int16_T)tmp;
      }

      if (y + 1 < 7) {
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        MicroMouseTemplate_DW.connection[tmp - 1] = (int16_T)(i + 1);
        MicroMouseTemplate_DW.connection[tmp + 167] = (int16_T)(y + 1);
        MicroMouseTemplate_DW.connection[tmp + 335] = (int16_T)(i + 1);
        MicroMouseTemplate_DW.connection[tmp + 503] = (int16_T)(y + 2);
        tmp = connectionend + 1;
        if (connectionend + 1 > 32767) {
          tmp = 32767;
        }

        connectionend = (int16_T)tmp;
      }
    }
  }
}

/* Function for Chart: '<Root>/Lameo' */
static void MicroMouseTemplat_delConnection(int16_T x1, int16_T b_y1, int16_T x2,
  int16_T y2)
{
  int32_T i;
  int16_T connection;
  for (i = 0; i < 168; i++) {
    connection = MicroMouseTemplate_DW.connection[i];
    if ((connection == x1) && (MicroMouseTemplate_DW.connection[i + 168] == b_y1)
        && (MicroMouseTemplate_DW.connection[i + 336] == x2) &&
        (MicroMouseTemplate_DW.connection[i + 504] == y2)) {
      connection = 0;
      MicroMouseTemplate_DW.connection[i] = 0;
      MicroMouseTemplate_DW.connection[i + 168] = 0;
      MicroMouseTemplate_DW.connection[i + 336] = 0;
      MicroMouseTemplate_DW.connection[i + 504] = 0;
    }

    if ((connection == x2) && (MicroMouseTemplate_DW.connection[i + 168] == y2) &&
        (MicroMouseTemplate_DW.connection[i + 336] == x1) &&
        (MicroMouseTemplate_DW.connection[i + 504] == b_y1)) {
      MicroMouseTemplate_DW.connection[i] = 0;
      MicroMouseTemplate_DW.connection[i + 168] = 0;
      MicroMouseTemplate_DW.connection[i + 336] = 0;
      MicroMouseTemplate_DW.connection[i + 504] = 0;
    }
  }
}

/* Function for Chart: '<Root>/Lameo' */
static void MicroMouseTemplate_route(int16_T *pathend, int16_T path[400])
{
  int32_T b;
  int32_T exitg1;
  int32_T i;
  int32_T pathend_0;
  int32_T tmp;
  int16_T tmp_data[2];
  int16_T b_y1;
  int16_T connection;
  int16_T connection_0;
  int16_T qend;
  int16_T x1;
  for (pathend_0 = 0; pathend_0 < 49; pathend_0++) {
    MicroMouseTemplate_B.dist[pathend_0] = MAX_int16_T;
  }

  memset(&MicroMouseTemplate_B.pre[0], 0, 98U * sizeof(int16_T));
  MicroMouseTemplate_DW.q_sizes[0] = 200;
  MicroMouseTemplate_DW.q_sizes[1] = 2;
  memset(&MicroMouseTemplate_B.q_data[0], 0, 400U * sizeof(int16_T));
  memset(&path[0], 0, 400U * sizeof(int16_T));
  *pathend = 0;
  MicroMouseTemplate_B.dist[(MicroMouseTemplate_DW.pos[0] + 7 *
    (MicroMouseTemplate_DW.pos[1] - 1)) - 1] = 0;
  MicroMouseTemplate_B.q_data[0] = MicroMouseTemplate_DW.pos[0];
  MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]] =
    MicroMouseTemplate_DW.pos[1];
  qend = 1;
  while (qend > 0) {
    x1 = MicroMouseTemplate_B.q_data[0];
    b_y1 = MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]];
    for (i = 0; i < 168; i++) {
      if ((MicroMouseTemplate_DW.connection[i] == x1) &&
          (MicroMouseTemplate_DW.connection[i + 168] == b_y1)) {
        pathend_0 = MicroMouseTemplate_B.dist[((b_y1 - 1) * 7 + x1) - 1] + 1;
        tmp = pathend_0;
        if (pathend_0 > 32767) {
          tmp = 32767;
        }

        connection = MicroMouseTemplate_DW.connection[i + 504];
        connection_0 = MicroMouseTemplate_DW.connection[i + 336];
        b = (connection - 1) * 7 + connection_0;
        if (MicroMouseTemplate_B.dist[b - 1] > tmp) {
          if (pathend_0 > 32767) {
            pathend_0 = 32767;
          }

          MicroMouseTemplate_B.dist[b - 1] = (int16_T)pathend_0;
          MicroMouseTemplate_B.pre[b - 1] = x1;
          MicroMouseTemplate_B.pre[b + 48] = b_y1;
          pathend_0 = qend + 1;
          if (qend + 1 > 32767) {
            pathend_0 = 32767;
          }

          MicroMouseTemplate_B.q_data[pathend_0 - 1] = connection_0;
          MicroMouseTemplate_B.q_data[(pathend_0 +
            MicroMouseTemplate_DW.q_sizes[0]) - 1] = connection;
          pathend_0 = qend + 1;
          if (qend + 1 > 32767) {
            pathend_0 = 32767;
          }

          qend = (int16_T)pathend_0;
        }
      }
    }

    b = qend;
    for (i = 0; i <= b - 2; i++) {
      for (pathend_0 = 0; pathend_0 < 2; pathend_0++) {
        tmp_data[pathend_0] = MicroMouseTemplate_B.q_data
          [(MicroMouseTemplate_DW.q_sizes[0] * pathend_0 + i) + 1];
      }

      for (pathend_0 = 0; pathend_0 < 2; pathend_0++) {
        MicroMouseTemplate_B.q_data[i + MicroMouseTemplate_DW.q_sizes[0] *
          pathend_0] = tmp_data[pathend_0];
      }
    }

    qend--;
  }

  MicroMouseTemplate_DW.q_sizes[0] = 200;
  MicroMouseTemplate_DW.q_sizes[1] = 2;
  memset(&MicroMouseTemplate_B.q_data[0], 0, 400U * sizeof(int16_T));
  MicroMouseTemplate_B.q_data[0] = MicroMouseTemplate_DW.dest[0];
  MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]] =
    MicroMouseTemplate_DW.dest[1];
  do {
    exitg1 = 0;
    qend = MicroMouseTemplate_B.q_data[0];
    if (qend > 0) {
      pathend_0 = *pathend + 1;
      if (*pathend + 1 > 32767) {
        pathend_0 = 32767;
      }

      path[pathend_0 - 1] = qend;
      path[pathend_0 + 199] =
        MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]];
      pathend_0 = *pathend + 1;
      if (*pathend + 1 > 32767) {
        pathend_0 = 32767;
      }

      *pathend = (int16_T)pathend_0;
      tmp = MicroMouseTemplate_B.q_data[0];
      qend = MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]];
      for (b = 0; b < 2; b++) {
        MicroMouseTemplate_B.q_data[1 + MicroMouseTemplate_DW.q_sizes[0] * b] =
          MicroMouseTemplate_B.pre[(((qend - 1) * 7 + tmp) + 49 * b) - 1];
      }

      for (i = 0; i < 199; i++) {
        for (pathend_0 = 0; pathend_0 < 2; pathend_0++) {
          tmp_data[pathend_0] = MicroMouseTemplate_B.q_data
            [(MicroMouseTemplate_DW.q_sizes[0] * pathend_0 + i) + 1];
        }

        for (pathend_0 = 0; pathend_0 < 2; pathend_0++) {
          MicroMouseTemplate_B.q_data[i + MicroMouseTemplate_DW.q_sizes[0] *
            pathend_0] = tmp_data[pathend_0];
        }
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/* Function for Chart: '<Root>/Lameo' */
static real_T MicroMouseTemplate_thingy(int16_T *pathend, const real_T Sensors[8])
{
  real_T Turn;
  int32_T tmp;
  int32_T tmp_0;
  int16_T a_idx_1;
  int16_T a_idx_3;
  if (Sensors[1] == 1.0) {
    tmp = MicroMouseTemplate_DW.pos[0] + MicroMouseTemplate_DW.direction[1];
    if (tmp > 32767) {
      tmp = 32767;
    } else if (tmp < -32768) {
      tmp = -32768;
    }

    tmp -= MicroMouseTemplate_DW.direction[3];
    if (tmp > 32767) {
      tmp = 32767;
    } else if (tmp < -32768) {
      tmp = -32768;
    }

    tmp_0 = MicroMouseTemplate_DW.direction[0] + MicroMouseTemplate_DW.pos[1];
    if (tmp_0 > 32767) {
      tmp_0 = 32767;
    } else if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }

    tmp_0 -= MicroMouseTemplate_DW.direction[2];
    if (tmp_0 > 32767) {
      tmp_0 = 32767;
    } else if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }

    MicroMouseTemplat_delConnection(MicroMouseTemplate_DW.pos[0],
      MicroMouseTemplate_DW.pos[1], (int16_T)tmp, (int16_T)tmp_0);
  }

  if (Sensors[4] == 1.0) {
    tmp = MicroMouseTemplate_DW.pos[0] + MicroMouseTemplate_DW.direction[0];
    if (tmp > 32767) {
      tmp = 32767;
    } else if (tmp < -32768) {
      tmp = -32768;
    }

    tmp -= MicroMouseTemplate_DW.direction[2];
    if (tmp > 32767) {
      tmp = 32767;
    } else if (tmp < -32768) {
      tmp = -32768;
    }

    tmp_0 = MicroMouseTemplate_DW.pos[1] + MicroMouseTemplate_DW.direction[3];
    if (tmp_0 > 32767) {
      tmp_0 = 32767;
    } else if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }

    tmp_0 -= MicroMouseTemplate_DW.direction[1];
    if (tmp_0 > 32767) {
      tmp_0 = 32767;
    } else if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }

    MicroMouseTemplat_delConnection(MicroMouseTemplate_DW.pos[0],
      MicroMouseTemplate_DW.pos[1], (int16_T)tmp, (int16_T)tmp_0);
  }

  if (Sensors[3] == 1.0) {
    tmp = MicroMouseTemplate_DW.pos[0] + MicroMouseTemplate_DW.direction[2];
    if (tmp > 32767) {
      tmp = 32767;
    } else if (tmp < -32768) {
      tmp = -32768;
    }

    tmp -= MicroMouseTemplate_DW.direction[0];
    if (tmp > 32767) {
      tmp = 32767;
    } else if (tmp < -32768) {
      tmp = -32768;
    }

    tmp_0 = MicroMouseTemplate_DW.pos[1] + MicroMouseTemplate_DW.direction[1];
    if (tmp_0 > 32767) {
      tmp_0 = 32767;
    } else if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }

    tmp_0 -= MicroMouseTemplate_DW.direction[3];
    if (tmp_0 > 32767) {
      tmp_0 = 32767;
    } else if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }

    MicroMouseTemplat_delConnection(MicroMouseTemplate_DW.pos[0],
      MicroMouseTemplate_DW.pos[1], (int16_T)tmp, (int16_T)tmp_0);
  }

  MicroMouseTemplate_route(pathend, MicroMouseTemplate_B.path);
  Turn = 0.0;
  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp - 1] > MicroMouseTemplate_DW.pos[0]) &&
      (MicroMouseTemplate_DW.direction[0] == 1)) {
    Turn = 1.0;
    a_idx_1 = MicroMouseTemplate_DW.direction[1];
    a_idx_3 = MicroMouseTemplate_DW.direction[2];
    MicroMouseTemplate_DW.direction[0] = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[1] = 1;
    MicroMouseTemplate_DW.direction[2] = a_idx_1;
    MicroMouseTemplate_DW.direction[3] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp - 1] > MicroMouseTemplate_DW.pos[0]) &&
      (MicroMouseTemplate_DW.direction[2] == 1)) {
    Turn = -1.0;
    a_idx_3 = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[1] = 1;
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[3] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp - 1] < MicroMouseTemplate_DW.pos[0]) &&
      (MicroMouseTemplate_DW.direction[0] == 1)) {
    Turn = -1.0;
    MicroMouseTemplate_DW.direction[0] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[1] = MicroMouseTemplate_DW.direction[2];
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[3] = 1;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp - 1] < MicroMouseTemplate_DW.pos[0]) &&
      (MicroMouseTemplate_DW.direction[2] == 1)) {
    Turn = 1.0;
    a_idx_3 = MicroMouseTemplate_DW.direction[1];
    a_idx_1 = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[1] = a_idx_1;
    MicroMouseTemplate_DW.direction[2] = a_idx_3;
    MicroMouseTemplate_DW.direction[3] = 1;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp + 199] > MicroMouseTemplate_DW.pos[1]) &&
      (MicroMouseTemplate_DW.direction[1] == 1)) {
    Turn = -1.0;
    a_idx_3 = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = 1;
    MicroMouseTemplate_DW.direction[1] = MicroMouseTemplate_DW.direction[2];
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[3] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp + 199] > MicroMouseTemplate_DW.pos[1]) &&
      (MicroMouseTemplate_DW.direction[3] == 1)) {
    Turn = 1.0;
    a_idx_1 = MicroMouseTemplate_DW.direction[0];
    a_idx_3 = MicroMouseTemplate_DW.direction[2];
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[0] = 1;
    MicroMouseTemplate_DW.direction[1] = a_idx_1;
    MicroMouseTemplate_DW.direction[3] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp + 199] < MicroMouseTemplate_DW.pos[1]) &&
      (MicroMouseTemplate_DW.direction[1] == 1)) {
    Turn = 1.0;
    a_idx_3 = MicroMouseTemplate_DW.direction[2];
    a_idx_1 = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[1] = a_idx_1;
    MicroMouseTemplate_DW.direction[2] = 1;
    MicroMouseTemplate_DW.direction[3] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp + 199] < MicroMouseTemplate_DW.pos[1]) &&
      (MicroMouseTemplate_DW.direction[3] == 1)) {
    Turn = -1.0;
    a_idx_3 = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[1] = MicroMouseTemplate_DW.direction[2];
    MicroMouseTemplate_DW.direction[2] = 1;
    MicroMouseTemplate_DW.direction[3] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp + 199] < MicroMouseTemplate_DW.pos[1]) &&
      (MicroMouseTemplate_DW.direction[0] == 1)) {
    Turn = 2.0;
    a_idx_1 = MicroMouseTemplate_DW.direction[2];
    a_idx_3 = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[3] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[2] = 1;
    MicroMouseTemplate_DW.direction[0] = a_idx_1;
    MicroMouseTemplate_DW.direction[1] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp + 199] > MicroMouseTemplate_DW.pos[1]) &&
      (MicroMouseTemplate_DW.direction[2] == 1)) {
    Turn = 2.0;
    a_idx_3 = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[3] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = 1;
    MicroMouseTemplate_DW.direction[1] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp - 1] < MicroMouseTemplate_DW.pos[0]) &&
      (MicroMouseTemplate_DW.direction[1] == 1)) {
    Turn = 2.0;
    a_idx_1 = MicroMouseTemplate_DW.direction[2];
    a_idx_3 = MicroMouseTemplate_DW.direction[3];
    MicroMouseTemplate_DW.direction[3] = 1;
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = a_idx_1;
    MicroMouseTemplate_DW.direction[1] = a_idx_3;
  }

  tmp = *pathend - 1;
  if (*pathend - 1 < -32768) {
    tmp = -32768;
  }

  if ((MicroMouseTemplate_B.path[tmp - 1] > MicroMouseTemplate_DW.pos[0]) &&
      (MicroMouseTemplate_DW.direction[3] == 1)) {
    Turn = 2.0;
    a_idx_1 = MicroMouseTemplate_DW.direction[2];
    MicroMouseTemplate_DW.direction[3] = MicroMouseTemplate_DW.direction[1];
    MicroMouseTemplate_DW.direction[2] = MicroMouseTemplate_DW.direction[0];
    MicroMouseTemplate_DW.direction[0] = a_idx_1;
    MicroMouseTemplate_DW.direction[1] = 1;
  }

  return Turn;
}

/* Function for Chart: '<Root>/Lameo' */
static void MicroMouseTemplate_FollowLine(real_T Drive, const real_T b_Sensors[8],
  real_T *Left, real_T *Right)
{
  real_T PID;
  *Left = 0.0;
  *Right = 0.0;
  if (Drive == 1.0) {
    if ((b_Sensors[2] == 1.0) && (b_Sensors[5] == 0.0)) {
      MicroMouseTemplate_DW.error = -1.0;
    }

    if (b_Sensors[2] == 0.0) {
      if (b_Sensors[5] == 1.0) {
        MicroMouseTemplate_DW.error = 1.0;
      }

      if (b_Sensors[5] == 0.0) {
        MicroMouseTemplate_DW.error = 0.0;
      }
    }

    if ((MicroMouseTemplate_DW.error == 1.0) && (b_Sensors[2] == 1.0) &&
        (b_Sensors[5] == 1.0)) {
      MicroMouseTemplate_DW.error = 2.0;
    }

    if ((MicroMouseTemplate_DW.error == -1.0) && (b_Sensors[2] == 1.0) &&
        (b_Sensors[5] == 1.0)) {
      MicroMouseTemplate_DW.error = -2.0;
    }

    MicroMouseTemplate_DW.sumError += MicroMouseTemplate_DW.error;
    MicroMouseTemplate_DW.sumError -= 0.005 * MicroMouseTemplate_DW.sumError;
    MicroMouseTemplate_DW.Dave = (MicroMouseTemplate_DW.error -
      MicroMouseTemplate_DW.preError) + 0.8 * MicroMouseTemplate_DW.Dave;
    PID = (15.0 * MicroMouseTemplate_DW.error + 0.5 *
           MicroMouseTemplate_DW.sumError) + 100.0 * MicroMouseTemplate_DW.Dave;
    MicroMouseTemplate_DW.preError = MicroMouseTemplate_DW.error;
    if (100.0 - PID >= -100.0) {
      *Left = 100.0 - PID;
    } else {
      *Left = -100.0;
    }

    if (*Left > 100.0) {
      *Left = 100.0;
    }

    if (PID + 100.0 >= -100.0) {
      *Right = PID + 100.0;
    } else {
      *Right = -100.0;
    }

    if (*Right > 100.0) {
      *Right = 100.0;
    }

    if ((MicroMouseTemplate_DW.error == 0.0) && (b_Sensors[2] == 1.0) &&
        (b_Sensors[5] == 1.0)) {
      *Left = -50.0;
      *Right = -50.0;
    }
  }
}

static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj)
{
  ADC_Type_T adcStructLoc;
  obj->isSetupComplete = false;

  /* Start for MATLABSystem: '<S51>/Analog to Digital Converter' */
  obj->isInitialized = 1;
  adcStructLoc.InternalBufferPtr = (void*)(&obj->ADCInternalBuffer[0]);
  adcStructLoc.InjectedNoOfConversion = 0U;
  adcStructLoc.peripheralPtr = ADC2;
  adcStructLoc.dmaPeripheralPtr = DMA1;
  adcStructLoc.dmastream = LL_DMA_CHANNEL_2;
  adcStructLoc.DataTransferMode = ADC_DR_TRANSFER;
  adcStructLoc.DmaTransferMode = ADC_DMA_TRANSFER_UNLIMITED;
  adcStructLoc.InternalBufferSize = 9U;
  adcStructLoc.RegularNoOfConversion = 9U;
  obj->ADCHandle = ADC_Handle_Init(&adcStructLoc, ADC_DMA_INTERRUPT_MODE, 1,
    ADC_TRIGGER_AND_READ, LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS);
  enableADCAutomaticCalibrationOffset(obj->ADCHandle, 2);
  enableADC(obj->ADCHandle);
  startADCConversionForExternalTrigger(obj->ADCHandle, 1);
  obj->isSetupComplete = true;
}

static void MicroMouseT_PWMOutput_setupImpl(stm32cube_blocks_PWMOutput_Mi_T *obj)
{
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<S45>/PWM Output' */
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<S45>/PWM Output' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  enableTimerChannel3(obj->TimerHandle, ENABLE_CH);
  enableTimerChannel4(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<S45>/PWM Output' */
    enableCounter(obj->TimerHandle, false);
  }
}

static void MicroMous_PWMOutput_setupImpl_d(stm32cube_blocks_PWMOutput_Mi_T *obj)
{
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<S47>/PWM Output' */
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<S47>/PWM Output' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  enableTimerChannel1(obj->TimerHandle, ENABLE_CH);
  enableTimerChannel2(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<S47>/PWM Output' */
    enableCounter(obj->TimerHandle, false);
  }
}

/* Model step function for TID0 */
void MicroMouseTemplate_step0(void)    /* Sample time: [0.01s, 0.0s] */
{
  int32_T i;
  int32_T rtb_Right;
  uint32_T pinReadLoc;
  int16_T pathend;
  uint16_T rtb_TmpRTBAtMaxofElements7Outpo;
  uint16_T rtb_TmpRTBAtMaxofElementsOutpor;
  int8_T a__1[2];
  boolean_T shiftright;
  static const int8_T b_a[5] = { 1, 0, 0, 0, 0 };

  {                                    /* Sample time: [0.01s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* MATLABSystem: '<S51>/Analog to Digital Converter' */
  regularReadADCDMA(MicroMouseTemplate_DW.obj.ADCHandle, ADC_TRIGGER_AND_READ,
                    &ADC1s[0]);

  /* RateTransition generated from: '<S52>/Max of Elements' */
  rtb_TmpRTBAtMaxofElementsOutpor =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B;

  /* DSPFlip: '<S9>/Flip' incorporates:
   *  MATLABSystem: '<S51>/Analog to Digital Converter'
   */
  MicroMouseTemplate_B.Flip[0] = ADC1s[7];
  MicroMouseTemplate_B.Flip[7] = ADC1s[0];
  MicroMouseTemplate_B.Flip[1] = ADC1s[6];
  MicroMouseTemplate_B.Flip[6] = ADC1s[1];
  MicroMouseTemplate_B.Flip[2] = ADC1s[5];
  MicroMouseTemplate_B.Flip[5] = ADC1s[2];
  MicroMouseTemplate_B.Flip[3] = ADC1s[4];
  MicroMouseTemplate_B.Flip[4] = ADC1s[3];

  /* DataTypeConversion: '<S54>/Cast To Double' */
  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_B.CastToDouble[i] = MicroMouseTemplate_B.Flip[i];
  }

  /* End of DataTypeConversion: '<S54>/Cast To Double' */
  MicroMouseTem_MATLABSystem3(MicroMouseTemplate_B.CastToDouble[1],
    &MicroMouseTemplate_B.MATLABSystem4, &MicroMouseTemplate_DW.MATLABSystem4,
    &MicroMouseTemplate_P.MATLABSystem4);

  /* MinMax: '<S52>/Max of Elements1' incorporates:
   *  MATLABSystem: '<S52>/MATLAB System4'
   */
  MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.MATLABSystem4.MATLABSystem3[0];
  for (rtb_Right = 0; rtb_Right < 9; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem4.MATLABSystem3[rtb_Right + 1];
    if (MicroMouseTemplate_B.Lf < MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.Lf,
    &MicroMouseTemplate_B.MATLABSystem1, &MicroMouseTemplate_DW.MATLABSystem1,
    &MicroMouseTemplate_P.MATLABSystem1);

  /* End of MinMax: '<S52>/Max of Elements1' */

  /* MinMax: '<S52>/Min' incorporates:
   *  MATLABSystem: '<S52>/MATLAB System1'
   */
  MicroMouseTemplate_B.Add = MicroMouseTemplate_B.MATLABSystem1.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem1.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.Add > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Add = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[2],
    &MicroMouseTemplate_B.MATLABSystem1_ci,
    &MicroMouseTemplate_DW.MATLABSystem1_ci,
    &MicroMouseTemplate_P.MATLABSystem1_ci);

  /* MinMax: '<S52>/Max of Elements2' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System1'
   */
  MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1
    [0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.Lf < MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[3],
    &MicroMouseTemplate_B.MATLABSystem3_c,
    &MicroMouseTemplate_DW.MATLABSystem3_c,
    &MicroMouseTemplate_P.MATLABSystem3_c);

  /* MinMax: '<S52>/Max of Elements3' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System3'
   */
  MicroMouseTemplate_B.maxV =
    MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.maxV < MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.maxV = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[4],
    &MicroMouseTemplate_B.MATLABSystem4_c,
    &MicroMouseTemplate_DW.MATLABSystem4_c,
    &MicroMouseTemplate_P.MATLABSystem4_c);

  /* MinMax: '<S52>/Max of Elements4' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System4'
   */
  MicroMouseTemplate_B.maxV_m =
    MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.maxV_m < MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.maxV_m = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[5],
    &MicroMouseTemplate_B.MATLABSystem5, &MicroMouseTemplate_DW.MATLABSystem5,
    &MicroMouseTemplate_P.MATLABSystem5);

  /* MinMax: '<S52>/Max of Elements5' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System5'
   */
  MicroMouseTemplate_B.maxV_c =
    MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.maxV_c < MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.maxV_c = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem3(MicroMouseTemplate_B.CastToDouble[6],
    &MicroMouseTemplate_B.MATLABSystem3, &MicroMouseTemplate_DW.MATLABSystem3,
    &MicroMouseTemplate_P.MATLABSystem3);

  /* MinMax: '<S52>/Max of Elements6' incorporates:
   *  MATLABSystem: '<S52>/MATLAB System3'
   */
  MicroMouseTemplate_B.Add1 = MicroMouseTemplate_B.MATLABSystem3.MATLABSystem3[0];
  for (rtb_Right = 0; rtb_Right < 9; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem3.MATLABSystem3[rtb_Right + 1];
    if (MicroMouseTemplate_B.Add1 < MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Add1 = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.Add1,
    &MicroMouseTemplate_B.MATLABSystem2, &MicroMouseTemplate_DW.MATLABSystem2,
    &MicroMouseTemplate_P.MATLABSystem2);

  /* End of MinMax: '<S52>/Max of Elements6' */

  /* MinMax: '<S52>/Min1' incorporates:
   *  MATLABSystem: '<S52>/MATLAB System2'
   */
  MicroMouseTemplate_B.Add1 = MicroMouseTemplate_B.MATLABSystem2.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem2.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.Add1 > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Add1 = MicroMouseTemplate_B.Rf;
    }
  }

  /* RateTransition generated from: '<S52>/Max of Elements7' */
  rtb_TmpRTBAtMaxofElements7Outpo =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_;

  /* DataStoreWrite: '<S49>/ADC_H Write' */
  ADC_H[0] = rtb_TmpRTBAtMaxofElementsOutpor;

  /* MinMax: '<S52>/Min' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.Add), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_H Write' incorporates:
   *  MinMax: '<S52>/Min'
   */
  ADC_H[1] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S52>/Max of Elements2' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.Lf), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_H Write' incorporates:
   *  MinMax: '<S52>/Max of Elements2'
   */
  ADC_H[2] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S52>/Max of Elements3' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.maxV), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_H Write' incorporates:
   *  MinMax: '<S52>/Max of Elements3'
   */
  ADC_H[3] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S52>/Max of Elements4' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.maxV_m), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_H Write' incorporates:
   *  MinMax: '<S52>/Max of Elements4'
   */
  ADC_H[4] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S52>/Max of Elements5' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.maxV_c), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_H Write' incorporates:
   *  MinMax: '<S52>/Max of Elements5'
   */
  ADC_H[5] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S52>/Min1' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.Add1), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_H Write' incorporates:
   *  Constant: '<S49>/Constant'
   *  MinMax: '<S52>/Min1'
   */
  ADC_H[6] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);
  ADC_H[7] = rtb_TmpRTBAtMaxofElements7Outpo;
  ADC_H[8] = MicroMouseTemplate_P.Constant_Value_b;

  /* RateTransition generated from: '<S53>/Max of Elements8' */
  rtb_TmpRTBAtMaxofElementsOutpor =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_;
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[1],
    &MicroMouseTemplate_B.MATLABSystem1_c,
    &MicroMouseTemplate_DW.MATLABSystem1_c,
    &MicroMouseTemplate_P.MATLABSystem1_c);

  /* MinMax: '<S53>/Max of Elements9' incorporates:
   *  MATLABSystem: '<S53>/MATLAB System1'
   */
  MicroMouseTemplate_B.Add = MicroMouseTemplate_B.MATLABSystem1_c.MATLABSystem1
    [0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem1_c.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.Add > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Add = MicroMouseTemplate_B.Rf;
    }
  }

  /* MinMax: '<S53>/Max of Elements10' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System1'
   */
  MicroMouseTemplate_B.Add1 =
    MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.Add1 > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Add1 = MicroMouseTemplate_B.Rf;
    }
  }

  /* MinMax: '<S53>/Max of Elements11' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System3'
   */
  MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.Lf > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.Rf;
    }
  }

  /* MinMax: '<S53>/Max of Elements12' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System4'
   */
  MicroMouseTemplate_B.maxV =
    MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.maxV > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.maxV = MicroMouseTemplate_B.Rf;
    }
  }

  /* MinMax: '<S53>/Max of Elements13' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System5'
   */
  MicroMouseTemplate_B.maxV_m =
    MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.maxV_m > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.maxV_m = MicroMouseTemplate_B.Rf;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[6],
    &MicroMouseTemplate_B.MATLABSystem2_c,
    &MicroMouseTemplate_DW.MATLABSystem2_c,
    &MicroMouseTemplate_P.MATLABSystem2_c);

  /* MinMax: '<S53>/Max of Elements14' incorporates:
   *  MATLABSystem: '<S53>/MATLAB System2'
   */
  MicroMouseTemplate_B.maxV_c =
    MicroMouseTemplate_B.MATLABSystem2_c.MATLABSystem1[0];
  for (rtb_Right = 0; rtb_Right < 24; rtb_Right++) {
    MicroMouseTemplate_B.Rf =
      MicroMouseTemplate_B.MATLABSystem2_c.MATLABSystem1[rtb_Right + 1];
    if (MicroMouseTemplate_B.maxV_c > MicroMouseTemplate_B.Rf) {
      MicroMouseTemplate_B.maxV_c = MicroMouseTemplate_B.Rf;
    }
  }

  /* RateTransition generated from: '<S53>/Max of Elements15' */
  rtb_TmpRTBAtMaxofElements7Outpo =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1;

  /* DataStoreWrite: '<S49>/ADC_L Write' */
  ADC_L[0] = rtb_TmpRTBAtMaxofElementsOutpor;

  /* MinMax: '<S53>/Max of Elements9' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.Add), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_L Write' incorporates:
   *  MinMax: '<S53>/Max of Elements9'
   */
  ADC_L[1] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S53>/Max of Elements10' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.Add1), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_L Write' incorporates:
   *  MinMax: '<S53>/Max of Elements10'
   */
  ADC_L[2] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S53>/Max of Elements11' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.Lf), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_L Write' incorporates:
   *  MinMax: '<S53>/Max of Elements11'
   */
  ADC_L[3] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S53>/Max of Elements12' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.maxV), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_L Write' incorporates:
   *  MinMax: '<S53>/Max of Elements12'
   */
  ADC_L[4] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S53>/Max of Elements13' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.maxV_m), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_L Write' incorporates:
   *  MinMax: '<S53>/Max of Elements13'
   */
  ADC_L[5] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);

  /* MinMax: '<S53>/Max of Elements14' */
  MicroMouseTemplate_B.Rf = fmod(floor(MicroMouseTemplate_B.maxV_c), 65536.0);

  /* DataStoreWrite: '<S49>/ADC_L Write' incorporates:
   *  Constant: '<S49>/Constant1'
   *  MinMax: '<S53>/Max of Elements14'
   */
  ADC_L[6] = (uint16_T)(MicroMouseTemplate_B.Rf < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Rf : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.Rf);
  ADC_L[7] = rtb_TmpRTBAtMaxofElements7Outpo;
  ADC_L[8] = MicroMouseTemplate_P.Constant1_Value;

  /* RateTransition: '<S54>/Rate Transition' */
  if (MicroMouseTemplate_M->Timing.RateInteraction.TID0_1) {
    MicroMouseTemplate_DW.RateTransition_Buffer =
      MicroMouseTemplate_B.CastToDouble[0];

    /* RateTransition: '<S54>/Rate Transition1' */
    MicroMouseTemplate_DW.RateTransition1_Buffer =
      MicroMouseTemplate_B.CastToDouble[7];
  }

  /* End of RateTransition: '<S54>/Rate Transition' */
  for (i = 0; i < 8; i++) {
    /* DataTypeConversion: '<S9>/Cast To Double' incorporates:
     *  DSPFlip: '<S9>/Flip'
     *  Gain: '<S9>/Gain1'
     */
    MicroMouseTemplate_B.CastToDouble_m[i] = (real_T)((uint32_T)
      MicroMouseTemplate_P.Gain1_Gain * MicroMouseTemplate_B.Flip[i]) *
      1.4901161193847656E-8;

    /* DataStoreWrite: '<S1>/Data Store Write' */
    Detections[i] = false;

    /* DataStoreWrite: '<S1>/Data Store Write1' */
    Thresholds[i] = 0U;
  }

  /* DataStoreWrite: '<S1>/Data Store Write2' */
  currTicksRS = 0;

  /* DataStoreWrite: '<S1>/Data Store Write3' */
  currTicksLS = 0;

  /* MATLAB Function: '<S6>/MATLAB Function' */
  MicroMouseTemplate_DW.c++;
  for (i = 0; i < 5; i++) {
    MicroMouseTemplate_B.a[i] = b_a[i];
  }

  if (MicroMouseTemplate_DW.c < 0.0) {
    i = -(int32_T)MicroMouseTemplate_DW.c;
    shiftright = false;
  } else {
    i = (int32_T)MicroMouseTemplate_DW.c;
    shiftright = true;
  }

  if (i > 5) {
    i -= i / 5 * 5;
  }

  if (i > 2) {
    i = 5 - i;
    shiftright = !shiftright;
  }

  a__1[0] = 0;
  a__1[1] = 0;
  if (i > 0) {
    if (shiftright) {
      for (rtb_Right = 5; rtb_Right >= i + 1; rtb_Right--) {
        MicroMouseTemplate_B.a[rtb_Right - 1] = MicroMouseTemplate_B.a
          [(rtb_Right - i) - 1];
      }

      memset(&MicroMouseTemplate_B.a[0], 0, (uint32_T)i * sizeof(int8_T));
    } else {
      memcpy(&a__1[0], &b_a[0], (uint32_T)i * sizeof(int8_T));
      memset(&MicroMouseTemplate_B.a[0], 0, (uint32_T)((4 - i) + 1) * sizeof
             (int8_T));
      for (rtb_Right = 0; rtb_Right < i; rtb_Right++) {
        MicroMouseTemplate_B.a[(rtb_Right - i) + 5] = a__1[rtb_Right];
      }
    }
  }

  /* Outputs for Atomic SubSystem: '<Root>/GPIO for IR LEDs' */
  /* MATLABSystem: '<S22>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[2] != 0) {
    i = 512;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 512U);

  /* End of MATLABSystem: '<S22>/Digital Port Write' */

  /* MATLABSystem: '<S24>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[2] != 0) {
    i = 16384;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 16384U);

  /* End of MATLABSystem: '<S24>/Digital Port Write' */

  /* MATLABSystem: '<S26>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[1] != 0) {
    i = 256;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 256U);

  /* End of MATLABSystem: '<S26>/Digital Port Write' */

  /* MATLABSystem: '<S28>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[1] != 0) {
    i = 32768;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 32768U);

  /* End of MATLABSystem: '<S28>/Digital Port Write' */

  /* MATLABSystem: '<S30>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[3] != 0) {
    i = 4096;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 4096U);

  /* End of MATLABSystem: '<S30>/Digital Port Write' */

  /* MATLABSystem: '<S32>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_B.a[0] != 0) {
    i = 4096;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 4096U);

  /* End of MATLABSystem: '<S32>/Digital Port Write' */

  /* MATLABSystem: '<S34>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[0] != 0) {
    i = 8192;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8192U);

  /* End of MATLABSystem: '<S34>/Digital Port Write' */

  /* MATLABSystem: '<S36>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[3] != 0) {
    i = 2048;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 2048U);

  /* End of MATLABSystem: '<S36>/Digital Port Write' */
  /* End of Outputs for SubSystem: '<Root>/GPIO for IR LEDs' */

  /* MATLABSystem: '<S72>/Digital Port Read' */
  MicroMouseTemplate_B.pinReadLoc = LL_GPIO_ReadInputPort(GPIOB);

  /* SignalConversion generated from: '<S3>/ SFunction ' incorporates:
   *  MATLAB Function: '<Root>/Function Sense'
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  MicroMouseTemplate_B.CastToDouble[0] = MicroMouseTemplate_B.a[0];
  MicroMouseTemplate_B.CastToDouble[1] = MicroMouseTemplate_B.a[1];
  MicroMouseTemplate_B.CastToDouble[2] = MicroMouseTemplate_B.a[2];
  MicroMouseTemplate_B.CastToDouble[3] = MicroMouseTemplate_B.a[3];
  MicroMouseTemplate_B.CastToDouble[4] = MicroMouseTemplate_B.a[3];
  MicroMouseTemplate_B.CastToDouble[5] = MicroMouseTemplate_B.a[2];
  MicroMouseTemplate_B.CastToDouble[6] = MicroMouseTemplate_B.a[1];
  MicroMouseTemplate_B.CastToDouble[7] = MicroMouseTemplate_B.a[0];

  /* MATLAB Function: '<Root>/Function Sense' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  if (!MicroMouseTemplate_DW.prePAT_not_empty) {
    memcpy(&MicroMouseTemplate_DW.prePAT[0], &MicroMouseTemplate_B.CastToDouble
           [0], sizeof(real_T) << 3U);
    MicroMouseTemplate_DW.prePAT_not_empty = true;
  }

  if (!MicroMouseTemplate_DW.preNoLED_not_empty) {
    MicroMouseTemplate_DW.preNoLED = MicroMouseTemplate_B.a[4];
    MicroMouseTemplate_DW.preNoLED_not_empty = true;
  }

  if (!MicroMouseTemplate_DW.ADCOFF_not_empty) {
    MicroMouseTemplate_DW.ADCOFF.size[0] = 1;
    MicroMouseTemplate_DW.ADCOFF.size[1] = 8;
    memset(&MicroMouseTemplate_DW.ADCOFF.data[0], 0, sizeof(real_T) << 3U);
    MicroMouseTemplate_DW.ADCOFF_not_empty = true;
  }

  if (MicroMouseTemplate_DW.preNoLED == 1.0) {
    MicroMouseTemplate_DW.ADCOFF.size[0] = 8;
    MicroMouseTemplate_DW.ADCOFF.size[1] = 1;
    memcpy(&MicroMouseTemplate_DW.ADCOFF.data[0],
           &MicroMouseTemplate_B.CastToDouble_m[0], sizeof(real_T) << 3U);
  }

  MicroMouseTemplate_DW.preNoLED = MicroMouseTemplate_B.a[4];
  for (i = 0; i < 8; i++) {
    if (MicroMouseTemplate_DW.prePAT[i] == 1.0) {
      MicroMouseTemplate_DW.ADCON[i] = MicroMouseTemplate_B.CastToDouble_m[i];
    }

    MicroMouseTemplate_B.CastToDouble_m[i] = MicroMouseTemplate_DW.ADCON[i] -
      MicroMouseTemplate_DW.ADCOFF.data[i];
    MicroMouseTemplate_DW.prePAT[i] = MicroMouseTemplate_B.CastToDouble[i];

    /* MATLAB Function: '<Root>/Function Sensor Anal' */
    MicroMouseTemplate_B.CastToDouble[i] = 0.0;
  }

  /* MATLAB Function: '<Root>/Function Sensor Anal' */
  if (MicroMouseTemplate_B.CastToDouble_m[2] > MicroMouseTemplate_DW.LineValL) {
    MicroMouseTemplate_B.CastToDouble[2] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[5] > MicroMouseTemplate_DW.LineValR) {
    MicroMouseTemplate_B.CastToDouble[5] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[1] > MicroMouseTemplate_DW.WalCalFr) {
    MicroMouseTemplate_B.CastToDouble[1] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[6] > MicroMouseTemplate_DW.WalCalFl) {
    MicroMouseTemplate_B.CastToDouble[6] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[4] > MicroMouseTemplate_DW.WalCalL) {
    MicroMouseTemplate_B.CastToDouble[4] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[3] > MicroMouseTemplate_DW.WalCalR) {
    MicroMouseTemplate_B.CastToDouble[3] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[7] > MicroMouseTemplate_DW.WelCalL *
      1.05) {
    MicroMouseTemplate_DW.sens8 = 1.0;
  } else if (MicroMouseTemplate_B.CastToDouble_m[7] <
             MicroMouseTemplate_DW.WelCalL * 0.95) {
    MicroMouseTemplate_DW.sens8 = 0.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[0] > MicroMouseTemplate_DW.WelCalR *
      1.05) {
    MicroMouseTemplate_DW.sens1 = 1.0;
  } else if (MicroMouseTemplate_B.CastToDouble_m[0] <
             MicroMouseTemplate_DW.WelCalR * 0.95) {
    MicroMouseTemplate_DW.sens1 = 0.0;
  }

  MicroMouseTemplate_B.CastToDouble[7] = MicroMouseTemplate_DW.sens8;
  MicroMouseTemplate_B.CastToDouble[0] = MicroMouseTemplate_DW.sens1;

  /* MATLABSystem: '<S70>/Digital Port Read' */
  pinReadLoc = LL_GPIO_ReadInputPort(GPIOE);

  /* Chart: '<Root>/Lameo' incorporates:
   *  Logic: '<S12>/NOT'
   *  Logic: '<S12>/NOT1'
   *  MATLAB Function: '<Root>/Function Sensor Anal'
   *  MATLABSystem: '<S70>/Digital Port Read'
   *  MATLABSystem: '<S72>/Digital Port Read'
   * */
  if (MicroMouseTemplate_DW.temporalCounter_i1 < 255U) {
    MicroMouseTemplate_DW.temporalCounter_i1++;
  }

  if (MicroMouseTemplate_DW.bitsForTID0.is_active_c2_MicroMouseTemplate == 0U) {
    MicroMouseTemplate_DW.bitsForTID0.is_active_c2_MicroMouseTemplate = 1U;
    MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Idle;
    MicroMouseTemplate_B.Left = 0.0;
    MicroMouseTemplate_B.Right = 0.0;
    MicroMouseTemplate_Init();
  } else {
    switch (MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate) {
     case MicroMouseTempla_IN_Calibration:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 200U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Idle;
        MicroMouseTemplate_B.Left = 0.0;
        MicroMouseTemplate_B.Right = 0.0;
        MicroMouseTemplate_Init();
      } else {
        MicroMouseTemplate_B.Calibrate = 1.0;
      }
      break;

     case MicroMouseTemplate_IN_Crossing:
      if (MicroMouseTemplate_DW.Turn == -1.0) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_TurnLeft;
        MicroMouseTemplate_B.Left = -100.0;
        MicroMouseTemplate_B.Right = 100.0;
      } else if (MicroMouseTemplate_DW.Turn == 1.0) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_TurnRight;
        MicroMouseTemplate_B.Left = 100.0;
        MicroMouseTemplate_B.Right = -100.0;
      } else if (MicroMouseTemplate_DW.Turn == 0.0) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive;
        MicroMouseTemplate_B.Drive = 1.0;
      } else if (MicroMouseTemplate_DW.Turn == 2.0) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Flip;
        MicroMouseTemplate_B.Left = 100.0;
        MicroMouseTemplate_B.Right = -100.0;
      }
      break;

     case MicroMouseTemplate_IN_Delay:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 100U) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Crossing;
        MicroMouseTemplate_DW.Turn = MicroMouseTemplate_thingy(&pathend,
          MicroMouseTemplate_B.CastToDouble);
        i = MicroMouseTemplate_DW.pos[0] + MicroMouseTemplate_DW.direction[1];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        i -= MicroMouseTemplate_DW.direction[3];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        MicroMouseTemplate_DW.pos[0] = (int16_T)i;
        i = MicroMouseTemplate_DW.direction[0] + MicroMouseTemplate_DW.pos[1];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        i -= MicroMouseTemplate_DW.direction[2];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        MicroMouseTemplate_DW.pos[1] = (int16_T)i;
      }
      break;

     case MicroMouseTemplate_IN_Drive:
      if ((MicroMouseTemplate_B.CastToDouble_m[2] +
           MicroMouseTemplate_B.CastToDouble_m[5] <
           (MicroMouseTemplate_DW.LineValL + MicroMouseTemplate_DW.LineValR) *
           0.7) && (MicroMouseTemplate_DW.temporalCounter_i1 >= 50U)) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplat_IN_Fuckmeeeee;
      } else {
        MicroMouseTemplate_FollowLine(MicroMouseTemplate_B.Drive,
          MicroMouseTemplate_B.CastToDouble, &MicroMouseTemplate_B.Left,
          &MicroMouseTemplate_B.Right);
      }
      break;

     case MicroMouseTemplate_IN_Flip:
      if ((MicroMouseTemplate_DW.temporalCounter_i1 >= 40U) &&
          (MicroMouseTemplate_B.CastToDouble[5] == 0.0)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplat_IN_TurnWrong2;
        MicroMouseTemplate_B.Left = -50.0;
        MicroMouseTemplate_B.Right = 50.0;
      }
      break;

     case MicroMouseTemplat_IN_Fuckmeeeee:
      if ((MicroMouseTemplate_DW.pos[0] == MicroMouseTemplate_DW.dest[0]) &&
          (MicroMouseTemplate_DW.pos[1] == MicroMouseTemplate_DW.dest[1])) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Idle;
        MicroMouseTemplate_B.Left = 0.0;
        MicroMouseTemplate_B.Right = 0.0;
        MicroMouseTemplate_Init();
      } else {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Crossing;
        MicroMouseTemplate_DW.Turn = MicroMouseTemplate_thingy(&pathend,
          MicroMouseTemplate_B.CastToDouble);
        i = MicroMouseTemplate_DW.pos[0] + MicroMouseTemplate_DW.direction[1];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        i -= MicroMouseTemplate_DW.direction[3];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        MicroMouseTemplate_DW.pos[0] = (int16_T)i;
        i = MicroMouseTemplate_DW.direction[0] + MicroMouseTemplate_DW.pos[1];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        i -= MicroMouseTemplate_DW.direction[2];
        if (i > 32767) {
          i = 32767;
        } else if (i < -32768) {
          i = -32768;
        }

        MicroMouseTemplate_DW.pos[1] = (int16_T)i;
      }
      break;

     case MicroMouseTemplate_IN_Idle:
      if (((MicroMouseTemplate_B.pinReadLoc & 4U) == 0U) &&
          (MicroMouseTemplate_DW.temporalCounter_i1 >= 200U)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTempla_IN_Calibration;
      } else if ((pinReadLoc & 64U) == 0U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Delay;
      } else {
        MicroMouseTemplate_B.Calibrate = 0.0;
        MicroMouseTemplate_B.Drive = 0.0;
      }
      break;

     case MicroMouseTemplate_IN_TurnLeft:
      if ((MicroMouseTemplate_DW.temporalCounter_i1 >= 20U) &&
          (MicroMouseTemplate_B.CastToDouble[2] == 0.0)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplat_IN_TurnWrong1;
        MicroMouseTemplate_B.Left = 50.0;
        MicroMouseTemplate_B.Right = -50.0;
      }
      break;

     case MicroMouseTemplate_IN_TurnRight:
      if ((MicroMouseTemplate_DW.temporalCounter_i1 >= 20U) &&
          (MicroMouseTemplate_B.CastToDouble[5] == 0.0)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_TurnWrong;
        MicroMouseTemplate_B.Left = -50.0;
        MicroMouseTemplate_B.Right = 50.0;
      }
      break;

     case MicroMouseTemplate_IN_TurnWrong:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 5U) {
        MicroMouseTemplate_B.Left = 0.0;
        MicroMouseTemplate_B.Right = 0.0;
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive;
        MicroMouseTemplate_B.Drive = 1.0;
      }
      break;

     case MicroMouseTemplat_IN_TurnWrong1:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 5U) {
        MicroMouseTemplate_B.Left = 0.0;
        MicroMouseTemplate_B.Right = 0.0;
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive;
        MicroMouseTemplate_B.Drive = 1.0;
      }
      break;

     default:
      /* case IN_TurnWrong2: */
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 5U) {
        MicroMouseTemplate_B.Left = 0.0;
        MicroMouseTemplate_B.Right = 0.0;
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive;
        MicroMouseTemplate_B.Drive = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Lameo' */

  /* MATLAB Function: '<Root>/Function Calibration' */
  i = 0;
  rtb_Right = 0;
  if (MicroMouseTemplate_B.Calibrate == 1.0) {
    rtb_Right = 75;
    i = -75;
    if (MicroMouseTemplate_B.CastToDouble_m[2] > MicroMouseTemplate_DW.maxdl) {
      MicroMouseTemplate_DW.maxdl = MicroMouseTemplate_DW.maxdl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[2];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[2] < MicroMouseTemplate_DW.mindl) {
      MicroMouseTemplate_DW.mindl = MicroMouseTemplate_DW.mindl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[2];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[5] > MicroMouseTemplate_DW.maxdr) {
      MicroMouseTemplate_DW.maxdr = MicroMouseTemplate_DW.maxdr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[5];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[5] < MicroMouseTemplate_DW.mindr) {
      MicroMouseTemplate_DW.mindr = MicroMouseTemplate_DW.mindr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[5];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[3] > MicroMouseTemplate_DW.maxwr) {
      MicroMouseTemplate_DW.maxwr = MicroMouseTemplate_DW.maxwr * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[3];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[3] < MicroMouseTemplate_DW.minwr) {
      MicroMouseTemplate_DW.minwr = MicroMouseTemplate_DW.minwr * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[3];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[4] > MicroMouseTemplate_DW.maxwl) {
      MicroMouseTemplate_DW.maxwl = MicroMouseTemplate_DW.maxwl * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[4];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[4] < MicroMouseTemplate_DW.minwl) {
      MicroMouseTemplate_DW.minwl = MicroMouseTemplate_DW.minwl * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[4];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[1] > MicroMouseTemplate_DW.maxwfr) {
      MicroMouseTemplate_DW.maxwfr = MicroMouseTemplate_DW.maxwfr * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[1];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[1] < MicroMouseTemplate_DW.minwfr) {
      MicroMouseTemplate_DW.minwfr = MicroMouseTemplate_DW.minwfr * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[1];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[6] > MicroMouseTemplate_DW.maxwfl) {
      MicroMouseTemplate_DW.maxwfl = MicroMouseTemplate_DW.maxwfl * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[6];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[6] < MicroMouseTemplate_DW.minwfl) {
      MicroMouseTemplate_DW.minwfl = MicroMouseTemplate_DW.minwfl * 0.5 + 0.5 *
        MicroMouseTemplate_B.CastToDouble_m[6];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[0] > MicroMouseTemplate_DW.maxwer) {
      MicroMouseTemplate_DW.maxwer = MicroMouseTemplate_DW.maxwer * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[0];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[0] < MicroMouseTemplate_DW.minwer) {
      MicroMouseTemplate_DW.minwer = MicroMouseTemplate_DW.minwer * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[0];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[7] > MicroMouseTemplate_DW.maxwel) {
      MicroMouseTemplate_DW.maxwel = MicroMouseTemplate_DW.maxwel * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[7];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[7] < MicroMouseTemplate_DW.minwel) {
      MicroMouseTemplate_DW.minwel = MicroMouseTemplate_DW.minwel * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[7];
    }
  }

  MicroMouseTemplate_DW.LineValR = (MicroMouseTemplate_DW.mindr +
    MicroMouseTemplate_DW.maxdr) / 2.0;
  MicroMouseTemplate_DW.LineValL = (MicroMouseTemplate_DW.mindl +
    MicroMouseTemplate_DW.maxdl) / 2.0;
  MicroMouseTemplate_DW.WalCalL = MicroMouseTemplate_DW.maxwl * 0.85;
  MicroMouseTemplate_DW.WalCalR = MicroMouseTemplate_DW.maxwr * 0.85;
  MicroMouseTemplate_DW.WalCalFl = MicroMouseTemplate_DW.maxwfl * 0.6;
  MicroMouseTemplate_DW.WalCalFr = MicroMouseTemplate_DW.maxwfr * 0.6;
  MicroMouseTemplate_DW.WelCalL = (MicroMouseTemplate_DW.minwel +
    MicroMouseTemplate_DW.maxwel) / 2.0;
  MicroMouseTemplate_DW.WelCalR = (MicroMouseTemplate_DW.minwer +
    MicroMouseTemplate_DW.maxwer) / 2.0;

  /* End of MATLAB Function: '<Root>/Function Calibration' */

  /* Sum: '<Root>/Add1' */
  MicroMouseTemplate_B.Add1 = (real_T)i + MicroMouseTemplate_B.Left;

  /* Sum: '<Root>/Add' */
  MicroMouseTemplate_B.Add = (real_T)rtb_Right + MicroMouseTemplate_B.Right;

  /* MATLAB Function: '<S8>/Fowards Backwards' */
  if (MicroMouseTemplate_B.Add1 > 10.0) {
    MicroMouseTemplate_B.Rf = MicroMouseTemplate_B.Add1 / 3.0 + 66.0;
    MicroMouseTemplate_B.Add1 = 0.0;
  } else if (MicroMouseTemplate_B.Add1 < -10.0) {
    MicroMouseTemplate_B.Rf = 0.0;
    MicroMouseTemplate_B.Add1 = fabs(MicroMouseTemplate_B.Add1 / 3.0 - 66.0);
  } else {
    MicroMouseTemplate_B.Rf = 0.0;
    MicroMouseTemplate_B.Add1 = 0.0;
  }

  if (MicroMouseTemplate_B.Add > 10.0) {
    MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.Add / 3.0 + 66.0;
    MicroMouseTemplate_B.Add = 0.0;
  } else if (MicroMouseTemplate_B.Add < -10.0) {
    MicroMouseTemplate_B.Lf = 0.0;
    MicroMouseTemplate_B.Add = fabs(MicroMouseTemplate_B.Add / 3.0 - 66.0);
  } else {
    MicroMouseTemplate_B.Lf = 0.0;
    MicroMouseTemplate_B.Add = 0.0;
  }

  /* End of MATLAB Function: '<S8>/Fowards Backwards' */

  /* MATLABSystem: '<S45>/PWM Output' */
  setDutyCycleInPercentageChannel3(MicroMouseTemplate_DW.obj_n.TimerHandle,
    MicroMouseTemplate_B.Rf);
  setDutyCycleInPercentageChannel4(MicroMouseTemplate_DW.obj_n.TimerHandle,
    MicroMouseTemplate_B.Add1);

  /* MATLABSystem: '<S47>/PWM Output' */
  setDutyCycleInPercentageChannel1(MicroMouseTemplate_DW.obj_g.TimerHandle,
    MicroMouseTemplate_B.Lf);
  setDutyCycleInPercentageChannel2(MicroMouseTemplate_DW.obj_g.TimerHandle,
    MicroMouseTemplate_B.Add);

  /* MATLABSystem: '<S43>/Digital Port Write' incorporates:
   *  Constant: '<S8>/Constant'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOD;
  if (MicroMouseTemplate_P.Constant_Value != 0.0) {
    i = 128;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 128U);

  /* End of MATLABSystem: '<S43>/Digital Port Write' */

  /* MATLABSystem: '<S62>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.CastToDouble[3] != 0.0) {
    i = 8192;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8192U);

  /* End of MATLABSystem: '<S62>/Digital Port Write' */

  /* MATLABSystem: '<S64>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.CastToDouble[1] != 0.0) {
    i = 16384;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 16384U);

  /* End of MATLABSystem: '<S64>/Digital Port Write' */

  /* MATLABSystem: '<S66>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.CastToDouble[4] != 0.0) {
    i = 32768;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 32768U);

  /* End of MATLABSystem: '<S66>/Digital Port Write' */

  /* MATLABSystem: '<S60>/Digital Port Write' incorporates:
   *  Constant: '<S11>/Constant'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_P.Constant_Value_i != 0.0) {
    i = 8;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8U);

  /* End of MATLABSystem: '<S60>/Digital Port Write' */

  /* user code (Update function Body for TID0) */

  /* System '<Root>' */
  refreshIMUValues();

  /* System '<Root>' */
  CustomWhile();
}

/* Model step function for TID1 */
void MicroMouseTemplate_step1(void)    /* Sample time: [0.1s, 0.0s] */
{
  real_T maxV;
  real_T u1;
  int32_T k;
  uint16_T rtb_MaxofElements;
  uint16_T rtb_MaxofElements7;

  /* RateTransition: '<S54>/Rate Transition' */
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_DW.RateTransition_Buffer,
    &MicroMouseTemplate_B.MATLABSystem2_ci,
    &MicroMouseTemplate_DW.MATLABSystem2_ci,
    &MicroMouseTemplate_P.MATLABSystem2_ci);

  /* MinMax: '<S52>/Max of Elements' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System2'
   */
  maxV = MicroMouseTemplate_B.MATLABSystem2_ci.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    u1 = MicroMouseTemplate_B.MATLABSystem2_ci.MATLABSystem1[k + 1];
    if (maxV < u1) {
      maxV = u1;
    }
  }

  u1 = fmod(floor(maxV), 65536.0);
  rtb_MaxofElements = (uint16_T)(u1 < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-u1 : (int32_T)(uint16_T)u1);

  /* End of MinMax: '<S52>/Max of Elements' */

  /* RateTransition: '<S54>/Rate Transition1' */
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_DW.RateTransition1_Buffer,
    &MicroMouseTemplate_B.MATLABSystem6, &MicroMouseTemplate_DW.MATLABSystem6,
    &MicroMouseTemplate_P.MATLABSystem6);

  /* MinMax: '<S52>/Max of Elements7' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System6'
   */
  maxV = MicroMouseTemplate_B.MATLABSystem6.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    u1 = MicroMouseTemplate_B.MATLABSystem6.MATLABSystem1[k + 1];
    if (maxV < u1) {
      maxV = u1;
    }
  }

  u1 = fmod(floor(maxV), 65536.0);
  rtb_MaxofElements7 = (uint16_T)(u1 < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-u1 : (int32_T)(uint16_T)u1);

  /* End of MinMax: '<S52>/Max of Elements7' */

  /* RateTransition generated from: '<S52>/Max of Elements7' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_ = rtb_MaxofElements7;

  /* RateTransition generated from: '<S52>/Max of Elements' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B = rtb_MaxofElements;

  /* MinMax: '<S53>/Max of Elements15' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System6'
   */
  maxV = MicroMouseTemplate_B.MATLABSystem6.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    u1 = MicroMouseTemplate_B.MATLABSystem6.MATLABSystem1[k + 1];
    if (maxV > u1) {
      maxV = u1;
    }
  }

  u1 = fmod(floor(maxV), 65536.0);
  rtb_MaxofElements = (uint16_T)(u1 < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-u1 : (int32_T)(uint16_T)u1);

  /* End of MinMax: '<S53>/Max of Elements15' */

  /* MinMax: '<S53>/Max of Elements8' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System2'
   */
  maxV = MicroMouseTemplate_B.MATLABSystem2_ci.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    u1 = MicroMouseTemplate_B.MATLABSystem2_ci.MATLABSystem1[k + 1];
    if (maxV > u1) {
      maxV = u1;
    }
  }

  u1 = fmod(floor(maxV), 65536.0);
  rtb_MaxofElements7 = (uint16_T)(u1 < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-u1 : (int32_T)(uint16_T)u1);

  /* End of MinMax: '<S53>/Max of Elements8' */

  /* RateTransition generated from: '<S53>/Max of Elements15' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1 = rtb_MaxofElements;

  /* RateTransition generated from: '<S53>/Max of Elements8' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_ = rtb_MaxofElements7;

  /* user code (Update function Body for TID1) */

  /* System '<Root>' */
  refreshIMUValues();

  /* System '<Root>' */
  CustomWhile();
}

/* Model initialize function */
void MicroMouseTemplate_initialize(void)
{
  {
    int32_T i;
    for (i = 0; i < 9; i++) {
      /* Start for DataStoreMemory: '<S9>/Data Store Memory' */
      ADC1s[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_p;

      /* Start for DataStoreMemory: '<S9>/Data Store Memory1' */
      ADC_H[i] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_p;

      /* Start for DataStoreMemory: '<S9>/Data Store Memory2' */
      ADC_L[i] = MicroMouseTemplate_P.DataStoreMemory2_InitialValue_p;
    }

    for (i = 0; i < 8; i++) {
      /* Start for DataStoreMemory: '<S1>/Data Store Memory' */
      Detections[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_p4;

      /* Start for DataStoreMemory: '<S1>/Data Store Memory1' */
      Thresholds[i] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_j;
    }

    /* Start for DataStoreMemory: '<S1>/Data Store Memory2' */
    currTicksRS = MicroMouseTemplate_P.DataStoreMemory2_InitialValue_b;

    /* Start for DataStoreMemory: '<S1>/Data Store Memory4' */
    currTicksLS = MicroMouseTemplate_P.DataStoreMemory4_InitialValue_a;

    /* Start for DataStoreMemory: '<S10>/Data Store Memory' */
    IMU_Accel[0] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;

    /* Start for DataStoreMemory: '<S10>/Data Store Memory1' */
    IMU_Gyro[0] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;

    /* Start for DataStoreMemory: '<S10>/Data Store Memory' */
    IMU_Accel[1] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;

    /* Start for DataStoreMemory: '<S10>/Data Store Memory1' */
    IMU_Gyro[1] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;

    /* Start for DataStoreMemory: '<S10>/Data Store Memory' */
    IMU_Accel[2] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;

    /* Start for DataStoreMemory: '<S10>/Data Store Memory1' */
    IMU_Gyro[2] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory' */
    MicroMouseTemplate_DW.LineValL =
      MicroMouseTemplate_P.DataStoreMemory_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory1' */
    MicroMouseTemplate_DW.LineValR =
      MicroMouseTemplate_P.DataStoreMemory1_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory2' */
    MicroMouseTemplate_DW.WalCalL =
      MicroMouseTemplate_P.DataStoreMemory2_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory3' */
    MicroMouseTemplate_DW.WalCalR =
      MicroMouseTemplate_P.DataStoreMemory3_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory4' */
    MicroMouseTemplate_DW.WalCalFl =
      MicroMouseTemplate_P.DataStoreMemory4_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory5' */
    MicroMouseTemplate_DW.WalCalFr =
      MicroMouseTemplate_P.DataStoreMemory5_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory6' */
    MicroMouseTemplate_DW.WelCalR =
      MicroMouseTemplate_P.DataStoreMemory6_InitialValue;

    /* Start for DataStoreMemory: '<Root>/Data Store Memory7' */
    MicroMouseTemplate_DW.WelCalL =
      MicroMouseTemplate_P.DataStoreMemory7_InitialValue;

    /* user code (Initialize function Body) */

    /* System '<Root>' */
    initIMU();

    /* InitializeConditions for RateTransition generated from: '<S52>/Max of Elements' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B =
      MicroMouseTemplate_P.TmpRTBAtMaxofElementsOutport1_I;

    /* InitializeConditions for RateTransition generated from: '<S52>/Max of Elements7' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_ =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements7Outport1_;

    /* InitializeConditions for RateTransition generated from: '<S53>/Max of Elements8' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_ =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements8Outport1_;

    /* InitializeConditions for RateTransition generated from: '<S53>/Max of Elements15' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1 =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements15Outport1;

    /* SystemInitialize for MATLAB Function: '<Root>/Function Calibration' */
    MicroMouseTemplate_DW.mindl = 3.0;
    MicroMouseTemplate_DW.mindr = 3.0;
    MicroMouseTemplate_DW.minwl = 3.0;
    MicroMouseTemplate_DW.minwfr = 3.0;
    MicroMouseTemplate_DW.minwfl = 3.0;
    MicroMouseTemplate_DW.minwr = 3.0;
    MicroMouseTemplate_DW.minwer = 3.0;
    MicroMouseTemplate_DW.minwel = 3.0;
    MicroMouseTemplate_DW.ADCOFF.size[1] = 0;

    /* Start for MATLABSystem: '<S51>/Analog to Digital Converter' */
    MicroMouseTemplate_DW.obj.isInitialized = 0;
    MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted = false;
    MicroMouseTemp_SystemCore_setup(&MicroMouseTemplate_DW.obj);
    MicroMou_MATLABSystem3_Init(&MicroMouseTemplate_DW.MATLABSystem4,
      &MicroMouseTemplate_P.MATLABSystem4);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem1,
      &MicroMouseTemplate_P.MATLABSystem1);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem1_ci,
      &MicroMouseTemplate_P.MATLABSystem1_ci);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem3_c,
      &MicroMouseTemplate_P.MATLABSystem3_c);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem4_c,
      &MicroMouseTemplate_P.MATLABSystem4_c);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem5,
      &MicroMouseTemplate_P.MATLABSystem5);
    MicroMou_MATLABSystem3_Init(&MicroMouseTemplate_DW.MATLABSystem3,
      &MicroMouseTemplate_P.MATLABSystem3);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem2,
      &MicroMouseTemplate_P.MATLABSystem2);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem1_c,
      &MicroMouseTemplate_P.MATLABSystem1_c);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem2_c,
      &MicroMouseTemplate_P.MATLABSystem2_c);

    /* Start for MATLABSystem: '<S45>/PWM Output' */
    MicroMouseTemplate_DW.obj_n.matlabCodegenIsDeleted = false;
    MicroMouseTemplate_DW.obj_n.isSetupComplete = false;
    MicroMouseTemplate_DW.obj_n.isInitialized = 1;
    MicroMouseT_PWMOutput_setupImpl(&MicroMouseTemplate_DW.obj_n);
    MicroMouseTemplate_DW.obj_n.isSetupComplete = true;

    /* Start for MATLABSystem: '<S47>/PWM Output' */
    MicroMouseTemplate_DW.obj_g.matlabCodegenIsDeleted = false;
    MicroMouseTemplate_DW.obj_g.isSetupComplete = false;
    MicroMouseTemplate_DW.obj_g.isInitialized = 1;
    MicroMous_PWMOutput_setupImpl_d(&MicroMouseTemplate_DW.obj_g);
    MicroMouseTemplate_DW.obj_g.isSetupComplete = true;
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem2_ci,
      &MicroMouseTemplate_P.MATLABSystem2_ci);
    MicroMou_MATLABSystem1_Init(&MicroMouseTemplate_DW.MATLABSystem6,
      &MicroMouseTemplate_P.MATLABSystem6);
  }
}

/* Model terminate function */
void MicroMouseTemplate_terminate(void)
{
  /* Terminate for MATLABSystem: '<S51>/Analog to Digital Converter' */
  if (!MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted) {
    MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted = true;
    if ((MicroMouseTemplate_DW.obj.isInitialized == 1) &&
        MicroMouseTemplate_DW.obj.isSetupComplete) {
      ADC_Handle_Deinit(MicroMouseTemplate_DW.obj.ADCHandle,
                        ADC_DMA_INTERRUPT_MODE, 1);
    }
  }

  /* End of Terminate for MATLABSystem: '<S51>/Analog to Digital Converter' */

  /* Terminate for MATLABSystem: '<S45>/PWM Output' */
  if (!MicroMouseTemplate_DW.obj_n.matlabCodegenIsDeleted) {
    MicroMouseTemplate_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((MicroMouseTemplate_DW.obj_n.isInitialized == 1) &&
        MicroMouseTemplate_DW.obj_n.isSetupComplete) {
      disableCounter(MicroMouseTemplate_DW.obj_n.TimerHandle);
      disableTimerInterrupts(MicroMouseTemplate_DW.obj_n.TimerHandle, 0);
      disableTimerChannel3(MicroMouseTemplate_DW.obj_n.TimerHandle, ENABLE_CH);
      disableTimerChannel4(MicroMouseTemplate_DW.obj_n.TimerHandle, ENABLE_CH);
    }
  }

  /* End of Terminate for MATLABSystem: '<S45>/PWM Output' */

  /* Terminate for MATLABSystem: '<S47>/PWM Output' */
  if (!MicroMouseTemplate_DW.obj_g.matlabCodegenIsDeleted) {
    MicroMouseTemplate_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((MicroMouseTemplate_DW.obj_g.isInitialized == 1) &&
        MicroMouseTemplate_DW.obj_g.isSetupComplete) {
      disableCounter(MicroMouseTemplate_DW.obj_g.TimerHandle);
      disableTimerInterrupts(MicroMouseTemplate_DW.obj_g.TimerHandle, 0);
      disableTimerChannel1(MicroMouseTemplate_DW.obj_g.TimerHandle, ENABLE_CH);
      disableTimerChannel2(MicroMouseTemplate_DW.obj_g.TimerHandle, ENABLE_CH);
    }
  }

  /* End of Terminate for MATLABSystem: '<S47>/PWM Output' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
