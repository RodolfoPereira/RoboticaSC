#ifndef UTIL_H
#define UTIL_H

float cos(float ang){ return (Cos(ang)/100.0);}
float sin(float ang){ return (Sin(ang)/100.0);}
float atan2(float ang){
	float resto = ang%360;
	if((resto<180) && (resto>-180))
		return resto;	
	else if(resto>0)
		return resto-360;
	else if(resto<0)
		return resto+360;

	return 0;
}
float pow(float base){
	return base*base;
}

#endif
