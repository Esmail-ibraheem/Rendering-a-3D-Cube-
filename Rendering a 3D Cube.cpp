#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

int ScreenWidth = 160 , ScreenHeight = 44 ;
float zBuffer[160 * 44] ;
char buffer[160 * 44] ;
int CubeWidth = 20 ;
float Alpha , Beta , Theta ;
float x , y ,z ;
int DistanceFromCamera = 100 ;
int DistanceFromScreen = 44 ;
float ooz ;
int xp , yp ;
int idx ;
int HorizentalOffest ;
float increasment = 0.6; 
int BackGroundAssciiCode = ' ' ;

float CalculateX(int i , int j , int k){
    return j * sin(Alpha) * sin(Beta) * cos(Theta) - k * cos(Alpha) * sin(Beta) * cos(Theta) +
           j * cos(Alpha) * sin(Theta) + k * sin(Alpha) * sin(Theta) +
           i * cos(Beta)  * cos(Theta) ; 
}

float CalculateY(int i , int j , int k){
    return j * cos(Alpha) * cos(Theta) + k * sin(Alpha) * cos(Theta) - 
           j * sin(Alpha) * sin(Beta) * sin(Theta) +
           k * cos(Alpha) * sin(Beta) * sin(Theta) - i * cos(Beta) * sin(Theta)  ;
}

float CalculateZ(int i , int j , int k){
    return  k * cos(Alpha) * cos(Beta) - j * sin(Alpha) * cos(Beta) + i * sin(Beta) ; 
}

void CalculateSurface(float CubeX , float CubeY , float CubeZ , int chr){
    x = CalculateX(CubeX , CubeY , CubeZ) ;
    y = CalculateY(CubeX , CubeY , CubeZ) ;
    z = CalculateZ(CubeX , CubeY , CubeZ) + DistanceFromCamera ;

    ooz = 1/z ;
    xp = (int)(ScreenWidth/2 + HorizentalOffest + ooz * x * 2 * DistanceFromScreen) ; 
    yp = (int)(ScreenHeight/2 + ooz * y * DistanceFromScreen) ;

    idx = xp + yp * ScreenWidth ;

    if(idx >=0 && idx < ScreenWidth * ScreenHeight){
        if(ooz > zBuffer[idx]){
            zBuffer[idx] = ooz ;
            buffer[idx] = chr ; 
        }
    }
}

int main(){
    printf("\x1b[J") ;
    while(1){
        memset(buffer , BackGroundAssciiCode , ScreenWidth * ScreenHeight) ;
        memset(zBuffer , 0 , ScreenWidth * ScreenHeight * 4) ; 

        CubeWidth = 20 ; // render the First Cube
        HorizentalOffest = -2 * CubeWidth ;
        for(float CubeX = -CubeWidth ; CubeX < CubeWidth ; CubeX+=increasment){
            for(float CubeY = -CubeWidth ; CubeY < CubeWidth ; CubeY+=increasment){
                CalculateSurface(CubeX , CubeY , -CubeWidth , '1');
                CalculateSurface(CubeWidth , CubeY , CubeX , '0') ;
                CalculateSurface(-CubeWidth , CubeY , -CubeX , '1') ; 
                CalculateSurface(-CubeX , CubeY , CubeWidth , '0') ; 
                CalculateSurface(CubeX , -CubeWidth , -CubeY , '1') ; 
                CalculateSurface(CubeX , CubeWidth , CubeY , '0') ;  
            }
        }

        CubeWidth = 10 ; // render the Second Cube 
        HorizentalOffest = 1 * CubeWidth ;
        for(float CubeX = -CubeWidth ; CubeX < CubeWidth ; CubeX+=increasment){
            for(float CubeY = -CubeWidth ; CubeY < CubeWidth ; CubeY+=increasment){
                CalculateSurface(CubeX , CubeY , -CubeWidth , '1');
                CalculateSurface(CubeWidth , CubeY , CubeX , '0') ;
                CalculateSurface(-CubeWidth , CubeY , -CubeX , '1') ; 
                CalculateSurface(-CubeX , CubeY , CubeWidth , '0') ; 
                CalculateSurface(CubeX , -CubeWidth , -CubeY , '1') ; 
                CalculateSurface(CubeX , CubeWidth , CubeY , '0') ;  
            }
        }

        CubeWidth = 7 ; // render the Third Cube
        HorizentalOffest = 5 * CubeWidth ;
        for(float CubeX = -CubeWidth ; CubeX < CubeWidth ; CubeX+=increasment){
            for(float CubeY = -CubeWidth ; CubeY < CubeWidth ; CubeY+=increasment){
                CalculateSurface(CubeX , CubeY , -CubeWidth , '1') ;
                CalculateSurface(CubeWidth , CubeY , CubeX , '0') ; 
                CalculateSurface(-CubeWidth , CubeY , -CubeX , '1') ; 
                CalculateSurface(-CubeX , CubeY , CubeWidth , '0') ;
                CalculateSurface(CubeX , -CubeWidth , -CubeY , '1') ; 
                CalculateSurface(CubeX , CubeWidth , CubeY , '0') ; 

            }
        }

        CubeWidth = 5 ; // render the last Cube
        HorizentalOffest = 12 * CubeWidth ;
        for(float CubeX = -CubeWidth ; CubeX < CubeWidth ; CubeX+=increasment){
            for(float CubeY = -CubeWidth ; CubeY < CubeWidth ; CubeY+=increasment){
                CalculateSurface(CubeX , CubeY , -CubeWidth , '1') ;
                CalculateSurface(CubeWidth , CubeY , CubeX , '0') ; 
                CalculateSurface(-CubeWidth , CubeY , -CubeX , '1') ; 
                CalculateSurface(-CubeX , CubeY , CubeWidth , '0') ;
                CalculateSurface(CubeX , -CubeWidth , -CubeY , '1') ; 
                CalculateSurface(CubeX , CubeWidth , CubeY , '0') ; 

            }
        }

        for(int k = 0 ; k < ScreenWidth * ScreenHeight ; k++){
            putchar(k % ScreenWidth ? buffer[k] : 10) ;
        }

        printf("\x1b[H") ;
        Alpha+=0.05 ;
        Beta+=0.05 ;
        Theta+=0.01 ;

        usleep(8000) ;  
    }
}
