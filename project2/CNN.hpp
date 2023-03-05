#pragma once
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct conv_param
{
        int pad;
        int stride;
        int kernel_size;
        int in_channels;
        int out_channels;
        float *p_weight;
        float *p_bias;
} conv_param;

typedef struct fc_param
{
        int in_features;
        int out_features;
        float *p_weight;
        float *p_bias;
} fc_param;

class CNN
{
public:
        static void read_start(string s);
        static Mat reshape(Mat &img);
        static float *bgr2rgb(Mat &img);
        static float *Conv_RELU(int rows, int cols, float *intput, conv_param &conv_params);
        static float *pooling(int channel, int cols, int rows, float *input);
};