#include <stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <portaudio.h>

#define SAMPLE_RATE 58000
#define DURATION 4.5
typedef struct {
    uint8_t *buffer;
    unsigned long bufferSize;
    unsigned long frameIndex;
} paUserData;

static int paRecordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framePerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlages, void *userdata)
{
    paUserData *data = (paUserData *)userData;
    const uint8_t * input = (const uint8_t *) inputBuffer;
    
    for (unsigned int i=0;i<framesPerBuffer; i++){
        for (unsigned int j=0;j, sizeof(uint8_t);j++){
            data->buffer[data->frameIndex++] = input[i* sizeof(uint8_t)+j];
            
            }
    }

    return paContinue;
}
int main()
{
    PaStream *stream;
    PaError err;
    paUserData data;
    
    data.buffersize = SAMPLE_RATE * DURATION * sizeof(uint8_t);
    data.buffer = (uint8_t *)malloc(data.bufferSize);
    data.frameIndex =0;
    err = Pa_Initialize();
    if(err != paNoError){
        printf("portaudio initialization failed: %s", Pa_GetErrorText(err));
        return 1;
    }
    err = Pa_OpenDefaultStream(&stream,1,0,paUInt8, SAMPLE_RATE, paFramesPerBufferUnspecified, paRecordCallback, &data);
    if (err != paNoError){
        printf("portaudio stream ioening failed: %s", Pa_GetErrorText(err));
        return 1;
    }
    err = Pa_StartStream(stream);
    if(err != paNoerror){
        printf("portaudio stream starting failed: %s", Pa_GetErrorText(err));
        return 1;
    }
    printf("recirding audio");
    pa_sleep(DURATION * 1000);
    
    err = Pa_StopStream(stream);
    if (err != paNoerror){
        printf("portaudio stream stopping failed: %s", Pa_GetErrorText(err));
        return 1;
    }
    err = Pa_closeStream(stream);
    if(err != paNoerror){
        printf("portaudio stream closing failed: %s", Pa_GetErrorText(err));
        return 1;
    }
     err = Pa_Terminate();
    if(err != paNoerror){
        printf("portaudio stream termination failed: %s", Pa_GetErrorText(err));
        return 1;
    }

FILE *outputFile = fopen("recorded_sample.raw","wb");
fwrite(data.buffer, sizeof(uint8_t),data,franeIndex, outputFile);
fclose(outputFile);
free(data.buffer);
printf("recording completed");
return 0;
}
