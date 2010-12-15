#include "testApp.h"
float *audio_input = NULL;
float *audio_output = NULL;
float *magnitude, *phase, *power;
std::vector<float> magnitudeVect;
float *magnitude_average, *magnitude_average_snapshot;
float *vlist;
int buffer_size = 1024, fft_size = 512;
fft myfft;

//--------------------------------------------------------------
void testApp::setup(){
	audio_input = new float[buffer_size];
	audio_output = new float[buffer_size];
	magnitude = new float[fft_size];
	phase = new float[fft_size];
	power = new float[fft_size];
	magnitude_average = new float[fft_size];
	magnitude_average_snapshot = new float[fft_size];
	vlist = new float[fft_size];
	for (int i = 0; i < fft_size; i++)
	{
		magnitude[i] = 0;
		phase[i] = 0;
		power[i] = 0;
		magnitude_average_snapshot[i] = 0;
		magnitude_average[i] = 0;
		vlist[i] = 0;
		magnitudeVect.push_back(0);
	}
	
	
	ofSoundStreamSetup(0, 1, this, 44100, buffer_size, 4);	
}

//--------------------------------------------------------------
void testApp::update(){
	for (int i = 0; i < fft_size; i++)
	{
		float x = 0.025;
		magnitude_average[i] = (magnitude[i] * x) + (magnitude_average[i] * (1 - x));
	}
	
	
	
	for (int i = 0; i < fft_size; i++)
	{
		float v = fabs(magnitude_average[i] - magnitude_average_snapshot[i]);
		v *=5;
		vlist[i] = v;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//--------------------------- rectangles
	ofFill();
	for (int i = 0; i < fft_size; i++){
		ofSetColor(255*vlist[i]/7, 120*vlist[i]/7, 80*vlist[i]/7);
		ofRect(252+1*i,450,1,-vlist[i]*10);
	}
	ofSetColor(0x000000);
}
//--------------------------------------------------------------
void testApp::audioReceived(float* input, int bufferSize, int nChannels)
{
	memcpy(audio_input, input, sizeof(float) * bufferSize);
	float avg_power = 0.0f;
	float final = 2550.0f;
	myfft.powerSpectrum(0, (int)fft_size, audio_input, buffer_size, 
						magnitude, phase, power, &avg_power);
	
	for (int i = 0; i < fft_size; i++)
	{
		magnitude[i] = powf(magnitude[i], 0.5);
	}
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

