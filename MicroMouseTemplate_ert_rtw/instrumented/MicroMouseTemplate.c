#include "MicroMouseTemplate.h"
#include "rtwtypes.h"
#include "MicroMouseTemplate_types.h"
#include "MicroMouseTemplate_private.h"
#include <string.h>
#include <math.h>
#include "stm_timer_ll.h"
#include "stm_adc_ll.h"
#define MicroMouseTempla_IN_Calibration ((uint8_T)4U)
#define MicroMouseTemplate_IN_Back     ((uint8_T)1U)
#define MicroMouseTemplate_IN_Back1    ((uint8_T)2U)
#define MicroMouseTemplate_IN_Back2    ((uint8_T)3U)
#define MicroMouseTemplate_IN_Center1  ((uint8_T)5U)
#define MicroMouseTemplate_IN_Crossing ((uint8_T)6U)
#define MicroMouseTemplate_IN_Delay    ((uint8_T)7U)
#define MicroMouseTemplate_IN_Drive2   ((uint8_T)8U)
#define MicroMouseTemplate_IN_Drive3   ((uint8_T)9U)
#define MicroMouseTemplate_IN_Drive4   ((uint8_T)10U)
#define MicroMouseTemplate_IN_Flip     ((uint8_T)11U)
#define MicroMouseTemplate_IN_Idle     ((uint8_T)12U)
#define MicroMouseTemplate_IN_Init1    ((uint8_T)13U)
#define MicroMouseTemplate_IN_OK       ((uint8_T)14U)
#define MicroMouseTemplate_IN_Revert   ((uint8_T)15U)
#define MicroMouseTemplate_IN_TurnLeft ((uint8_T)16U)
#define MicroMouseTemplate_IN_TurnRight ((uint8_T)17U)
#define MicroMouseTemplate_IN_Wait     ((uint8_T)18U)
#define MicroMouseTemplate_IN_htot     ((uint8_T)19U)
#define MicroMouseTemplate_IN_save     ((uint8_T)20U)

extern I2C_HandleTypeDef hi2c2;
real32_T IMU_Accel[3];
real32_T IMU_Gyro[3];
int32_T currTicksRS;
int32_T currTicksLS;
uint16_T ADC1s[9];
uint16_T ADC_H[9];
uint16_T ADC_L[9];
uint16_T Thresholds[8];
boolean_T Detections[8];
B_MicroMouseTemplate_T MicroMouseTemplate_B;
DW_MicroMouseTemplate_T MicroMouseTemplate_DW;
static RT_MODEL_MicroMouseTemplate_T MicroMouseTemplate_M_;
RT_MODEL_MicroMouseTemplate_T *const MicroMouseTemplate_M =
  &MicroMouseTemplate_M_;
static void MicroMouseTemplate_CenterAngle(real_T Angle, real_T Setpoint, real_T
  *Left, real_T *Right);
static void MicroMouseTemplate_Crossing(const real_T *angle);
static void MicroMouseTemplat_delConnection(int16_T x1, int16_T b_y1, int16_T x2,
  int16_T y2);
static void MicroMouseTemplate_route(int16_T path[400]);
static real_T MicroMouseTemplate_thingy(const real_T Sensors[8]);
static void MicroMouseTemplate_FollowLine1(const real_T b_Sensors[8], real_T
  *DesA, real_T *errorR);
static void MicroMouseTemplate_CenterAngle1(real_T Angle, real_T Setpoint,
  real_T *Left, real_T *Right);
static void MicroMouseTemplate_Drive4(const real_T Sensors[8], const boolean_T
  *NOT1, const real_T *cross, const real_T *angle);
static void MicroMouseTemplate_Init(void);
static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj);
static void MicroMouseT_PWMOutput_setupImpl(stm32cube_blocks_PWMOutput_Mi_T *obj);
static void MicroMous_PWMOutput_setupImpl_d(stm32cube_blocks_PWMOutput_Mi_T *obj);
static void rate_monotonic_scheduler(void);
void MicroMouseTemplate_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  eventFlags[1] = ((boolean_T)rtmStepTask(MicroMouseTemplate_M, 1));
}

static void rate_monotonic_scheduler(void)
{
  MicroMouseTemplate_M->Timing.RateInteraction.TID0_1 =
    (MicroMouseTemplate_M->Timing.TaskCounters.TID[1] == 0);
  (MicroMouseTemplate_M->Timing.TaskCounters.TID[1])++;
  if ((MicroMouseTemplate_M->Timing.TaskCounters.TID[1]) > 19) {
    MicroMouseTemplate_M->Timing.TaskCounters.TID[1] = 0;
  }
}

void MicroMou_MATLABSystem1_Init(DW_MATLABSystem1_MicroMouseTe_T *localDW,
  P_MATLABSystem1_MicroMouseTem_T *localP)
{
  int32_T i;
  localDW->objisempty = true;
  localDW->obj.InitialCondition = localP->MATLABSystem1_InitialCondition;
  localDW->obj.isInitialized = 1;
  for (i = 0; i < 25; i++) {
    localDW->obj.Buffer[i] = localDW->obj.InitialCondition;
  }
}

void MicroMouseTem_MATLABSystem1(real_T rtu_0, B_MATLABSystem1_MicroMouseTem_T
  *localB, DW_MATLABSystem1_MicroMouseTe_T *localDW,
  P_MATLABSystem1_MicroMouseTem_T *localP)
{
  if (localDW->obj.InitialCondition != localP->MATLABSystem1_InitialCondition) {
    localDW->obj.InitialCondition = localP->MATLABSystem1_InitialCondition;
  }

  memcpy(&localB->MATLABSystem1[0], &localDW->obj.Buffer[0], 25U * sizeof(real_T));
  localB->rtu_0[0] = rtu_0;
  memcpy(&localB->rtu_0[1], &localDW->obj.Buffer[0], 24U * sizeof(real_T));
  memcpy(&localDW->obj.Buffer[0], &localB->rtu_0[0], 25U * sizeof(real_T));
}

void MicroMou_MATLABSystem3_Init(DW_MATLABSystem3_MicroMouseTe_T *localDW,
  P_MATLABSystem3_MicroMouseTem_T *localP)
{
  int32_T i;
  localDW->objisempty = true;
  localDW->obj.InitialCondition = localP->MATLABSystem3_InitialCondition;
  localDW->obj.isInitialized = 1;
  for (i = 0; i < 10; i++) {
    localDW->obj.Buffer[i] = localDW->obj.InitialCondition;
  }
}

void MicroMouseTem_MATLABSystem3(real_T rtu_0, B_MATLABSystem3_MicroMouseTem_T
  *localB, DW_MATLABSystem3_MicroMouseTe_T *localDW,
  P_MATLABSystem3_MicroMouseTem_T *localP)
{
  if (localDW->obj.InitialCondition != localP->MATLABSystem3_InitialCondition) {
    localDW->obj.InitialCondition = localP->MATLABSystem3_InitialCondition;
  }

  memcpy(&localB->MATLABSystem3[0], &localDW->obj.Buffer[0], 10U * sizeof(real_T));
  localB->rtu_0[0] = rtu_0;
  memcpy(&localB->rtu_0[1], &localDW->obj.Buffer[0], 9U * sizeof(real_T));
  memcpy(&localDW->obj.Buffer[0], &localB->rtu_0[0], 10U * sizeof(real_T));
}

static void MicroMouseTemplate_CenterAngle(real_T Angle, real_T Setpoint, real_T
  *Left, real_T *Right)
{
  real_T error;
  error = Setpoint - Angle;
  MicroMouseTemplate_DW.sumError_h += error;
  MicroMouseTemplate_DW.sumError_h -= 0.005 * MicroMouseTemplate_DW.sumError_h;
  *Right = (error - MicroMouseTemplate_DW.preError_j) * 60.0 + 6.0 * error;
  MicroMouseTemplate_DW.preError_j = error;
  if (0.0 - *Right >= -100.0) {
    *Left = 0.0 - *Right;
  } else {
    *Left = -100.0;
  }

  if (*Left > 100.0) {
    *Left = 100.0;
  }

  if (*Right < -100.0) {
    *Right = -100.0;
  }

  if (*Right > 100.0) {
    *Right = 100.0;
  }
}

static void MicroMouseTemplate_Crossing(const real_T *angle)
{
  if ((MicroMouseTemplate_DW.Turn == 2.0) && (MicroMouseTemplate_DW.Next == 1.0))
  {
    MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Back2;
    MicroMouseTemplate_B.Left = -50.0;
    MicroMouseTemplate_B.Right = -50.0;
  } else if ((MicroMouseTemplate_DW.Turn == -1.0) && (MicroMouseTemplate_DW.Next
              == 1.0)) {
    MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Back1;
    MicroMouseTemplate_B.Left = -50.0;
    MicroMouseTemplate_B.Right = -50.0;
  } else if ((MicroMouseTemplate_DW.Turn == 1.0) && (MicroMouseTemplate_DW.Next ==
              1.0)) {
    MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Back;
    MicroMouseTemplate_B.Left = -50.0;
    MicroMouseTemplate_B.Right = -50.0;
  } else if ((MicroMouseTemplate_DW.Turn == 0.0) && (MicroMouseTemplate_DW.Next ==
              1.0)) {
    MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Drive4;
    MicroMouseTemplate_DW.DesA = 0.0;
    MicroMouseTemplate_DW.anglec = *angle;
  }
}

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

real_T rt_roundd(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void MicroMouseTemplate_route(int16_T path[400])
{
  int32_T b;
  int32_T exitg1;
  int32_T i;
  int32_T i_0;
  int16_T tmp_data[2];
  int16_T b_y1;
  int16_T connection;
  int16_T connection_0;
  int16_T connection_1;
  int16_T qend;
  int16_T x1;
  for (i = 0; i < 49; i++) {
    MicroMouseTemplate_B.dist[i] = MAX_int16_T;
  }

  memset(&MicroMouseTemplate_B.pre[0], 0, 98U * sizeof(int16_T));
  MicroMouseTemplate_DW.q_sizes[0] = 200;
  MicroMouseTemplate_DW.q_sizes[1] = 2;
  memset(&MicroMouseTemplate_B.q_data[0], 0, 400U * sizeof(int16_T));
  memset(&path[0], 0, 400U * sizeof(int16_T));
  MicroMouseTemplate_DW.pathend = 0;
  MicroMouseTemplate_B.dist[(MicroMouseTemplate_DW.pos[0] + 7 *
    (MicroMouseTemplate_DW.pos[1] - 1)) - 1] = 0;
  MicroMouseTemplate_B.q_data[0] = MicroMouseTemplate_DW.pos[0];
  MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]] =
    MicroMouseTemplate_DW.pos[1];
  qend = 1;
  while (qend > 0) {
    x1 = MicroMouseTemplate_B.q_data[0];
    b_y1 = MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]];
    for (i_0 = 0; i_0 < 168; i_0++) {
      MicroMouseTemplate_B.fine = 0.5;
      connection_1 = MicroMouseTemplate_DW.connection[i_0];
      if (connection_1 == MicroMouseTemplate_DW.pos[0]) {
        connection_0 = MicroMouseTemplate_DW.connection[i_0 + 168];
        if (connection_0 == MicroMouseTemplate_DW.pos[1]) {
          connection = MicroMouseTemplate_DW.connection[i_0 + 336];
          if (connection_1 > connection) {
            if (MicroMouseTemplate_DW.direction[3] == 1) {
              MicroMouseTemplate_B.fine = 0.0;
            }
          } else if ((connection_1 < connection) &&
                     (MicroMouseTemplate_DW.direction[1] == 1)) {
            MicroMouseTemplate_B.fine = 0.0;
          }

          connection = MicroMouseTemplate_DW.connection[i_0 + 504];
          if (connection_0 > connection) {
            if (MicroMouseTemplate_DW.direction[2] == 1) {
              MicroMouseTemplate_B.fine = 0.0;
            }
          } else if ((connection_0 < connection) &&
                     (MicroMouseTemplate_DW.direction[0] == 1)) {
            MicroMouseTemplate_B.fine = 0.0;
          }
        } else {
          MicroMouseTemplate_B.fine = 0.0;
        }
      } else {
        MicroMouseTemplate_B.fine = 0.0;
      }

      if ((connection_1 == x1) && (MicroMouseTemplate_DW.connection[i_0 + 168] ==
           b_y1)) {
        i = MicroMouseTemplate_B.dist[((b_y1 - 1) * 7 + x1) - 1] + 1;
        b = i;
        if (i > 32767) {
          b = 32767;
        }

        b = (int32_T)rt_roundd((real_T)b + MicroMouseTemplate_B.fine);
        if (b < 32768) {
          connection = (int16_T)b;
        } else {
          connection = MAX_int16_T;
        }

        connection_1 = MicroMouseTemplate_DW.connection[i_0 + 336];
        connection_0 = MicroMouseTemplate_DW.connection[i_0 + 504];
        b = (connection_0 - 1) * 7 + connection_1;
        if (MicroMouseTemplate_B.dist[b - 1] > connection) {
          if (i > 32767) {
            i = 32767;
          }

          i = (int32_T)rt_roundd((real_T)i + MicroMouseTemplate_B.fine);
          if (i < 32768) {
            MicroMouseTemplate_B.dist[b - 1] = (int16_T)i;
          } else {
            MicroMouseTemplate_B.dist[b - 1] = MAX_int16_T;
          }

          MicroMouseTemplate_B.pre[b - 1] = x1;
          MicroMouseTemplate_B.pre[b + 48] = b_y1;
          i = qend + 1;
          if (qend + 1 > 32767) {
            i = 32767;
          }

          MicroMouseTemplate_B.q_data[i - 1] = connection_1;
          MicroMouseTemplate_B.q_data[(i + MicroMouseTemplate_DW.q_sizes[0]) - 1]
            = connection_0;
          i = qend + 1;
          if (qend + 1 > 32767) {
            i = 32767;
          }

          qend = (int16_T)i;
        }
      }
    }

    b = qend;
    for (i_0 = 0; i_0 <= b - 2; i_0++) {
      for (i = 0; i < 2; i++) {
        tmp_data[i] = MicroMouseTemplate_B.q_data
          [(MicroMouseTemplate_DW.q_sizes[0] * i + i_0) + 1];
      }

      for (i = 0; i < 2; i++) {
        MicroMouseTemplate_B.q_data[i_0 + MicroMouseTemplate_DW.q_sizes[0] * i] =
          tmp_data[i];
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
      i = MicroMouseTemplate_DW.pathend + 1;
      if (MicroMouseTemplate_DW.pathend + 1 > 32767) {
        i = 32767;
      }

      path[i - 1] = qend;
      path[i + 199] = MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes
        [0]];
      i = MicroMouseTemplate_DW.pathend + 1;
      if (MicroMouseTemplate_DW.pathend + 1 > 32767) {
        i = 32767;
      }

      MicroMouseTemplate_DW.pathend = (int16_T)i;
      i = MicroMouseTemplate_B.q_data[0];
      qend = MicroMouseTemplate_B.q_data[MicroMouseTemplate_DW.q_sizes[0]];
      for (i_0 = 0; i_0 < 2; i_0++) {
        MicroMouseTemplate_B.q_data[1 + MicroMouseTemplate_DW.q_sizes[0] * i_0] =
          MicroMouseTemplate_B.pre[(((qend - 1) * 7 + i) + 49 * i_0) - 1];
      }

      for (i_0 = 0; i_0 < 199; i_0++) {
        for (i = 0; i < 2; i++) {
          tmp_data[i] = MicroMouseTemplate_B.q_data
            [(MicroMouseTemplate_DW.q_sizes[0] * i + i_0) + 1];
        }

        for (i = 0; i < 2; i++) {
          MicroMouseTemplate_B.q_data[i_0 + MicroMouseTemplate_DW.q_sizes[0] * i]
            = tmp_data[i];
        }
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

static real_T MicroMouseTemplate_thingy(const real_T Sensors[8])
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
  } else if (Sensors[6] == 1.0) {
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

  MicroMouseTemplate_route(MicroMouseTemplate_B.path);
  Turn = 0.0;
  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

  tmp = MicroMouseTemplate_DW.pathend - 1;
  if (MicroMouseTemplate_DW.pathend - 1 < -32768) {
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

static void MicroMouseTemplate_FollowLine1(const real_T b_Sensors[8], real_T
  *DesA, real_T *errorR)
{
  if ((b_Sensors[2] == 1.0) && (b_Sensors[5] == 0.0)) {
    MicroMouseTemplate_DW.error = -0.5;
  } else if ((b_Sensors[2] == 0.0) && (b_Sensors[5] == 1.0)) {
    MicroMouseTemplate_DW.error = 0.5;
  } else if ((b_Sensors[2] == 0.0) && (b_Sensors[5] == 0.0)) {
    MicroMouseTemplate_DW.error = 0.0;
  } else if ((b_Sensors[0] == 0.0) && (b_Sensors[2] == 1.0)) {
    MicroMouseTemplate_DW.error = 2.0;
  } else if ((b_Sensors[7] == 0.0) && (b_Sensors[5] == 1.0)) {
    MicroMouseTemplate_DW.error = -2.0;
  }

  MicroMouseTemplate_DW.sumError += MicroMouseTemplate_DW.error;
  MicroMouseTemplate_DW.sumError -= 0.005 * MicroMouseTemplate_DW.sumError;
  *errorR = MicroMouseTemplate_DW.error;
  MicroMouseTemplate_DW.Dave = (MicroMouseTemplate_DW.error -
    MicroMouseTemplate_DW.preError) + 0.9 * MicroMouseTemplate_DW.Dave;
  *DesA = 10.0 * MicroMouseTemplate_DW.error + 6.0 * MicroMouseTemplate_DW.Dave;
  MicroMouseTemplate_DW.preError = MicroMouseTemplate_DW.error;
}

static void MicroMouseTemplate_CenterAngle1(real_T Angle, real_T Setpoint,
  real_T *Left, real_T *Right)
{
  real_T PID;
  real_T error;
  error = Setpoint - Angle;
  MicroMouseTemplate_DW.sumError_e += error;
  MicroMouseTemplate_DW.sumError_e -= 0.005 * MicroMouseTemplate_DW.sumError_e;
  PID = (error - MicroMouseTemplate_DW.preError_k) * 60.0 + 6.0 * error;
  MicroMouseTemplate_DW.preError_k = error;
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
}

static void MicroMouseTemplate_Drive4(const real_T Sensors[8], const boolean_T
  *NOT1, const real_T *cross, const real_T *angle)
{
  int32_T i;
  int16_T temp;
  boolean_T tmp;
  tmp = ((*cross == 1.0) && (MicroMouseTemplate_DW.temporalCounter_i1 >= 80U));
  if (tmp && ((MicroMouseTemplate_DW.pos[0] == MicroMouseTemplate_DW.dest[0]) &&
              (MicroMouseTemplate_DW.pos[1] == MicroMouseTemplate_DW.dest[1])))
  {
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_OK;
    temp = MicroMouseTemplate_DW.start[0];
    MicroMouseTemplate_DW.start[0] = MicroMouseTemplate_DW.dest[0];
    MicroMouseTemplate_DW.dest[0] = temp;
    temp = MicroMouseTemplate_DW.start[1];
    MicroMouseTemplate_DW.start[1] = MicroMouseTemplate_DW.dest[1];
    MicroMouseTemplate_DW.dest[1] = temp;
    MicroMouseTemplate_B.Left = 0.0;
    MicroMouseTemplate_B.Right = 0.0;
  } else if (*NOT1) {
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Revert;
    memcpy(&MicroMouseTemplate_DW.connection[0],
           &MicroMouseTemplate_DW.connectionsave[0], 672U * sizeof(int16_T));
    MicroMouseTemplate_DW.start[0] = MicroMouseTemplate_DW.beginpos[0];
    MicroMouseTemplate_DW.pos[0] = MicroMouseTemplate_DW.beginpos[0];
    MicroMouseTemplate_DW.dest[0] = MicroMouseTemplate_DW.endpos[0];
    MicroMouseTemplate_DW.start[1] = MicroMouseTemplate_DW.beginpos[1];
    MicroMouseTemplate_DW.pos[1] = MicroMouseTemplate_DW.beginpos[1];
    MicroMouseTemplate_DW.dest[1] = MicroMouseTemplate_DW.endpos[1];
    MicroMouseTemplate_DW.direction[0] = 1;
    MicroMouseTemplate_DW.direction[1] = 0;
    MicroMouseTemplate_DW.direction[2] = 0;
    MicroMouseTemplate_DW.direction[3] = 0;
  } else if (tmp) {
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Crossing;
    MicroMouseTemplate_DW.Turn = MicroMouseTemplate_thingy(Sensors);
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
    MicroMouseTemplate_DW.Next = 1.0;
  } else {
    MicroMouseTemplate_FollowLine1(Sensors, &MicroMouseTemplate_B.TurnA,
      &MicroMouseTemplate_B.errorR_k);
    MicroMouseTemplate_DW.anglec += MicroMouseTemplate_B.errorR_k * 0.05;
    MicroMouseTemplate_CenterAngle1(*angle, (MicroMouseTemplate_DW.DesA +
      MicroMouseTemplate_B.TurnA) + MicroMouseTemplate_DW.anglec,
      &MicroMouseTemplate_B.Left, &MicroMouseTemplate_B.Right);
  }
}

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

static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj)
{
  ADC_Type_T adcStructLoc;
  obj->isSetupComplete = false;
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
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  enableTimerChannel3(obj->TimerHandle, ENABLE_CH);
  enableTimerChannel4(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    enableCounter(obj->TimerHandle, false);
  }
}

static void MicroMous_PWMOutput_setupImpl_d(stm32cube_blocks_PWMOutput_Mi_T *obj)
{
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  enableTimerChannel1(obj->TimerHandle, ENABLE_CH);
  enableTimerChannel2(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    enableCounter(obj->TimerHandle, false);
  }
}

void MicroMouseTemplate_step0(void)
{
  int32_T i;
  int32_T k;
  uint16_T rtb_TmpRTBAtMaxofElements7Outpo;
  uint16_T rtb_TmpRTBAtMaxofElementsOutpor;
  int8_T a__1[3];
  boolean_T NOT;
  boolean_T NOT1;
  static const int8_T b_a[7] = { 1, 0, 0, 0, 0, 0, 0 };

  {
    rate_monotonic_scheduler();
  }

  regularReadADCDMA(MicroMouseTemplate_DW.obj.ADCHandle, ADC_TRIGGER_AND_READ,
                    &ADC1s[0]);
  rtb_TmpRTBAtMaxofElementsOutpor =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B;
  MicroMouseTemplate_B.Flip[0] = ADC1s[7];
  MicroMouseTemplate_B.Flip[7] = ADC1s[0];
  MicroMouseTemplate_B.Flip[1] = ADC1s[6];
  MicroMouseTemplate_B.Flip[6] = ADC1s[1];
  MicroMouseTemplate_B.Flip[2] = ADC1s[5];
  MicroMouseTemplate_B.Flip[5] = ADC1s[2];
  MicroMouseTemplate_B.Flip[3] = ADC1s[4];
  MicroMouseTemplate_B.Flip[4] = ADC1s[3];
  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_B.CastToDouble[i] = MicroMouseTemplate_B.Flip[i];
  }

  MicroMouseTem_MATLABSystem3(MicroMouseTemplate_B.CastToDouble[1],
    &MicroMouseTemplate_B.MATLABSystem4, &MicroMouseTemplate_DW.MATLABSystem4,
    &MicroMouseTemplate_P.MATLABSystem4);
  MicroMouseTemplate_B.Lb = MicroMouseTemplate_B.MATLABSystem4.MATLABSystem3[0];
  for (k = 0; k < 9; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem4.MATLABSystem3[k + 1];
    if (MicroMouseTemplate_B.Lb < MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.Lb = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.Lb,
    &MicroMouseTemplate_B.MATLABSystem1, &MicroMouseTemplate_DW.MATLABSystem1,
    &MicroMouseTemplate_P.MATLABSystem1);
  MicroMouseTemplate_B.errorR =
    MicroMouseTemplate_B.MATLABSystem1.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem1.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.errorR > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.errorR = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[2],
    &MicroMouseTemplate_B.MATLABSystem1_ci,
    &MicroMouseTemplate_DW.MATLABSystem1_ci,
    &MicroMouseTemplate_P.MATLABSystem1_ci);
  MicroMouseTemplate_B.Lb = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1
    [0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.Lb < MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.Lb = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[3],
    &MicroMouseTemplate_B.MATLABSystem3_c,
    &MicroMouseTemplate_DW.MATLABSystem3_c,
    &MicroMouseTemplate_P.MATLABSystem3_c);
  MicroMouseTemplate_B.maxV =
    MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.maxV < MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.maxV = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[4],
    &MicroMouseTemplate_B.MATLABSystem4_c,
    &MicroMouseTemplate_DW.MATLABSystem4_c,
    &MicroMouseTemplate_P.MATLABSystem4_c);
  MicroMouseTemplate_B.maxV_m =
    MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.maxV_m < MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.maxV_m = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[5],
    &MicroMouseTemplate_B.MATLABSystem5, &MicroMouseTemplate_DW.MATLABSystem5,
    &MicroMouseTemplate_P.MATLABSystem5);
  MicroMouseTemplate_B.maxV_c =
    MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.maxV_c < MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.maxV_c = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem3(MicroMouseTemplate_B.CastToDouble[6],
    &MicroMouseTemplate_B.MATLABSystem3, &MicroMouseTemplate_DW.MATLABSystem3,
    &MicroMouseTemplate_P.MATLABSystem3);
  MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.MATLABSystem3.MATLABSystem3[0];
  for (k = 0; k < 9; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem3.MATLABSystem3[k + 1];
    if (MicroMouseTemplate_B.Lf < MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.Lf,
    &MicroMouseTemplate_B.MATLABSystem2, &MicroMouseTemplate_DW.MATLABSystem2,
    &MicroMouseTemplate_P.MATLABSystem2);
  MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.MATLABSystem2.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem2.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.Lf > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.cross;
    }
  }

  rtb_TmpRTBAtMaxofElements7Outpo =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_;
  ADC_H[0] = rtb_TmpRTBAtMaxofElementsOutpor;
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.errorR), 65536.0);
  ADC_H[1] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.Lb), 65536.0);
  ADC_H[2] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.maxV), 65536.0);
  ADC_H[3] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.maxV_m), 65536.0);
  ADC_H[4] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.maxV_c), 65536.0);
  ADC_H[5] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.Lf), 65536.0);
  ADC_H[6] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  ADC_H[7] = rtb_TmpRTBAtMaxofElements7Outpo;
  ADC_H[8] = MicroMouseTemplate_P.Constant_Value_b;
  rtb_TmpRTBAtMaxofElementsOutpor =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_;
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[1],
    &MicroMouseTemplate_B.MATLABSystem1_c,
    &MicroMouseTemplate_DW.MATLABSystem1_c,
    &MicroMouseTemplate_P.MATLABSystem1_c);
  MicroMouseTemplate_B.errorR =
    MicroMouseTemplate_B.MATLABSystem1_c.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem1_c.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.errorR > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.errorR = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1
    [0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.Lf > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTemplate_B.Lb = MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.Lb > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.Lb = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTemplate_B.maxV =
    MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.maxV > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.maxV = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTemplate_B.maxV_m =
    MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.maxV_m > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.maxV_m = MicroMouseTemplate_B.cross;
    }
  }

  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_B.CastToDouble[6],
    &MicroMouseTemplate_B.MATLABSystem2_c,
    &MicroMouseTemplate_DW.MATLABSystem2_c,
    &MicroMouseTemplate_P.MATLABSystem2_c);
  MicroMouseTemplate_B.maxV_c =
    MicroMouseTemplate_B.MATLABSystem2_c.MATLABSystem1[0];
  for (k = 0; k < 24; k++) {
    MicroMouseTemplate_B.cross =
      MicroMouseTemplate_B.MATLABSystem2_c.MATLABSystem1[k + 1];
    if (MicroMouseTemplate_B.maxV_c > MicroMouseTemplate_B.cross) {
      MicroMouseTemplate_B.maxV_c = MicroMouseTemplate_B.cross;
    }
  }

  rtb_TmpRTBAtMaxofElements7Outpo =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1;
  ADC_L[0] = rtb_TmpRTBAtMaxofElementsOutpor;
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.errorR), 65536.0);
  ADC_L[1] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.Lf), 65536.0);
  ADC_L[2] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.Lb), 65536.0);
  ADC_L[3] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.maxV), 65536.0);
  ADC_L[4] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.maxV_m), 65536.0);
  ADC_L[5] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  MicroMouseTemplate_B.cross = fmod(floor(MicroMouseTemplate_B.maxV_c), 65536.0);
  ADC_L[6] = (uint16_T)(MicroMouseTemplate_B.cross < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.cross :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.cross);
  ADC_L[7] = rtb_TmpRTBAtMaxofElements7Outpo;
  ADC_L[8] = MicroMouseTemplate_P.Constant1_Value;
  if (MicroMouseTemplate_M->Timing.RateInteraction.TID0_1) {
    MicroMouseTemplate_DW.RateTransition_Buffer =
      MicroMouseTemplate_B.CastToDouble[0];
    MicroMouseTemplate_DW.RateTransition1_Buffer =
      MicroMouseTemplate_B.CastToDouble[7];
  }

  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_B.CastToDouble_m[i] = (real_T)((uint32_T)
      MicroMouseTemplate_P.Gain1_Gain * MicroMouseTemplate_B.Flip[i]) *
      1.4901161193847656E-8;
    Detections[i] = false;
    Thresholds[i] = 0U;
  }

  currTicksRS = 0;
  currTicksLS = 0;
  MicroMouseTemplate_DW.c++;
  for (i = 0; i < 7; i++) {
    MicroMouseTemplate_B.a[i] = b_a[i];
  }

  if (MicroMouseTemplate_DW.c < 0.0) {
    i = -(int32_T)MicroMouseTemplate_DW.c;
    NOT1 = false;
  } else {
    i = (int32_T)MicroMouseTemplate_DW.c;
    NOT1 = true;
  }

  if (i > 7) {
    i -= i / 7 * 7;
  }

  if (i > 3) {
    i = 7 - i;
    NOT1 = !NOT1;
  }

  a__1[0] = 0;
  a__1[1] = 0;
  a__1[2] = 0;
  if (i > 0) {
    if (NOT1) {
      for (k = 7; k >= i + 1; k--) {
        MicroMouseTemplate_B.a[k - 1] = MicroMouseTemplate_B.a[(k - i) - 1];
      }

      memset(&MicroMouseTemplate_B.a[0], 0, (uint32_T)i * sizeof(int8_T));
    } else {
      memcpy(&a__1[0], &b_a[0], (uint32_T)i * sizeof(int8_T));
      memset(&MicroMouseTemplate_B.a[0], 0, (uint32_T)((6 - i) + 1) * sizeof
             (int8_T));
      for (k = 0; k < i; k++) {
        MicroMouseTemplate_B.a[(k - i) + 7] = a__1[k];
      }
    }
  }

  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[0] != 0) {
    i = 512;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 512U);
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[0] != 0) {
    i = 16384;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 16384U);
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[3] != 0) {
    i = 256;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 256U);
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[3] != 0) {
    i = 32768;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 32768U);
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[5] != 0) {
    i = 4096;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 4096U);
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_B.a[0] != 0) {
    i = 4096;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 4096U);
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[0] != 0) {
    i = 8192;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8192U);
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.a[5] != 0) {
    i = 2048;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 2048U);
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[0] = MicroMouseTemplate_B.a[0];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[1] = MicroMouseTemplate_B.a[3];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[2] = MicroMouseTemplate_B.a[0];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[3] = MicroMouseTemplate_B.a[5];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[4] = MicroMouseTemplate_B.a[5];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[5] = MicroMouseTemplate_B.a[0];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[6] = MicroMouseTemplate_B.a[3];
  MicroMouseTemplate_B.TmpSignalConversionAtSFunct[7] = MicroMouseTemplate_B.a[0];
  if (!MicroMouseTemplate_DW.prePAT_not_empty) {
    for (i = 0; i < 8; i++) {
      MicroMouseTemplate_DW.prePAT[i] =
        MicroMouseTemplate_B.TmpSignalConversionAtSFunct[i];
    }

    MicroMouseTemplate_DW.prePAT_not_empty = true;
  }

  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_B.CastToDouble[i] = MicroMouseTemplate_DW.preDif[i];
    MicroMouseTemplate_B.cross = MicroMouseTemplate_DW.prePAT[i];
    if (MicroMouseTemplate_B.cross == 1.0) {
      MicroMouseTemplate_DW.ADCON[i] = MicroMouseTemplate_B.CastToDouble_m[i];
    }

    if (MicroMouseTemplate_B.TmpSignalConversionAtSFunct[i] == 1) {
      MicroMouseTemplate_DW.ADCOFF[i] = MicroMouseTemplate_B.CastToDouble_m[i];
    }

    if (MicroMouseTemplate_B.cross == 1.0) {
      MicroMouseTemplate_B.CastToDouble[i] = MicroMouseTemplate_DW.ADCON[i] -
        MicroMouseTemplate_DW.ADCOFF[i];
    }
  }

  if (MicroMouseTemplate_DW.prePAT[1] == 1.0) {
    MicroMouseTemplate_B.CastToDouble[1] = 0.5 *
      MicroMouseTemplate_B.CastToDouble[1] + 0.5 * MicroMouseTemplate_DW.preDif
      [1];
  }

  if (MicroMouseTemplate_DW.prePAT[3] == 1.0) {
    MicroMouseTemplate_B.CastToDouble[3] = MicroMouseTemplate_B.CastToDouble[3] *
      0.5 + 0.5 * MicroMouseTemplate_DW.preDif[3];
  }

  if (MicroMouseTemplate_DW.prePAT[4] == 1.0) {
    MicroMouseTemplate_B.CastToDouble[4] = MicroMouseTemplate_B.CastToDouble[4] *
      0.5 + 0.5 * MicroMouseTemplate_DW.preDif[4];
  }

  if (MicroMouseTemplate_DW.prePAT[6] == 1.0) {
    MicroMouseTemplate_B.CastToDouble[6] = 0.5 *
      MicroMouseTemplate_B.CastToDouble[6] + 0.5 * MicroMouseTemplate_DW.preDif
      [6];
  }

  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_DW.preDif[i] = MicroMouseTemplate_B.CastToDouble[i];
    MicroMouseTemplate_DW.prePAT[i] =
      MicroMouseTemplate_B.TmpSignalConversionAtSFunct[i];
    MicroMouseTemplate_B.CastToDouble_m[i] = 0.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[2] > MicroMouseTemplate_DW.LineValL) {
    MicroMouseTemplate_B.CastToDouble_m[2] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[5] > MicroMouseTemplate_DW.LineValR) {
    MicroMouseTemplate_B.CastToDouble_m[5] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[1] > MicroMouseTemplate_DW.WalCalFr) {
    MicroMouseTemplate_B.CastToDouble_m[1] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[6] > MicroMouseTemplate_DW.WalCalFl) {
    MicroMouseTemplate_B.CastToDouble_m[6] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[4] > MicroMouseTemplate_DW.WalCalL) {
    MicroMouseTemplate_B.CastToDouble_m[4] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[3] > MicroMouseTemplate_DW.WalCalR) {
    MicroMouseTemplate_B.CastToDouble_m[3] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[7] > MicroMouseTemplate_DW.WelCalL) {
    MicroMouseTemplate_B.CastToDouble_m[7] = 1.0;
  }

  if (MicroMouseTemplate_B.CastToDouble[0] > MicroMouseTemplate_DW.WelCalR) {
    MicroMouseTemplate_B.CastToDouble_m[0] = 1.0;
  }

  MicroMouseTemplate_B.cross = (((MicroMouseTemplate_B.CastToDouble[0] +
    MicroMouseTemplate_B.CastToDouble[7]) + MicroMouseTemplate_B.CastToDouble[5])
    + MicroMouseTemplate_B.CastToDouble[2] < (((MicroMouseTemplate_DW.LineValR +
    MicroMouseTemplate_DW.LineValL) + MicroMouseTemplate_DW.WelCalR) +
    MicroMouseTemplate_DW.WelCalL) * 0.6);
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.CastToDouble_m[3] != 0.0) {
    i = 8192;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8192U);
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if ((MicroMouseTemplate_B.CastToDouble_m[1] != 0.0) ||
      (MicroMouseTemplate_B.CastToDouble_m[6] != 0.0)) {
    i = 16384;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 16384U);
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.CastToDouble_m[4] != 0.0) {
    i = 32768;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 32768U);
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_P.Constant_Value != 0.0) {
    i = 8;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8U);
  MicroMouseTemplate_DW.sum += IMU_Gyro[2] * 0.005;
  MicroMouseTemplate_B.pinReadLoc = LL_GPIO_ReadInputPort(GPIOB);
  NOT1 = ((MicroMouseTemplate_B.pinReadLoc & 4U) == 0U);
  MicroMouseTemplate_B.pinReadLoc = LL_GPIO_ReadInputPort(GPIOE);
  NOT = ((MicroMouseTemplate_B.pinReadLoc & 64U) == 0U);
  if (MicroMouseTemplate_DW.temporalCounter_i1 < 255U) {
    MicroMouseTemplate_DW.temporalCounter_i1++;
  }

  if (MicroMouseTemplate_DW.bitsForTID0.is_active_c2_MicroMouseTemplate == 0U) {
    MicroMouseTemplate_DW.bitsForTID0.is_active_c2_MicroMouseTemplate = 1U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      MicroMouseTemplate_IN_Init1;
    MicroMouseTemplate_Init();
    MicroMouseTemplate_DW.beginpos[0] = 1;
    MicroMouseTemplate_DW.endpos[0] = 4;
    MicroMouseTemplate_DW.start[0] = 1;
    MicroMouseTemplate_DW.pos[0] = 1;
    MicroMouseTemplate_DW.dest[0] = 4;
    MicroMouseTemplate_DW.beginpos[1] = 1;
    MicroMouseTemplate_DW.endpos[1] = 4;
    MicroMouseTemplate_DW.start[1] = 1;
    MicroMouseTemplate_DW.pos[1] = 1;
    MicroMouseTemplate_DW.dest[1] = 4;
    MicroMouseTemplate_DW.direction[0] = 1;
    MicroMouseTemplate_DW.direction[1] = 0;
    MicroMouseTemplate_DW.direction[2] = 0;
    MicroMouseTemplate_DW.direction[3] = 0;
    memcpy(&MicroMouseTemplate_DW.connectionsave[0],
           &MicroMouseTemplate_DW.connection[0], 672U * sizeof(int16_T));
  } else {
    switch (MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate) {
     case MicroMouseTemplate_IN_Back:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 6U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_TurnRight;
        MicroMouseTemplate_DW.DesA = MicroMouseTemplate_DW.sum - 90.0;
      }
      break;

     case MicroMouseTemplate_IN_Back1:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 6U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_TurnLeft;
        MicroMouseTemplate_DW.DesA = MicroMouseTemplate_DW.sum + 90.0;
      }
      break;

     case MicroMouseTemplate_IN_Back2:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 6U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Flip;
        MicroMouseTemplate_B.Left = -100.0;
        MicroMouseTemplate_B.Right = 100.0;
        MicroMouseTemplate_DW.DesA = MicroMouseTemplate_DW.sum + 180.0;
      }
      break;

     case MicroMouseTempla_IN_Calibration:
      if (MicroMouseTemplate_DW.sum - MicroMouseTemplate_DW.DesA < 0.0) {
        MicroMouseTemplate_B.Calibrate = 0.0;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Idle;
        MicroMouseTemplate_B.Left = 0.0;
        MicroMouseTemplate_B.Right = 0.0;
        MicroMouseTemplate_DW.pathend = 0;
      } else {
        MicroMouseTemplate_B.Calibrate = 1.0;
        MicroMouseTemplate_CenterAngle(MicroMouseTemplate_DW.sum,
          MicroMouseTemplate_DW.DesA, &MicroMouseTemplate_B.Left,
          &MicroMouseTemplate_B.Right);
      }
      break;

     case MicroMouseTemplate_IN_Center1:
      if ((MicroMouseTemplate_DW.Setpoint - MicroMouseTemplate_DW.sum < 0.0) ||
          (MicroMouseTemplate_DW.temporalCounter_i1 >= 100U)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive2;
        MicroMouseTemplate_B.Left = 100.0;
        MicroMouseTemplate_B.Right = 100.0;
      } else {
        MicroMouseTemplate_CenterAngle(MicroMouseTemplate_DW.sum,
          MicroMouseTemplate_DW.Setpoint, &MicroMouseTemplate_B.Left,
          &MicroMouseTemplate_B.Right);
      }
      break;

     case MicroMouseTemplate_IN_Crossing:
      MicroMouseTemplate_Crossing(&MicroMouseTemplate_DW.sum);
      break;

     case MicroMouseTemplate_IN_Delay:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 200U) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Crossing;
        MicroMouseTemplate_DW.Turn = MicroMouseTemplate_thingy
          (MicroMouseTemplate_B.CastToDouble_m);
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
        MicroMouseTemplate_DW.Next = 1.0;
      }
      break;

     case MicroMouseTemplate_IN_Drive2:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 100U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Center1;
        MicroMouseTemplate_DW.Setpoint += 90.0;
      }
      break;

     case MicroMouseTemplate_IN_Drive3:
      MicroMouseTemplate_FollowLine1(MicroMouseTemplate_B.CastToDouble_m,
        &MicroMouseTemplate_B.cross, &MicroMouseTemplate_B.errorR);
      MicroMouseTemplate_DW.anglec += MicroMouseTemplate_B.errorR * 0.05;
      MicroMouseTemplate_CenterAngle1(MicroMouseTemplate_DW.sum,
        (MicroMouseTemplate_DW.DesA + MicroMouseTemplate_B.cross) +
        MicroMouseTemplate_DW.anglec, &MicroMouseTemplate_B.Left,
        &MicroMouseTemplate_B.Right);
      break;

     case MicroMouseTemplate_IN_Drive4:
      MicroMouseTemplate_Drive4(MicroMouseTemplate_B.CastToDouble_m, &NOT1,
        &MicroMouseTemplate_B.cross, &MicroMouseTemplate_DW.sum);
      break;

     case MicroMouseTemplate_IN_Flip:
      if ((MicroMouseTemplate_DW.DesA - MicroMouseTemplate_DW.sum < 0.0) ||
          (MicroMouseTemplate_DW.temporalCounter_i1 >= 140U)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive4;
        MicroMouseTemplate_DW.DesA = 0.0;
        MicroMouseTemplate_DW.anglec = MicroMouseTemplate_DW.sum;
      } else {
        MicroMouseTemplate_CenterAngle(MicroMouseTemplate_DW.sum,
          MicroMouseTemplate_DW.DesA, &MicroMouseTemplate_B.Left,
          &MicroMouseTemplate_B.Right);
      }
      break;

     case MicroMouseTemplate_IN_Idle:
      if (NOT1) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Wait;
      } else if (NOT) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Delay;
      } else {
        MicroMouseTemplate_B.Calibrate = 0.0;
      }
      break;

     case MicroMouseTemplate_IN_Init1:
      MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
        MicroMouseTemplate_IN_Idle;
      MicroMouseTemplate_B.Left = 0.0;
      MicroMouseTemplate_B.Right = 0.0;
      MicroMouseTemplate_DW.pathend = 0;
      break;

     case MicroMouseTemplate_IN_OK:
      if (NOT) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_save;
        memcpy(&MicroMouseTemplate_DW.connectionsave[0],
               &MicroMouseTemplate_DW.connection[0], 672U * sizeof(int16_T));
      } else if (NOT1) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Revert;
        memcpy(&MicroMouseTemplate_DW.connection[0],
               &MicroMouseTemplate_DW.connectionsave[0], 672U * sizeof(int16_T));
        MicroMouseTemplate_DW.start[0] = MicroMouseTemplate_DW.beginpos[0];
        MicroMouseTemplate_DW.pos[0] = MicroMouseTemplate_DW.beginpos[0];
        MicroMouseTemplate_DW.dest[0] = MicroMouseTemplate_DW.endpos[0];
        MicroMouseTemplate_DW.start[1] = MicroMouseTemplate_DW.beginpos[1];
        MicroMouseTemplate_DW.pos[1] = MicroMouseTemplate_DW.beginpos[1];
        MicroMouseTemplate_DW.dest[1] = MicroMouseTemplate_DW.endpos[1];
        MicroMouseTemplate_DW.direction[0] = 1;
        MicroMouseTemplate_DW.direction[1] = 0;
        MicroMouseTemplate_DW.direction[2] = 0;
        MicroMouseTemplate_DW.direction[3] = 0;
      }
      break;

     case MicroMouseTemplate_IN_Revert:
      if (NOT) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Delay;
      }
      break;

     case MicroMouseTemplate_IN_TurnLeft:
      if ((MicroMouseTemplate_DW.DesA - MicroMouseTemplate_DW.sum < 0.0) ||
          (MicroMouseTemplate_DW.temporalCounter_i1 >= 80U)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive4;
        MicroMouseTemplate_DW.DesA = 0.0;
        MicroMouseTemplate_DW.anglec = MicroMouseTemplate_DW.sum;
      } else {
        MicroMouseTemplate_CenterAngle(MicroMouseTemplate_DW.sum,
          MicroMouseTemplate_DW.DesA, &MicroMouseTemplate_B.Left,
          &MicroMouseTemplate_B.Right);
      }
      break;

     case MicroMouseTemplate_IN_TurnRight:
      if ((MicroMouseTemplate_DW.DesA - MicroMouseTemplate_DW.sum > 0.0) ||
          (MicroMouseTemplate_DW.temporalCounter_i1 >= 80U)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive4;
        MicroMouseTemplate_DW.DesA = 0.0;
        MicroMouseTemplate_DW.anglec = MicroMouseTemplate_DW.sum;
      } else {
        MicroMouseTemplate_CenterAngle(MicroMouseTemplate_DW.sum,
          MicroMouseTemplate_DW.DesA, &MicroMouseTemplate_B.Left,
          &MicroMouseTemplate_B.Right);
      }
      break;

     case MicroMouseTemplate_IN_Wait:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 200U) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTempla_IN_Calibration;
        MicroMouseTemplate_DW.DesA = MicroMouseTemplate_DW.sum - 720.0;
      }
      break;

     case MicroMouseTemplate_IN_htot:
      MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
      MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
        MicroMouseTemplate_IN_Center1;
      MicroMouseTemplate_DW.Setpoint += 90.0;
      break;

     default:
      MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
      MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
        MicroMouseTemplate_IN_Delay;
      break;
    }
  }

  if (MicroMouseTemplate_B.Calibrate == 1.0) {
    if (MicroMouseTemplate_B.CastToDouble[2] > MicroMouseTemplate_DW.maxdl) {
      MicroMouseTemplate_DW.maxdl = MicroMouseTemplate_DW.maxdl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[2];
    }

    if (MicroMouseTemplate_B.CastToDouble[2] < MicroMouseTemplate_DW.mindl) {
      MicroMouseTemplate_DW.mindl = MicroMouseTemplate_DW.mindl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[2];
    }

    if (MicroMouseTemplate_B.CastToDouble[5] > MicroMouseTemplate_DW.maxdr) {
      MicroMouseTemplate_DW.maxdr = MicroMouseTemplate_DW.maxdr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[5];
    }

    if (MicroMouseTemplate_B.CastToDouble[5] < MicroMouseTemplate_DW.mindr) {
      MicroMouseTemplate_DW.mindr = MicroMouseTemplate_DW.mindr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[5];
    }

    if (MicroMouseTemplate_B.CastToDouble[3] > MicroMouseTemplate_DW.maxwr) {
      MicroMouseTemplate_DW.maxwr = MicroMouseTemplate_DW.maxwr * 0.95 + 0.05 *
        MicroMouseTemplate_B.CastToDouble[3];
    }

    if (MicroMouseTemplate_B.CastToDouble[3] < MicroMouseTemplate_DW.minwr) {
      MicroMouseTemplate_DW.minwr = MicroMouseTemplate_DW.minwr * 0.95 + 0.05 *
        MicroMouseTemplate_B.CastToDouble[3];
    }

    if (MicroMouseTemplate_B.CastToDouble[4] > MicroMouseTemplate_DW.maxwl) {
      MicroMouseTemplate_DW.maxwl = MicroMouseTemplate_DW.maxwl * 0.95 + 0.05 *
        MicroMouseTemplate_B.CastToDouble[4];
    }

    if (MicroMouseTemplate_B.CastToDouble[4] < MicroMouseTemplate_DW.minwl) {
      MicroMouseTemplate_DW.minwl = MicroMouseTemplate_DW.minwl * 0.95 + 0.05 *
        MicroMouseTemplate_B.CastToDouble[4];
    }

    if (MicroMouseTemplate_B.CastToDouble[1] > MicroMouseTemplate_DW.maxwfr) {
      MicroMouseTemplate_DW.maxwfr = MicroMouseTemplate_DW.maxwfr * 0.9 + 0.1 *
        MicroMouseTemplate_B.CastToDouble[1];
    }

    if (MicroMouseTemplate_B.CastToDouble[1] < MicroMouseTemplate_DW.minwfr) {
      MicroMouseTemplate_DW.minwfr = MicroMouseTemplate_DW.minwfr * 0.9 + 0.1 *
        MicroMouseTemplate_B.CastToDouble[1];
    }

    if (MicroMouseTemplate_B.CastToDouble[6] > MicroMouseTemplate_DW.maxwfl) {
      MicroMouseTemplate_DW.maxwfl = MicroMouseTemplate_DW.maxwfl * 0.9 + 0.1 *
        MicroMouseTemplate_B.CastToDouble[6];
    }

    if (MicroMouseTemplate_B.CastToDouble[6] < MicroMouseTemplate_DW.minwfl) {
      MicroMouseTemplate_DW.minwfl = MicroMouseTemplate_DW.minwfl * 0.9 + 0.1 *
        MicroMouseTemplate_B.CastToDouble[6];
    }

    if (MicroMouseTemplate_B.CastToDouble[0] > MicroMouseTemplate_DW.maxwer) {
      MicroMouseTemplate_DW.maxwer = MicroMouseTemplate_DW.maxwer * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[0];
    }

    if (MicroMouseTemplate_B.CastToDouble[0] < MicroMouseTemplate_DW.minwer) {
      MicroMouseTemplate_DW.minwer = MicroMouseTemplate_DW.minwer * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[0];
    }

    if (MicroMouseTemplate_B.CastToDouble[7] > MicroMouseTemplate_DW.maxwel) {
      MicroMouseTemplate_DW.maxwel = MicroMouseTemplate_DW.maxwel * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[7];
    }

    if (MicroMouseTemplate_B.CastToDouble[7] < MicroMouseTemplate_DW.minwel) {
      MicroMouseTemplate_DW.minwel = MicroMouseTemplate_DW.minwel * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble[7];
    }
  }

  MicroMouseTemplate_DW.LineValR = (MicroMouseTemplate_DW.maxdr -
    MicroMouseTemplate_DW.mindr) * 0.82 + MicroMouseTemplate_DW.mindr;
  MicroMouseTemplate_DW.LineValL = (MicroMouseTemplate_DW.maxdl -
    MicroMouseTemplate_DW.mindl) * 0.82 + MicroMouseTemplate_DW.mindl;
  MicroMouseTemplate_DW.WalCalL = (MicroMouseTemplate_DW.maxwl -
    MicroMouseTemplate_DW.minwl) * 0.37 + MicroMouseTemplate_DW.minwl;
  MicroMouseTemplate_DW.WalCalR = (MicroMouseTemplate_DW.maxwr -
    MicroMouseTemplate_DW.minwr) * 0.37 + MicroMouseTemplate_DW.minwr;
  MicroMouseTemplate_DW.WalCalFl = (MicroMouseTemplate_DW.maxwfl -
    MicroMouseTemplate_DW.minwfl) * 0.25 + MicroMouseTemplate_DW.minwfl;
  MicroMouseTemplate_DW.WalCalFr = (MicroMouseTemplate_DW.maxwfr -
    MicroMouseTemplate_DW.minwfr) * 0.25 + MicroMouseTemplate_DW.minwfr;
  MicroMouseTemplate_DW.WelCalL = (MicroMouseTemplate_DW.maxwel -
    MicroMouseTemplate_DW.minwel) * 0.82 + MicroMouseTemplate_DW.minwel;
  MicroMouseTemplate_DW.WelCalR = (MicroMouseTemplate_DW.maxwer -
    MicroMouseTemplate_DW.minwer) * 0.82 + MicroMouseTemplate_DW.minwer;
  MicroMouseTemplate_DW.Rmem_not_empty = true;
  MicroMouseTemplate_DW.Lmem_not_empty = true;
  if (MicroMouseTemplate_B.Left > 10.0) {
    MicroMouseTemplate_B.cross = MicroMouseTemplate_B.Left / 3.0 + 66.0;
    MicroMouseTemplate_B.errorR = 0.0;
  } else if (MicroMouseTemplate_B.Left < -10.0) {
    MicroMouseTemplate_B.cross = 0.0;
    MicroMouseTemplate_B.errorR = fabs(MicroMouseTemplate_B.Left / 3.0 - 66.0);
  } else {
    MicroMouseTemplate_B.cross = 0.0;
    MicroMouseTemplate_B.errorR = 0.0;
  }

  if (MicroMouseTemplate_B.Right > 10.0) {
    MicroMouseTemplate_B.Lf = MicroMouseTemplate_B.Right / 3.0 + 66.0;
    MicroMouseTemplate_B.Lb = 0.0;
  } else if (MicroMouseTemplate_B.Right < -10.0) {
    MicroMouseTemplate_B.Lf = 0.0;
    MicroMouseTemplate_B.Lb = fabs(MicroMouseTemplate_B.Right / 3.0 - 66.0);
  } else {
    MicroMouseTemplate_B.Lf = 0.0;
    MicroMouseTemplate_B.Lb = 0.0;
  }

  setDutyCycleInPercentageChannel3(MicroMouseTemplate_DW.obj_n.TimerHandle,
    MicroMouseTemplate_B.cross);
  setDutyCycleInPercentageChannel4(MicroMouseTemplate_DW.obj_n.TimerHandle,
    MicroMouseTemplate_B.errorR);
  setDutyCycleInPercentageChannel1(MicroMouseTemplate_DW.obj_g.TimerHandle,
    MicroMouseTemplate_B.Lf);
  setDutyCycleInPercentageChannel2(MicroMouseTemplate_DW.obj_g.TimerHandle,
    MicroMouseTemplate_B.Lb);
  MicroMouseTemplate_B.portNameLoc = GPIOD;
  if (MicroMouseTemplate_P.Constant_Value_l != 0.0) {
    i = 128;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 128U);
  refreshIMUValues();
  CustomWhile();
}

void MicroMouseTemplate_step1(void)
{
  real_T maxV;
  real_T u1;
  int32_T k;
  uint16_T rtb_MaxofElements;
  uint16_T rtb_MaxofElements7;
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_DW.RateTransition_Buffer,
    &MicroMouseTemplate_B.MATLABSystem2_ci,
    &MicroMouseTemplate_DW.MATLABSystem2_ci,
    &MicroMouseTemplate_P.MATLABSystem2_ci);
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
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_DW.RateTransition1_Buffer,
    &MicroMouseTemplate_B.MATLABSystem6, &MicroMouseTemplate_DW.MATLABSystem6,
    &MicroMouseTemplate_P.MATLABSystem6);
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
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_ = rtb_MaxofElements7;
  MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B = rtb_MaxofElements;
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
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1 = rtb_MaxofElements;
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_ = rtb_MaxofElements7;
  refreshIMUValues();
  CustomWhile();
}

void MicroMouseTemplate_initialize(void)
{
  {
    int32_T i;
    for (i = 0; i < 9; i++) {
      ADC1s[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_p;
      ADC_H[i] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_p;
      ADC_L[i] = MicroMouseTemplate_P.DataStoreMemory2_InitialValue_p;
    }

    for (i = 0; i < 8; i++) {
      Detections[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_p4;
      Thresholds[i] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_j;
    }

    currTicksRS = MicroMouseTemplate_P.DataStoreMemory2_InitialValue_b;
    currTicksLS = MicroMouseTemplate_P.DataStoreMemory4_InitialValue_a;
    IMU_Accel[0] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;
    IMU_Gyro[0] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;
    IMU_Accel[1] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;
    IMU_Gyro[1] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;
    IMU_Accel[2] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;
    IMU_Gyro[2] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;
    MicroMouseTemplate_DW.LineValL =
      MicroMouseTemplate_P.DataStoreMemory_InitialValue;
    MicroMouseTemplate_DW.LineValR =
      MicroMouseTemplate_P.DataStoreMemory1_InitialValue;
    MicroMouseTemplate_DW.WalCalL =
      MicroMouseTemplate_P.DataStoreMemory2_InitialValue;
    MicroMouseTemplate_DW.WalCalR =
      MicroMouseTemplate_P.DataStoreMemory3_InitialValue;
    MicroMouseTemplate_DW.WalCalFl =
      MicroMouseTemplate_P.DataStoreMemory4_InitialValue;
    MicroMouseTemplate_DW.WalCalFr =
      MicroMouseTemplate_P.DataStoreMemory5_InitialValue;
    MicroMouseTemplate_DW.WelCalR =
      MicroMouseTemplate_P.DataStoreMemory6_InitialValue;
    MicroMouseTemplate_DW.WelCalL =
      MicroMouseTemplate_P.DataStoreMemory7_InitialValue;
    initIMU();
    MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B =
      MicroMouseTemplate_P.TmpRTBAtMaxofElementsOutport1_I;
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_ =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements7Outport1_;
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_ =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements8Outport1_;
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1 =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements15Outport1;
    MicroMouseTemplate_DW.mindl = 3.0;
    MicroMouseTemplate_DW.mindr = 3.0;
    MicroMouseTemplate_DW.minwl = 3.0;
    MicroMouseTemplate_DW.minwfr = 3.0;
    MicroMouseTemplate_DW.minwfl = 3.0;
    MicroMouseTemplate_DW.minwr = 3.0;
    MicroMouseTemplate_DW.minwer = 3.0;
    MicroMouseTemplate_DW.minwel = 3.0;
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
    MicroMouseTemplate_DW.obj_n.matlabCodegenIsDeleted = false;
    MicroMouseTemplate_DW.obj_n.isSetupComplete = false;
    MicroMouseTemplate_DW.obj_n.isInitialized = 1;
    MicroMouseT_PWMOutput_setupImpl(&MicroMouseTemplate_DW.obj_n);
    MicroMouseTemplate_DW.obj_n.isSetupComplete = true;
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

void MicroMouseTemplate_terminate(void)
{
  if (!MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted) {
    MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted = true;
    if ((MicroMouseTemplate_DW.obj.isInitialized == 1) &&
        MicroMouseTemplate_DW.obj.isSetupComplete) {
      ADC_Handle_Deinit(MicroMouseTemplate_DW.obj.ADCHandle,
                        ADC_DMA_INTERRUPT_MODE, 1);
    }
  }

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
}
