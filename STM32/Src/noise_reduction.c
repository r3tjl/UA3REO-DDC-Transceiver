#include "noise_reduction.h"
#include "stm32f4xx_hal.h"
#include "arm_const_structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "arm_math.h"
#include "settings.h"
#include "functions.h"

arm_lms_norm_instance_f32	lms2_Norm_instance;
float32_t	                lms2_stateF32[NOISE_REDUCTION_TAPS+NOISE_REDUCTION_BLOCK_SIZE];
float32_t	                lms2_normCoeff_f32[NOISE_REDUCTION_TAPS];
float32_t	                lms2_reference[NOISE_REDUCTION_REFERENCE_SIZE];
float32_t   							lms2_errsig2[NOISE_REDUCTION_BLOCK_SIZE];

void InitNoiseReduction(void)
{
	float32_t  step = 0.0001;
	if(TRX.Agc) step = 0.0000001;
  arm_lms_norm_init_f32(&lms2_Norm_instance, NOISE_REDUCTION_TAPS, lms2_normCoeff_f32, lms2_stateF32, step, NOISE_REDUCTION_BLOCK_SIZE);
	arm_fill_f32(0.0,lms2_reference,NOISE_REDUCTION_REFERENCE_SIZE);
	arm_fill_f32(0.0,lms2_normCoeff_f32,NOISE_REDUCTION_TAPS);
}

void processNoiseReduction(float* bufferIn, float* bufferOut)
{
	static uint16_t reference_index=0;
	static uint16_t reference_index_new=0;
	arm_copy_f32(bufferIn, &lms2_reference[reference_index], NOISE_REDUCTION_BLOCK_SIZE);
	arm_lms_norm_f32(&lms2_Norm_instance, bufferIn, &lms2_reference[reference_index_new], bufferOut, lms2_errsig2, NOISE_REDUCTION_BLOCK_SIZE);
	reference_index+=NOISE_REDUCTION_BLOCK_SIZE;
	if(reference_index>=NOISE_REDUCTION_REFERENCE_SIZE) reference_index=0;
	reference_index_new=reference_index+NOISE_REDUCTION_BLOCK_SIZE;
	if(reference_index_new>=NOISE_REDUCTION_REFERENCE_SIZE) reference_index_new=0;
}