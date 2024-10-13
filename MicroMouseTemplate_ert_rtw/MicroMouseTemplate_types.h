#ifndef MicroMouseTemplate_types_h_
#define MicroMouseTemplate_types_h_
#include "rtwtypes.h"
#include "stm_timer_ll.h"
#include "stm_adc_ll.h"
#ifndef struct_tag_TL74IR3Rn74hKhfKckCIBC
#define struct_tag_TL74IR3Rn74hKhfKckCIBC

struct tag_TL74IR3Rn74hKhfKckCIBC
{
  int32_T isInitialized;
  real_T InitialCondition;
  real_T Buffer[25];
};

#endif

#ifndef typedef_CircularBuffer_MicroMouseTemp_T
#define typedef_CircularBuffer_MicroMouseTemp_T

typedef struct tag_TL74IR3Rn74hKhfKckCIBC CircularBuffer_MicroMouseTemp_T;

#endif

#ifndef struct_tag_v2DAHo7klwgURvzbuzh8NC
#define struct_tag_v2DAHo7klwgURvzbuzh8NC

struct tag_v2DAHo7klwgURvzbuzh8NC
{
  int32_T isInitialized;
  real_T InitialCondition;
  real_T Buffer[10];
};

#endif

#ifndef typedef_CircularBuffer_MicroMouseTe_p_T
#define typedef_CircularBuffer_MicroMouseTe_p_T

typedef struct tag_v2DAHo7klwgURvzbuzh8NC CircularBuffer_MicroMouseTe_p_T;

#endif

#ifndef struct_tag_S5MMpcz8vT0FlmhmEl4q5C
#define struct_tag_S5MMpcz8vT0FlmhmEl4q5C

struct tag_S5MMpcz8vT0FlmhmEl4q5C
{
  int32_T isInitialized;
};

#endif

#ifndef typedef_stm32cube_blocks_DigitalPortW_T
#define typedef_stm32cube_blocks_DigitalPortW_T

typedef struct tag_S5MMpcz8vT0FlmhmEl4q5C stm32cube_blocks_DigitalPortW_T;

#endif

#include "stm_timer_ll.h"
#include "stm_timer_ll.h"
#ifndef struct_tag_C3ug75osl8w3UN1OXa3ipB
#define struct_tag_C3ug75osl8w3UN1OXa3ipB

struct tag_C3ug75osl8w3UN1OXa3ipB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  TIM_Type_T* TimerHandle;
};

#endif

#ifndef typedef_stm32cube_blocks_PWMOutput_Mi_T
#define typedef_stm32cube_blocks_PWMOutput_Mi_T

typedef struct tag_C3ug75osl8w3UN1OXa3ipB stm32cube_blocks_PWMOutput_Mi_T;

#endif

#include "stm_adc_ll.h"
#include "stm_adc_ll.h"
#ifndef struct_tag_wiywjhRn0JhvylthmapQgB
#define struct_tag_wiywjhRn0JhvylthmapQgB

struct tag_wiywjhRn0JhvylthmapQgB
{
  int32_T isInitialized;
};

#endif

#ifndef typedef_stm32cube_blocks_DigitalPortR_T
#define typedef_stm32cube_blocks_DigitalPortR_T

typedef struct tag_wiywjhRn0JhvylthmapQgB stm32cube_blocks_DigitalPortR_T;

#endif

#ifndef struct_tag_6dsyvroagB27OCKFoJuL7
#define struct_tag_6dsyvroagB27OCKFoJuL7

struct tag_6dsyvroagB27OCKFoJuL7
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  ADC_Type_T* ADCHandle;
  uint16_T ADCInternalBuffer[18];
};

#endif

#ifndef typedef_stm32cube_blocks_AnalogInput__T
#define typedef_stm32cube_blocks_AnalogInput__T

typedef struct tag_6dsyvroagB27OCKFoJuL7 stm32cube_blocks_AnalogInput__T;

#endif

#ifndef struct_emxArray_real_T_8x8
#define struct_emxArray_real_T_8x8

struct emxArray_real_T_8x8
{
  real_T data[64];
  int32_T size[2];
};

#endif

#ifndef typedef_emxArray_real_T_8x8_MicroMous_T
#define typedef_emxArray_real_T_8x8_MicroMous_T

typedef struct emxArray_real_T_8x8 emxArray_real_T_8x8_MicroMous_T;

#endif

typedef struct P_MATLABSystem1_MicroMouseTem_T_ P_MATLABSystem1_MicroMouseTem_T;
typedef struct P_MATLABSystem3_MicroMouseTem_T_ P_MATLABSystem3_MicroMouseTem_T;
typedef struct P_MicroMouseTemplate_T_ P_MicroMouseTemplate_T;
typedef struct tag_RTM_MicroMouseTemplate_T RT_MODEL_MicroMouseTemplate_T;

#endif

