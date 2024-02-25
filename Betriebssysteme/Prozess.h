#pragma once
class Prozess
{
public:
	Prozess(unsigned int deadline, unsigned int bereitzeit, unsigned int ausfuerungsZeit);
	~Prozess();
	Prozess();

	unsigned int getDeadline();
	unsigned int getBereitZeit();
	unsigned int getAusfuehrungsZeit();
	unsigned int getLatenz();
	void setDeadline(unsigned int wert);
	void setBereitZeit(unsigned int wert);
	void setAusfuehrungsZeit(unsigned int wert);
	void aktualLatenz();


private:
	unsigned int mDeadline;
	unsigned int mBereitZeit;
	unsigned int mAusfuehrungsZeit;
	unsigned int mLatenz;
};

