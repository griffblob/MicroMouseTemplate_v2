/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate.c
 *
 * Code generated for Simulink model 'MicroMouseTemplate'.
 *
 * Model version                  : 3.8
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Sep 17 16:15:38 2024
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

/* Named constants for Chart: '<Root>/HelloMicroMouse!' */
#define Micr_IN_WaitUntilButtonPressed1 ((uint8_T)4U)
#define MicroMouseTemplate_IN_Delay    ((uint8_T)1U)
#define MicroMouseTemplate_IN_Drive    ((uint8_T)2U)
#define Micro_IN_WaitUntilButtonPressed ((uint8_T)3U)

/* user code (top of source file) */
/* System '<Root>' */
extern I2C_HandleTypeDef hi2c2;

/* Exported block states */
real32_T IMU_Accel[3];                 /* '<S11>/Data Store Memory' */
real32_T IMU_Gyro[3];                  /* '<S11>/Data Store Memory1' */
int32_T currTicksRS;                   /* '<S1>/Data Store Memory2' */
int32_T currTicksLS;                   /* '<S1>/Data Store Memory4' */
uint16_T ADC1s[9];                     /* '<S10>/Data Store Memory' */
uint16_T ADC_H[9];                     /* '<S10>/Data Store Memory1' */
uint16_T ADC_L[9];                     /* '<S10>/Data Store Memory2' */
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

  /* Start for MATLABSystem: '<S53>/MATLAB System1' */
  localDW->objisempty = true;
  localDW->obj.InitialCondition = localP->MATLABSystem1_InitialCondition;
  localDW->obj.isInitialized = 1;

  /*  Number of inputs */
  /*  Initialize the buffer during the first call */
  for (i = 0; i < 25; i++) {
    localDW->obj.Buffer[i] = localDW->obj.InitialCondition;
  }

  /* End of Start for MATLABSystem: '<S53>/MATLAB System1' */
}

/* Output and update for atomic system: */
void MicroMouseTem_MATLABSystem1(real_T rtu_0, B_MATLABSystem1_MicroMouseTem_T
  *localB, DW_MATLABSystem1_MicroMouseTe_T *localDW,
  P_MATLABSystem1_MicroMouseTem_T *localP)
{
  /* MATLABSystem: '<S53>/MATLAB System1' */
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

  /* End of MATLABSystem: '<S53>/MATLAB System1' */
}

/* System initialize for atomic system: */
void MicroMou_MATLABSystem3_Init(DW_MATLABSystem3_MicroMouseTe_T *localDW,
  P_MATLABSystem3_MicroMouseTem_T *localP)
{
  int32_T i;

  /* Start for MATLABSystem: '<S53>/MATLAB System3' */
  localDW->objisempty = true;
  localDW->obj.InitialCondition = localP->MATLABSystem3_InitialCondition;
  localDW->obj.isInitialized = 1;

  /*  Number of inputs */
  /*  Initialize the buffer during the first call */
  for (i = 0; i < 10; i++) {
    localDW->obj.Buffer[i] = localDW->obj.InitialCondition;
  }

  /* End of Start for MATLABSystem: '<S53>/MATLAB System3' */
}

/* Output and update for atomic system: */
void MicroMouseTem_MATLABSystem3(real_T rtu_0, B_MATLABSystem3_MicroMouseTem_T
  *localB, DW_MATLABSystem3_MicroMouseTe_T *localDW,
  P_MATLABSystem3_MicroMouseTem_T *localP)
{
  /* MATLABSystem: '<S53>/MATLAB System3' */
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

  /* End of MATLABSystem: '<S53>/MATLAB System3' */
}

static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj)
{
  ADC_Type_T adcStructLoc;
  obj->isSetupComplete = false;

  /* Start for MATLABSystem: '<S52>/Analog to Digital Converter' */
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

  /* Start for MATLABSystem: '<S46>/PWM Output' */
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<S46>/PWM Output' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  enableTimerChannel3(obj->TimerHandle, ENABLE_CH);
  enableTimerChannel4(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<S46>/PWM Output' */
    enableCounter(obj->TimerHandle, false);
  }
}

static void MicroMous_PWMOutput_setupImpl_d(stm32cube_blocks_PWMOutput_Mi_T *obj)
{
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<S48>/PWM Output' */
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<S48>/PWM Output' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  enableTimerChannel1(obj->TimerHandle, ENABLE_CH);
  enableTimerChannel2(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<S48>/PWM Output' */
    enableCounter(obj->TimerHandle, false);
  }
}

/* Model step function for TID0 */
void MicroMouseTemplate_step0(void)    /* Sample time: [0.01s, 0.0s] */
{
  real_T WelCalL;
  real_T WelCalR;
  real_T rtb_Lb;
  real_T rtb_Lf;
  int32_T i;
  int32_T rtb_Left_f;
  int32_T rtb_Right_a;
  uint32_T pinReadLoc;
  uint32_T pinReadLoc_0;
  uint16_T rtb_TmpRTBAtMaxofElements7Outpo;
  uint16_T rtb_TmpRTBAtMaxofElementsOutpor;
  int8_T a[5];
  int8_T a__1[2];
  boolean_T shiftright;
  static const int8_T b_a[5] = { 1, 0, 0, 0, 0 };

  {                                    /* Sample time: [0.01s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* MATLABSystem: '<S52>/Analog to Digital Converter' */
  regularReadADCDMA(MicroMouseTemplate_DW.obj.ADCHandle, ADC_TRIGGER_AND_READ,
                    &ADC1s[0]);

  /* RateTransition generated from: '<S53>/Max of Elements' */
  rtb_TmpRTBAtMaxofElementsOutpor =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B;

  /* DSPFlip: '<S10>/Flip' incorporates:
   *  MATLABSystem: '<S52>/Analog to Digital Converter'
   */
  MicroMouseTemplate_B.Flip[0] = ADC1s[7];
  MicroMouseTemplate_B.Flip[7] = ADC1s[0];
  MicroMouseTemplate_B.Flip[1] = ADC1s[6];
  MicroMouseTemplate_B.Flip[6] = ADC1s[1];
  MicroMouseTemplate_B.Flip[2] = ADC1s[5];
  MicroMouseTemplate_B.Flip[5] = ADC1s[2];
  MicroMouseTemplate_B.Flip[3] = ADC1s[4];
  MicroMouseTemplate_B.Flip[4] = ADC1s[3];

  /* DataTypeConversion: '<S55>/Cast To Double' */
  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_B.CastToDouble[i] = MicroMouseTemplate_B.Flip[i];
  }

  /* End of DataTypeConversion: '<S55>/Cast To Double' */
  MicroMouseTem_MATLABSystem3((real_T)MicroMouseTemplate_B.CastToDouble[1],
    &MicroMouseTemplate_B.MATLABSystem4, &MicroMouseTemplate_DW.MATLABSystem4,
    &MicroMouseTemplate_P.MATLABSystem4);

  /* MinMax: '<S53>/Max of Elements1' incorporates:
   *  MATLABSystem: '<S53>/MATLAB System4'
   */
  rtb_Lb = MicroMouseTemplate_B.MATLABSystem4.MATLABSystem3[0];
  for (rtb_Left_f = 0; rtb_Left_f < 9; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem4.MATLABSystem3[rtb_Left_f + 1];
    if (rtb_Lb < WelCalL) {
      rtb_Lb = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1(rtb_Lb, &MicroMouseTemplate_B.MATLABSystem1,
    &MicroMouseTemplate_DW.MATLABSystem1, &MicroMouseTemplate_P.MATLABSystem1);

  /* End of MinMax: '<S53>/Max of Elements1' */

  /* MinMax: '<S53>/Min' incorporates:
   *  MATLABSystem: '<S53>/MATLAB System1'
   */
  WelCalR = MicroMouseTemplate_B.MATLABSystem1.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem1.MATLABSystem1[rtb_Left_f + 1];
    if (WelCalR > WelCalL) {
      WelCalR = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1((real_T)MicroMouseTemplate_B.CastToDouble[2],
    &MicroMouseTemplate_B.MATLABSystem1_ci,
    &MicroMouseTemplate_DW.MATLABSystem1_ci,
    &MicroMouseTemplate_P.MATLABSystem1_ci);

  /* MinMax: '<S53>/Max of Elements2' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System1'
   */
  rtb_Lb = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[rtb_Left_f + 1];
    if (rtb_Lb < WelCalL) {
      rtb_Lb = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1((real_T)MicroMouseTemplate_B.CastToDouble[3],
    &MicroMouseTemplate_B.MATLABSystem3_c,
    &MicroMouseTemplate_DW.MATLABSystem3_c,
    &MicroMouseTemplate_P.MATLABSystem3_c);

  /* MinMax: '<S53>/Max of Elements3' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System3'
   */
  MicroMouseTemplate_B.maxV =
    MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[rtb_Left_f + 1];
    if (MicroMouseTemplate_B.maxV < WelCalL) {
      MicroMouseTemplate_B.maxV = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1((real_T)MicroMouseTemplate_B.CastToDouble[4],
    &MicroMouseTemplate_B.MATLABSystem4_c,
    &MicroMouseTemplate_DW.MATLABSystem4_c,
    &MicroMouseTemplate_P.MATLABSystem4_c);

  /* MinMax: '<S53>/Max of Elements4' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System4'
   */
  MicroMouseTemplate_B.maxV_m =
    MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[rtb_Left_f + 1];
    if (MicroMouseTemplate_B.maxV_m < WelCalL) {
      MicroMouseTemplate_B.maxV_m = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1((real_T)MicroMouseTemplate_B.CastToDouble[5],
    &MicroMouseTemplate_B.MATLABSystem5, &MicroMouseTemplate_DW.MATLABSystem5,
    &MicroMouseTemplate_P.MATLABSystem5);

  /* MinMax: '<S53>/Max of Elements5' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System5'
   */
  MicroMouseTemplate_B.maxV_c =
    MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[rtb_Left_f + 1];
    if (MicroMouseTemplate_B.maxV_c < WelCalL) {
      MicroMouseTemplate_B.maxV_c = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem3((real_T)MicroMouseTemplate_B.CastToDouble[6],
    &MicroMouseTemplate_B.MATLABSystem3, &MicroMouseTemplate_DW.MATLABSystem3,
    &MicroMouseTemplate_P.MATLABSystem3);

  /* MinMax: '<S53>/Max of Elements6' incorporates:
   *  MATLABSystem: '<S53>/MATLAB System3'
   */
  rtb_Lf = MicroMouseTemplate_B.MATLABSystem3.MATLABSystem3[0];
  for (rtb_Left_f = 0; rtb_Left_f < 9; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem3.MATLABSystem3[rtb_Left_f + 1];
    if (rtb_Lf < WelCalL) {
      rtb_Lf = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1(rtb_Lf, &MicroMouseTemplate_B.MATLABSystem2,
    &MicroMouseTemplate_DW.MATLABSystem2, &MicroMouseTemplate_P.MATLABSystem2);

  /* End of MinMax: '<S53>/Max of Elements6' */

  /* MinMax: '<S53>/Min1' incorporates:
   *  MATLABSystem: '<S53>/MATLAB System2'
   */
  rtb_Lf = MicroMouseTemplate_B.MATLABSystem2.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem2.MATLABSystem1[rtb_Left_f + 1];
    if (rtb_Lf > WelCalL) {
      rtb_Lf = WelCalL;
    }
  }

  /* RateTransition generated from: '<S53>/Max of Elements7' */
  rtb_TmpRTBAtMaxofElements7Outpo =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_;

  /* DataStoreWrite: '<S50>/ADC_H Write' */
  ADC_H[0] = rtb_TmpRTBAtMaxofElementsOutpor;

  /* MinMax: '<S53>/Min' */
  WelCalL = fmod(floor(WelCalR), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_H Write' incorporates:
   *  MinMax: '<S53>/Min'
   */
  ADC_H[1] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S53>/Max of Elements2' */
  WelCalL = fmod(floor(rtb_Lb), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_H Write' incorporates:
   *  MinMax: '<S53>/Max of Elements2'
   */
  ADC_H[2] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S53>/Max of Elements3' */
  WelCalL = fmod(floor(MicroMouseTemplate_B.maxV), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_H Write' incorporates:
   *  MinMax: '<S53>/Max of Elements3'
   */
  ADC_H[3] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S53>/Max of Elements4' */
  WelCalL = fmod(floor(MicroMouseTemplate_B.maxV_m), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_H Write' incorporates:
   *  MinMax: '<S53>/Max of Elements4'
   */
  ADC_H[4] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S53>/Max of Elements5' */
  WelCalL = fmod(floor(MicroMouseTemplate_B.maxV_c), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_H Write' incorporates:
   *  MinMax: '<S53>/Max of Elements5'
   */
  ADC_H[5] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S53>/Min1' */
  WelCalL = fmod(floor(rtb_Lf), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_H Write' incorporates:
   *  Constant: '<S50>/Constant'
   *  MinMax: '<S53>/Min1'
   */
  ADC_H[6] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);
  ADC_H[7] = rtb_TmpRTBAtMaxofElements7Outpo;
  ADC_H[8] = MicroMouseTemplate_P.Constant_Value_b;

  /* RateTransition generated from: '<S54>/Max of Elements8' */
  rtb_TmpRTBAtMaxofElementsOutpor =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_;
  MicroMouseTem_MATLABSystem1((real_T)MicroMouseTemplate_B.CastToDouble[1],
    &MicroMouseTemplate_B.MATLABSystem1_c,
    &MicroMouseTemplate_DW.MATLABSystem1_c,
    &MicroMouseTemplate_P.MATLABSystem1_c);

  /* MinMax: '<S54>/Max of Elements9' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System1'
   */
  WelCalR = MicroMouseTemplate_B.MATLABSystem1_c.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem1_c.MATLABSystem1[rtb_Left_f + 1];
    if (WelCalR > WelCalL) {
      WelCalR = WelCalL;
    }
  }

  /* MinMax: '<S54>/Max of Elements10' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System1'
   */
  rtb_Lf = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem1_ci.MATLABSystem1[rtb_Left_f + 1];
    if (rtb_Lf > WelCalL) {
      rtb_Lf = WelCalL;
    }
  }

  /* MinMax: '<S54>/Max of Elements11' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System3'
   */
  rtb_Lb = MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem3_c.MATLABSystem1[rtb_Left_f + 1];
    if (rtb_Lb > WelCalL) {
      rtb_Lb = WelCalL;
    }
  }

  /* MinMax: '<S54>/Max of Elements12' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System4'
   */
  MicroMouseTemplate_B.maxV =
    MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem4_c.MATLABSystem1[rtb_Left_f + 1];
    if (MicroMouseTemplate_B.maxV > WelCalL) {
      MicroMouseTemplate_B.maxV = WelCalL;
    }
  }

  /* MinMax: '<S54>/Max of Elements13' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System5'
   */
  MicroMouseTemplate_B.maxV_m =
    MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem5.MATLABSystem1[rtb_Left_f + 1];
    if (MicroMouseTemplate_B.maxV_m > WelCalL) {
      MicroMouseTemplate_B.maxV_m = WelCalL;
    }
  }

  MicroMouseTem_MATLABSystem1((real_T)MicroMouseTemplate_B.CastToDouble[6],
    &MicroMouseTemplate_B.MATLABSystem2_c,
    &MicroMouseTemplate_DW.MATLABSystem2_c,
    &MicroMouseTemplate_P.MATLABSystem2_c);

  /* MinMax: '<S54>/Max of Elements14' incorporates:
   *  MATLABSystem: '<S54>/MATLAB System2'
   */
  MicroMouseTemplate_B.maxV_c =
    MicroMouseTemplate_B.MATLABSystem2_c.MATLABSystem1[0];
  for (rtb_Left_f = 0; rtb_Left_f < 24; rtb_Left_f++) {
    WelCalL = MicroMouseTemplate_B.MATLABSystem2_c.MATLABSystem1[rtb_Left_f + 1];
    if (MicroMouseTemplate_B.maxV_c > WelCalL) {
      MicroMouseTemplate_B.maxV_c = WelCalL;
    }
  }

  /* RateTransition generated from: '<S54>/Max of Elements15' */
  rtb_TmpRTBAtMaxofElements7Outpo =
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1;

  /* DataStoreWrite: '<S50>/ADC_L Write' */
  ADC_L[0] = rtb_TmpRTBAtMaxofElementsOutpor;

  /* MinMax: '<S54>/Max of Elements9' */
  WelCalL = fmod(floor(WelCalR), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_L Write' incorporates:
   *  MinMax: '<S54>/Max of Elements9'
   */
  ADC_L[1] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S54>/Max of Elements10' */
  WelCalL = fmod(floor(rtb_Lf), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_L Write' incorporates:
   *  MinMax: '<S54>/Max of Elements10'
   */
  ADC_L[2] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S54>/Max of Elements11' */
  WelCalL = fmod(floor(rtb_Lb), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_L Write' incorporates:
   *  MinMax: '<S54>/Max of Elements11'
   */
  ADC_L[3] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S54>/Max of Elements12' */
  WelCalL = fmod(floor(MicroMouseTemplate_B.maxV), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_L Write' incorporates:
   *  MinMax: '<S54>/Max of Elements12'
   */
  ADC_L[4] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S54>/Max of Elements13' */
  WelCalL = fmod(floor(MicroMouseTemplate_B.maxV_m), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_L Write' incorporates:
   *  MinMax: '<S54>/Max of Elements13'
   */
  ADC_L[5] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);

  /* MinMax: '<S54>/Max of Elements14' */
  WelCalL = fmod(floor(MicroMouseTemplate_B.maxV_c), 65536.0);

  /* DataStoreWrite: '<S50>/ADC_L Write' incorporates:
   *  Constant: '<S50>/Constant1'
   *  MinMax: '<S54>/Max of Elements14'
   */
  ADC_L[6] = (uint16_T)(WelCalL < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
                        -WelCalL : (int32_T)(uint16_T)WelCalL);
  ADC_L[7] = rtb_TmpRTBAtMaxofElements7Outpo;
  ADC_L[8] = MicroMouseTemplate_P.Constant1_Value;

  /* RateTransition: '<S55>/Rate Transition' */
  if (MicroMouseTemplate_M->Timing.RateInteraction.TID0_1) {
    MicroMouseTemplate_DW.RateTransition_Buffer =
      MicroMouseTemplate_B.CastToDouble[0];

    /* RateTransition: '<S55>/Rate Transition1' */
    MicroMouseTemplate_DW.RateTransition1_Buffer =
      MicroMouseTemplate_B.CastToDouble[7];
  }

  /* End of RateTransition: '<S55>/Rate Transition' */
  for (i = 0; i < 8; i++) {
    /* DataTypeConversion: '<S10>/Cast To Double' incorporates:
     *  DSPFlip: '<S10>/Flip'
     *  Gain: '<S10>/Gain1'
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

  /* MATLAB Function: '<S8>/MATLAB Function' */
  MicroMouseTemplate_DW.c++;
  for (i = 0; i < 5; i++) {
    a[i] = b_a[i];
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
      for (rtb_Left_f = 5; rtb_Left_f >= i + 1; rtb_Left_f--) {
        a[rtb_Left_f - 1] = a[(rtb_Left_f - i) - 1];
      }

      memset(&a[0], 0, (uint32_T)i * sizeof(int8_T));
    } else {
      memcpy(&a__1[0], &b_a[0], (uint32_T)i * sizeof(int8_T));
      memset(&a[0], 0, (uint32_T)((4 - i) + 1) * sizeof(int8_T));
      for (rtb_Left_f = 0; rtb_Left_f < i; rtb_Left_f++) {
        a[(rtb_Left_f - i) + 5] = a__1[rtb_Left_f];
      }
    }
  }

  /* Outputs for Atomic SubSystem: '<Root>/GPIO for IR LEDs' */
  /* MATLABSystem: '<S23>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[2] != 0) {
    i = 512;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 512U);

  /* End of MATLABSystem: '<S23>/Digital Port Write' */

  /* MATLABSystem: '<S25>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[2] != 0) {
    i = 16384;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 16384U);

  /* End of MATLABSystem: '<S25>/Digital Port Write' */

  /* MATLABSystem: '<S27>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[1] != 0) {
    i = 256;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 256U);

  /* End of MATLABSystem: '<S27>/Digital Port Write' */

  /* MATLABSystem: '<S29>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[1] != 0) {
    i = 32768;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 32768U);

  /* End of MATLABSystem: '<S29>/Digital Port Write' */

  /* MATLABSystem: '<S31>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[3] != 0) {
    i = 4096;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 4096U);

  /* End of MATLABSystem: '<S31>/Digital Port Write' */

  /* MATLABSystem: '<S33>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (a[0] != 0) {
    i = 4096;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 4096U);

  /* End of MATLABSystem: '<S33>/Digital Port Write' */

  /* MATLABSystem: '<S35>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[0] != 0) {
    i = 8192;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8192U);

  /* End of MATLABSystem: '<S35>/Digital Port Write' */

  /* MATLABSystem: '<S37>/Digital Port Write' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (a[3] != 0) {
    i = 2048;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 2048U);

  /* End of MATLABSystem: '<S37>/Digital Port Write' */
  /* End of Outputs for SubSystem: '<Root>/GPIO for IR LEDs' */

  /* MATLABSystem: '<S73>/Digital Port Read' */
  pinReadLoc = LL_GPIO_ReadInputPort(GPIOB);

  /* MATLABSystem: '<S71>/Digital Port Read' */
  pinReadLoc_0 = LL_GPIO_ReadInputPort(GPIOE);

  /* Chart: '<Root>/HelloMicroMouse!' incorporates:
   *  Logic: '<S13>/NOT'
   *  Logic: '<S13>/NOT1'
   *  MATLABSystem: '<S71>/Digital Port Read'
   *  MATLABSystem: '<S73>/Digital Port Read'
   * */
  if (MicroMouseTemplate_DW.temporalCounter_i1 < 255U) {
    MicroMouseTemplate_DW.temporalCounter_i1++;
  }

  if (MicroMouseTemplate_DW.bitsForTID0.is_active_c2_MicroMouseTemplate == 0U) {
    MicroMouseTemplate_DW.bitsForTID0.is_active_c2_MicroMouseTemplate = 1U;
    MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
    MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
      Micro_IN_WaitUntilButtonPressed;
  } else {
    switch (MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate) {
     case MicroMouseTemplate_IN_Delay:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 100U) {
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Drive;
        MicroMouseTemplate_B.Drive = 1.0;
      }
      break;

     case MicroMouseTemplate_IN_Drive:
      if ((pinReadLoc & 4U) == 0U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          Micro_IN_WaitUntilButtonPressed;
      }
      break;

     case Micro_IN_WaitUntilButtonPressed:
      if (((pinReadLoc & 4U) == 0U) && (MicroMouseTemplate_DW.temporalCounter_i1
           >= 200U)) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          Micr_IN_WaitUntilButtonPressed1;
      } else if ((pinReadLoc_0 & 64U) == 0U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          MicroMouseTemplate_IN_Delay;
      } else {
        MicroMouseTemplate_B.Calibrate = 0.0;
        MicroMouseTemplate_B.Drive = 0.0;
      }
      break;

     default:
      /* case IN_WaitUntilButtonPressed1: */
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 100U) {
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_DW.bitsForTID0.is_c2_MicroMouseTemplate =
          Micro_IN_WaitUntilButtonPressed;
      } else {
        MicroMouseTemplate_B.Calibrate = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/HelloMicroMouse!' */

  /* SignalConversion generated from: '<S4>/ SFunction ' incorporates:
   *  MATLAB Function: '<Root>/Function Sense'
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  MicroMouseTemplate_B.CastToDouble[0] = (uint16_T)a[0];
  MicroMouseTemplate_B.CastToDouble[1] = (uint16_T)a[1];
  MicroMouseTemplate_B.CastToDouble[2] = (uint16_T)a[2];
  MicroMouseTemplate_B.CastToDouble[3] = (uint16_T)a[3];
  MicroMouseTemplate_B.CastToDouble[4] = (uint16_T)a[3];
  MicroMouseTemplate_B.CastToDouble[5] = (uint16_T)a[2];
  MicroMouseTemplate_B.CastToDouble[6] = (uint16_T)a[1];
  MicroMouseTemplate_B.CastToDouble[7] = (uint16_T)a[0];

  /* MATLAB Function: '<Root>/Function Sense' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  if (!MicroMouseTemplate_DW.prePAT_not_empty) {
    for (i = 0; i < 8; i++) {
      MicroMouseTemplate_DW.prePAT[i] = MicroMouseTemplate_B.CastToDouble[i];
    }

    MicroMouseTemplate_DW.prePAT_not_empty = true;
  }

  if (!MicroMouseTemplate_DW.preNoLED_not_empty) {
    MicroMouseTemplate_DW.preNoLED = a[4];
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

  MicroMouseTemplate_DW.preNoLED = a[4];
  for (i = 0; i < 8; i++) {
    if (MicroMouseTemplate_DW.prePAT[i] == 1.0) {
      MicroMouseTemplate_DW.ADCON[i] = MicroMouseTemplate_B.CastToDouble_m[i];
    }

    MicroMouseTemplate_B.CastToDouble_m[i] = MicroMouseTemplate_DW.ADCON[i] -
      MicroMouseTemplate_DW.ADCOFF.data[i];
    MicroMouseTemplate_DW.prePAT[i] = MicroMouseTemplate_B.CastToDouble[i];
  }

  /* MATLAB Function: '<Root>/Function Calibration' */
  rtb_Left_f = 0;
  rtb_Right_a = 0;
  if (MicroMouseTemplate_B.Calibrate == 1.0) {
    rtb_Right_a = 100;
    rtb_Left_f = -100;
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
      MicroMouseTemplate_DW.maxwr = MicroMouseTemplate_DW.maxwr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[3];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[3] < MicroMouseTemplate_DW.minwr) {
      MicroMouseTemplate_DW.minwr = MicroMouseTemplate_DW.minwr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[3];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[4] > MicroMouseTemplate_DW.maxwl) {
      MicroMouseTemplate_DW.maxwl = MicroMouseTemplate_DW.maxwl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[4];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[4] < MicroMouseTemplate_DW.minwl) {
      MicroMouseTemplate_DW.minwl = MicroMouseTemplate_DW.minwl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[4];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[1] > MicroMouseTemplate_DW.maxwfr) {
      MicroMouseTemplate_DW.maxwfr = MicroMouseTemplate_DW.maxwfr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[1];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[1] < MicroMouseTemplate_DW.minwfr) {
      MicroMouseTemplate_DW.minwfr = MicroMouseTemplate_DW.minwfr * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[1];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[6] > MicroMouseTemplate_DW.maxwfl) {
      MicroMouseTemplate_DW.maxwfl = MicroMouseTemplate_DW.maxwfl * 0.8 + 0.2 *
        MicroMouseTemplate_B.CastToDouble_m[6];
    }

    if (MicroMouseTemplate_B.CastToDouble_m[6] < MicroMouseTemplate_DW.minwfl) {
      MicroMouseTemplate_DW.minwfl = MicroMouseTemplate_DW.minwfl * 0.8 + 0.2 *
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

  WelCalL = (MicroMouseTemplate_DW.minwel + MicroMouseTemplate_DW.maxwel) / 2.0;
  WelCalR = (MicroMouseTemplate_DW.minwer + MicroMouseTemplate_DW.maxwer) / 2.0;

  /* MATLAB Function: '<Root>/Function Sensor Anal' incorporates:
   *  MATLAB Function: '<Root>/Function Calibration'
   */
  for (i = 0; i < 8; i++) {
    MicroMouseTemplate_B.CastToDouble[i] = 0U;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[2] > (MicroMouseTemplate_DW.mindl +
       MicroMouseTemplate_DW.maxdl) / 2.0) {
    MicroMouseTemplate_B.CastToDouble[2] = 1U;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[5] > (MicroMouseTemplate_DW.mindr +
       MicroMouseTemplate_DW.maxdr) / 2.0) {
    MicroMouseTemplate_B.CastToDouble[5] = 1U;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[7] > WelCalL * 1.1) {
    MicroMouseTemplate_DW.sens8 = 1.0;
  } else if (MicroMouseTemplate_B.CastToDouble_m[7] < WelCalL * 0.9) {
    MicroMouseTemplate_DW.sens8 = 0.0;
  }

  if (MicroMouseTemplate_B.CastToDouble_m[0] > WelCalR * 1.1) {
    MicroMouseTemplate_DW.sens1 = 1.0;
  } else if (MicroMouseTemplate_B.CastToDouble_m[0] < WelCalR * 0.9) {
    MicroMouseTemplate_DW.sens1 = 0.0;
  }

  /* MATLAB Function: '<Root>/Function Follow Line' */
  WelCalL = 0.0;
  WelCalR = 0.0;
  if (MicroMouseTemplate_B.Drive == 1.0) {
    if (MicroMouseTemplate_B.CastToDouble[2] == 1) {
      if (MicroMouseTemplate_B.CastToDouble[5] == 0) {
        MicroMouseTemplate_DW.error = -1.0;
      }
    } else if (MicroMouseTemplate_B.CastToDouble[5] == 1) {
      MicroMouseTemplate_DW.error = 1.0;
    } else {
      MicroMouseTemplate_DW.error = 0.0;
    }

    if ((MicroMouseTemplate_DW.error == 1.0) &&
        (MicroMouseTemplate_B.CastToDouble[2] == 1) &&
        (MicroMouseTemplate_B.CastToDouble[5] == 1)) {
      MicroMouseTemplate_DW.error = 2.0;
    }

    if ((MicroMouseTemplate_DW.error == -1.0) &&
        (MicroMouseTemplate_B.CastToDouble[2] == 1) &&
        (MicroMouseTemplate_B.CastToDouble[5] == 1)) {
      MicroMouseTemplate_DW.error = -2.0;
    }

    MicroMouseTemplate_DW.sumError += MicroMouseTemplate_DW.error;
    MicroMouseTemplate_DW.sumError -= 0.005 * MicroMouseTemplate_DW.sumError;
    MicroMouseTemplate_DW.Dave = (MicroMouseTemplate_DW.error -
      MicroMouseTemplate_DW.preError) + 0.8 * MicroMouseTemplate_DW.Dave;
    WelCalR = (30.0 * MicroMouseTemplate_DW.error +
               MicroMouseTemplate_DW.sumError) + 100.0 *
      MicroMouseTemplate_DW.Dave;
    MicroMouseTemplate_DW.preError = MicroMouseTemplate_DW.error;
    if (100.0 - WelCalR >= -100.0) {
      WelCalL = 100.0 - WelCalR;
    } else {
      WelCalL = -100.0;
    }

    if (WelCalL > 100.0) {
      WelCalL = 100.0;
    }

    if (WelCalR + 100.0 >= -100.0) {
      WelCalR += 100.0;
    } else {
      WelCalR = -100.0;
    }

    if (WelCalR > 100.0) {
      WelCalR = 100.0;
    }

    if ((MicroMouseTemplate_DW.error == 0.0) &&
        (MicroMouseTemplate_B.CastToDouble[2] == 1) &&
        (MicroMouseTemplate_B.CastToDouble[5] == 1)) {
      WelCalL = -50.0;
      WelCalR = -50.0;
    }
  }

  /* End of MATLAB Function: '<Root>/Function Follow Line' */

  /* Sum: '<Root>/Add1' */
  WelCalL += (real_T)rtb_Left_f;

  /* Sum: '<Root>/Add' */
  WelCalR += (real_T)rtb_Right_a;

  /* MATLAB Function: '<S9>/Fowards Backwards' */
  if (!MicroMouseTemplate_DW.Rmem_not_empty) {
    MicroMouseTemplate_DW.Rmem = WelCalL;
    MicroMouseTemplate_DW.Rmem_not_empty = true;
  }

  if (!MicroMouseTemplate_DW.Lmem_not_empty) {
    MicroMouseTemplate_DW.Lmem = WelCalR;
    MicroMouseTemplate_DW.Lmem_not_empty = true;
  }

  MicroMouseTemplate_DW.Rmem = 0.6 * MicroMouseTemplate_DW.Rmem + 0.4 * WelCalL;
  MicroMouseTemplate_DW.Lmem = 0.6 * MicroMouseTemplate_DW.Lmem + 0.4 * WelCalR;
  if (MicroMouseTemplate_DW.Rmem > 10.0) {
    WelCalL = MicroMouseTemplate_DW.Rmem / 3.0 + 66.0;
    WelCalR = 0.0;
  } else if (MicroMouseTemplate_DW.Rmem < -10.0) {
    WelCalL = 0.0;
    WelCalR = fabs(MicroMouseTemplate_DW.Rmem / 3.0 - 66.0);
  } else {
    WelCalL = 0.0;
    WelCalR = 0.0;
  }

  if (MicroMouseTemplate_DW.Lmem > 10.0) {
    rtb_Lf = MicroMouseTemplate_DW.Lmem / 3.0 + 66.0;
    rtb_Lb = 0.0;
  } else if (MicroMouseTemplate_DW.Lmem < -10.0) {
    rtb_Lf = 0.0;
    rtb_Lb = fabs(MicroMouseTemplate_DW.Lmem / 3.0 - 66.0);
  } else {
    rtb_Lf = 0.0;
    rtb_Lb = 0.0;
  }

  /* End of MATLAB Function: '<S9>/Fowards Backwards' */

  /* MATLABSystem: '<S46>/PWM Output' */
  setDutyCycleInPercentageChannel3(MicroMouseTemplate_DW.obj_n.TimerHandle,
    WelCalL);
  setDutyCycleInPercentageChannel4(MicroMouseTemplate_DW.obj_n.TimerHandle,
    WelCalR);

  /* MATLABSystem: '<S48>/PWM Output' */
  setDutyCycleInPercentageChannel1(MicroMouseTemplate_DW.obj_g.TimerHandle,
    rtb_Lf);
  setDutyCycleInPercentageChannel2(MicroMouseTemplate_DW.obj_g.TimerHandle,
    rtb_Lb);

  /* MATLABSystem: '<S44>/Digital Port Write' incorporates:
   *  Constant: '<S9>/Constant'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOD;
  if (MicroMouseTemplate_P.Constant_Value != 0.0) {
    i = 128;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 128U);

  /* End of MATLABSystem: '<S44>/Digital Port Write' */

  /* MATLABSystem: '<S63>/Digital Port Write' incorporates:
   *  MATLAB Function: '<Root>/Function Sensor Anal'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_DW.sens1 != 0.0) {
    i = 8192;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8192U);

  /* End of MATLABSystem: '<S63>/Digital Port Write' */

  /* MATLABSystem: '<S65>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, 0U);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, 16384U);

  /* MATLABSystem: '<S67>/Digital Port Write' incorporates:
   *  MATLAB Function: '<Root>/Function Sensor Anal'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_DW.sens8 != 0.0) {
    i = 32768;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 32768U);

  /* End of MATLABSystem: '<S67>/Digital Port Write' */

  /* MATLABSystem: '<S61>/Digital Port Write' incorporates:
   *  Constant: '<S12>/Constant'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_P.Constant_Value_i != 0.0) {
    i = 8;
  } else {
    i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)i & 8U);

  /* End of MATLABSystem: '<S61>/Digital Port Write' */

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

  /* RateTransition: '<S55>/Rate Transition' */
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_DW.RateTransition_Buffer,
    &MicroMouseTemplate_B.MATLABSystem2_ci,
    &MicroMouseTemplate_DW.MATLABSystem2_ci,
    &MicroMouseTemplate_P.MATLABSystem2_ci);

  /* MinMax: '<S53>/Max of Elements' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System2'
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

  /* End of MinMax: '<S53>/Max of Elements' */

  /* RateTransition: '<S55>/Rate Transition1' */
  MicroMouseTem_MATLABSystem1(MicroMouseTemplate_DW.RateTransition1_Buffer,
    &MicroMouseTemplate_B.MATLABSystem6, &MicroMouseTemplate_DW.MATLABSystem6,
    &MicroMouseTemplate_P.MATLABSystem6);

  /* MinMax: '<S53>/Max of Elements7' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System6'
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

  /* End of MinMax: '<S53>/Max of Elements7' */

  /* RateTransition generated from: '<S53>/Max of Elements7' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_ = rtb_MaxofElements7;

  /* RateTransition generated from: '<S53>/Max of Elements' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B = rtb_MaxofElements;

  /* MinMax: '<S54>/Max of Elements15' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System6'
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

  /* End of MinMax: '<S54>/Max of Elements15' */

  /* MinMax: '<S54>/Max of Elements8' incorporates:
   *  MATLABSystem: '<S55>/MATLAB System2'
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

  /* End of MinMax: '<S54>/Max of Elements8' */

  /* RateTransition generated from: '<S54>/Max of Elements15' */
  MicroMouseTemplate_DW.TmpRTBAtMaxofElements15Outport1 = rtb_MaxofElements;

  /* RateTransition generated from: '<S54>/Max of Elements8' */
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
      /* Start for DataStoreMemory: '<S10>/Data Store Memory' */
      ADC1s[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_p;

      /* Start for DataStoreMemory: '<S10>/Data Store Memory1' */
      ADC_H[i] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_p;

      /* Start for DataStoreMemory: '<S10>/Data Store Memory2' */
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

    /* Start for DataStoreMemory: '<S11>/Data Store Memory' */
    IMU_Accel[0] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory1' */
    IMU_Gyro[0] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory' */
    IMU_Accel[1] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory1' */
    IMU_Gyro[1] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory' */
    IMU_Accel[2] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_j;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory1' */
    IMU_Gyro[2] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_k;

    /* user code (Initialize function Body) */

    /* System '<Root>' */
    initIMU();

    /* InitializeConditions for RateTransition generated from: '<S53>/Max of Elements' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElementsOutport1_B =
      MicroMouseTemplate_P.TmpRTBAtMaxofElementsOutport1_I;

    /* InitializeConditions for RateTransition generated from: '<S53>/Max of Elements7' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements7Outport1_ =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements7Outport1_;

    /* InitializeConditions for RateTransition generated from: '<S54>/Max of Elements8' */
    MicroMouseTemplate_DW.TmpRTBAtMaxofElements8Outport1_ =
      MicroMouseTemplate_P.TmpRTBAtMaxofElements8Outport1_;

    /* InitializeConditions for RateTransition generated from: '<S54>/Max of Elements15' */
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

    /* Start for MATLABSystem: '<S52>/Analog to Digital Converter' */
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

    /* Start for MATLABSystem: '<S46>/PWM Output' */
    MicroMouseTemplate_DW.obj_n.matlabCodegenIsDeleted = false;
    MicroMouseTemplate_DW.obj_n.isSetupComplete = false;
    MicroMouseTemplate_DW.obj_n.isInitialized = 1;
    MicroMouseT_PWMOutput_setupImpl(&MicroMouseTemplate_DW.obj_n);
    MicroMouseTemplate_DW.obj_n.isSetupComplete = true;

    /* Start for MATLABSystem: '<S48>/PWM Output' */
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
  /* Terminate for MATLABSystem: '<S52>/Analog to Digital Converter' */
  if (!MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted) {
    MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted = true;
    if ((MicroMouseTemplate_DW.obj.isInitialized == 1) &&
        MicroMouseTemplate_DW.obj.isSetupComplete) {
      ADC_Handle_Deinit(MicroMouseTemplate_DW.obj.ADCHandle,
                        ADC_DMA_INTERRUPT_MODE, 1);
    }
  }

  /* End of Terminate for MATLABSystem: '<S52>/Analog to Digital Converter' */

  /* Terminate for MATLABSystem: '<S46>/PWM Output' */
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

  /* End of Terminate for MATLABSystem: '<S46>/PWM Output' */

  /* Terminate for MATLABSystem: '<S48>/PWM Output' */
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

  /* End of Terminate for MATLABSystem: '<S48>/PWM Output' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
