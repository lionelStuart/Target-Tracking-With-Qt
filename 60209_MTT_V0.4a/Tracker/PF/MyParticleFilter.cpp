#include "MyParticleFilter.h"

namespace PF{

double round(int val){  return (val> 0.0) ? floor(val+ 0.5) : ceil(val- 0.5);}

CMyParticleFilter::~CMyParticleFilter(void)
{
}
void CMyParticleFilter::init(const cv::Mat &_frame,const cv::Rect &_trackingWindow)
{
	_frame.copyTo(m_data.image);
	if(m_data.use_lbp)
	{
		cv::Mat temp;
		cv::cvtColor(m_data.image,temp,CV_BGR2GRAY);
		lbp_from_gray(temp,m_data.lbp);
	}
	else
	{
		if(m_data.lbp.empty())
			m_data.lbp=cv::Mat::zeros(m_data.image.rows,m_data.image.cols,CV_8UC1);
	}
	m_state=state_selecting;
	m_data.selector.setRect(_trackingWindow);
	m_state=m_state(m_data);
}
void CMyParticleFilter::tracking(const cv::Mat &_frame,cv::Rect &_trackingWindow)
{
	_frame.copyTo(m_data.image);
	if(m_data.use_lbp)
	{
		cv::Mat temp;
		cv::cvtColor(m_data.image,temp,CV_BGR2GRAY);
		lbp_from_gray(temp,m_data.lbp);
	}
	else
	{
		if(m_data.lbp.empty())
			m_data.lbp=cv::Mat::zeros(m_data.image.rows,m_data.image.cols,CV_8UC1);
	}
    cv:: Rect bounds(0,0, m_data.image.cols, m_data.image.rows);
	cv::Size target_size=m_data.target.size();
	cv::Mat_<float> target=m_data.filter.state();
	int width = round(target_size.width * target(ParticleFilter::STATE_SCALE));
	int height = round(target_size.height * target(ParticleFilter::STATE_SCALE));
	int x = round(target(ParticleFilter::STATE_X)) - width/2;
	int y = round(target(ParticleFilter::STATE_Y)) - height/2;
	Rect rect = Rect(x, y, width, height) & bounds;
	_trackingWindow=rect;
	m_state=m_state(m_data);
}
void CMyParticleFilter::cancelTracking()
{
	m_state=CMyParticleFilter::state_start;
}
void CMyParticleFilter::drawParticles(bool _bDraw,cv::Mat &_showImage)
{
	m_data.draw_particles=_bDraw;
	cv::Mat target_display_area(m_data.image, Rect(m_data.image.cols - m_data.selection.width, 0, m_data.selection.width, m_data.selection.height));//OnRT
	m_data.target.copyTo(target_display_area);
	_showImage=m_data.image;
}
float CMyParticleFilter::getConfidence()
{
	return m_data.filter.confidence();
}
CMyParticleFilter::State_ CMyParticleFilter:: state_start(StateData& d)
{

	if( d.selector.selecting() )
	{
		cout << "state_selecting" << endl;
		return state_selecting;//1
	}
	else
	{
		return state_start;//2
	}
}
CMyParticleFilter::State_ CMyParticleFilter::state_selecting(StateData& d)
{
	if( d.selector.valid() )
	{
		cout << "state_initializing: (" << d.selection.x << ", " << d.selection.y << ", " << d.selection.width << ", " << d.selection.height  << ")" << endl;
		d.selection = d.selector.selection();
		cout << "selection: (" << d.selection.x << ", " << d.selection.y << ", " << d.selection.width << ", " << d.selection.height  << ")" << endl;
		return state_initializing(d); // Call with current frame
	}
	else
	{
		Mat roi(d.image, d.selector.selection());
		bitwise_not(roi, roi);
		return state_selecting;//3
	}
}
CMyParticleFilter::State_ CMyParticleFilter::state_initializing(StateData& d)
{
	if( d.selector.selecting() )
	{
		cout << "state_selecting" << endl;
		return state_selecting;//4
	}

	// Generate initial target histogram//更新固定的目标模板
	update_target_histogram(d.image, d.lbp, d.selection, d.target_histogram, d.target, d.use_lbp);

	// Initialize condensation filter with center of selection
	d.filter.init(d.selection);

	// Start video running if paused
	d.paused = false;

	cout << "state_tracking" << endl;
	return state_tracking(d); // Call with current frame
}

CMyParticleFilter::State_ CMyParticleFilter::state_tracking(StateData& d)
{
	if( d.selector.selecting() )
	{
		cout << "state_selecting" << endl;
		return state_selecting;//5
	}

	// Update particle filter
	d.filter.update(d.image, d.lbp, d.selection.size(), d.target_histogram, d.use_lbp);

	Size target_size(d.target.cols, d.target.rows);

	// Draw particles
	if( d.draw_particles )
		d.filter.draw_particles(d.image, target_size, WHITE);

	// Draw estimated state with color based on confidence
	float confidence = d.filter.confidence();

	// TODO - Make these values not arbitrary
	if( confidence > 0.1 )
	{
		d.filter.draw_estimated_state(d.image, target_size, GREEN);
	}
	else if( confidence > 0.025 )
	{
		d.filter.draw_estimated_state(d.image, target_size, YELLOW);
	}
	else
	{
		d.filter.draw_estimated_state(d.image, target_size, RED);
	}

	return state_tracking;//6
}

 void CMyParticleFilter:: update_target_histogram(Mat& image, Mat& lbp_image, Rect& selection, Mat& histogram, Mat& target, bool use_lbp)
{
	Mat roi(image, selection), lbp_roi(lbp_image, selection);
	roi.copyTo(target);
	Mat new_hist;
	float alpha = 0.2;

	calc_hist(roi, lbp_roi, new_hist, use_lbp);
	normalize(new_hist, new_hist);

	if(histogram.empty())
	{
		histogram = new_hist;
	}
	else
	{
		// TODO - support for adaptive updates not fully implemented.
		histogram = ((1.f - alpha) * histogram) + (alpha * new_hist);
		normalize(histogram, histogram);
	}
	cout << "Target updated" << endl;
}
void parse_command_line(int argc, char** argv, Options& o)
{
	int c = -1;
	while( (c = getopt(argc, argv, "lo:p:")) != -1 )
	{
		switch(c)
		{
		case 'l':
			o.use_lbp = true;
			break;
		case 'o':
			o.outfile = optarg;
			break;
		case 'p':
			o.num_particles = atoi(optarg);
			break;
		default:
			cerr << "Usage: " << argv[0] << " [-o output_file] [-p num_particles] [-l] [input_file]" << endl << endl;
			cerr << "\t-o output_file : Optional mjpeg output file" << endl;
			cerr << "\t-p num_particles: Number of particles (samples) to use, default is 200" << endl;
			cerr << "\t-l: Use local binary patterns in histogram" << endl;
			cerr << "\tinput_file : Optional file to read, otherwise use camera" << endl;
			exit(1);
		}
	}

	if( optind < argc )
	{
		o.infile = argv[optind];
	}

	cout << "Num particles: " << o.num_particles << endl;
	cout << "Input file: " << o.infile << endl;
	cout << "Output file: " << o.outfile << endl;
	cout << "Use LBP: " << o.use_lbp << endl;

}
//namespace PF
}
