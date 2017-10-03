/*****************************************************************/
/***MyParticleFilter��****namespace PF*************************/
/***ʹ�ýṹ��Option��ʼ��*************************************/
/***CMyParticleFilter��*****************************************/
/***ͨ�÷���init/tracking****************************************/
/***cancleTrackingȡ������**************************************/
/***drawParticles��ָ��ͼ�л�����*******************************/
/***getConfidence��ȡ���Ŷ�************************************/
/***����parse_command_line�ӿ���̨��������Option***********/
/************************************By Lionel*******************/
/*****************************************************************/
//getOpt������parse_command_line���Ǳ����
#ifndef CMyParticleFilter_H
#define CMyParticleFilter_H
#include "filter.h"
#include "lbp.h"
#include "selector.h"
//#include "state.h"
#include "hist.h"
#include<opencv2\opencv.hpp>
#include<getopt.h>
using namespace cv;
using namespace std;
namespace PF{
typedef unsigned int uint;
//static Param
//static const char* WINDOW  = "Particle Tracker";
static const char*NONE="DONOTUSE";
const Scalar RED = Scalar(0, 0, 255);
const Scalar BLUE = Scalar(255, 0, 0);
const Scalar GREEN = Scalar(0, 255, 0);
const Scalar CYAN = Scalar(255, 255, 0);
const Scalar MAGENTA = Scalar(255, 0, 255);
const Scalar YELLOW = Scalar(0, 255, 255);
const Scalar WHITE = Scalar(255, 255, 255);
const Scalar BLACK = Scalar(0, 0, 0);
const uint NUM_PARTICLES = 200;
//TAG DEFAULT Option
struct Options
{
	Options()
		:num_particles(NUM_PARTICLES),//������Ĭ��Ϊ200
		use_lbp(false),
		infile(),
		outfile()
	{}

	int num_particles;
	bool use_lbp;
	string infile;
	string outfile;
};
//struct StateData;
struct StateData
{
	StateData(int num_particles, bool use_lbp_):
    image(),
	lbp(),
	target(),
	target_histogram(),
	selector(NONE),//setWindowANDMouse,//key
	selection(),
	use_lbp(use_lbp_),
	paused(false),
	draw_particles(false),
	filter(num_particles){};

Mat image;
Mat lbp;
Mat target;
Mat target_histogram;
Selector selector;
Rect selection;
bool use_lbp;
bool paused;
bool draw_particles;
ParticleFilter filter;
};
//Class myParticleFilter
class CMyParticleFilter
{
public:
	CMyParticleFilter(const Options&_option=Options()):
	  m_data(_option.num_particles,_option.use_lbp),m_state(CMyParticleFilter::state_start){lbp_init();};
	~CMyParticleFilter(void);
	void init(const cv::Mat &_frame,const cv::Rect &_trackingWindow);
	void tracking(const cv::Mat &_frame,cv::Rect &_trackingWindow);
	void cancelTracking();
	void drawParticles(bool _bDraw,cv::Mat &_showImage);
	float getConfidence();
private:
	struct State_;
	typedef State_ (*State)(StateData&);
	struct State_
	{
		State_( State pp ) : p( pp ) { }
		operator State() { return p; }
		State p;
	};
	static State_ state_start(StateData& d);
	static State_ state_selecting(StateData& d);
	static State_ state_initializing(StateData& d);
	static State_ state_tracking(StateData& d);
	static void update_target_histogram(Mat& image, Mat& lbp_image, Rect& selection, Mat& histogram, Mat& target, bool use_lbp);
private:
	StateData m_data;
	State m_state;
};
//read_Option_From_command_Line
void parse_command_line(int argc, char** argv, Options& o);
//namespace PF
};
#endif 

