

class CVIn
{
public:
	int m_index
		, m_width
		, m_height
		, m_fourcc
		, m_widthSet
		, m_heightSet;

	CVIn(int index);
	~CVIn();
	int getX(int i);
	int getY(int i);
	void close();
	bool grabFrame();
	bool isOpened() const;
	void open(int index);
	bool retrieveFrame(int, unsigned char* frame);

};
