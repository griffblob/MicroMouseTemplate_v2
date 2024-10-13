#include <stddef.h>
#include "code_profiling_utility_functions.h"
#include "MicroMouseTemplate.h"
#include "rtwtypes.h"
#include "MW_target_hardware_resources.h"

unsigned int profilingDataIdx = 0;
unsigned long int _tmwrunningCoreID;
struct _profilingData
{
  unsigned long int sectionID[400];
  unsigned long int timerValue[400];
  unsigned long int coreID[400];
} profilingData;

void store_code_profiling_data_point(void * pData, uint32_T numMemUnits,
  uint32_T sectionId)
{
  uint32_T * pTimerValue = (uint32_T *) pData;
  size_t elNum = 0;
  size_t numEls = numMemUnits/sizeof(uint32_T);
  if (profilingDataIdx==400) {
    return;
  }

  for (elNum=0; elNum<numEls; ++elNum) {
    profilingData.sectionID[profilingDataIdx] = sectionId;
    profilingData.timerValue[profilingDataIdx] = pTimerValue[elNum];
    profilingData.coreID[profilingDataIdx] = _tmwrunningCoreID;
    profilingDataIdx++;
  }
}

void code_profiling_atomic_read_store(uint32_T sectionId)
{
  __disable_irq();

  /* Using a timer that increments on each tick. */
  uint32_T timerValue = (uint32_T)profileTimerRead();
  store_code_profiling_data_point((void *)(&timerValue), (uint32_T)(sizeof
    (uint32_T)), sectionId);
  __enable_irq();
}

volatile int IsrOverrun = 0;
boolean_T isRateRunning[2] = { 0, 0 };

boolean_T need2runFlags[2] = { 0, 0 };

void rt_OneStep(void)
{
  boolean_T eventFlags[2];
  if (isRateRunning[0]++) {
    IsrOverrun = 1;
    isRateRunning[0]--;
    return;
  }

  MicroMouseTemplate_SetEventsForThisBaseStep(eventFlags);
  __enable_irq();
  taskTimeStart_MicroMouseTemplate(2U);
  MicroMouseTemplate_step0();
  taskTimeEnd_MicroMouseTemplate(2U);
  __disable_irq();
  isRateRunning[0]--;
  if (eventFlags[1]) {
    if (need2runFlags[1]++) {
      IsrOverrun = 1;
      need2runFlags[1]--;
      return;
    }
  }

  if (need2runFlags[1]) {
    if (isRateRunning[1]) {
      return;
    }

    isRateRunning[1]++;
    __enable_irq();
    switch (1)
    {
     case 1 :
      taskTimeStart_MicroMouseTemplate(3U);
      MicroMouseTemplate_step1();
      taskTimeEnd_MicroMouseTemplate(3U);
      break;

     default :
      break;
    }

    __disable_irq();
    need2runFlags[1]--;
    isRateRunning[1]--;
  }
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(int argc, char **argv)
{
  float modelBaseRate = 0.005;
  float systemClock = 80.0;
  stopRequested = false;
  runModel = false;

#if !defined(MW_FREERTOS) && defined(MW_MULTI_TASKING_MODE) && (MW_MULTI_TASKING_MODE == 1)

  MW_ASM (" SVC #1");

#endif

  ;
  HAL_Init();
  SystemClock_Config();
  PeriphCommonClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_I2C2_Init();
  MX_TIM4_Init();
  MX_ADC2_Init();
  MX_USB_DEVICE_Init();
  MX_USART2_UART_Init();
  rtmSetErrorStatus(MicroMouseTemplate_M, 0);
  taskTimeStart_MicroMouseTemplate(1U);
  MicroMouseTemplate_initialize();
  taskTimeEnd_MicroMouseTemplate(1U);
  __disable_irq();
  ARMCM_SysTick_Config(modelBaseRate);
  runModel =
    rtmGetErrorStatus(MicroMouseTemplate_M) == (NULL);
  __enable_irq();
  __enable_irq();
  while (runModel) {
    stopRequested = !(
                      rtmGetErrorStatus(MicroMouseTemplate_M) == (NULL));
    if (stopRequested) {
      SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }

    ;
  }

  taskTimeStart_MicroMouseTemplate(4U);
  MicroMouseTemplate_terminate();
  taskTimeEnd_MicroMouseTemplate(4U);

#if !defined(MW_FREERTOS) && !defined(USE_RTX)

  (void) systemClock;

#endif

  ;
  __disable_irq();
  return 0;
}
