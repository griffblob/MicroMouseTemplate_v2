/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate.h
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

#ifndef MicroMouseTemplate_h_
#define MicroMouseTemplate_h_
#ifndef MicroMouseTemplate_COMMON_INCLUDES_
#define MicroMouseTemplate_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "main.h"
#endif                                 /* MicroMouseTemplate_COMMON_INCLUDES_ */

#include "MicroMouseTemplate_types.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
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

/* user code (top of header file) */
#include "MicroMouseProgramming\Core\Inc\IMU.h"
#include "MicroMouseProgramming\Core\Inc\CustomWhile.h"
#include "MicroMouseProgramming\Core\Inc\Motors.h"

/* Block signals for system '<S52>/MATLAB System1' */
typedef struct {
  real_T MATLABSystem1[25];            /* '<S52>/MATLAB System1' */
  real_T rtu_0[25];
} B_MATLABSystem1_MicroMouseTem_T;

/* Block states (default storage) for system '<S52>/MATLAB System1' */
typedef struct {
  CircularBuffer_MicroMouseTemp_T obj; /* '<S52>/MATLAB System1' */
  boolean_T objisempty;                /* '<S52>/MATLAB System1' */
} DW_MATLABSystem1_MicroMouseTe_T;

/* Block signals for system '<S52>/MATLAB System3' */
typedef struct {
  real_T MATLABSystem3[10];            /* '<S52>/MATLAB System3' */
  real_T rtu_0[10];
} B_MATLABSystem3_MicroMouseTem_T;

/* Block states (default storage) for system '<S52>/MATLAB System3' */
typedef struct {
  CircularBuffer_MicroMouseTe_p_T obj; /* '<S52>/MATLAB System3' */
  boolean_T objisempty;                /* '<S52>/MATLAB System3' */
} DW_MATLABSystem3_MicroMouseTe_T;

/* Block signals (default storage) */
typedef struct {
  int16_T path[400];
  int16_T q_data[400];
  int16_T pre[98];
  int16_T dist[49];
  real_T CastToDouble[8];              /* '<S54>/Cast To Double' */
  real_T CastToDouble_m[8];            /* '<S9>/Cast To Double' */
  uint16_T Flip[8];                    /* '<S9>/Flip' */
  GPIO_TypeDef * portNameLoc;
  real_T Calibrate;                    /* '<Root>/Lameo' */
  real_T Drive;                        /* '<Root>/Lameo' */
  real_T Left;                         /* '<Root>/Lameo' */
  real_T Right;                        /* '<Root>/Lameo' */
  real_T maxV;
  real_T maxV_m;
  real_T maxV_c;
  real_T Add1;                         /* '<Root>/Add1' */
  real_T Add;                          /* '<Root>/Add' */
  real_T Rf;                           /* '<S8>/Fowards Backwards' */
  real_T Lf;                           /* '<S8>/Fowards Backwards' */
  int8_T a[5];
  uint32_T pinReadLoc;
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem6;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem5;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem4_c;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem3_c;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem2_ci;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem1_ci;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem2_c;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem1_c;/* '<S52>/MATLAB System1' */
  B_MATLABSystem3_MicroMouseTem_T MATLABSystem4;/* '<S52>/MATLAB System3' */
  B_MATLABSystem3_MicroMouseTem_T MATLABSystem3;/* '<S52>/MATLAB System3' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem2;/* '<S52>/MATLAB System1' */
  B_MATLABSystem1_MicroMouseTem_T MATLABSystem1;/* '<S52>/MATLAB System1' */
} B_MicroMouseTemplate_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int16_T connection[672];             /* '<Root>/Lameo' */
  emxArray_real_T_8x8_MicroMous_T ADCOFF;/* '<Root>/Function Sense' */
  real_T prePAT[8];                    /* '<Root>/Function Sense' */
  real_T ADCON[8];                     /* '<Root>/Function Sense' */
  stm32cube_blocks_AnalogInput__T obj; /* '<S51>/Analog to Digital Converter' */
  stm32cube_blocks_PWMOutput_Mi_T obj_g;/* '<S47>/PWM Output' */
  stm32cube_blocks_PWMOutput_Mi_T obj_n;/* '<S45>/PWM Output' */
  real_T RateTransition_Buffer;        /* '<S54>/Rate Transition' */
  real_T RateTransition1_Buffer;       /* '<S54>/Rate Transition1' */
  real_T LineValL;                     /* '<Root>/Data Store Memory' */
  real_T LineValR;                     /* '<Root>/Data Store Memory1' */
  real_T WalCalL;                      /* '<Root>/Data Store Memory2' */
  real_T WalCalR;                      /* '<Root>/Data Store Memory3' */
  real_T WalCalFl;                     /* '<Root>/Data Store Memory4' */
  real_T WalCalFr;                     /* '<Root>/Data Store Memory5' */
  real_T WelCalR;                      /* '<Root>/Data Store Memory6' */
  real_T WelCalL;                      /* '<Root>/Data Store Memory7' */
  real_T Turn;                         /* '<Root>/Lameo' */
  real_T preError;                     /* '<Root>/Lameo' */
  real_T sumError;                     /* '<Root>/Lameo' */
  real_T error;                        /* '<Root>/Lameo' */
  real_T Dave;                         /* '<Root>/Lameo' */
  real_T c;                            /* '<S6>/MATLAB Function' */
  real_T sens1;                        /* '<Root>/Function Sensor Anal' */
  real_T sens8;                        /* '<Root>/Function Sensor Anal' */
  real_T preNoLED;                     /* '<Root>/Function Sense' */
  real_T mindl;                        /* '<Root>/Function Calibration' */
  real_T maxdl;                        /* '<Root>/Function Calibration' */
  real_T mindr;                        /* '<Root>/Function Calibration' */
  real_T maxdr;                        /* '<Root>/Function Calibration' */
  real_T minwl;                        /* '<Root>/Function Calibration' */
  real_T maxwl;                        /* '<Root>/Function Calibration' */
  real_T minwfr;                       /* '<Root>/Function Calibration' */
  real_T maxwfr;                       /* '<Root>/Function Calibration' */
  real_T minwfl;                       /* '<Root>/Function Calibration' */
  real_T maxwfl;                       /* '<Root>/Function Calibration' */
  real_T minwr;                        /* '<Root>/Function Calibration' */
  real_T maxwr;                        /* '<Root>/Function Calibration' */
  real_T minwer;                       /* '<Root>/Function Calibration' */
  real_T maxwer;                       /* '<Root>/Function Calibration' */
  real_T minwel;                       /* '<Root>/Function Calibration' */
  real_T maxwel;                       /* '<Root>/Function Calibration' */
  int32_T q_sizes[2];                  /* '<Root>/Lameo' */
  int16_T direction[4];                /* '<Root>/Lameo' */
  int16_T pos[2];                      /* '<Root>/Lameo' */
  int16_T dest[2];                     /* '<Root>/Lameo' */
  struct {
    uint_T is_c2_MicroMouseTemplate:4; /* '<Root>/Lameo' */
    uint_T is_active_c2_MicroMouseTemplate:1;/* '<Root>/Lameo' */
  } bitsForTID0;

  volatile uint16_T TmpRTBAtMaxofElementsOutport1_B;/* synthesized block */
  volatile uint16_T TmpRTBAtMaxofElements7Outport1_;/* synthesized block */
  volatile uint16_T TmpRTBAtMaxofElements8Outport1_;/* synthesized block */
  volatile uint16_T TmpRTBAtMaxofElements15Outport1;/* synthesized block */
  uint8_T temporalCounter_i1;          /* '<Root>/Lameo' */
  boolean_T prePAT_not_empty;          /* '<Root>/Function Sense' */
  boolean_T preNoLED_not_empty;        /* '<Root>/Function Sense' */
  boolean_T ADCOFF_not_empty;          /* '<Root>/Function Sense' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem6;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem5;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem4_c;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem3_c;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem2_ci;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem1_ci;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem2_c;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem1_c;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem3_MicroMouseTe_T MATLABSystem4;/* '<S52>/MATLAB System3' */
  DW_MATLABSystem3_MicroMouseTe_T MATLABSystem3;/* '<S52>/MATLAB System3' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem2;/* '<S52>/MATLAB System1' */
  DW_MATLABSystem1_MicroMouseTe_T MATLABSystem1;/* '<S52>/MATLAB System1' */
} DW_MicroMouseTemplate_T;

/* Parameters for system: '<S52>/MATLAB System1' */
struct P_MATLABSystem1_MicroMouseTem_T_ {
  real_T MATLABSystem1_InitialCondition;/* Expression: 0
                                         * Referenced by: '<S52>/MATLAB System1'
                                         */
};

/* Parameters for system: '<S52>/MATLAB System3' */
struct P_MATLABSystem3_MicroMouseTem_T_ {
  real_T MATLABSystem3_InitialCondition;/* Expression: 0
                                         * Referenced by: '<S52>/MATLAB System3'
                                         */
};

/* Parameters (default storage) */
struct P_MicroMouseTemplate_T_ {
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Constant_Value_i;             /* Expression: 1
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T DataStoreMemory_InitialValue; /* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory'
                                        */
  real_T DataStoreMemory1_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory1'
                                        */
  real_T DataStoreMemory2_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory2'
                                        */
  real_T DataStoreMemory3_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory3'
                                        */
  real_T DataStoreMemory4_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory4'
                                        */
  real_T DataStoreMemory5_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory5'
                                        */
  real_T DataStoreMemory6_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory6'
                                        */
  real_T DataStoreMemory7_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory7'
                                        */
  int32_T DataStoreMemory2_InitialValue_b;
                          /* Computed Parameter: DataStoreMemory2_InitialValue_b
                           * Referenced by: '<S1>/Data Store Memory2'
                           */
  int32_T DataStoreMemory4_InitialValue_a;
                          /* Computed Parameter: DataStoreMemory4_InitialValue_a
                           * Referenced by: '<S1>/Data Store Memory4'
                           */
  real32_T DataStoreMemory_InitialValue_j;
                           /* Computed Parameter: DataStoreMemory_InitialValue_j
                            * Referenced by: '<S10>/Data Store Memory'
                            */
  real32_T DataStoreMemory1_InitialValue_k;
                          /* Computed Parameter: DataStoreMemory1_InitialValue_k
                           * Referenced by: '<S10>/Data Store Memory1'
                           */
  uint16_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S9>/Gain1'
                                        */
  uint16_T TmpRTBAtMaxofElementsOutport1_I;
                          /* Computed Parameter: TmpRTBAtMaxofElementsOutport1_I
                           * Referenced by:
                           */
  uint16_T TmpRTBAtMaxofElements7Outport1_;
                          /* Computed Parameter: TmpRTBAtMaxofElements7Outport1_
                           * Referenced by:
                           */
  uint16_T Constant_Value_b;           /* Computed Parameter: Constant_Value_b
                                        * Referenced by: '<S49>/Constant'
                                        */
  uint16_T TmpRTBAtMaxofElements8Outport1_;
                          /* Computed Parameter: TmpRTBAtMaxofElements8Outport1_
                           * Referenced by:
                           */
  uint16_T TmpRTBAtMaxofElements15Outport1;
                          /* Computed Parameter: TmpRTBAtMaxofElements15Outport1
                           * Referenced by:
                           */
  uint16_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S49>/Constant1'
                                        */
  uint16_T DataStoreMemory_InitialValue_p;
                           /* Computed Parameter: DataStoreMemory_InitialValue_p
                            * Referenced by: '<S9>/Data Store Memory'
                            */
  uint16_T DataStoreMemory1_InitialValue_p;
                          /* Computed Parameter: DataStoreMemory1_InitialValue_p
                           * Referenced by: '<S9>/Data Store Memory1'
                           */
  uint16_T DataStoreMemory2_InitialValue_p;
                          /* Computed Parameter: DataStoreMemory2_InitialValue_p
                           * Referenced by: '<S9>/Data Store Memory2'
                           */
  uint16_T DataStoreMemory1_InitialValue_j;
                          /* Computed Parameter: DataStoreMemory1_InitialValue_j
                           * Referenced by: '<S1>/Data Store Memory1'
                           */
  boolean_T DataStoreMemory_InitialValue_p4;
                          /* Computed Parameter: DataStoreMemory_InitialValue_p4
                           * Referenced by: '<S1>/Data Store Memory'
                           */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem6;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem5;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem4_c;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem3_c;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem2_ci;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem1_ci;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem2_c;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem1_c;/* '<S52>/MATLAB System1' */
  P_MATLABSystem3_MicroMouseTem_T MATLABSystem4;/* '<S52>/MATLAB System3' */
  P_MATLABSystem3_MicroMouseTem_T MATLABSystem3;/* '<S52>/MATLAB System3' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem2;/* '<S52>/MATLAB System1' */
  P_MATLABSystem1_MicroMouseTem_T MATLABSystem1;/* '<S52>/MATLAB System1' */
};

/* Code_Instrumentation_Declarations_Placeholder */

/* Real-time Model Data Structure */
struct tag_RTM_MicroMouseTemplate_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;

    struct {
      boolean_T TID0_1;
    } RateInteraction;
  } Timing;
};

/* Block parameters (default storage) */
extern P_MicroMouseTemplate_T MicroMouseTemplate_P;

/* Block signals (default storage) */
extern B_MicroMouseTemplate_T MicroMouseTemplate_B;

/* Block states (default storage) */
extern DW_MicroMouseTemplate_T MicroMouseTemplate_DW;

/*
 * Exported States
 *
 * Note: Exported states are block states with an exported global
 * storage class designation.  Code generation will declare the memory for these
 * states and exports their symbols.
 *
 */
extern real32_T IMU_Accel[3];          /* '<S10>/Data Store Memory' */
extern real32_T IMU_Gyro[3];           /* '<S10>/Data Store Memory1' */
extern int32_T currTicksRS;            /* '<S1>/Data Store Memory2' */
extern int32_T currTicksLS;            /* '<S1>/Data Store Memory4' */
extern uint16_T ADC1s[9];              /* '<S9>/Data Store Memory' */
extern uint16_T ADC_H[9];              /* '<S9>/Data Store Memory1' */
extern uint16_T ADC_L[9];              /* '<S9>/Data Store Memory2' */
extern uint16_T Thresholds[8];         /* '<S1>/Data Store Memory1' */
extern boolean_T Detections[8];        /* '<S1>/Data Store Memory' */

/* External function called from main */
extern void MicroMouseTemplate_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void MicroMouseTemplate_initialize(void);
extern void MicroMouseTemplate_step0(void);
extern void MicroMouseTemplate_step1(void);
extern void MicroMouseTemplate_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MicroMouseTemplate_T *const MicroMouseTemplate_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S49>/Cast1' : Eliminate redundant data type conversion
 * Block '<S49>/Cast3' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MicroMouseTemplate'
 * '<S1>'   : 'MicroMouseTemplate/Detections and Thresholds'
 * '<S2>'   : 'MicroMouseTemplate/Function Calibration'
 * '<S3>'   : 'MicroMouseTemplate/Function Sense'
 * '<S4>'   : 'MicroMouseTemplate/Function Sensor Anal'
 * '<S5>'   : 'MicroMouseTemplate/GPIO for IR LEDs'
 * '<S6>'   : 'MicroMouseTemplate/IR LED Pattern'
 * '<S7>'   : 'MicroMouseTemplate/Lameo'
 * '<S8>'   : 'MicroMouseTemplate/Motors'
 * '<S9>'   : 'MicroMouseTemplate/Subsystem'
 * '<S10>'  : 'MicroMouseTemplate/Subsystem1'
 * '<S11>'  : 'MicroMouseTemplate/Subsystem2'
 * '<S12>'  : 'MicroMouseTemplate/Subsystem3'
 * '<S13>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_LEFT'
 * '<S14>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_RIGHT'
 * '<S15>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_LEFT'
 * '<S16>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_RIGHT'
 * '<S17>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_LEFT'
 * '<S18>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_LEFT'
 * '<S19>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_RIGHT'
 * '<S20>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_RIGHT'
 * '<S21>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_LEFT/ECSoC'
 * '<S22>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_LEFT/ECSoC/ECSimCodegen'
 * '<S23>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_RIGHT/ECSoC'
 * '<S24>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_RIGHT/ECSoC/ECSimCodegen'
 * '<S25>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_LEFT/ECSoC'
 * '<S26>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_LEFT/ECSoC/ECSimCodegen'
 * '<S27>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_RIGHT/ECSoC'
 * '<S28>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_RIGHT/ECSoC/ECSimCodegen'
 * '<S29>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_LEFT/ECSoC'
 * '<S30>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_LEFT/ECSoC/ECSimCodegen'
 * '<S31>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_LEFT/ECSoC'
 * '<S32>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_LEFT/ECSoC/ECSimCodegen'
 * '<S33>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_RIGHT/ECSoC'
 * '<S34>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_RIGHT/ECSoC/ECSimCodegen'
 * '<S35>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_RIGHT/ECSoC'
 * '<S36>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_RIGHT/ECSoC/ECSimCodegen'
 * '<S37>'  : 'MicroMouseTemplate/IR LED Pattern/MATLAB Function'
 * '<S38>'  : 'MicroMouseTemplate/Motors/Fowards Backwards'
 * '<S39>'  : 'MicroMouseTemplate/Motors/MOTOR_EN'
 * '<S40>'  : 'MicroMouseTemplate/Motors/PWM Output'
 * '<S41>'  : 'MicroMouseTemplate/Motors/PWM Output1'
 * '<S42>'  : 'MicroMouseTemplate/Motors/MOTOR_EN/ECSoC'
 * '<S43>'  : 'MicroMouseTemplate/Motors/MOTOR_EN/ECSoC/ECSimCodegen'
 * '<S44>'  : 'MicroMouseTemplate/Motors/PWM Output/ECSoC'
 * '<S45>'  : 'MicroMouseTemplate/Motors/PWM Output/ECSoC/ECSimCodegen'
 * '<S46>'  : 'MicroMouseTemplate/Motors/PWM Output1/ECSoC'
 * '<S47>'  : 'MicroMouseTemplate/Motors/PWM Output1/ECSoC/ECSimCodegen'
 * '<S48>'  : 'MicroMouseTemplate/Subsystem/ADC2 IN10  IN1'
 * '<S49>'  : 'MicroMouseTemplate/Subsystem/get Highs and Lows'
 * '<S50>'  : 'MicroMouseTemplate/Subsystem/ADC2 IN10  IN1/ECSoC'
 * '<S51>'  : 'MicroMouseTemplate/Subsystem/ADC2 IN10  IN1/ECSoC/ECSimCodegen'
 * '<S52>'  : 'MicroMouseTemplate/Subsystem/get Highs and Lows/Subsystem'
 * '<S53>'  : 'MicroMouseTemplate/Subsystem/get Highs and Lows/Subsystem1'
 * '<S54>'  : 'MicroMouseTemplate/Subsystem/get Highs and Lows/Subsystem2'
 * '<S55>'  : 'MicroMouseTemplate/Subsystem2/CTRL_LEDs'
 * '<S56>'  : 'MicroMouseTemplate/Subsystem2/LED_0'
 * '<S57>'  : 'MicroMouseTemplate/Subsystem2/LED_1'
 * '<S58>'  : 'MicroMouseTemplate/Subsystem2/LED_2'
 * '<S59>'  : 'MicroMouseTemplate/Subsystem2/CTRL_LEDs/ECSoC'
 * '<S60>'  : 'MicroMouseTemplate/Subsystem2/CTRL_LEDs/ECSoC/ECSimCodegen'
 * '<S61>'  : 'MicroMouseTemplate/Subsystem2/LED_0/ECSoC'
 * '<S62>'  : 'MicroMouseTemplate/Subsystem2/LED_0/ECSoC/ECSimCodegen'
 * '<S63>'  : 'MicroMouseTemplate/Subsystem2/LED_1/ECSoC'
 * '<S64>'  : 'MicroMouseTemplate/Subsystem2/LED_1/ECSoC/ECSimCodegen'
 * '<S65>'  : 'MicroMouseTemplate/Subsystem2/LED_2/ECSoC'
 * '<S66>'  : 'MicroMouseTemplate/Subsystem2/LED_2/ECSoC/ECSimCodegen'
 * '<S67>'  : 'MicroMouseTemplate/Subsystem3/SW_1'
 * '<S68>'  : 'MicroMouseTemplate/Subsystem3/SW_2'
 * '<S69>'  : 'MicroMouseTemplate/Subsystem3/SW_1/ECSoC'
 * '<S70>'  : 'MicroMouseTemplate/Subsystem3/SW_1/ECSoC/ECSimCodegen'
 * '<S71>'  : 'MicroMouseTemplate/Subsystem3/SW_2/ECSoC'
 * '<S72>'  : 'MicroMouseTemplate/Subsystem3/SW_2/ECSoC/ECSimCodegen'
 */
#endif                                 /* MicroMouseTemplate_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
