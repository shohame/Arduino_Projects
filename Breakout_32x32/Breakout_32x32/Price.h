#ifndef __PRICE_H
#define __PRICE_H

#define PRICE_DEFAULT_WIDTH		3
#define	PRICE_DEFAULT_HEIGHT	4
#define	PRICE_DEFAULT_SPEED		3		// 3 Pixel / Sec

#define	PRICE_TYPE_COUNT		5		

enum ePriceType 
{
	eLarge	= 10,
	eSmall,
	eThree,
	eBall,
	eFire
};

class Price : public MovingBrick

{
public:
	ePriceType m_eType;

	Price(void);
	~Price(void);
	void Init();
	void Init(int8 a_x, int8 a_y, ePriceType a_Type);

	void MarkBrickOnMatrix();


};




#endif	//	#ifndef __PRICE_H


