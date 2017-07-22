#include <alsa/asoundlib.h>
#include <stdio.h>

#define PCM_DEVICE "default"

int download_up_first(){
	printf("downloading\n");
	return 0;
}

int play_wav(int file_d, int r, int c, int s){
	FILE *sound;
	unsigned int pcm, tmp, dir;
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t *frames;
	int loops;
	char* buff;
	int buff_size;
	int rate, channels, seconds;
	rate = r; 
	channels = c;
	seconds = s;

	sound = fopen("ahyes.wav", "r");
	if(sound == -1){
		return -1;
	}
	if(pcm = snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0) < 0){
		printf("Problem encountered, cannot open %s\n%s\n", PCM_DEVICE, snd_strerror(pcm));
	}

	//default parameters
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(pcm_handle, params);

	if(pcm = snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0){
		printf("Can't set interleaved mode\n%s\n", snd_strerror(pcm));
	}

	if(pcm = snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_ACCESS_RW_S16_LE) < 0){
		printf("Can't set format\n%s\n", snd_strerror(pcm));
	}

	if(pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, channels) < 0){
		printf("Can't set channels number.\n%s\n", snd_strerror(pcm);
	}

	if(pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0) < 0){
		printf("Cant't set rate. \n%s\n", snd_strerror(pcm));
	}

	printf("PCM name: %s\n", snd_pcm_name(pcm_handle));
	printf("PCM state: %s\n", snd_pcm_state_name(snd_pcm_state(pcm_handle)));

	snd_pcm_hw_params_get_channels(params, &tmp);
	printf("channels: %i", tmp);

	if (tmp == 1){
		printf("mono");
	}else if(tmp == 2){
		printf("stereo");
	}
	
	snd_pcm_hw_params_get_rate(params, &tmp, 0);
	printf("rate: %d bps\n", tmp);
	printf("seconds: %d\n", seconds);

	snd_pcm_hw_params_get_period_size(params, &frames, 0);
	buff_size = frames * channels * 2;
	buff = (char*) malloc(buff_size);
	snd_pcm_hw_params_get_period_time(params, &tmp, NULL);
	
	for(loops = (seconds * 1000000) / tmp; loops > 0; loops--) {

		if(pcm = read(file_d, buff, buff_size) == 0){
			printf("early end of file\n");
			return 0;
		}

		if(pcm = snd_pcm_writei(pcm_handle, buff, frames) == -EPIPE){
			printf("XRUN\n");
			snd_pcm_prepare(pcm_handle);
		}else if(pcm < 0){
			printf("ERROR, Can't write to PCM device. %s\n", snd_strerror(pcm));
		}
	}

	snd_pcm_drain(pcm_handle);
	snd_pcm_close(pcm_handle);
	free(buff);

	return 0;
}

int main(){
	printf("hello world!\n");
	play_wav(fle, 22050, 1, 8);	
}
