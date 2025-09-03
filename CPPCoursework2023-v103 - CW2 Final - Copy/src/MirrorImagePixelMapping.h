#pragma once
#include "header.h"
#include "DrawingSurface.h"
#include "ImagePixelMapping.h"


//Modified version of ImagePixelMappingShiftXY
class MirrorImagePixelMapping :
	public ImagePixelMappingShiftXY
{
public:
	MirrorImagePixelMapping(double x, double y, bool flip)
		: ImagePixelMappingShiftXY(x,y)
	{
		isFlipped = flip;
		
	};

	//same as in original, but with check for isFlipped
	bool mapCoordinates(double& x, double& y, const SimpleImage& image) override
	{
		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;

		//Make sprite face other direction
		if (isFlipped) {
			x = 64 - x - 1;
		}
		
		if (!ImagePixelMappingShiftXY::mapCoordinates(x, y, image)) {
			return false;
		}

		return true;
	}

	bool changePixelColour(int x, int y, int& colour, DrawingSurface* pTarget) override
	{
		if (colour == 0x000000) {
			return false;
		}

		return true;
	}

	void setFlipped(bool flip) {
		isFlipped = flip;
	}

private:
	bool isFlipped;

};


//Rotate and shift for animated projectiles
class RotateAndShiftXYImagePixelMapping :
	public ImagePixelMappingRotate
{
public:
	RotateAndShiftXYImagePixelMapping(double x, double y, double r)
		: ImagePixelMappingRotate(r)
	{
		shift= new ImagePixelMappingShiftXY(x, y);
	};

	~RotateAndShiftXYImagePixelMapping() {
		delete shift;
	}

	//Shift to the correct sprite, then rotate
	bool mapCoordinates(double& x, double& y, const SimpleImage& image) override
	{
		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;

		//Shift the sprite
		if (!shift->mapCoordinates(x, y, image)) {
			return false;
		}

		
		// Shift offset to the centre of the image, so we can rotate around centre
		x -= centreX;
		y -= centreY;

		// Rotate it
		double dAngle = atan(y / (x + 0.0001));
		if (x < 0)
			dAngle += M_PI;
		double hyp = ::sqrt(x * x + y * y);
		dAngle += (double)rotation;

		x = hyp * ::cos(dAngle);
		y = hyp * ::sin(dAngle);

		// Shift offset back to the corner
		x += centreX;
		y += centreY;

		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;
		
		return true;
		
	}

	bool changePixelColour(int x, int y, int& colour, DrawingSurface* pTarget) override
	{
		if (colour == 0x000000) {
			return false;
		}

		return true;
	}

	void setShifts(double x, double y) {
		shift->setXShift(x);
		shift->setYShift(y);
	}

	void setCentres(double x, double y) {
		centreX = x +32;
		centreY = y +32;
	}


private:
	ImagePixelMappingShiftXY* shift;
	double centreX = 0;
	double centreY = 0;


};

