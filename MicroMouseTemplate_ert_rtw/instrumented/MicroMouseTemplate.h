#ifndef MicroMouseTemplate_h_
#define MicroMouseTemplate_h_
#ifndef MicroMouseTemplate_COMMON_INCLUDES_
#define MicroMouseTemplate_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "main.h"
#endif

#include "MicroMouseTemplate_types.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#include "MicroMouseProgramming\Core\Inc\IMU.h"
#include "MicroMouseProgramming\Core\Inc\CustomWhile.h"
#include "MicroMouseProgramming\Core\Inc\Motors.h"

typedef struct {
  real_T MATLABSystem1[25];
  real_T rtu_0[25];
} B_MATLABSystem1_MicroMouseTem_T;

typedef struct {
  CircularBuffer_MicroMouseTemp_T obj;
  boolean_T objisempty;
} DW_MATLABSystem1_MicroMouseTe_T;

typedef struct {
  real_T MATLABSystem3[10];
  real_T rtu_0[10];
} B_MATLABSystem3_MicroMouseTem_T;

typedef struct {
  CircularBuffer_MicroMouseTe_p_T obj;
  boolean_T objisempty;
} DW_MATLABSystem3_MicroMouseTe_T;

typedef struct {
  int16_T path[400];
  int16_T q_data[400];
  int16_T pre[98];
  int16_T dist[49];
  real_T CastToDouble[8];
  real_T CastToDouble_m[8];
  uint16_T Flip[8];
  GPIO_TypeDef * portNameLoc;
  real_T Calibrate;
  real_T Drive;
  real_T Left;
  real_T Right;
  real_T maxV;
  real_T maxV_m;
  real_T Rf;
  real_T Rb;
  real_T Lf;
  real_T Lb;
  real_T cross;
  int8_T a[6];
  int32_T k;
  uint32_T pinReadLoc;
  uint32_T pinReadLoc_c;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem6;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem5;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem4_c;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem3_c;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem2_ci;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem1_ci;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem2_c;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem1_c;
  B_MATLABSystem3_MicroMouseTem_T MATLABSystem4;
  B_MATLABSystem3_MicroMouseTem_T MATLABSystem3;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem2;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem1;
} B_MicroMouseTemplate_T;

typedef struct {
  int16_T connection[672];
  emxArray_real_T_8x8_MicroMous_T ADCOFF;
  real_T prePAT[8];
  real_T preDif[8];
  real_T ADCON[8];
  stm32cube_blocks_AnalogInput__T obj;
  stm32cube_blocks_PWMOutput_Mi_T obj_g;
  stm32cube_blocks_PWMOutput_Mi_T obj_n;
  real_T RateTransition_Buffer;
  real_T RateTransition1_Buffer;
  real_T LineValL;
  real_T LineValR;
  real_T WalCalL;
  real_T WalCalR;
  real_T WalCalFl;
  real_T WalCalFr;
  real_T WelCalR;
  real_T WelCalL;
  real_T sum;
  real_T Turn;
  real_T desA;
  real_T DesA;
  real_T res;
  real_T preError;
  real_T sumError;
  real_T error;
  real_T Dave;
  real_T preError_e;
  real_T preSide;
  real_T sumError_i;
  real_T error_h;
  real_T Dave_m;
  real_T preError_j;
  real_T sumError_h;
  real_T Dave_a;
  real_T c;
  real_T preNoLED;
  real_T mindl;
  real_T maxdl;
  real_T mindr;
  real_T maxdr;
  real_T minwl;
  real_T maxwl;
  real_T minwfr;
  real_T maxwfr;
  real_T minwfl;
  real_T maxwfl;
  real_T minwr;
  real_T maxwr;
  real_T minwer;
  real_T maxwer;
  real_T minwel;
  real_T maxwel;
  int32_T q_sizes[2];
  int16_T direction[4];
  int16_T pos[2];
  int16_T dest[2];
  int16_T start[2];
  struct {
    uint_T is_c2_MicroMouseTemplate:5;
    uint_T is_Hehehehe:2;
    uint_T is_active_c2_MicroMouseTemplate:1;
  } bitsForTID0;

  int16_T pathend;
  volatile uint16_T TmpRTBAtMaxofElementsOutport1_B;
  volatile uint16_T TmpRTBAtMaxofElements7Outport1_;
  volatile uint16_T TmpRTBAtMaxofElements8Outport1_;
  volatile uint16_T TmpRTBAtMaxofElements15Outport1;
  uint16_T temporalCounter_i1;
  uint8_T temporalCounter_i2;
  boolean_T prePAT_not_empty;
  boolean_T preNoLED_not_empty;
  boolean_T ADCOFF_not_empty;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem6;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem5;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem4_c;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem3_c;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem2_ci;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem1_ci;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem2_c;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem1_c;
  DW_MATLABSystem3_MicroMouseTe_T MATLABSystem4;
  DW_MATLABSystem3_MicroMouseTe_T MATLABSystem3;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem2;
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem1;
} DW_MicroMouseTemplate_T;

struct P_MATLABSystem1_MicroMouseTem_T_ {
  real_T MATLABSystem1_InitialCondition;
};

struct P_MATLABSystem3_MicroMouseTem_T_ {
  real_T MATLABSystem3_InitialCondition;
};

struct P_MicroMouseTemplate_T_ {
  real_T Constant_Value;
  real_T Constant_Value_l;
  real_T Switch_Threshold;
  real_T Constant_Value_i;
  real_T DataStoreMemory_InitialValue;
  real_T DataStoreMemory1_InitialValue;
  real_T DataStoreMemory2_InitialValue;
  real_T DataStoreMemory3_InitialValue;
  real_T DataStoreMemory4_InitialValue;
  real_T DataStoreMemory5_InitialValue;
  real_T DataStoreMemory6_InitialValue;
  real_T DataStoreMemory7_InitialValue;
  int32_T DataStoreMemory2_InitialValue_b;
  int32_T DataStoreMemory4_InitialValue_a;
  real32_T DataStoreMemory_InitialValue_j;
  real32_T DataStoreMemory1_InitialValue_k;
  uint16_T Gain1_Gain;
  uint16_T TmpRTBAtMaxofElementsOutport1_I;
  uint16_T TmpRTBAtMaxofElements7Outport1_;
  uint16_T Constant_Value_b;
  uint16_T TmpRTBAtMaxofElements8Outport1_;
  uint16_T TmpRTBAtMaxofElements15Outport1;
  uint16_T Constant1_Value;
  uint16_T DataStoreMemory_InitialValue_p;
  uint16_T DataStoreMemory1_InitialValue_p;
  uint16_T DataStoreMemory2_InitialValue_p;
  uint16_T DataStoreMemory1_InitialValue_j;
  boolean_T DataStoreMemory_InitialValue_p4;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem6;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem5;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem4_c;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem3_c;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem2_ci;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem1_ci;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem2_c;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem1_c;
  P_MATLABSystem3_MicroMouseTem_T MATLABSystem4;
  P_MATLABSystem3_MicroMouseTem_T MATLABSystem3;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem2;
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem1;
};

struct tag_RTM_MicroMouseTemplate_T {
  const char_T * volatile errorStatus;
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;

    struct {
      boolean_T TID0_1;
    } RateInteraction;
  } Timing;
};

extern P_MicroMouseTemplate_T MicroMouseTemplate_P;
extern B_MicroMouseTemplate_T MicroMouseTemplate_B;
extern DW_MicroMouseTemplate_T MicroMouseTemplate_DW;
extern real32_T IMU_Accel[3];
extern real32_T IMU_Gyro[3];
extern int32_T currTicksRS;
extern int32_T currTicksLS;
extern uint16_T ADC1s[9];
extern uint16_T ADC_H[9];
extern uint16_T ADC_L[9];
extern uint16_T Thresholds[8];
extern boolean_T Detections[8];
extern void MicroMouseTemplate_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void MicroMouseTemplate_initialize(void);
extern void MicroMouseTemplate_step0(void);
extern void MicroMouseTemplate_step1(void);
extern void MicroMouseTemplate_terminate(void);
extern RT_MODEL_MicroMouseTemplate_T *const MicroMouseTemplate_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

#endif

