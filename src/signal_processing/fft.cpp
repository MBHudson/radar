#include "fft.h"

FFT::FFT(int fftSize,int inputSize):fftSize(fftSize){
  outputMem = fftwf_alloc_complex(fftSize*sizeof(fftw_complex));
  tmp = fftwf_alloc_complex(inputSize*sizeof(fftw_complex));
  forwardDFT = fftwf_plan_dft_1d(fftSize,tmp,outputMem,FFTW_FORWARD,FFTW_ESTIMATE); 
  inverseDFT = fftwf_plan_dft_1d(fftSize,tmp,outputMem,FFTW_BACKWARD,FFTW_ESTIMATE);
  
  //free tmp
  fftwf_free(tmp);
};

FFT::~FFT(){fftwf_free(outputMem);};

void FFT::resetFFTSize(int fftSize,int inputSize){
  this->fftSize = fftSize;
  tmp = fftwf_alloc_complex(inputSize*sizeof(fftw_complex));
  forwardDFT = fftwf_plan_dft_1d(fftSize,tmp,outputMem,FFTW_FORWARD,FFTW_ESTIMATE); 
  inverseDFT = fftwf_plan_dft_1d(fftSize,tmp,outputMem,FFTW_BACKWARD,FFTW_ESTIMATE);
  
  //free tmp
  fftwf_free(tmp);
};

void FFT::getFFT(radar::complexFloatBuffPtr input, radar::complexFloatBuffPtr output){
  fftwf_complex* inputTMP = reinterpret_cast<fftwf_complex*>(input.get());
  fftwf_complex* outputTMP = reinterpret_cast<fftwf_complex*>(output.get());
  fftwf_execute_dft(forwardDFT,inputTMP,outputTMP);
  output.reset(reinterpret_cast<radar::complexFloat*>(outputTMP));
  return;
};

void FFT::getIFFT(radar::complexFloatBuffPtr input, radar::complexFloatBuffPtr output){
  fftwf_complex* inputTMP = reinterpret_cast<fftwf_complex*>(input.get());
  fftwf_complex* outputTMP = reinterpret_cast<fftwf_complex*>(output.get());
  fftwf_execute_dft(forwardDFT,inputTMP,outputTMP);
  output.reset(reinterpret_cast<radar::complexFloat*>(outputTMP));
  return;
};

