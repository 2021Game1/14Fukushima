#ifndef CMATRIX_H
#define CMATRIX_H

/*
}gNXNX
4s4ñÌsñf[^ðµ¢Ü·
*/

class CMatrix{
public:
	//\¦mFp
	//4~4ÌsñðæÊoÍ
	void Print();
	//ftHgRXgN^
	CMatrix();
	//PÊsñÌì¬
	CMatrix Identity();
	//sñlÌæ¾
	//M(s,ñ)
	float M(int r, int c)const;
	//gåk¬sñÌì¬
	//Scale({¦X,{¦Y,{¦Z)
	CMatrix Scale(float sx, float sy, float sz);
	//ñ]sñ(X²)Ìì¬
	//RotateX(px)
	CMatrix RotateX(float degree);
	//ñ]sñiY²jÌì¬
	//RotateY(px)
	CMatrix RotateY(float degree);
	//ñ]sñ(Z²)Ìì¬
	//RotateZ(px)
	CMatrix RotateZ(float degree);
private:
	//4~4Ìsñf[^ÌÝè
	float mM[4][4];
	

};
#endif

