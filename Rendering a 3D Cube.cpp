#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<string.h>

int Width = 160 , Height = 44 ;
int CubeWidth = 20 ;
float zBuffer[160 * 44] ; 
char buffer[160 * 44] ; 
float Alpha , Beta , Theta ;
float x, y ,z ;
int DistanceFromCamera = 100 ;
float ooz ;
int xp , yp ;
int idx ;
int HorizentalOffest ;
float increasment = 0.8 ; 
int k1 = 40 ;
int BackGroundASSCIICode = ' ' ; 

float CalculateX(int i , int j , int k){
    return j * sin(Alpha) * sin(Beta) * cos(Theta) - k * cos(Alpha) * sin(Beta) * cos(Theta) +
           j * cos(Alpha) * sin(Theta) + k * sin(Alpha) * sin(Theta) +
           i * cos(Beta)  * cos(Theta) ; 
}
float CalculateY(int i , int j , int k){
    return j * cos(Alpha) * cos(Theta) + k * sin(Alpha) * cos(Theta) - 
           j * sin(Alpha) * sin(Beta) * sin(Theta) +
           k * cos(Alpha) * sin(Beta) * sin(Theta) - i * cos(Beta) * sin(Theta) ; 
}
float CalculateZ(int i , int j , int k){
    return k * cos(Alpha) * cos(Beta) - j * sin(Alpha) * cos(Beta) + i * sin(Beta) ;  
}

void CalculateSurface(float CubeX , float CubeY , float CubeZ , int ch){
    x = CalculateX(CubeX , CubeY , CubeZ) ;
    y = CalculateY(CubeX , CubeY , CubeZ) ;
    z = CalculateZ(CubeX , CubeY , CubeZ) + DistanceFromCamera ; 

    ooz = 1/z ;
    xp = (int)(Width/2 + HorizentalOffest + ooz * x * 2 * k1) ;
    yp = (int)(Height/2 + ooz * y * k1) ; 

    idx = xp + yp * Width ; 
    if(idx >= 0 && idx < Width * Height){
        if(ooz > zBuffer[idx]){
            zBuffer[idx] = ooz;
            buffer[idx] = ch ; 
        }
    }       
}

int main(){
    printf("\x1b[J") ; 
    while(1){
        memset(buffer , BackGroundASSCIICode , Width * Height) ;
        memset(zBuffer , 0 , Width * Height * 4) ; 

        CubeWidth = 20 ; // render the First Cube
        HorizentalOffest = -2 * CubeWidth ; 
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

        CubeWidth = 10 ; // render the Second Cube
        HorizentalOffest = 1 * CubeWidth ;
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
        for(int k = 0 ; k < Width * Height ; k++){
            putchar(k % Width ? buffer[k] : 10) ; 
        }

        printf("\x1b[H") ; 

        Alpha+= 0.05 ;
        Beta+=0.05   ;
        Theta+=0.01 ;

        usleep(8000) ;  

    }
    
}
