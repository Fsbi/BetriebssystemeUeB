#include "Prozess.h"

Prozess::Prozess(unsigned int deadline, unsigned int bereitzeit, unsigned int ausfuerungsZeit)
{
	mDeadline = deadline;
	mBereitZeit = bereitzeit;
	mAusfuehrungsZeit = ausfuerungsZeit;
	mLatenz = deadline - ausfuerungsZeit;
}

Prozess::~Prozess()
{
}

Prozess::Prozess()
{
	mDeadline = 0;
	mBereitZeit = 0;
	mAusfuehrungsZeit = 0;
	mLatenz = 0;
}

unsigned int Prozess::getDeadline()
{
	return mDeadline;
}

unsigned int Prozess::getBereitZeit()
{
	return mBereitZeit;
}

unsigned int Prozess::getAusfuehrungsZeit()
{
	return mAusfuehrungsZeit;
}

unsigned int Prozess::getLatenz()
{
	return mLatenz;
}

void Prozess::setDeadline(unsigned int wert)
{
	mDeadline = wert;
}

void Prozess::setBereitZeit(unsigned int wert)
{
	mBereitZeit = wert;
}

void Prozess::setAusfuehrungsZeit(unsigned int wert)
{
	mAusfuehrungsZeit = wert;
}

void Prozess::aktualLatenz()
{
	mLatenz = mDeadline - mAusfuehrungsZeit;
}
